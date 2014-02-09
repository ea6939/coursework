/** This class takes care of all in-game statistics 
 * @author ZeyU YANG
 * 
 */
package com.pacman.statistics;

import com.pacman.playermanagement.ProfileManager;

public class Statistics {

	private int		currentLevel, gamesPlayed, wins, deaths, dotsEaten, ghostBeaten, highScore;
	private float	totalGameTime;
	private float	timeDeathRatio;
	public String	currentUser	= "Guest";

	/** Constructor of Statistics Item. Taking user name from playerManagement class
	 * 
	 * @param user
	 */
	public Statistics(String user) {

		this.currentUser = user;
		ProfileManager.findUser(user);
		this.highScore = Integer.parseInt(ProfileManager.getHighScore());
		this.deaths = Integer.parseInt(ProfileManager.getDeaths());
		this.gamesPlayed = Integer.parseInt(ProfileManager.getGamesPlayed());
		this.dotsEaten = Integer.parseInt(ProfileManager.getDots());
		this.ghostBeaten = Integer.parseInt(ProfileManager.getGhosts());
		this.wins = Integer.parseInt(ProfileManager.getWins());
		this.currentLevel = 0;
		this.totalGameTime = Float.parseFloat(ProfileManager.getTime());
		this.timeDeathRatio = 0;

		/**updates the highscore.
		 * 
		 * 
		 */
	}

	public void updateHighScore(int newScore) {
		if (newScore > this.highScore) {
			this.highScore = newScore;
		}

	}

	/**getter for current level
	 * 
	 * 
	 * @return
	 */

	public int getCurrentLevel() {

		return currentLevel;

	}

	/**Goes to the next level when the previous level is completed 
	 * 
	 * 
	 */
	public void updateCurrentLevel() {

		currentLevel = currentLevel + 1;
	}

	/**setter for level
	 * 
	 * 
	 * @param level
	 */
	public void setCurrentLevel(int level) {

		currentLevel = level;
	}

	/**Updates death value after death of pacman
	 * 
	 * 
	 */
	public void updateDeath() {

		this.deaths = deaths + 1;

	}

	/**updates the number of game played
	 * 
	 */

	public void updateGamesPlayed() {

		gamesPlayed = gamesPlayed + 1;
	}

	/**updates the death value
	 * 
	 */

	public void updateDotEaten() {

		dotsEaten = dotsEaten + 1;
	}

	/**updates the ghost killed
	 * 
	 */

	public void updateGhostBeaten() {

		this.ghostBeaten = ghostBeaten + 1;

	}

	/** updates the win game number
	 * 
	 * 
	 */

	public void updateWins() {

		this.wins = wins + 1;

	}

	/** calculates the skill level
	 * 
	 */
	public void setTimeDeathRatio() {

		if (gamesPlayed == 0) {

			timeDeathRatio = 0;
		}

		else {

			timeDeathRatio = (totalGameTime / deaths);
		}

	}

	/**Converts the game time.
	 * @param totalGameTime
	 * @return
	 */
	public int convertTime(float totalGameTime) {

		return (int) totalGameTime;

	}

	/**counts the total game time of one account
	 * 
	 * @param gameTime
	 */

	public void updateTime(float gameTime) {

		totalGameTime = totalGameTime + convertTime(gameTime);

	}

	/**updates all statistic values to player profile
	 * 
	 */
	public void updateToProfile() {

		if (!currentUser.equals("Guest")) {

			ProfileManager.setDeaths("" + deaths);
			ProfileManager.setHighScore("" + highScore);

			ProfileManager.setDots("" + dotsEaten);

			ProfileManager.setGamesPlayed("" + gamesPlayed);

			ProfileManager.setGhosts("" + ghostBeaten);
			if (currentLevel > Integer.parseInt(ProfileManager.getLevel())) {
				ProfileManager.setLevel("" + currentLevel);
			}
			ProfileManager.setWins("" + wins);
			ProfileManager.setTime("" + totalGameTime);
			setTimeDeathRatio();
			ProfileManager.setTimeDeathRatio("" + timeDeathRatio);

			ProfileManager.updateProfile();
			ProfileManager.printProfile();
		}
	}

}