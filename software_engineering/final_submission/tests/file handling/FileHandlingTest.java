package com.pacman.filehandling;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;

public class FileHandlingTest {
	
	private final static String profileDataPath = "res/profiles.txt";
	private final static String testDataPath = "res/test.txt";
	
	@Test
	public void testWrite() {
		ArrayList<String> test = new ArrayList<String>();
		ArrayList<String> compare = new ArrayList<String>();
		test.add("Test");
		FileHandling.printTextFile(testDataPath, test);
		compare = FileHandling.loadTextFile(testDataPath);
		assertTrue(compare.equals(test));

	}

}
