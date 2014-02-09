package com.pacman.game;

/**
 * This class will represent a single tile on the Maze.
 * 
 * @author Thaer
 *
 */
public class Tile {
	/**
	 * These are the different types of tiles we can have.
	 * @author Thaer
	 *
	 */
	public enum Type {
		FREE, WALL, DOT, ENERGIZER, DOOR, INVISIBLE_WALL
	};

	private Type	type;

	/**
	 * Changes the type of the tile
	 * 
	 * @param state
	 */
	public void setType(Type state) {
		this.type = state;
	}

	/**
	 * Gets the type of the tile
	 * @return
	 */
	public Type getType() {
		return type;
	}

	/**
	 * Each tile has an id that corresponds to its type.
	 * This makes parsing a text file holding tile information a lot easier.
	 * @param tileString The tile id.
	 */
	public Tile(char tileString) {
		switch (tileString) {
		case '0':
			setType(Type.FREE);
		break;
		case '1':
			setType(Type.WALL);
		break;
		case '2':
			setType(Type.DOT);
		break;
		case '3':
			setType(Type.ENERGIZER);
		break;
		case '4':
			setType(Type.DOOR);
		break;
		case '5':
			setType(Type.INVISIBLE_WALL);
		break;
		}
	}

	/**
	 * Checks if a tile is of a certain type
	 * @param type
	 * @return
	 */
	public boolean is(Type type) {
		return this.type == type;
	}

	/**
	 * Checks if a tile is considered blocked so a movable object can't pass through it.
	 * @return
	 */
	public boolean isBlocked() {
		return is(Type.INVISIBLE_WALL) || is(Type.WALL) || is(Type.DOOR);
	}
}
