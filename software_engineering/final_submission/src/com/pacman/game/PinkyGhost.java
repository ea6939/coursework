package com.pacman.game;

/**
 * 
 * This class implements the chase pattern of Pinky, the pink ghost.
 * He always chases the space 2 tiles in front of pacman.
 * 
 * @author Thaer
 *
 */
public class PinkyGhost extends Ghost {
	private final int				TARGET_OFFSET	= 4;
	private static final Vector2I	homePos			= new Vector2I(2, 0);
	private static final int		startDelay		= 4;

	/**
	 * Constructs a Pinky ghost
	 * 
	 * @param position
	 * @param speed
	 * @param height
	 * @param width
	 * @param startPos
	 */
	public PinkyGhost(Vector2I position, int speed, int height, int width, Vector2I startPos) {
		super(position, speed, height, width, homePos, startPos, startDelay);
	}

	//pinky's target is 2 tiles in front of pacman
	protected void setChaseTarget(Direction pacDir, Vector2I pacPos, Vector2I blinkyPos) {
		switch (pacDir) {
		case RIGHT:
			chaseTarget.set(pacPos.x + TARGET_OFFSET, pacPos.y);
		break;
		case LEFT:
			chaseTarget.set(pacPos.x - TARGET_OFFSET, pacPos.y);
		break;
		case UP:
			chaseTarget.set(pacPos.x, pacPos.y + TARGET_OFFSET);
		break;
		case DOWN:
			chaseTarget.set(pacPos.x, pacPos.y - TARGET_OFFSET);
		break;
		default:
		break;
		}
	}
}
