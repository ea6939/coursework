package com.pacman.settings;
import java.awt.Color;
import org.junit.* ;
import static org.junit.Assert.* ;

public class SettingTest {
	
	Settings setTest;
	@Test
	public void getTest (){

	//check if the value is correctly get with get methods

	this.setTest = new Settings();
	
		assertTrue(setTest.getPacmanColor()== Color.YELLOW && setTest.getVolume() == 0);

	}

	@Test
	  public void changeTest (){
		
		setTest.setPacmanColor(Color.RED);
		setTest.setVolume(100);

		assertTrue(setTest.getPacmanColor()== Color.RED && setTest.getVolume() == 100);
		
		

	  
	}


}
