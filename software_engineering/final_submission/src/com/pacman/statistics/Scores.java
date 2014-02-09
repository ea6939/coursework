/** Implementation of Statistics of Pacman game, stores value from gameplay and applys them to player accounts.
 *  @author Ze Yu, Yang
 * 
 */
package com.pacman.statistics;

import com.pacman.playermanagement.ProfileManager;

public class Scores {

	private int	highestScore;

	/**constructor of Scores item, takes string value of highscore from playermanagement.
	 * 
	 * 
	 */

	public Scores() {

		this.highestScore = Integer.parseInt(ProfileManager.getHighScore());

	}

	/** Clear method for highscore
	 * 
	 */
	// used in stats screen
	public void clearHighestScore() {

		this.highestScore = 0;

	}

	/** Setter for new high score
	 * 
	 * @param endGameScore
	 */
	public void setHighestScore(int endGameScore) {

		highestScore = endGameScore;

	}

	/**Checks at the endgame if the score is higher than the high score stored in playerManagement class.
	 * 
	 * @param endgamescore
	 * @return
	 */

	public boolean checkHighestScore(int endgamescore) {

		boolean isHighScore = false;

		if (endgamescore > highestScore) ;
		isHighScore = true;

		return isHighScore;

	}

	/** Store the highest score as a string value, back to playerManagement.
	 * 
	 */

	public void updateToProfileManager() {

		ProfileManager.setHighScore("" + highestScore);

		ProfileManager.updateProfile();

		ProfileManager.printProfile();

	}

}
