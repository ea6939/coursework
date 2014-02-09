package com.pacman.game;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Map;

import com.pacman.game.Ghost.GhostState;
import com.pacman.game.MovableObject.Direction;
import com.pacman.statistics.Statistics;

/**
 * The world class. Holds all the game elements such as pacman, ghosts and maze.
 * Handles all the interactions between game elements and their movement.
 * 
 * @author Thaer
 *
 */
public class World {
	/**
	 * State of the game
	 * 
	 * @author Thaer
	 *
	 */
	public enum GameState {
		WAITING, RUNNING, PAUSED, WON, LOST
	};

	private GameState					state;
	private float						stateTime	= 0;

	//dimension of the maze
	public static final int				NUM_ROWS	= 36;
	public static final int				NUM_COLS	= 28;

	//dimensions of a tile
	public final int					wTile;
	public final int					hTile;

	//width and height of a world in pixels
	int									width;
	int									height;

	private float						totalTime	= 0;
	//WAIT_TIME is how long to display the "Get ready" screen before starting the game
	private final int					WAIT_TIME	= 2;

	//starts at level 0
	ArrayList<Level>					levels;
	public Level						level;

	public Ghost[]						ghosts;
	private Pacman						pacman;
	private ArrayList<MovableObject>	movableObjects;

	//instance to keep track of statistics
	private Statistics					stats;

	/**
	 * creates new world starting from the first level
	 * 
	 * @param width
	 * @param height
	 * @param levels
	 * @param user
	 */
	public World(int width, int height, ArrayList<Level> levels, String user) {
		this.width = width;
		this.height = height;
		wTile = width / NUM_COLS;
		hTile = height / NUM_ROWS;

		this.levels = levels;
		//gets first level
		level = levels.get(0);

		stats = new Statistics(user);
		//initializes world
		initialize();
	}

	/**
	 * Creates new world starting from a specific level
	 * 
	 * @param width
	 * @param height
	 * @param levels
	 * @param user
	 * @param startingLevel
	 */
	public World(int width, int height, ArrayList<Level> levels, String user, int startingLevel) {
		this.width = width;
		this.height = height;
		wTile = width / NUM_COLS;
		hTile = height / NUM_ROWS;

		this.levels = levels;
		level = levels.get(startingLevel);

		stats = new Statistics(user);
		initialize();
	}

	//initializes all the objects and their speed and position based on the information in the level
	private void initialize() {
		int pacmanSpeed = level.getPacmanSpeed();
		int ghostSpeed = (int) (level.getGhostSpeed() * pacmanSpeed);
		Map<String, Vector2I> positionMap = level.getPositions();

		pacman = new Pacman(positionMap.get("P"), pacmanSpeed, wTile, hTile);
		Vector2I startPos = positionMap.get("S");

		//creates the new ghost
		ghosts = new Ghost[] { new BlinkyGhost(positionMap.get("B"), ghostSpeed, wTile, hTile, startPos), new InkyGhost(positionMap.get("I"), ghostSpeed, wTile, hTile, startPos), new PinkyGhost(positionMap.get("K"), ghostSpeed, wTile, hTile, startPos), new ClydeGhost(positionMap.get("C"), ghostSpeed, wTile, hTile, startPos) };

		movableObjects = new ArrayList<MovableObject>();
		movableObjects.add(pacman);
		movableObjects.addAll(Arrays.asList(ghosts));
		stateTime = 0;
		state = GameState.WAITING;
	}

	//reset all the movable objects position
	private void reset() {
		pacman.init();
		for (Ghost g : ghosts) {
			g.init();
		}

		state = GameState.WAITING;
		stateTime = 0;
	}

	//move on to the next level
	private void increaseLevel() {
		if (level.getLevelNum() >= levels.size()) {
			endGame(GameState.WON);
		} else {
			//gets the next level (array is 0 indexed so no need to increment)
			Level nextLevel = levels.get(level.getLevelNum());
			nextLevel.setScore(level.getScore());
			level = nextLevel;
			reset();
		}
	}

	/**
	 * attempt to have pacman move in a direction, method used to have the player control pacman
	 * @param d
	 */
	public void tryMovePacman(Direction d) {
		pacman.setTryDir(d);
	}

	/**
	 * updates the positions of all movable objects and checks for collisions
	 * @param deltaTime
	 */
	public void update(float deltaTime) {
		totalTime += deltaTime;
		stateTime += deltaTime;

		if (state == GameState.WAITING) {
			if (stateTime > WAIT_TIME) state = GameState.RUNNING;
		}
		//if we are done waiting for the round to begin then update the positions
		else {
			Maze maze = level.getMaze();
			pacman.update(deltaTime, maze);
			for (Ghost ghost : ghosts)
				ghost.update(deltaTime, maze, pacman.getDir(), pacman.tilePos(), ghosts[0].tilePos());
			checkCollision();
		}

	}

	//checks the collisions between all game elements
	private void checkCollision() {
		checkOutOfMapCollisions();

		checkDotCollisions();

		if (level.isGameOver()) {
			stats.updateCurrentLevel();
			increaseLevel();
		}

		checkGhostCollisions();
	}

	//checks if pacman collides with any ghosts
	private void checkGhostCollisions() {
		for (Ghost ghost : ghosts) {
			if (pacman.tilePos().equals(ghost.tilePos())) {
				if (ghost.isFrightened()) {
					stats.updateGhostBeaten();
					ghost.die();
					level.eatGhost();
				} else if (ghost.getState() != GhostState.DYING) {
					stats.updateDeath();
					pacman.loseLife();
					if (pacman.getLives() == 0) {
						endGame(GameState.LOST);
					} else {
						reset();
					}
				}
			}
		}
	}

	//check for collisions with static game elements
	private void checkDotCollisions() {
		Vector2I tilePos = pacman.tilePos();
		Tile currentTile = level.getMaze().getTile(tilePos.x, tilePos.y);
		if (currentTile.is(Tile.Type.DOT)) {
			currentTile.setType(Tile.Type.FREE);
			stats.updateDotEaten();
			level.eatDot();
		} else if (currentTile.is(Tile.Type.ENERGIZER)) {
			currentTile.setType(Tile.Type.FREE);
			level.eatEnergizer();
			for (Ghost ghost : ghosts) {
				ghost.frighten();
			}
		}
	}

	//checks if any objects has gone outside of the map so they can teleport back
	private void checkOutOfMapCollisions() {
		int xBound = -wTile / 2;
		int yBound = -hTile / 2;

		for (MovableObject object : movableObjects) {
			//current tile position
			Vector2 objectPos = object.getPos();

			//if pacman or the ghosts is go out of bounds, loop around the map
			if (objectPos.x <= xBound) {
				object.getPos().set(objectPos.x + NUM_COLS * wTile, objectPos.y);
				object.getGoal().set(object.getPos());
			} else if (objectPos.x >= NUM_COLS * wTile + xBound) {
				object.getPos().set(objectPos.x - NUM_COLS * wTile, objectPos.y);
				object.getGoal().set(object.getPos());
			} else if (objectPos.y <= yBound) {
				object.getPos().set(objectPos.x, objectPos.y + NUM_ROWS * hTile);
				object.getGoal().set(object.getPos());
			} else if (objectPos.y >= NUM_ROWS * hTile + yBound) {
				object.getPos().set(objectPos.x, objectPos.y - NUM_ROWS * hTile);
				object.getGoal().set(object.getPos());
			}
		}
	}

	/**
	 * Ends the game 
	 * @param state Whether the game has been won or list
	 */
	public void endGame(GameState state) {
		this.state = state;
		if (state == GameState.WON) {
			stats.updateWins();
		}

		//updates all the stats
		stats.updateHighScore(level.getScore());
		stats.updateTime(totalTime);
		stats.updateGamesPlayed();
		stats.updateToProfile();
	}

	/**
	 * Toggles the game pause
	 * 
	 */
	public void togglePause() {
		if (state == GameState.PAUSED) {
			state = GameState.RUNNING;
		} else if (state == GameState.RUNNING) {
			state = GameState.PAUSED;
		}
	}

	/**
	 * Gets the tiles of the maze
	 * 
	 * @return
	 */
	public Tile[][] getTiles() {
		return level.getMaze().getTiles();
	}

	/**
	 * Gets the game state
	 * 
	 * @return
	 */
	public GameState getState() {
		return state;
	}

	/**
	 * Sets the game state
	 * 
	 * @param state
	 */
	public void setState(GameState state) {
		this.state = state;
	}

	/**
	 * Gets pacman
	 * @return
	 */
	public Pacman getPacman() {
		return pacman;
	}
}