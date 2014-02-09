package com.pacman.game;

import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;

import com.pacman.game.World.GameState;
import com.pacman.main.Assets;

/**
 * This class ensures the world is running correctly
 * 
 * @author Thaer
 *
 */
public class WorldTest {
	@Before
	public void setUp() throws Exception {
		Assets.loadLevels();
	}
	
	@Test
	public void testGetState() {
		World w = new World(250, 250, Assets.getLevels(), "Guest");
		assertEquals(w.getState(), GameState.WAITING);

		//run the world for 3 seconds so that gameplay can start
		w.update(3);
		
		assertEquals(w.getState(), GameState.RUNNING);
	}

	@Test
	public void testEndGame() {
		World w = new World(250, 250, Assets.getLevels(), "Guest");
		w.endGame(GameState.WON);
		assertEquals(w.getState(), GameState.WON);

		w = new World(250, 250, Assets.getLevels(), "Guest");
		w.endGame(GameState.LOST);
		assertEquals(w.getState(), GameState.LOST);

	}

	@Test
	public void testTogglePause() {
		World w = new World(250, 250, Assets.getLevels(), "Guest");

		//run the world for 3 seconds so that gameplay can start
		w.update(3);
		
		assertEquals(w.getState(), GameState.RUNNING);
		w.togglePause();
		assertEquals(w.getState(), GameState.PAUSED);
		w.togglePause();
		assertEquals(w.getState(), GameState.RUNNING);
	}

}
