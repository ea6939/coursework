package com.pacman.game;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import com.pacman.game.MovableObject.Direction;

public class MovableObjectTest {

	final double	delta	= 0.00001;

	@Test
	public void testInitPosition() {
		MovableObject m = new MovableObject(new Vector2I(10, 10), 150, 10, 10);
		m.initPosition();

		//direction should be initialized as up
		assertEquals(m.getDir(), Direction.UP);
		assertEquals(m.tilePos(), new Vector2I(10, 10));
	}

	@Test
	public void testAtGoal() {
		//object should be at his goal when he starts, that is to say not moving
		MovableObject m = new MovableObject(new Vector2I(10, 10), 0, 10, 10);
		m.initPosition();

		assertEquals(m.atGoal(), true);
	}

	@Test
	public void testClipped() {
		MovableObject m = new MovableObject(new Vector2I(10, 10), 0, 10, 10);
		m.initPosition();

		Vector2 clipped = m.clipped();
		assertEquals(clipped.x, 100, delta);
		assertEquals(clipped.y, 100, delta);
	}

	@Test
	public void testDistToClipped() {
		MovableObject m = new MovableObject(new Vector2I(10, 10), 0, 10, 10);
		m.initPosition();

		//he should start perfectly aligned to his tile
		assertEquals(m.distToClipped(), 0, delta);
	}

	@Test
	public void testTilePos() {
		MovableObject m = new MovableObject(new Vector2I(10, 10), 0, 10, 10);
		m.initPosition();

		//should start at tile 10,10
		assertEquals(m.tilePos(), new Vector2I(10, 10));
	}

	@Test
	public void testGetPos() {
		MovableObject m = new MovableObject(new Vector2I(10, 10), 0, 10, 10);
		m.initPosition();

		Vector2 pos = m.getPos();
		assertEquals(pos.x, 10 * 10, delta);
		assertEquals(pos.y, 10 * 10, delta);
	}

	@Test
	public void testSetPos() {
		MovableObject m = new MovableObject(new Vector2I(10, 10), 0, 10, 10);
		m.initPosition();

		m.setPos(new Vector2(150, 150));
		Vector2 pos = m.getPos();
		assertEquals(pos.x, 150, delta);
		assertEquals(pos.y, 150, delta);
	}

}
