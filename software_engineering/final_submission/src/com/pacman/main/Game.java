package com.pacman.main;

import java.awt.CardLayout;
import java.awt.Insets;

import javax.swing.JFrame;
import javax.swing.JPanel;

import com.pacman.rendering.Screen;

/**
 * this is the frame that will contain all the content we wish to display
 * It will also contain information about the current user that is playing the game
 * 
 * @author Thaer
 *
 */
@SuppressWarnings("serial")
public class Game extends JFrame {

	final int		WIDTH;
	final int		HEIGHT;
	public String	user;
	JPanel			display	= new JPanel(new CardLayout());
	Screen			currentScreen;
	//string used to identify the current screen
	String			current	= "currentScreen";

	/**
	 * Creates a new game  
	 * 
	 * @param width dimensions in pixels
	 * @param height
	 * @param title
	 * @param name
	 */
	public Game(int width, int height, String title, String name) {
		WIDTH = width;
		HEIGHT = height;
		user = name;

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLocation(0, 0);
		setTitle(title);
		setResizable(true);
		setVisible(true);

		//this ensures that the content pane's size is of WIDTH, HEIGHT because the setSize method takes the insets into account
		Insets insets = getInsets();
		setSize(WIDTH + insets.right + insets.left, HEIGHT + insets.bottom + insets.top);
	}

	/**
	 * swaps current display screen to a new one
	 * @param newScreen
	 */
	public void setScreen(Screen newScreen) {
		//terminate rendering and updating thread for the current screen
		currentScreen.finish();

		//remove current screen from display
		CardLayout layout = (CardLayout) (display.getLayout());
		display.removeAll();

		//adds newScreen to display and refreshes the display so that we can see the new screen
		currentScreen = newScreen;
		display.add(newScreen, current);
		display.revalidate();
		layout.show(display, current);

		//ensures that key presses are handled correctly
		newScreen.requestFocusInWindow();

		//starts the updating and rendering loop for the newScreen
		newScreen.start();
	}

	/**
	 * sets the starting screen
	 * @param screen
	 */
	public void initScreen(Screen screen) {
		currentScreen = screen;
		display.add(screen, current);
		add(display);
		screen.requestFocusInWindow();
		screen.start();
	}

	/**
	 * gets the width
	 */
	public int getWidth() {
		return WIDTH;
	}

	/**
	 * gets the height
	 */
	public int getHeight() {
		return HEIGHT;
	}

	/**
	 * sets the current user that is playing
	 * @param temp
	 */
	public void setUser(String temp) {
		user = temp;
	}

	/**
	 * gets the current user that is playing
	 * @return
	 */
	public String getUser() {
		return user;
	}
}
