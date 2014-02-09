/* This Integration test uses both FileHandling and ProfileManager
* filehandling is reading for profile data from database using its classes
*
* Since ProfileManager sends a String which contains the filepath of file
* to FileHandling, which, in turn, reads the file, and sends back the data
* to ProfileManager
*/
package com.pacman.Integration;

import static org.junit.Assert.*;

import org.junit.*;

import com.pacman.playermanagement.ProfileManager;

public class Integration {


	@Test
	public void testWritingToDatabase() {
		ProfileManager.createNewUser("newuser", "password");
		assertTrue(ProfileManager.findUser("newuser"));
		
		
	}
}
