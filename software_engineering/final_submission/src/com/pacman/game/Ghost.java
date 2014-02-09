package com.pacman.game;

import java.util.ArrayList;
import java.util.Random;

/**
 * This abstract class implements all the different states of a ghost.
 * It also handles all the transitions between states and the different behaviours and movement patterns of a ghost depending on each ghost.
 * A ghost has a chase target which is the tile it is actively trying to reach. 
 * This must be implemented by inheritance, and is the only way that the 4 ghosts differ in behavior.
 * 
 * @author Thaer
 *
 */
public abstract class Ghost extends MovableObject {
	/**
	 * The state of a Ghost. Behaves differently depending on state.
	 * @author Thaer
	 *
	 */
	public enum GhostState {
		SCATTER, FRIGHTENED, CHASE, HEADING_TO_START, DYING, WAITING
	};

	Random				rng;
	//this is a ghosts home position, it is off the map and it is a tile the ghost tries to reach when it is in scatter mode
	private Vector2I	homePos;
	// this is the target the ghosts are chasing
	protected Vector2I	chaseTarget;
	//this is the ghosts starting position, where it returns to after being killed in order to revive
	protected Vector2I	startPos;
	private GhostState	state;
	//time spent in each state
	private float		stateTime			= 0;
	//time to wait inside the cage before moving
	private final float	WAIT_DURATION;
	private final float	SCATTER_DURATION	= 7;
	private final float	FRIGHTEN_DURATION	= 5;

	/**
	 * Creates a new ghost.
	 * 
	 * @param position
	 * @param speed
	 * @param height
	 * @param width
	 * @param homePos
	 * @param startPos
	 * @param waitDuration
	 */
	public Ghost(Vector2I position, int speed, int height, int width, Vector2I homePos, Vector2I startPos, int waitDuration) {
		super(position, speed, height, width);

		this.homePos = homePos;
		this.startPos = startPos;
		WAIT_DURATION = waitDuration;
		rng = new Random();

		init();
	}

	/**
	 * Initializes the ghosts position and sets the ghost to waiting mode. Also resets the chase target.
	 */
	public void init() {
		super.initPosition();
		changeState(GhostState.WAITING);
		chaseTarget = homePos.cpy();
	}

	// looks ahead to the next tile and checks which tiles are available for the ghost to go to 
	private Vector2I[] getUpcomingSurroundingTiles() {
		//gets the tile position of the tile that the ghost is moving to
		Vector2I nextTile = new Vector2I((int) (getGoal().x / getWidth()), (int) (getGoal().y / getHeight()));

		//vectors representing all possible positions
		Vector2I upVec = nextTile.cpy().add(Direction.directionToVector(Direction.UP));
		Vector2I leftVec = nextTile.cpy().add(Direction.directionToVector(Direction.LEFT));
		Vector2I downVec = nextTile.cpy().add(Direction.directionToVector(Direction.DOWN));
		Vector2I rightVec = nextTile.cpy().add(Direction.directionToVector(Direction.RIGHT));

		//the tiles to which the ghost can go
		Vector2I[] surroundVecs = null;
		// going backwards is not a valid  so we must exclude that from the possible tile in which the ghost can go to
		switch (getDir()) {
		case DOWN:
			surroundVecs = new Vector2I[] { leftVec, downVec, rightVec };
		break;
		case LEFT:
			surroundVecs = new Vector2I[] { upVec, leftVec, downVec };
		break;
		case RIGHT:
			surroundVecs = new Vector2I[] { upVec, downVec, rightVec };
		break;
		case UP:
			surroundVecs = new Vector2I[] { upVec, leftVec, rightVec };
		break;
		default:
		break;
		}
		return surroundVecs;

	}

	// picks a random direction for the ghost to go during frightened mode
	private void computeRandomDirection(Maze maze) {
		Vector2I[] surroundings = getUpcomingSurroundingTiles();
		ArrayList<Vector2I> availableTiles = new ArrayList<Vector2I>();

		//only keeps the tiles that are not blocked
		for (Vector2I tile : surroundings) {
			if (!maze.isBlocked(tile.x, tile.y, getTryDir())) availableTiles.add(tile);
		}

		// chooses random tile to go to
		Vector2I chosenTile = availableTiles.get(rng.nextInt(availableTiles.size()));
		Vector2I nextTile = new Vector2I((int) (getGoal().x / getWidth()), (int) (getGoal().y / getHeight()));
		if (chosenTile != null) {
			//computes the direction to the chosen tile and tries to turn in that direction
			Vector2I directionVector = new Vector2I(chosenTile.x - nextTile.x, nextTile.y - chosenTile.y);
			Direction newDirection = Direction.vectorToDirection(directionVector);
			if (newDirection != Direction.NONE) setTryDir(newDirection);
		}
	}

	//finds the tile that the ghost can move to that is the closest to the chase target
	private void computeDirection(Maze maze) {
		Vector2I[] surroundings = getUpcomingSurroundingTiles();

		Vector2I chosenTile = null;
		float smallestDistanceToTarget = -1;

		for (Vector2I tile : surroundings) {
			if (maze.isBlocked(tile.x, tile.y, getTryDir())) continue;
			float distance = tile.dist(chaseTarget);
			//keeps the tile that is the closest to the chase target
			if (chosenTile == null || distance < smallestDistanceToTarget) {
				smallestDistanceToTarget = distance;
				chosenTile = tile;
			}
		}

		//tries to turn in the direction of that tile
		if (chosenTile != null) {
			Vector2I nextTile = new Vector2I((int) (getGoal().x / getWidth()), (int) (getGoal().y / getHeight()));
			Vector2I directionVector = new Vector2I(chosenTile.x - nextTile.x, chosenTile.y - nextTile.y);
			setTryDir(Direction.vectorToDirection(directionVector));
		}

	}

	protected void tryChangeDirection(Maze maze) {
		// ghosts can only change direction once they are fully on a tile and
		// not mid-way between a tile
		if (atGoal()) setDir(getTryDir());
	}

	/**
	 * Sets the ghost in frightened (running away) mode
	 */
	public void frighten() {
		if (getState() == GhostState.CHASE || getState() == GhostState.SCATTER || getState() == GhostState.FRIGHTENED) {
			changeState(GhostState.FRIGHTENED);
		}
	}

	/**
	 * Checks if the ghost is in frightened mode
	 * @return
	 */
	public boolean isFrightened() {
		return getState() == GhostState.FRIGHTENED;
	}

	/**
	 * kills the ghost (called when it is eaten by pacman)
	 */
	public void die() {
		changeState(GhostState.DYING);
	}

	/**
	 * Changes the ghost state and resets the stateTime
	 * @param state
	 */
	public void changeState(GhostState state) {
		this.state = state;
		stateTime = 0;
	}

	/**
	 * Gets the ghost state
	 * 
	 * @return
	 */
	public GhostState getState() {
		return state;
	}

	/**
	 * Updates the ghost movement based on the maze and the ghost's current state
	 * 
	 * @param deltaTime time elapsed between each frame
	 * @param maze 
	 * @param pacDir direction of pacman
	 * @param pacPos pacman's position
	 * @param blinkyPos blinky's position
	 */
	public void update(float deltaTime, Maze maze, Direction pacDir, Vector2I pacPos, Vector2I blinkyPos) {
		stateTime += deltaTime;

		switch (getState()) {
		//keeps waiting for a specified time then heads to the starting position
		case WAITING:
			if (stateTime > WAIT_DURATION) {
				changeState(GhostState.HEADING_TO_START);
			}
			return;
			//heads to the start position. If the ghost is dead it revives upon reaching the start position and is put into scatter mode
		case HEADING_TO_START:
		case DYING:
			chaseTarget.set(startPos);
			computeDirection(maze);
			if (tilePos().equals(startPos)) {
				changeState(GhostState.SCATTER);
			}
		break;
		//computes the chase target and chases it
		case CHASE:
			setChaseTarget(pacDir, pacPos, blinkyPos);
			computeDirection(maze);
		break;
		//tries to get to the home position
		case SCATTER:
			chaseTarget.set(homePos);
			computeDirection(maze);
			if (stateTime > SCATTER_DURATION) {
				changeState(GhostState.CHASE);
			}
		break;
		//moves randomly about the maze
		case FRIGHTENED:
			computeRandomDirection(maze);
			if (stateTime > FRIGHTEN_DURATION) {
				changeState(GhostState.CHASE);
			}
		break;
		default:
		break;
		}
		//try to change in the desired direction
		tryChangeDirection(maze);
		// ghosts cannot change goals mid-tile so we have to wait to fully reach
		// a tile before trying to move to another one
		if (atGoal()) updateGoal(maze);
		//moves towards its goal
		moveToGoal(deltaTime);
	}

	// this method needs to be implemented, each ghost much change his current
	// target based on the given information
	protected abstract void setChaseTarget(Direction pacDir, Vector2I pacPos, Vector2I blinkyPos);

}
