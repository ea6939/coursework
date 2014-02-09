package com.pacman.rendering;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Toolkit;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JPanel;

import com.pacman.main.Game;

@SuppressWarnings("serial")
/**
 * This screen inherits from JPanel. Each screen has its own render method, execution thread and event handling.
 * This enables us to abstract away most swing details and completely separate each screen from the other
 * 
 * @author Thaer
 *
 */
public abstract class Screen extends JPanel implements Runnable {
	Game		game;
	int			width;
	int			height;
	//this is the time interval that will be used to update the world with
	final float	TIME_STEP	= 1 / 60f;
	boolean		running		= false;

	/**
	 * Initializes the screen with the game instance
	 * 
	 * @param game
	 */
	public Screen(Game game) {
		this.game = game;
		this.width = game.getWidth();
		this.height = game.getHeight();
		setBackground(Color.BLACK);
		setDoubleBuffered(true);
		addKeyListener(new TAdapter());
	}

	protected void changeScreen(Screen screen) {
		game.setScreen(screen);
	}

	/**
	 * used by by swing to propagate events
	 */
	public void addNotify() {
		super.addNotify();
	}

	/**
	 * starts the game loop
	 */
	public void start() {
		running = true;
		new Thread(this).start();
	}

	/**
	 * terminates the game loop
	 */
	public void finish() {
		running = false;
	}

	/**
	 * Method is called when swing wants to render the panel
	 */
	public void paint(Graphics g) {
		super.paint(g);

		render((Graphics2D) g);

		//ensures display is up to date
		Toolkit.getDefaultToolkit().sync();
		g.dispose();
	}

	//called by the game loop, used to render graphics
	protected abstract void render(Graphics2D g2d);

	//called by the game loop, used to update the world
	protected abstract void update(float deltaTime);

	protected abstract void keyRelease(KeyEvent e);

	protected abstract void keyPress(KeyEvent e);

	/**
	 * the game loop. it starts running when the start() method is called
	 * it is fixed time step and updates the game world based on the time between two frames
	 */
	public void run() {
		long prevTime = System.currentTimeMillis();
		while (running) {

			long curTime = System.currentTimeMillis();
			float frameTime = (curTime - prevTime) / 1000f;

			while (frameTime > TIME_STEP) {
				update(TIME_STEP);
				frameTime -= TIME_STEP;
				prevTime = curTime;
			}

			repaint();
		}
	}

	//captures key events and passes them on to their respective methods
	private class TAdapter extends KeyAdapter {
		public void keyReleased(KeyEvent e) {
			keyRelease(e);
		}

		public void keyPressed(KeyEvent e) {
			keyPress(e);
		}
	}

}