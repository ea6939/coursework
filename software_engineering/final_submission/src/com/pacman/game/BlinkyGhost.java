package com.pacman.game;

/**
 * This class implements the chase pattern of Blinky, the red ghost. He chases pacman as closely as possible.
 * 
 * @author Thaer 
 *
 */

public class BlinkyGhost extends Ghost {
	private static final Vector2I	homePos		= new Vector2I(World.NUM_COLS - 3, 0);
	private static final int		startDelay	= 0;

	/**
	 * Creates a blinky ghost
	 * 
	 * @param position
	 * @param speed
	 * @param height
	 * @param width
	 * @param startPos
	 */
	public BlinkyGhost(Vector2I position, int speed, int height, int width, Vector2I startPos) {
		super(position, speed, height, width, homePos, startPos, startDelay);
	}

	//blinky's target in chase mode is pacman's current position
	protected void setChaseTarget(Direction pacDir, Vector2I pacPos, Vector2I blinkyPos) {
		chaseTarget.set(pacPos);
	}

}
