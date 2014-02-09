/** Screen with a menu. Used to access different features of the game, such as login and settings.
 * @author Loren Lugosch, Thaer Jleilati
 */

package com.pacman.rendering;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

import com.pacman.main.Game;
import com.pacman.menus.Menu;
import com.pacman.menus.MenuItem;

@SuppressWarnings("serial")
public class MenuScreen extends Screen {
	Menu		menu;
	Font		stringFont;
	final int	X_POSITION			= 100;
	final int	X_POSITION_CURSOR	= 80;

	/** Constructor for a menu screen. Defines font for menu items.
	 * 
	 * @param game
	 */
	public MenuScreen(Game game) {
		super(game);
		stringFont = new Font("comic sans ms", Font.PLAIN, 20);
	}

	/** Constructor for a menu screen. Sets up a menu.
	 * 
	 * @param game
	 * @param menu
	 */
	public MenuScreen(Game game, Menu menu) {
		super(game);
		this.menu = menu;
	}

	/** Method for rendering menu items.
	 * 
	 */
	@Override
	protected void render(Graphics2D g2d) {
		drawMenuItems(menu, g2d);
	}

	/** Unused update method. Can be changed to introduce animations in the menus.
	 * 
	 */
	@Override
	protected void update(float deltaTime) {
		// TODO Auto-generated method stub

	}

	/** Defines action upon key release.
	 * 
	 */
	@Override
	protected void keyRelease(KeyEvent e) {
		switch (e.getKeyCode()) {
		case KeyEvent.VK_UP:
		break;
		}
	}

	protected void moved(MouseEvent e) {
		//
	}

	/** Defines action upon pressing a key.
	 * Users can use the arrow keys to move up/down.
	 */
	@Override
	protected void keyPress(KeyEvent e) {
		switch (e.getKeyCode()) {
		case KeyEvent.VK_UP:
			menu.selectPrevious();
		break;
		case KeyEvent.VK_DOWN:
			menu.selectNext();
		break;
		// If enter, enter that menu item's game screen
		}

	}

	/** Draws the menu items in the appropriate positions.
	 * Case where there is no menu is handled.
	 * @param menu
	 * @param g2d
	 */
	public void drawMenuItems(Menu menu, Graphics2D g2d) {
		g2d.setFont(stringFont);
		try {
			for (int i = 0; i < menu.numberOfMenuItems(); i++) {

				MenuItem item = menu.getMenuItems()[i];

				// Draw the ith menu item on the screen
				g2d.setColor(Color.WHITE);
				g2d.drawString(item.toString(), X_POSITION, yPosition(i));
				if (item.selected == true) {
					drawPacmanAtI(i, g2d);
				}
			}
		} catch (NullPointerException n) {
			g2d.drawString("no menu!", 100, 50);
		}
	}

	/** Returns the appropriate height for the ith item.
	 * 
	 * @param i
	 * @return 20*i+game.getHeight()/2
	 */
	private int yPosition(int i) {
		return 20 * i + game.getHeight() / 2;
	}

	/** Draws a pacman shaped cursor at the appropriate position.
	 * Shows the user where which item is selected.
	 * 
	 * @param i
	 * @param g2d
	 */
	private void drawPacmanAtI(int i, Graphics2D g2d) {
		g2d.setColor(Color.yellow);
		g2d.fillOval(X_POSITION_CURSOR, yPosition(i) - 20, 20, 20);

		g2d.setColor(Color.black);
		g2d.fillOval(X_POSITION_CURSOR + 13, yPosition(i) - 13, 8, 8);

	}

}