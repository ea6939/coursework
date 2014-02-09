/**
 * Full Management for all users. Does almost all logic and database access and management 
 * 
 * @author Chris
 */
package com.pacman.playermanagement;

import java.util.ArrayList;
import java.util.Iterator;

import com.pacman.filehandling.FileHandling;

public class ProfileManager {

	//  Username, Password, high_score (HS), (Deaths), 2games_played (GP), dots_eaten(Dots), (Ghosts), (Wins), (Level), Time, WinRatio (%), Set3, Set4;
	//	private String pro;
	private static int			proNumb;
	private static String[]		currentPro		= new String[11];								//profile line broken down into each element
	private final static String	profileDataPath	= "res/profiles.txt";

	static ArrayList<String>	profiles		= FileHandling.loadTextFile(profileDataPath);

	/** Checks if username supplied exists, if so pulls data.
	 * 
	 * @param user				Supplied username
	 * @return					returns true if user exists.
	 */
	public static boolean findUser(String user) {
		proNumb = 0;
		Iterator<String> itr = profiles.iterator();
		while (itr.hasNext()) {
			splitString(itr.next());
			if (user.equalsIgnoreCase(currentPro[0])) {
				return true;
			}
			proNumb++; //use later when printing
		}
		return false;
	}

	/** Checks password against username
	 * 
	 * @param pass				Supplied Password
	 * @return					returns True if password is correct
	 */
	public static boolean checkPass(String pass) {
		if (pass.equals(currentPro[1])) {
			return true;
		} else {
			return false;
		}
	}

	/** Returns name of User for database
	 * 
	 * @param return value
	 */
	public static String getUser() {
		return currentPro[0];
	}

	/** Changes password
	 * 
	 * @param newPass			New value of password
	 */
	public static void changePass(String newPass) {
		currentPro[1] = newPass;
	}

	/** Returns value of HighScore from database
	 * 
	 * @param return value
	 */
	public static String getHighScore() {
		return currentPro[2];
	}

	/** Sets value of Highscore from database
	 * 
	 * @param return value
	 */
	public static void setHighScore(String highScore) {
		currentPro[2] = highScore;
	}

	/** Returns value of Deaths from database
	 * 
	 * @param return value
	 */
	public static String getDeaths() {
		return currentPro[3];
	}

	/** Sets value of Death from database
	 * 
	 * @param return value
	 */
	public static void setDeaths(String temp) {
		currentPro[3] = temp;
	}

	/** Returns value of Games Played from database
	 * 
	 * @param return value
	 */
	public static String getGamesPlayed() {
		return currentPro[4];
	}

	/** Sets value of Games Played from database
	 * 
	 * @param return value
	 */
	public static void setGamesPlayed(String temp) {
		currentPro[4] = temp;
	}

	/** Returns value of Dots from database
	 * 
	 * @param return value
	 */
	public static String getDots() {
		return currentPro[5];
	}

	/** Sets value of Dots from database
	 * 
	 * @param return value
	 */
	public static void setDots(String temp) {
		currentPro[5] = temp;
	}

	/** Returns value of Ghosts Killed from database
	 * 
	 * @param return value
	 */
	public static String getGhosts() {
		return currentPro[6];
	}

	/** Sets value of Ghosts from database
	 * 
	 * @param return value
	 */
	public static void setGhosts(String temp) {
		currentPro[6] = temp;
	}

	/** Returns value of Wins from database
	 * 
	 * @param return value
	 */
	public static String getWins() {
		return currentPro[7];
	}

	/** Sets value of Wins for database
	 * 
	 * @param return value
	 */
	public static void setWins(String temp) {
		currentPro[7] = temp;
	}

	/** Returns value of Level from database
	 * 
	 * @param return value
	 */
	public static String getLevel() {
		return currentPro[8];
	}

	/** Sets value of Level for database
	 * 
	 * @param return value
	 */
	public static void setLevel(String temp) {
		currentPro[8] = temp;
	}

	/** Returns value of Time played from database
	 * 
	 * @param return value
	 */
	public static String getTime() {
		return currentPro[9];
	}

	/** Sets value of Time from database
	 * 
	 * @param return value
	 */
	public static void setTime(String temp) {
		currentPro[9] = temp;
	}

	/** Sets value of Time/Death from database
	 * 
	 * @param return value
	 */
	public static String getTimeDeathRatio() {
		return currentPro[10];
	}

	/** Sets value of Time/Death from database
	 * 
	 * @param return value
	 */
	public static void setTimeDeathRatio(String temp) {
		currentPro[10] = temp;
	}

	/** Creates New User into database
	 * 
	 * @param username			New user's value for User name
	 * @param password 			New user's value for password
	 */
	public static void createNewUser(String username, String password) {
		if (!findUser(username)) {
			currentPro[0] = username;
			currentPro[1] = password;
			for (int x = 2; x < 11; x++) {
				currentPro[x] = "0";
			}
			currentPro[8] = "1";
			profiles.add(combString(currentPro));
			printProfile();
		}
	}

	/** Combines String Array to longstring
	 * 
	 * @param array					String Array with username, password, data...
	 * @return						combines array into one string
	 */
	public static String combString(String[] array) {
		String temps = "";
		for (int i = 0; i < array.length - 1; i++) {
			temps += array[i] + ", ";
		}
		temps += array[array.length - 1] + ";";
		return temps;
	}

	/** Splits the long string with user name, password, data's into array separating each
	 * 
	 * @param longString				one line of data from database
	 */
	public static void splitString(String longString) {
		char c = longString.charAt(0);
		int x = 0;
		String temp = "";
		for (int i = 0; i < longString.length(); i++) {
			c = longString.charAt(i);
			if (c == ',' || c == ';') {
				currentPro[x] = temp;
				temp = "";
				x++;
				i++; //for the space after ";_"
			} else {
				temp += c;
			}
		}
	}

	/** Updates Profile in memory
	 * 
	 */
	public static void updateProfile() {
		profiles.set(proNumb, combString(currentPro));
	}

	/** Prints updated profile's to database
	 * 
	 */
	public static void printProfile() {
		FileHandling.printTextFile(profileDataPath, profiles);
	}

	/** Returns currentPro
	 * 
	 * @return currentPro
	 */
	public static String[] getCurrentPro() {
		return currentPro;
	}

}
