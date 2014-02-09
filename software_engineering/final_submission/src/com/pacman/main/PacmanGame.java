package com.pacman.main;

import com.pacman.rendering.MainMenuScreen;

/**
 * This class will represent our game.
 * It is also the entry point for our game.
 * 
 * @author Thaer
 *
 */
public class PacmanGame {
	final static int	WIDTH	= 448;
	final static int	HEIGHT	= 576;

	/**
	 * initialize new game with gameScreen as the default screen
	 */
	public static void main(String[] args) {
		Game pacmanGame;
		//start the game with a guest user (can be changed later)
		pacmanGame = new Game(WIDTH, HEIGHT, "PacmanGame", "Guest");
		pacmanGame.initScreen(new MainMenuScreen(pacmanGame));
	}

}