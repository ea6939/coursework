package com.pacman.menus;

import static org.junit.Assert.*;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

public class MenuItemTest {
	static MenuItem[] menuItems;
	static Menu menu;
	
	@BeforeClass
	public static void testSetup() {
		menuItems = new MenuItem[]{new MenuItem(MenuItem.Type.PLAY, true), 
				  new MenuItem(MenuItem.Type.LOGIN, false), 
				  new MenuItem(MenuItem.Type.SETTINGS, false)};
		menu = new Menu(menuItems);
	}
	
	@AfterClass
	public static void testCleanup(){
		menuItems = null;
		menu = null;
	}
	
	@Test
	public void testMenuItem() {
		testSetup();
		int selectedCount = 0;
		for (int i = 0; i < menu.numberOfMenuItems(); i++){
			MenuItem currentItem = menu.getMenuItems()[i];
			if (currentItem.isSelected()) selectedCount++;
		}
		assertEquals(selectedCount,1);
		testCleanup();
	}
	
	
}
