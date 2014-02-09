package com.pacman.game;

/**
 * Class representing a 2d vector of floats with many helper methods for easy vector manipulations and math.
 * Many of the methods return @this which makes it easy to chain statements such as (new Vector2(10,5).add(3,7).sub(1,5).nor())
 * 
 * @author Thaer
 *
 */
public class Vector2 {
	public float	x, y;

	public Vector2() {}

	/**
	 * Create a new vector of floats
	 * 
	 * @param x
	 * @param y
	 */
	public Vector2(float x, float y) {
		this.x = x;
		this.y = y;
	}

	/**
	 * Create a new vector based on another
	 * 
	 * @param other
	 */
	public Vector2(Vector2 other) {
		this.x = other.x;
		this.y = other.y;
	}

	/**
	 * Returns a deep copy of the vector.
	 * 
	 * @return
	 */
	public Vector2 cpy() {
		return new Vector2(x, y);
	}

	/**
	 * Sets vector positions
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2 set(float x, float y) {
		this.x = x;
		this.y = y;
		return this;
	}

	/**
	 * Sets vector positions
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2 set(Vector2 other) {
		this.x = other.x;
		this.y = other.y;
		return this;
	}

	/**
	 * Adds positions to @this vector
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2 add(float x, float y) {
		this.x += x;
		this.y += y;
		return this;
	}

	/**
	 * Adds other vector to @this vector
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2 add(Vector2 other) {
		this.x += other.x;
		this.y += other.y;
		return this;
	}

	/**
	 * Subtract positions from @this vector
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2 sub(float x, float y) {
		this.x -= x;
		this.y -= y;
		return this;
	}

	/**
	 * Subtract other vector from@this vector
	 * 
	 * @param x
	 * @param y
	 * @return
	 */
	public Vector2 sub(Vector2 other) {
		this.x -= other.x;
		this.y -= other.y;
		return this;
	}

	/**
	 * Multiplies vector with a scalar
	 * 
	 */
	public Vector2 mul(float scalar) {
		this.x *= scalar;
		this.y *= scalar;
		return this;
	}

	/**
	 * Computes the dot product of two vectors
	 * 
	 * @param other
	 * @return
	 */
	public float dot(Vector2 other) {
		return this.x * other.x + this.y * other.y;
	}

	/**
	 * Computes length of vector
	 * @return
	 */
	public float len() {
		return (float) Math.sqrt(x * x + y * y);
	}

	/**
	 * Normalizes the vector (sets its unit length to 1, useful for directions)
	 * 
	 * @return
	 */
	public Vector2 norm() {
		float len = len();
		if (len != 0) {
			this.x /= len;
			this.y /= len;
		}
		return this;
	}

	/**
	 * Computes the euclidean distance between 2 vectors
	 * 
	 * @param other
	 * @return
	 */
	public float dist(Vector2 other) {
		float distX = this.x - other.x;
		float distY = this.y - other.y;
		return (float) Math.sqrt(distX * distX + distY * distY);
	}

	/**
	 * Computes the euclidean distance between 2 vectors
	 * 
	 * @param other
	 * @return
	 */
	public float dist(float x, float y) {
		float distX = this.x - x;
		float distY = this.y - y;
		return (float) Math.sqrt(distX * distX + distY * distY);
	}

	/**
	 * Equates two vectors, susceptible to floating point inaccuracies
	 * 
	 * @param other
	 * @return
	 */
	public boolean equals(Vector2 other) {
		return this.x == other.x && this.y == other.y;
	}

	/**
	 * Equates two vectors, susceptible to floating point inaccuracies
	 * 
	 * @param other
	 * @return
	 */
	public boolean equals(float x, float y) {
		return this.x == x && this.y == y;
	}

}