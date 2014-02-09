package com.pacman.game;

/**
 * This class implements the chase pattern of Inky, the blue ghost.
 * His chase target depends on blinky and pacman's position.
 * 
 * @author Thaer
 *
 */
public class InkyGhost extends Ghost {
	private static final Vector2I	homePos		= new Vector2I(World.NUM_COLS - 1, World.NUM_ROWS - 4);
	private static final int		startDelay	= 0;

	/**
	 * Creates an Inky Ghost
	 * 
	 * @param position
	 * @param speed
	 * @param height
	 * @param width
	 * @param startPos
	 */
	public InkyGhost(Vector2I position, int speed, int height, int width, Vector2I startPos) {
		super(position, speed, height, width, homePos, startPos, startDelay);
	}

	private final int	TARGET_OFFSET	= 2;

	//Inky's target in chase mode is computed using blinky's current position and the space 2 tiles in front of pacman
	protected void setChaseTarget(Direction pacDir, Vector2I pacPos, Vector2I blinkyPos) {
		Vector2I intermediate = null;

		switch (pacDir) {
		case RIGHT:
			intermediate = new Vector2I(pacPos.x + TARGET_OFFSET, pacPos.y);
		break;
		case LEFT:
			intermediate = new Vector2I(pacPos.x - TARGET_OFFSET, pacPos.y);
		break;
		case UP:
			intermediate = new Vector2I(pacPos.x, pacPos.y + TARGET_OFFSET);
		break;
		case DOWN:
			intermediate = new Vector2I(pacPos.x, pacPos.y - TARGET_OFFSET);
		break;
		default:
		break;
		}

		chaseTarget.set(blinkyPos.add(intermediate.sub(blinkyPos).mul(2)));
	}
}
