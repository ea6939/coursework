package com.pacman.game;

/**
 * This implements the Pacman class. 
 * The main difference from the ghosts is that the user can control Pacman.
 * 
 * @author Thaer
 *
 */
public class Pacman extends MovableObject {
	private int	lives	= 3;

	public Pacman(Vector2I position, int speed, int height, int width) {
		super(position, speed, height, width);
	}

	/**
	 * Keeps trying to change direction to "tryDir"
	 * This is so that the user can try to make pacman go right, and if there are walls to his right he will keep trying to turn right.
	 * This provides for snappier gameplay since the user can press a direction before pacman gets to an opening.
	 * 
	 * @param maze The maze layout so pacman can check for walls
	 */
	private void tryChangeDirection(Maze maze) {
		if (atGoal())
			setDir(getTryDir());
		//pacman can always reverse direction 
		else if (getTryDir() == Direction.RIGHT && getDir() == Direction.LEFT || getTryDir() == Direction.LEFT && getDir() == Direction.RIGHT || getTryDir() == Direction.UP && getDir() == Direction.DOWN || getTryDir() == Direction.DOWN && getDir() == Direction.UP) {
			setDir(getTryDir());
			//turn the corner only if the next tile is not blocked and pacman is aligned closely enough with the grid to be able to change directions
		} else if (distToClipped() < LEEWAY && !isNextBlocked(getTryDir(), maze)) {
			setDir(getTryDir());
		}
	}

	//update pacman movement
	protected void update(float deltaTime, Maze m) {
		tryChangeDirection(m);
		updateGoal(m);
		if (!atGoal()) moveToGoal(deltaTime);
	}

	/**
	 * Gets the number of remaining lives
	 * 
	 * @return
	 */
	public int getLives() {
		return lives;
	}

	/**
	 * Makes pacman lose a life
	 */
	public void loseLife() {
		lives--;
	}

	/**
	 * Resets pacman to his starting position
	 */
	public void init() {
		super.initPosition();
	}
}
