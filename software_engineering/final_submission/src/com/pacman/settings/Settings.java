/**Simple implementation of Settings in Pacman game, contains all setter and getter methods, takes values from input and set the values to World class.
 * @author Ze Yu, Yang
 */

package com.pacman.settings;

import java.awt.Color;

public class Settings {

	static Color	pacmanColor	= Color.yellow;
	static Color	mazeColor	= Color.blue;
	static int		volume		= 0;

	/** Returns the Volume value for Pacman, however the sound is not implement in current version yet. 
	 * 
	 * 
	 * @return
	 */
	public static int getVolume() {
		return volume;
	}

	/** Setter for volume.
	 * 
	 * 
	 * @param vol
	 */

	public static void setVolume(int vol) {
		volume = vol;
	}

	/** Getter for Pacman color
	 * 
	 * 
	 * @return
	 */

	public static Color getPacmanColor() {
		return pacmanColor;
	}

	/**Setter for Pacman Color
	 * 
	 * 
	 * @param color
	 */

	public static void setPacmanColor(Color color) {
		pacmanColor = color;
	}

	/**Getter for Maze color
	 * 
	 * @return
	 */

	public static Color getMazeColor() {
		return mazeColor;
	}

	/**Setter for Maze Color
	 * 
	 * 
	 * @param color
	 */

	public static void setMazeColor(Color color) {
		mazeColor = color;
		System.out.println(mazeColor);
	}

}
