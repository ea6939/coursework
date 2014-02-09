/** Screen for Profile 
 * 
 * @author Chris Peng
 * 
 */
package com.pacman.rendering;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.*;

import com.pacman.main.Game;
import com.pacman.playermanagement.ProfileManager;
import com.pacman.rendering.Screen;

@SuppressWarnings("serial")
public class ProfileScreen extends Screen implements ActionListener {
	//	final JTextField text1, text2;
	JLabel		user, hS, deaths, gP, dots, ghosts, wins, level, set1, set2, set3, set4, temp;
	JButton		SUBMIT;
	JPanel		panel;
	JTextField	text1;

	double		xpos	= 10;
	double		ypos	= 10;
	int			xspeed	= 1;																	//pixels per second
	int			yspeed	= 10;

	/** Sets up Profile Screen layout
	 * 
	 * @param game takes in game for record keeping
	 */
	public ProfileScreen(Game game) {
		super(game);
		setLayout(new GridBagLayout());
		setBackground(Color.LIGHT_GRAY);

		GridBagConstraints c = new GridBagConstraints();

		c.fill = GridBagConstraints.HORIZONTAL;
		c.ipady = 15;
		c.insets = new Insets(5, 5, 5, 5);
		c.weightx = .5;

		c.gridx = 0;
		c.gridy = 0;
		add(new JLabel("Username: "), c);

		user = new JLabel(ProfileManager.getUser());

		c.weightx = 0.5;
		c.gridx = 1;
		c.gridy = 0;
		add(user, c);

		//password

		c.gridx = 0;
		c.gridy = 1;
		add(new JLabel("Password: "), c);

		JButton changePW = new JButton("Change Password");

		c.gridx = 1;
		c.gridy = 1;
		add(changePW, c);

		//HS

		c.gridx = 0;
		c.gridy = 2;
		add(new JLabel("High Score: "), c);

		hS = new JLabel(ProfileManager.getHighScore());

		c.gridx = 1;
		c.gridy = 2;
		add(hS, c);

		//Deaths

		c.gridx = 0;
		c.gridy = 3;
		add(new JLabel("Deaths: "), c);

		temp = new JLabel(ProfileManager.getDeaths());

		c.gridx = 1;
		c.gridy = 3;
		add(temp, c);

		//Games Played

		c.gridx = 0;
		c.gridy = 4;
		add(new JLabel("Games Played: "), c);

		temp = new JLabel(ProfileManager.getGamesPlayed());

		c.gridx = 1;
		c.gridy = 4;
		add(temp, c);

		//Dots

		c.gridx = 0;
		c.gridy = 5;
		add(new JLabel("Dots Collected: "), c);

		temp = new JLabel(ProfileManager.getDots());

		c.gridx = 1;
		c.gridy = 5;
		add(temp, c);

		//Ghosts

		c.gridx = 0;
		c.gridy = 6;
		add(new JLabel("Ghosts Killed: "), c);

		temp = new JLabel(ProfileManager.getGhosts());

		c.gridx = 1;
		c.gridy = 6;
		add(temp, c);

		//Wins

		c.gridx = 0;
		c.gridy = 7;
		add(new JLabel("Games Won: "), c);

		temp = new JLabel(ProfileManager.getWins());

		c.gridx = 1;
		c.gridy = 7;
		add(temp, c);

		//Level

		c.gridx = 0;
		c.gridy = 8;
		add(new JLabel("Level: "), c);

		temp = new JLabel(ProfileManager.getLevel());

		c.gridx = 1;
		c.gridy = 8;
		add(temp, c);

		//Win:Ratio

		c.gridx = 0;
		c.gridy = 9;
		add(new JLabel("Skill Level: "), c);

		temp = new JLabel(ProfileManager.getTimeDeathRatio());

		c.gridx = 1;
		c.gridy = 9;
		add(temp, c);

		//total time played

		c.gridx = 0;
		c.gridy = 10;
		add(new JLabel("Total Time Played(s): "), c);

		temp = new JLabel(ProfileManager.getTime());

		c.gridx = 1;
		c.gridy = 10;
		add(temp, c);

		//Select Level
		//total time played

		c.gridx = 0;
		c.gridy = 11;
		add(new JLabel("Select Starting Level:"), c);

		//	text1 = new JTextField(3);
		text1 = new JTextField("1", 3);

		c.gridx = 1;
		c.gridy = 11;
		add(text1, c);

		JButton mainMenu = new JButton("Main Menu");

		c.gridx = 0;
		c.gridy = 12;
		add(mainMenu, c);

		JButton play = new JButton("Play");

		c.gridx = 1;
		c.gridy = 12;
		add(play, c);

		JButton logout = new JButton("Logout");

		c.gridx = 2;
		c.gridy = 12;
		add(logout, c);

		/*
		 * 			JButton changePW = new JButton("Change Password");
		
		c.gridx = 1;
		c.gridy = 1;
		add(changePW, c);
		 */
		changePW.addActionListener(this);
		mainMenu.addActionListener(this);
		play.addActionListener(this);
		logout.addActionListener(this);

	}

	/** Renders Screen (Unused)
	 * 
	 * 	
	 */
	@Override
	protected void render(Graphics2D g2d) {}

	/** Updates Time (Unused)
	 * 
	 * 	
	 */
	@Override
	protected void update(float deltaTime) {}

	/** Tracks Key (Unused)
	 * 
	 * 	
	 */
	@Override
	protected void keyRelease(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	/** Tracks Key press (Unused)
	 * 
	 * 	
	 */
	@Override
	protected void keyPress(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	/** Action Performer-- Changes screen
	 *
	 * Checks input fields and reponds
	 * 	
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		String id = ((JButton) e.getSource()).getText();
		if (id.equals("Change Password")) {
			changeScreen(new PassScreen(game));
		}
		if (id.equals("Main Menu")) {
			changeScreen(new MainMenuScreen(game));
		}
		if (id.equals("Play")) {
			String value1 = text1.getText();
			int val = Integer.parseInt(value1);
			if (val > Integer.parseInt(ProfileManager.getLevel()) || val < 1) {
				JOptionPane.showMessageDialog(this, "Please enter between 1 and " + ProfileManager.getLevel(), "Error", JOptionPane.ERROR_MESSAGE);
			} else {
				changeScreen(new GameScreen(game, val - 1));
			}
		}
		if (id.equals("Logout")) {
			game.setUser("Guest");
			changeScreen(new MainMenuScreen(game));
		}
	}
}
