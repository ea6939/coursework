package com.pacman.main;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import com.pacman.filehandling.FileHandling;
import com.pacman.game.Level;
import com.pacman.game.Tile;
import com.pacman.game.Vector2I;
import com.pacman.game.World;

/**
 * this class is used to load any assets such as images or data
 * 
 * @author Thaer
 *
 */
public class Assets {
	private final static String	levelDataPath	= "res/leveldata.txt";
	static ArrayList<Level>		levels;

	/**
	 * parse the level data from a text file
	 * and stores it into an array of levels
	 *  
	 */
	public static void loadLevels() {
		ArrayList<String> levelData = FileHandling.loadTextFile(levelDataPath);
		levels = new ArrayList<Level>();

		//start at level 1
		int currentLevelNum = 1;
		Tile[][] currentLevelTiles = new Tile[World.NUM_ROWS][World.NUM_COLS];
		int currentRow = 0;
		int currentCol = 0;
		double ghostSpeed = 0;
		int pacmanSpeed = 0;
		Map<String, Vector2I> positionMap = new HashMap<String, Vector2I>();

		for (String line : levelData) {
			//ignore blank lies
			if (line.length() == 0) continue;

			switch (line.charAt(0)) {
			//# marks the beginning of a comment, ignore it
			case '#':
			break;
			case 'S':
				pacmanSpeed = Integer.parseInt(line.substring(2, line.length()));
			break;
			case 'G':
				ghostSpeed = Double.parseDouble(line.substring(2, line.length()));
			break;
			case 'E':
				//all the data for that level has been parsed, created the Level object
				levels.add(new Level(currentLevelNum, currentLevelTiles, ghostSpeed, pacmanSpeed, positionMap));
				currentLevelNum++;
				currentLevelTiles = new Tile[World.NUM_ROWS][World.NUM_COLS];
				positionMap = new HashMap<String, Vector2I>();
				currentRow = 0;
				currentCol = 0;
			break;
			default:
				//places the tile data in the correct place in the array
				String[] row = line.split(" ");
				for (String tileString : row) {
					char c = tileString.charAt(0);
					if (tileString.matches("[a-zA-Z]")) {
						positionMap.put(c + "", new Vector2I(currentRow, currentCol));
						//creates a free tile
						currentLevelTiles[currentCol][currentRow] = new Tile('0');
					} else {
						currentLevelTiles[currentCol][currentRow] = new Tile(c);
					}
					currentRow++;
				}
				currentCol++;
				currentRow = 0;
			break;
			}
		}
	}

	/**
	 * return the array of levels
	 * 
	 * @return
	 */
	public static ArrayList<Level> getLevels() {
		return levels;
	}

}
