package com.pacman.game;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * This class defines a basic object that is placed on the maze, and that is always aligned to the gridlines of the maze.
 * Pacman and ghost are derived from this class
 * 
 * @author Thaer
 *
 */
public class MovableObject {
	//position in pixels on the map
	private Vector2		pos;
	//goal is the next tile the object is trying to move to (always at most 1 tile away) 
	private Vector2		goal;
	private final int	height;
	private final int	width;
	//speed in pixels per second
	private int			speed;
	//dir is the current objects direction, and tryDir is the direction its trying to turn to
	private Direction	dir;
	private Direction	tryDir;
	//how close an object has to be to a gap before it can turn
	final float			LEEWAY;
	final int			startX;
	final int			startY;

	/**
	 * Direction with some helper methods to convert between vectors and direction enums
	 * @author Thaer
	 *
	 */
	public enum Direction {
		LEFT, RIGHT, DOWN, UP, NONE;

		private static final Map<Direction, Vector2I>	directionVectorMap;
		private static final Map<Vector2I, Direction>	vectorDirectionMap;
		static {
			Map<Direction, Vector2I> mapD = new HashMap<Direction, Vector2I>(4);
			mapD.put(Direction.UP, new Vector2I(0, -1));
			mapD.put(Direction.DOWN, new Vector2I(0, 1));
			mapD.put(Direction.LEFT, new Vector2I(-1, 0));
			mapD.put(Direction.RIGHT, new Vector2I(1, 0));
			directionVectorMap = Collections.unmodifiableMap(mapD);

			Map<Vector2I, Direction> mapV = new HashMap<Vector2I, Direction>(4);
			mapV.put(new Vector2I(0, -1), Direction.UP);
			mapV.put(new Vector2I(0, 1), Direction.DOWN);
			mapV.put(new Vector2I(-1, 0), Direction.LEFT);
			mapV.put(new Vector2I(1, 0), Direction.RIGHT);
			vectorDirectionMap = Collections.unmodifiableMap(mapV);
		}

		/**
		 * Converts a vector to a direction 
		 * @param directionVector
		 * @return
		 */
		public static Direction vectorToDirection(Vector2I directionVector) {
			return vectorDirectionMap.get(directionVector);
		}

		/**
		 * Converts a direction to a vector
		 * @param dir
		 * @return
		 */
		public static Vector2I directionToVector(Direction dir) {
			return directionVectorMap.get(dir);
		}
	};

	/**
	 * Creates a new movable object
	 * 
	 * @param position
	 * @param speed
	 * @param height
	 * @param width
	 */
	public MovableObject(Vector2I position, int speed, int height, int width) {
		this.speed = speed;
		this.height = height;
		this.width = width;
		this.startX = position.x;
		this.startY = position.y;

		LEEWAY = (width + height) / 8f;

		initPosition();
	}

	/**
	 * Initializes object's position and direction
	 * 
	 */
	public void initPosition() {
		setTilePos(startX, startY);
		goal = pos.cpy();
		dir = Direction.UP;
		setTryDir(dir);
	}

	/**
	 * Sets the objects position as an integer tile position
	 * @param posX
	 * @param posY
	 */
	public void setTilePos(float posX, float posY) {
		pos = new Vector2(posX * width, posY * height);
	}

	/**
	 * Checks if the object has reached its goal
	 * @return
	 */
	public boolean atGoal() {
		return pos.equals(goal);
	}

	/**
	 * "Rounds" the objects position to the nearest tile, stays in pixels
	 * @return
	 */
	public Vector2 clipped() {
		return new Vector2(width * (int) ((pos.x + width / 2) / width), height * (int) ((pos.y + height / 2) / height));
	}

	/**
	 * Computes how close the object is to the center of its tile 
	 * @return
	 */
	public float distToClipped() {
		return pos.dist(clipped());
	}

	/**
	 * gets the current objects position in tiles
	 * @return
	 */
	public Vector2I tilePos() {
		return new Vector2I(((pos.x + width / 2) / width), ((pos.y + height / 2) / height));
	}

	/**
	 * gets the object's direction
	 * 
	 * @return
	 */
	public Direction getDir() {
		return dir;
	}

	/**
	 * Checks if the next tile the object is headed to is blocked
	 * 
	 * @param dir The direction in which we are trying to move to 
	 * @param maze 
	 * @return
	 */
	protected boolean isNextBlocked(Direction dir, Maze maze) {
		Vector2I nextGoal = getNextGoal(dir);

		//makes sure that the next tile is in range of the map
		if (0 <= nextGoal.x && nextGoal.x < World.NUM_COLS && 0 <= nextGoal.y && nextGoal.y < World.NUM_ROWS) {
			return maze.isBlocked(nextGoal.x, nextGoal.y, dir);
		}
		//any objects not in range of the map are considered unblocked
		return false;
	}

	//computes the tile that the object will reach next based on a direction
	private Vector2I getNextGoal(Direction dir) {
		Vector2I curPos = tilePos();
		Vector2I nextGoal = null;

		switch (dir) {
		case RIGHT:
			nextGoal = new Vector2I(curPos.x + 1, curPos.y);
		break;
		case LEFT:
			nextGoal = new Vector2I(curPos.x - 1, curPos.y);
		break;
		case UP:
			nextGoal = new Vector2I(curPos.x, curPos.y - 1);
		break;
		case DOWN:
			nextGoal = new Vector2I(curPos.x, curPos.y + 1);
		break;
		default:
		break;
		}

		return nextGoal;
	}

	/**
	 * Computes the goal of the movable object
	 * 
	 * @param maze
	 */
	public void updateGoal(Maze maze) {
		if (!isNextBlocked(dir, maze)) {
			Vector2I nextGoal = getNextGoal(dir);
			goal.set(width * nextGoal.x, height * nextGoal.y);
		}
	}

	/**
	 * moves towards the goal
	 * 
	 * @param deltaTime
	 */
	protected void moveToGoal(float deltaTime) {
		if (atGoal()) return;

		//gets the direction we are heading in
		Vector2 dirVec = goal.cpy().sub(pos).norm();
		//computes the amount the object has to move
		Vector2 moveVec = dirVec.mul(speed * deltaTime);

		//moves the object
		pos.add(moveVec);

		//if we reached our goal or we overshot it, sets the position as being the goal
		if (atGoal() || dirVec.dot(goal.cpy().sub(pos).norm()) < 0) pos.set(goal);
	}

	/**
	 * Sets the direction the object tries to turn to
	 * 
	 * @param tryDir
	 */
	public void setTryDir(Direction tryDir) {
		this.tryDir = tryDir;
	}

	/**
	 * gets position in pixels
	 * 
	 * @return
	 */
	public Vector2 getPos() {
		return pos;
	}

	/**
	 * sets maze position
	 * 
	 * @param pos
	 */
	public void setPos(Vector2 pos) {
		this.pos = pos;
	}

	/**
	 * 
	 * @return
	 */
	public Vector2 getGoal() {
		return goal;
	}

	/**
	 * 
	 * @param goal
	 */
	public void setGoal(Vector2 goal) {
		this.goal = goal;
	}

	/**
	 * 
	 * @return
	 */
	public int getHeight() {
		return height;
	}

	/**
	 * 
	 * @return
	 */
	public int getWidth() {
		return width;
	}

	/**
	 * 
	 * @return
	 */
	public int getSpeed() {
		return speed;
	}

	/**
	 * 
	 * @param speed
	 */
	public void setSpeed(int speed) {
		this.speed = speed;
	}

	/**
	 * 
	 * @param dir
	 */
	public void setDir(Direction dir) {
		this.dir = dir;
	}

	/**
	 * 
	 * @return
	 */
	protected Direction getTryDir() {
		return tryDir;
	}
}