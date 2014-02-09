/** General purpose menus with one item selected. Currently used in screens outside of gameplay.
 * @author Loren Lugosch
 */

package com.pacman.menus;

public class Menu {
	public MenuItem[]	menuItems;

	int					selectedIndex;

	/** Constructor for menu. First item selected by default.
	 * 
	 * @param menuItems
	 */
	public Menu(MenuItem[] menuItems) {
		this.menuItems = menuItems;
		selectedIndex = 0;
	}

	/** Returns the number of items in this menu.
	 * 
	 * @return menuItems.length
	 */
	public int numberOfMenuItems() {
		return menuItems.length;
	}

	/** Returns the items in this menu.
	 * 
	 * @return menuItems
	 */
	public MenuItem[] getMenuItems() {
		return menuItems;
	}

	/** Makes the previous item selected.
	 * If the first item was selected, the last item will be selected when this method is called.
	 */
	public void selectPrevious() {
		// Change the selected item from the kth item to the ((k-1) mod n) th item.
		menuItems[selectedIndex].selected = false;
		selectedIndex--;
		if (selectedIndex < 0) selectedIndex = menuItems.length - 1;
		menuItems[selectedIndex].selected = true;
	}

	/** Makes the next item selected.
	 * If the last item was selected, the first item will be selected when this method is called.
	 */
	public void selectNext() {
		// Change the selected item from the kth item to the ((k+1) mod n) th item.
		menuItems[selectedIndex].selected = false;
		selectedIndex++;
		if (selectedIndex > menuItems.length - 1) selectedIndex = 0;
		menuItems[selectedIndex].selected = true;
	}

	/** Returns the currently selected menu item.
	 * 
	 * @return menuItems[selectedIndex]
	 */
	public MenuItem getSelectedItem() {
		return menuItems[selectedIndex];
	}

	/** Returns the index of the currently selected menu item.
	 * 
	 * @return selectedIndex
	 */
	public int getSelectedIndex() {
		return selectedIndex;
	}
}