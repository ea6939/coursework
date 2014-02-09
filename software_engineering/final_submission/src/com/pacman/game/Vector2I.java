package com.pacman.game;

/**
 * Class representing a 2d vector of ints with many helper methods for easy vector manipulations and math.
 * Many of the methods return @this which makes it easy to chain statements such as (new Vector2(10,5).add(3,7).sub(1,5).nor())
 * 
 * This is useful when we are always dealing with integer positions (such as tile x and y on a map),
 * and avoids unnecessary casting from float to int.
 * 
 * @author Thaer
 *
 */
public class Vector2I {
	public int	x, y;

	/**
	 * Creates a vector based on another vector
	 * 
	 * @param x
	 * @param y
	 */
	public Vector2I(int x, int y) {
		this.x = x;
		this.y = y;
	}

	/**
	 * Creates a vector based on another vector, casts positions to int
	 * 
	 * @param x
	 * @param y
	 */
	public Vector2I(float x, float y) {
		this.x = (int) x;
		this.y = (int) y;
	}

	/**
	 * Creates a vector based on another vector, casts positions to int
	 * 
	 * @param x
	 * @param y
	 */
	public Vector2I(double x, double y) {
		this.x = (int) x;
		this.y = (int) y;
	}

	/**
	 * Computes Euclidean distance between two vectors
	 * 
	 * @param other
	 * @return
	 */
	public float dist(Vector2I other) {
		int distX = this.x - other.x;
		int distY = this.y - other.y;
		return (float) Math.sqrt(distX * distX + distY * distY);
	}

	/**
	 * Computes Euclidean distance between two vectors
	 * 
	 * @param other
	 * @return
	 */
	public float dist(int x, int y) {
		int distX = this.x - x;
		int distY = this.y - y;
		return (float) Math.sqrt(distX * distX + distY * distY);
	}

	/**
	 * Sets vector positions
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2I set(int x, int y) {
		this.x = x;
		this.y = y;
		return this;
	}

	/**
	 * Sets vector positions to be equal to those of another vector
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2I set(Vector2I other) {
		this.x = other.x;
		this.y = other.y;
		return this;
	}

	/**
	 * Adds another vector to @this vector
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2I add(int x, int y) {
		this.x += x;
		this.y += y;
		return this;
	}

	/**
	 * Adds another vector to @this vector
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2I add(Vector2I other) {
		this.x += other.x;
		this.y += other.y;
		return this;
	}

	/**
	 * Subtracts another vector from @this vector.
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2I sub(int x, int y) {
		this.x -= x;
		this.y -= y;
		return this;
	}

	/**
	 * Subtracts another vector from @this vector.
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2I sub(Vector2I other) {
		this.x -= other.x;
		this.y -= other.y;
		return this;
	}

	/**
	 * Multiples vector by scalar, casts positions to int.
	 * 
	 * @param scalar
	 * @return
	 */
	public Vector2I mul(float scalar) {
		this.x = (int) (this.x * scalar);
		this.y = (int) (this.y * scalar);
		return this;
	}

	/**
	 * String representation of vector
	 */
	public String toString() {
		return this.x + ":" + this.y;
	}

	/**
	 * @return A deep copy of the vector
	 */
	public Vector2I cpy() {
		return new Vector2I(x, y);
	}

	/**
	 * Equates vector to another
	 * 
	 * @param other
	 * @return
	 */
	public boolean equals(Vector2I other) {
		return this.x == other.x && this.y == other.y;
	}

	/**
	 * Equates vector to another
	 * 
	 * @param other
	 * @return
	 */
	public boolean equals(int x, int y) {
		return this.x == x && this.y == y;
	}

	/**
	 * Equates vector to an object based on the hash code
	 * 
	 * @param other
	 * @return
	 */
	public boolean equals(Object obj) {
		return hashCode() == obj.hashCode();
	}

	/**
	 * Hashing method to enable vector to be stored in a map.
	 */
	public int hashCode() {
		return 37 * this.x + this.y;
	}

}