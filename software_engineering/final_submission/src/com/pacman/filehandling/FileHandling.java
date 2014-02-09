package com.pacman.filehandling;

import java.io.*;
import java.util.ArrayList;

/**
 * This package will be used to abstract away all file handling and database 
manipulation. This way other packages can use this class to load and manipulate 
files/databases without directly being involved with IO operations. */
public class FileHandling {

	public FileHandling() {}

	//converts a file into a arrayList of lines
	public static ArrayList<String> loadTextFile(String filePath) {
		ArrayList<String> contents = new ArrayList<String>();
		BufferedReader reader = null;

		try {
			reader = new BufferedReader(new InputStreamReader(new FileInputStream(filePath)));
			String text = null;

			// repeat until all lines is read
			while ((text = reader.readLine()) != null) {
				contents.add(text);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (reader != null) {
					reader.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		return contents;
	}

	public static void printTextFile(String filepath, ArrayList<String> toPrint) {
		try {
			PrintWriter out = new PrintWriter(filepath);

			for (String str : toPrint) {
				out.println(str);
			}
			out.close();
		} catch (Exception e) {
			System.err.println("error" + e.getMessage());
		}

	}

}
