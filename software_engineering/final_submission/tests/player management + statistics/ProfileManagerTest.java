/* This doubles as an Integration test because Writing to profile
* and reading from profile is run through FileHandling
*
*/
package com.pacman.playermanagement;

import static org.junit.Assert.*;

import org.junit.*;

import com.pacman.playermanagement.ProfileManager;

public class ProfileManagerTest {

	@Test
	public void testSplitStringAndCurrentPro() {
		String s = "Username, Password, Data1, Data2, Data3, Data4;";
		ProfileManager.splitString(s);
		String[] sarray = ProfileManager.getCurrentPro();
		assertEquals(sarray[0], "Username");
		assertEquals(sarray[1], "Password");
		assertEquals(sarray[2], "Data1");
		assertEquals(sarray[3], "Data2");
		assertEquals(sarray[4], "Data3");
		assertEquals(sarray[5], "Data4");

	}

	@Test
	public void testCombString() {
		String[] sarray = { "Username", "Password", "Data1", "Data2", "Data3", "Data4" };
		String s = ProfileManager.combString(sarray);
		assertEquals(s, "Username, Password, Data1, Data2, Data3, Data4;");
	}

	@Test
	public void testFindUser() {
		assertTrue(ProfileManager.findUser("Guest"));
	}

	@Test
	public void testCheckPass() {
		assertTrue(ProfileManager.findUser("Guest"));
		assertTrue(ProfileManager.checkPass("12345"));
	}

	@Test
	public void testChangePass() {
		ProfileManager.findUser("Guest");
		assertTrue(ProfileManager.checkPass("12345"));
		ProfileManager.changePass("abc");
		assertTrue(ProfileManager.checkPass("abc"));
	}

	//	@Test
	//	public void testMisc(){
	//		System.out.println(ProfileManager.findUser("chrispeng"));
	//		System.out.println(ProfileManager.combString(ProfileManager.getCurrentPro()));
	//	}
	@Test
	public void testKeepTrackAllStatistics() {
		ProfileManager.setDeaths("0");
		ProfileManager.setDots("0");
		ProfileManager.setGamesPlayed("0");
		ProfileManager.setHighScore("0");
		ProfileManager.setTimeDeathRatio("0");
		ProfileManager.setWins("0");
		ProfileManager.setTime("0");
		ProfileManager.setLevel("1");

		assertTrue(ProfileManager.getDeaths().equals("0"));
		assertTrue(ProfileManager.getDots().equals("0"));
		assertTrue(ProfileManager.getGamesPlayed().equals("0"));
		assertTrue(ProfileManager.getHighScore().equals("0"));
		assertTrue(ProfileManager.getTimeDeathRatio().equals("0"));
		assertTrue(ProfileManager.getWins().equals("0"));
		assertTrue(ProfileManager.getTime().equals("0"));
		assertTrue(ProfileManager.getLevel().equals("1"));

	}

	@Test
	public void testCreateNewAccount() {
		ProfileManager.createNewUser("newuser", "password");
		assertTrue(ProfileManager.findUser("newuser"));
	}
}
