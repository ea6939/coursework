/** Screen for managing global game settings.
 * @author Loren Lugosch
 */

package com.pacman.rendering;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.KeyEvent;

import com.pacman.main.Game;
import com.pacman.menus.Menu;
import com.pacman.menus.MenuItem;
import com.pacman.settings.Settings;

@SuppressWarnings("serial")
public class SettingsScreen extends MenuScreen {
	Menu			menu;
	MenuItem[]		menuItems;
	MenuItem.Type	previousMenu;
	final Color		PURPLE	= new Color(152, 18, 196);

	/** Default constructor for a settings screen.
	 * Called from main menu.
	 * @param game
	 */
	public SettingsScreen(Game game) {
		super(game);
		menuItems = new MenuItem[] { new MenuItem(MenuItem.Type.CHANGE_MAZE_COLOR, true), new MenuItem(MenuItem.Type.CHANGE_PACMAN_COLOR, false) };
		menu = new Menu(menuItems);

	}

	/** Constructor for a settings screen with a particular menu.
	 * 
	 * @param game
	 * @param menu
	 */
	public SettingsScreen(Game game, Menu menu) {
		super(game, menu);
		this.menu = menu;
	}

	/** Constructor for a settings screen with a particular menu.
	 * Used if the function of a menu is ambiguous because the items in a menu are identical to those of another menu.
	 * 
	 * @param game
	 * @param menu
	 * @param previousMenu
	 */
	public SettingsScreen(Game game, Menu menu, MenuItem.Type previousMenu) {
		// This constructor is used if we want to display menu items relevant to each use case.
		super(game);
		this.menu = menu;
		this.previousMenu = previousMenu;
	}

	/** Draws the settings to the screen.
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

	}

	/** Defines action upon key release.
	 * 
	 */
	@Override
	protected void keyRelease(KeyEvent e) {

	}

	/** Defines action upon key release.
	 * Depending on the setting selected, hitting enter does different things.
	 * 
	 */
	@Override
	protected void keyPress(KeyEvent e) {
		switch (e.getKeyCode()) {
		case KeyEvent.VK_UP:
			menu.selectPrevious();
		break;
		case KeyEvent.VK_DOWN:
			menu.selectNext();//
		break;

		// backspace takes the user back to the last menu he/she was at
		case KeyEvent.VK_BACK_SPACE:
			if (previousMenu == MenuItem.Type.SETTINGS) {
				changeScreen(new SettingsScreen(game));
			} else {
				changeScreen(new MainMenuScreen(game));
			}
		break;

		// user selects one of the settings
		case KeyEvent.VK_ENTER:
			switch (menu.getSelectedItem().type) {
			case CHANGE_MAZE_COLOR:
				menuItems = new MenuItem[] { new MenuItem(MenuItem.Type.PURPLE, true), new MenuItem(MenuItem.Type.WHITE, false), new MenuItem(MenuItem.Type.GREEN, false) };
				menu = new Menu(menuItems);
				previousMenu = MenuItem.Type.CHANGE_MAZE_COLOR;
				changeScreen(new SettingsScreen(game, menu, previousMenu));
			break;
			case CHANGE_PACMAN_COLOR:
				menuItems = new MenuItem[] { new MenuItem(MenuItem.Type.WHITE, true), new MenuItem(MenuItem.Type.PURPLE, false), new MenuItem(MenuItem.Type.GREEN, false) };
				menu = new Menu(menuItems);
				previousMenu = MenuItem.Type.CHANGE_PACMAN_COLOR;
				changeScreen(new SettingsScreen(game, menu, previousMenu));
			break;
			case PLAY:
				changeScreen(new GameScreen(game));
			break;
			case SETTINGS:
				changeScreen(new SettingsScreen(game, menu));
			break;

			// If a color is selected, change whatever setting the color is relevant to.
			case WHITE:
				if (previousMenu == MenuItem.Type.CHANGE_PACMAN_COLOR)
					Settings.setPacmanColor(Color.WHITE);
				else if (previousMenu == MenuItem.Type.CHANGE_MAZE_COLOR) Settings.setMazeColor(Color.WHITE);

				changeScreen(new SettingsScreen(game));
			break;
			case PURPLE:
				if (previousMenu == MenuItem.Type.CHANGE_PACMAN_COLOR)
					Settings.setPacmanColor(PURPLE);
				else if (previousMenu == MenuItem.Type.CHANGE_MAZE_COLOR) Settings.setMazeColor(PURPLE);

				changeScreen(new SettingsScreen(game));
			break;
			case GREEN:
				if (previousMenu == MenuItem.Type.CHANGE_PACMAN_COLOR)
					Settings.setPacmanColor(Color.GREEN);
				else if (previousMenu == MenuItem.Type.CHANGE_MAZE_COLOR) Settings.setMazeColor(Color.GREEN);

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