/** Screen shown at startup.
 * @author Loren Lugosch
 */

package com.pacman.rendering;

import java.awt.Graphics2D;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;

import com.pacman.main.Game;
import com.pacman.menus.Menu;
import com.pacman.menus.MenuItem;

@SuppressWarnings("serial")
public class MainMenuScreen extends MenuScreen {
	Menu	menu;

	/** Constructor for a main menu screen.
	 * 
	 * @param game
	 */
	public MainMenuScreen(Game game) {
		super(game);
		MenuItem[] menuItems = new MenuItem[] { new MenuItem(MenuItem.Type.PLAY, true), new MenuItem(MenuItem.Type.LOGIN, false), new MenuItem(MenuItem.Type.SETTINGS, false) };
		menu = new Menu(menuItems);

	}

	/** Renders menu items.
	 * 
	 */
	@Override
	protected void render(Graphics2D g2d) {
		super.drawMenuItems(menu, g2d);
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
	* Users can use the arrow keys to move up/down and enter to select.
	*/
	@Override
	protected void keyPress(KeyEvent e) {
		// TODO Auto-generated method stub
		switch (e.getKeyCode()) {
		case KeyEvent.VK_UP:
			menu.selectPrevious();
		break;
		case KeyEvent.VK_DOWN:
			menu.selectNext();
		break;
		case KeyEvent.VK_ENTER:
			switch (menu.getSelectedItem().type) {
			case PLAY:
				changeScreen(new GameScreen(game));
			break;
			case LOGIN:
				if (game.getUser() == "Guest") {
					changeScreen(new LoginScreen(game));
				} else {
					changeScreen(new ProfileScreen(game));
				}
			break;
			case SETTINGS:
				changeScreen(new SettingsScreen(game));
			break;
			default:
			break;
			}

		break;
		// If enter, enter that menu item's game screen
		}

	}

}
