package com.pacman.game;

import com.pacman.game.MovableObject.Direction;
import com.pacman.game.Tile.Type;

/**
 * This is the Maze class that holds all the tiles of the maze.
 * Each tile can have a different type such as WALL or Dot.
 * 
 * @author Thaer
 *
 */
public class Maze {
	Tile[][]	tiles;

	public Maze(Tile[][] tiles) {
		this.tiles = tiles;
	}

	/**
	 * Returns the requested tile if it is within range, otherwise returns null
	 * Integer tile positions. (0,0) is top-left, (10,5) would be 10 tiles to the right and 5 tiles down.
	 *  
	 * @param x 
	 * @param y
	 * @return
	 */
	public Tile getTile(int x, int y) {
		if (y < 0 || y >= tiles.length || x < 0 || x >= tiles[0].length) return null;

		//the coordinates are flipped because of the way the array is indexed
		return tiles[y][x];
	}

	/**
	 * Checks if the tile is blocked. 
	 * 
	 * @param x x position of tile
	 * @param y y position of tile
	 * @param dir Takes in the movable objects direction since objects are allowed to pass through doors when they come from underneath.
	 * @return
	 */
	public boolean isBlocked(int x, int y, Direction dir) {
		Tile t = getTile(x, y);

		//if the tile is out of range its considered as not blocked
		if (t == null) return false;

		//stops movable objects from passing through the top of the door
		if (dir != Direction.DOWN && t.is(Type.DOOR)) {
			return false;
		} else {
			return t.isBlocked();
		}
	}

	/**
	 * Gets the maze tiles
	 * @return
	 */
	public Tile[][] getTiles() {
		return tiles;
	}
}
