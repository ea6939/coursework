package com.pacman.game;

import java.util.Map;

/**
 * This class holds all the information specific to a certain level, such as the maze layout and the speeds of the objects. 
 * This enables to easily define different levels.
 * This class also increases the score when pacman eats different objects.
 * 
 * @author Thaer
 *
 */
public class Level {
	private final int				MAX_NUMBER_DOTS	= 244;

	private Maze					maze;
	private int						dotsEaten		= 0;
	private final int				levelNum;
	private int						score			= 0;
	private boolean					gameOver		= false;
	private final double			ghostSpeed;
	private final int				pacmanSpeed;

	//this holds all starting positions of pacman and the ghosts mapped to the ID of an object 
	//(P pacman, B Blinky, C clyde, I inky, K Pinky) 
	private Map<String, Vector2I>	positionMap;

	/**
	 * 
	 * @param levelNum The number of level starting at 1.
	 * @param currentLevelTiles Tiles that make up the maze.
	 * @param ghostSpeed
	 * @param pacmanSpeed
	 * @param positionMap Starting positions of ghosts and pacman.
	 */
	public Level(int levelNum, Tile[][] currentLevelTiles, double ghostSpeed, int pacmanSpeed, Map<String, Vector2I> positionMap) {
		this.levelNum = levelNum;
		this.ghostSpeed = ghostSpeed;
		this.pacmanSpeed = pacmanSpeed;
		this.positionMap = positionMap;
		this.maze = new Maze(currentLevelTiles);
	}

	/**
	 * Gets the score
	 * @return
	 */
	public int getScore() {
		return score;
	}

	/**
	 * Sets the score
	 * @return
	 */
	public void setScore(int score) {
		this.score = score;
	}

	/**
	 * Gets the level maze
	 * @return
	 */
	public Maze getMaze() {
		return maze;
	}

	/**
	 * Gets dots eaten
	 * @return
	 */
	public int getDotsEaten() {
		return dotsEaten;
	}

	/**
	 * Sets dots eaten
	 * @return
	 */
	public void setDotsEaten(int dotsEaten) {
		this.dotsEaten = dotsEaten;
	}

	/**
	 * Gets the level number
	 * @return
	 */
	public int getLevelNum() {
		return levelNum;
	}

	/**
	 * Gets the ghost speed
	 * @return
	 */
	public double getGhostSpeed() {
		return ghostSpeed;
	}

	/**
	 * Gets pacmans speed
	 * @return
	 */
	public int getPacmanSpeed() {
		return pacmanSpeed;
	}

	/**
	 * Gets the starting positions of all ghosts and pacman
	 * @return
	 */
	public Map<String, Vector2I> getPositions() {
		return positionMap;
	}

	/**
	 * This is true when pacman has eaten all the dots
	 * 
	 * @return
	 */
	public boolean isGameOver() {
		return gameOver;
	}

	private void increaseDotsEaten() {
		setDotsEaten(getDotsEaten() + 1);
		if (getDotsEaten() == MAX_NUMBER_DOTS) {
			gameOver = true;
		}
	}

	/**
	 * Called when pacman eats a dot, increases the score
	 */
	public void eatDot() {
		setScore(getScore() + 10);
		increaseDotsEaten();
	}

	/**
	 * Called when pacman eats an energizer, increases the score
	 */
	public void eatEnergizer() {
		setScore(getScore() + 50);
		increaseDotsEaten();
	}

	/**
	 * Calls when ghost eats a ghost, increases the score
	 */
	public void eatGhost() {
		setScore(getScore() + 500);
	}

}
