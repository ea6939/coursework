package com.pacman.game;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class PacmanTest {

	@Test
	public void testGetLives() {
		Pacman p = new Pacman(new Vector2I(10, 10), 150, 30, 30);
		assertEquals(p.getLives(), 3);
	}

	@Test
	public void testLoseLife() {
		Pacman p = new Pacman(new Vector2I(10, 10), 150, 30, 30);
		assertEquals(p.getLives(), 3);
		p.loseLife();
		assertEquals(p.getLives(), 2);
		p.loseLife();
		assertEquals(p.getLives(), 1);
		p.loseLife();
		assertEquals(p.getLives(), 0);
	}

}
