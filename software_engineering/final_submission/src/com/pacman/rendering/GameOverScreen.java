package com.pacman.rendering;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;

import com.pacman.main.Game;

@SuppressWarnings("serial")
/**
 * This screen is displayed when the game is over
 * @author Thaer
 *
 */
public class GameOverScreen extends Screen {
	private final int		SCORE;
	private final int		LEVEL_NUM;
	private final Font		gameOverFont	= new Font("comic sans ms", Font.BOLD, 50);
	private final Font		stringFont		= new Font("comic sans ms", Font.PLAIN, 20);
	private final String	message;

	/**
	 * Initialize the game over screen 
	 * 
	 * @param game
	 * @param score score the player has reached
	 * @param levelNum level the player has reached
	 * @param message message to display
	 */
	public GameOverScreen(Game game, int score, int levelNum, String message) {
		super(game);
		this.SCORE = score;
		this.LEVEL_NUM = levelNum;
		this.message = message;
	}

	//draws screen elements
	protected void render(Graphics2D g2d) {
		g2d.setColor(Color.black);
		g2d.fillRect(0, 0, width, height);

		g2d.setColor(Color.white);
		g2d.setFont(gameOverFont);
		g2d.drawString(message, (int) (width * 0.15), height / 2 - gameOverFont.getSize());
		g2d.setFont(stringFont);
		g2d.drawString("Level reached: " + Integer.toString(LEVEL_NUM), 0, stringFont.getSize());
		g2d.drawString("Final score: " + Integer.toString(SCORE), 0, stringFont.getSize() * 2);

		g2d.drawString("Play again? (ENTER)", (int) (width * 0.25), height - stringFont.getSize() * 2);
		g2d.drawString("Return to menu? (BACKSPACE)", (int) (width * 0.15), height - stringFont.getSize());
	}

	//handles key events
	protected void keyPress(KeyEvent e) {
		switch (e.getKeyCode()) {
		case (KeyEvent.VK_ENTER):
			changeScreen(new GameScreen(game));
		break;
		case (KeyEvent.VK_BACK_SPACE):
			changeScreen(new MainMenuScreen(game));
		break;
		}
	}

	protected void update(float deltaTime) {}

	protected void keyRelease(KeyEvent e) {}
}
