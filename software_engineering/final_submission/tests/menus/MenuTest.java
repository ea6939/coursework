package com.pacman.menus;

import static org.junit.Assert.*;

import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

public class MenuTest {
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
	public void testMenu() {
		testSetup();
		assertEquals(menu.getSelectedIndex(),0);
		testCleanup();
	}

	@Test
	public void testNumberOfMenuItems() {
		testSetup();
		assertTrue(menu.numberOfMenuItems() == 3);
		testCleanup();
	}

	@Test
	public void testSelectPrevious() {
		testSetup();
		menu.selectPrevious();
		assertEquals(menu.getSelectedIndex(),2);
		testCleanup();
	}

	@Test
	public void testSelectNext() {
		testSetup();
		menu.selectNext();
		menu.selectNext();
		menu.selectNext();
		assertEquals(menu.getSelectedIndex(),0);
		testCleanup();
	}

}
