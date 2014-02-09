package com.pacman.game;

/**
 * This class implements the chase pattern of Clyde, the orange ghost. 
 * He runs to his home position when pacman is too close, other wise he chases pacman.
 * 
 * @author Thaer
 *
 */
public class ClydeGhost extends Ghost {
	private static final Vector2I	homePos		= new Vector2I(0, World.NUM_ROWS - 4);
	private static final int		startDelay	= 4;

	/**
	 * Creates a Clyde Ghost
	 * 
	 * @param position
	 * @param speed
	 * @param height
	 * @param width
	 * @param startPos
	 */
	public ClydeGhost(Vector2I position, int speed, int height, int width, Vector2I startPos) {
		super(position, speed, height, width, homePos, startPos, startDelay);
	}

	private final int	THRESHOLD_DISTANCE	= 8;

	//clydes target in chase mode is pacman if pacman is farther than THRESHOLD_DISTANCE tiles, otherwise his target is his home position
	protected void setChaseTarget(Direction pacDir, Vector2I pacPos, Vector2I blinkyPos) {
		float distToPacman = tilePos().dist(pacPos);
		if (distToPacman < THRESHOLD_DISTANCE) {
			chaseTarget.set(homePos);
		} else {
			chaseTarget.set(pacPos);
		}
	}

}
