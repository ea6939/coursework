package com.pacman.rendering;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;

import com.pacman.game.Ghost;
import com.pacman.game.MovableObject.Direction;
import com.pacman.game.Tile;
import com.pacman.game.Vector2;
import com.pacman.game.World;
import com.pacman.game.World.GameState;
import com.pacman.main.Assets;
import com.pacman.main.Game;
import com.pacman.settings.Settings;

/**
 * this screen will be used to render gameplay and handle events
 * @author Thaer
 *
 */
@SuppressWarnings("serial")
public class GameScreen extends Screen {
	int					wTile;
	int					hTile;
	World				world;

	Color[]				ghostColors			= new Color[] { Color.RED, Color.CYAN, Color.PINK, Color.ORANGE };
	final Color			FRIGHTENED_COLOR	= new Color(66, 115, 252);
	final Color			DYING_COLOR			= new Color(255, 255, 255, 50);
	final Color			DOOR_COLOR			= new Color(255, 127, 0, 85);
	final Color			PACMAN_COLOR;
	final Color			MAZE_COLOR;

	private final Font	stringFont			= new Font("comic sans ms", Font.BOLD, 22);
	private final Font	pauseMessageFont	= new Font("comic sans ms", Font.BOLD, 12);
	private float		totalTime			= 0;

	/**
	 * Creates a new game screen
	 * 
	 * @param game
	 * @param startingLevel level at which to start the game
	 */
	public GameScreen(Game game, int startingLevel) {
		super(game);

		wTile = width / World.NUM_COLS;
		hTile = height / World.NUM_ROWS;

		//reload level data so we start with unmodified levels
		Assets.loadLevels();
		//creates a new world at a starting level
		world = new World(width, height, Assets.getLevels(), game.getUser(), startingLevel);

		//get the pacman color from the settings class
		PACMAN_COLOR = Settings.getPacmanColor();
		MAZE_COLOR = Settings.getMazeColor();
	}

	/**
	 * Creates a new gamescreen at starting level 0
	 * 
	 * @param game
	 */
	public GameScreen(Game game) {
		super(game);

		wTile = width / World.NUM_COLS;
		hTile = height / World.NUM_ROWS;

		//reload level data so we start with unmodified levels
		Assets.loadLevels();
		world = new World(width, height, Assets.getLevels(), game.getUser());

		//get the pacman color from the settings class
		PACMAN_COLOR = Settings.getPacmanColor();
		MAZE_COLOR = Settings.getMazeColor();
	}

	/**
	 * Renders all game elements
	 */
	protected void render(Graphics2D g2d) {
		drawTiles(g2d);

		drawPacman(g2d);

		drawGhosts(g2d);

		drawHUD(g2d);
	}

	//draws information such as score and number of lives remaining
	private void drawHUD(Graphics2D g2d) {
		//draws lives
		g2d.setColor(PACMAN_COLOR);
		for (int i = 0; i < world.getPacman().getLives(); i++) {
			g2d.fillOval((int) (world.wTile * (i + 1) * 1.5), world.hTile * (World.NUM_ROWS - 4), world.wTile, world.hTile);
		}

		//draws get ready! graphic
		g2d.setColor(Color.white);
		g2d.setFont(stringFont);
		if (world.getState() == GameState.WAITING) g2d.drawString("GET READY!", world.wTile * (World.NUM_COLS / 2 - 4), world.hTile * (World.NUM_ROWS / 2 + 1));

		//draws pause message and graphic (if paused)
		g2d.setColor(Color.white);
		g2d.setFont(pauseMessageFont);
		g2d.drawString("P: pause Q: quit", 10, pauseMessageFont.getSize());
		g2d.setFont(stringFont);
		if (world.getState() == GameState.PAUSED) g2d.drawString("  PAUSED", world.wTile * (World.NUM_COLS / 2 - 4), world.hTile * (World.NUM_ROWS / 2 + 1));
		//draws score
		g2d.drawString("SCORE: " + Integer.toString(world.level.getScore()), (3 * world.wTile) / 2, world.hTile * (World.NUM_ROWS - 1));
		//draws level number
		g2d.drawString("LEVEL: " + Integer.toString(world.level.getLevelNum()), World.NUM_COLS * (int) (world.wTile * 0.75), world.hTile * (World.NUM_ROWS - 1));
	}

	private void drawGhosts(Graphics2D g2d) {
		int len = world.ghosts.length;
		for (int i = 0; i < len; i++) {
			Ghost g = world.ghosts[i];
			if (g.isFrightened()) {
				g2d.setColor(FRIGHTENED_COLOR);
			} else if (g.getState() == Ghost.GhostState.DYING) {
				g2d.setColor(DYING_COLOR);
			} else {
				g2d.setColor(ghostColors[i]);
			}

			Vector2 ghostPos = g.getPos();
			g2d.fillOval((int) ghostPos.x, (int) ghostPos.y, world.wTile, world.hTile);

			// draws mouth
			g2d.setColor(Color.black);
			g2d.fillOval((int) ghostPos.x + wTile / 2 - 3 + Direction.directionToVector(world.ghosts[i].getDir()).x * 5, (int) ghostPos.y + wTile / 2 - 3 + Direction.directionToVector(world.ghosts[i].getDir()).y * 5, 6, 6);
		}
	}

	private void drawPacman(Graphics2D g2d) {
		//draws pacman
		g2d.setColor(PACMAN_COLOR);
		Vector2 pacPos = world.getPacman().getPos();
		g2d.fillOval((int) pacPos.x, (int) pacPos.y, world.wTile, world.hTile);

		// draws mouth
		g2d.setColor(Color.black);
		g2d.fillOval((int) pacPos.x + wTile / 2 - 3 + Direction.directionToVector(world.getPacman().getDir()).x * 5, (int) pacPos.y + wTile / 2 - 3 + Direction.directionToVector(world.getPacman().getDir()).y * 5, 6, 6);
	}

	private void drawTiles(Graphics2D g2d) {
		// draws tiles
		Tile[][] tiles = world.getTiles();
		int numRows = tiles.length;
		int numCols = tiles[0].length;

		for (int y = 0; y < numRows; y++) {
			for (int x = 0; x < numCols; x++) {
				Tile current = tiles[y][x];
				switch (current.getType()) {
				case DOT:
					g2d.setColor(Color.WHITE);
					int dotW = wTile / 4 + 1;
					int dotH = hTile / 4 + 1;
					g2d.fillOval(x * wTile + dotW, y * hTile + dotH, dotW, dotH);
				break;
				case WALL:
					g2d.setColor(MAZE_COLOR);
					g2d.fillRect(x * wTile, y * hTile, wTile, hTile);
				break;
				case ENERGIZER:
					g2d.setColor(Color.WHITE);
					//adds makes the energizers blink for half a second every 3 seconds
					if ((int) (totalTime / 0.5) % 3 != 0) {
						g2d.fillOval(x * wTile, y * hTile, wTile, hTile);
					}
				break;
				case DOOR:
					g2d.setColor(DOOR_COLOR);
					g2d.fillRect(x * wTile, y * hTile, wTile, hTile);
				break;
				case INVISIBLE_WALL:
				case FREE:
				default:
				break;
				}
			}
		}
	}

	/**
	 * Updates the world logic if needed
	 * 
	 */
	protected void update(float deltaTime) {
		switch (world.getState()) {
		//don't do anything when world is paused
		case PAUSED:
		break;
		case LOST:
			changeScreen(new GameOverScreen(game, world.level.getScore(), world.level.getLevelNum(), "GAME OVER"));
		break;
		case WON:
			changeScreen(new GameOverScreen(game, world.level.getScore(), world.level.getLevelNum(), "GOOD JOB!"));
		break;
		default:
			totalTime += deltaTime;
			world.update(deltaTime);
		}
	}

	@Override
	protected void keyRelease(KeyEvent e) {}

	@Override
	/**
	 * handles keyboard events and passes them to world instance
	 */
	protected void keyPress(KeyEvent e) {
		switch (e.getKeyCode()) {
		case (KeyEvent.VK_UP):
			world.tryMovePacman(Direction.UP);
		break;
		case (KeyEvent.VK_DOWN):
			world.tryMovePacman(Direction.DOWN);
		break;
		case (KeyEvent.VK_RIGHT):
			world.tryMovePacman(Direction.RIGHT);
		break;
		case (KeyEvent.VK_LEFT):
			world.tryMovePacman(Direction.LEFT);
		break;
		case (KeyEvent.VK_ENTER):
		case (KeyEvent.VK_P):
			world.togglePause();
		break;
		case (KeyEvent.VK_Q):
			world.endGame(GameState.LOST);
		break;
		}

	}
}