/** Items in a menu.
 * @author Loren Lugosch
 */

package com.pacman.menus;

public class MenuItem {
	public enum Type {
		PLAY, LOGIN, SETTINGS, STATISTICS, CHANGE_VOLUME, TOP_SCORES, TOP_PLAYS, CHANGE_MAZE_COLOR, CHANGE_PACMAN_COLOR, RED, BLUE, GREEN, WHITE, PURPLE
	};

	public boolean	selected;
	public Type		type;

	/** Constructor for a menuItem of a certain Type.
	 * 
	 * @param type
	 * @param selected
	 */
	public MenuItem(Type type, boolean selected) {
		this.type = type;
		this.selected = selected;
	}

	/** toString() for menu items.
	 * 
	 * @return s.replace('_', ' ')
	 */
	public String toString() {
		String s = type.toString();
		return s.replace('_', ' ');
	}

	/** Returns whether this menu item is selected or not.
	 * 
	 * @return selected
	 */
	public boolean isSelected() {
		return selected;
	}
}
