/**
 * Implements a class representing a 2d grid world for simulating a cellular automaton.
 *      - Worlds can be constructed empty, from a size, or from an existing Grid with an initial state for the world.
 *      - Worlds can be resized.
 *      - Worlds can return counts of the alive and dead cells in the current Grid state.
 *      - Worlds can return their current Grid state.
 *
 *      - A World holds two equally sized Grid objects for the current state and next state.
 *          - These buffers are swapped after each update step.
 *
 *      - Stepping a world forward in time applies the rules of Conway's Game of Life.
 *          - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 *      - Worlds have a private helper function used to count the number of alive cells in a 3x3 neighbours
 *        around a given cell.
 *
 *      - Updating the world state can conditionally be performed using a toroidal topology.
 *          - Moving off the left edge you appear on the right edge and vice versa.
 *          - Moving off the top edge you appear on the bottom edge and vice versa.
 *
 * @author 963541
 * @date March, 2020
 */
#include "world.h"

//helper function for returning true modulo (used in torodial location calculation)
int mod(int a, int b) {
	return (a % b + b) % b;
}

/**
 * World::World()
 *
 * Construct an empty world of size 0x0.
 *
 * @example
 *
 *      // Make a 0x0 empty world
 *      World world;
 *
 */

World::World() : World(0) {}

/**
 * World::World(square_size)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x16 world
 *      World x(16);
 *
 *      // Also make a 16x16 world
 *      World y = World(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the world.
 */
World::World(int square_size) : World(square_size,square_size) {}

/**
 * World::World(width, height)
 *
 * Construct a world with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 world
 *      World world(16, 9);
 *
 * @param width
 *      The width of the world.
 * @param height
 *      The height of the world.
 */
 World::World(int width, int height) {
	 Grid worldGrid;
	 Grid nextGrid;
	 worldGrid = Grid(width,height);
	 nextGrid = Grid(width,height);
	 this->currentState = worldGrid;
	 this->nextState = nextGrid;
 }

/**
 * World::World(initial_state)
 *
 * Construct a world using the size and values of an existing grid.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 *      // Make a world by using a grid as an initial state
 *      World world(grid);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      World bad_world = grid; // All around me are familiar faces...
 *
 * @param initial_state
 *      The state of the constructed world.
 */
World::World(Grid initial_state) {
	this->currentState = initial_state;
	this->nextState = initial_state;
}

/**
 * World::get_width()
 *
 * Gets the current width of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << world.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the width of the worlds grid to the console
 *      std::cout << read_only_world.get_width() << std::endl;
 *
 * @return
 *      The width of the world.
 */

 int World::get_width() const {
 	return currentState.get_width();
 }
/**
 * World::get_height()
 *
 * Gets the current height of the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << world.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the height of the worlds grid to the console
 *      std::cout << read_only_world.get_height() << std::endl;
 *
 * @return
 *      The height of the world.
 */
 int World::get_height() const {
 	return currentState.get_height();
 }


/**
 * World::get_total_cells()
 *
 * Gets the total number of cells in the world.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << world.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the total number of cells on the worlds current state grid to the console
 *      std::cout << read_only_world.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
int World::get_total_cells() const {
	return currentState.get_total_cells();
}

/**
 * World::get_alive_cells()
 *
 * Counts how many cells in the world are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << world.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of alive cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
 int World::get_alive_cells() const {
 	return currentState.get_alive_cells();
 }

/**
 * World::get_dead_cells()
 *
 * Counts how many cells in the world are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << world.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the number of dead cells in the worlds current state grid to the console
 *      std::cout << read_only_world.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
 int World::get_dead_cells() const {
 	return currentState.get_dead_cells();
 }

/**
 * World::get_state()
 *
 * Return a read-only reference to the current state
 * The function should be callable from a constant context.
 * The function should not invoke a copy the current state.
 *
 * @example
 *
 *      // Make a world
 *      World world(4, 4);
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << world.get_state() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const World &read_only_world = world;
 *
 *      // Print the current state of the world to the console without copy
 *      std::cout << read_only_world.get_state() << std::endl;
 *
 * @return
 *      A reference to the current state.
 */
	const Grid& World::get_state() const {
		return this->currentState;
	}


/**
 * World::resize(square_size)
 *
 * Resize the current state grid in to the new square width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 8x8
 *      world.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */

	void World::resize(int square_size) {
		resize(square_size, square_size);
	}



/**
 * World::resize(new_width, new_height)
 *
 * Resize the current state grid in to the new width and height.
 *
 * The content of the current state grid should be preserved within the kept region.
 * The values in the next state grid do not need to be preserved, allowing an easy optimization.
 *
 * @example
 *
 *      // Make a grid
 *      World world(4, 4);
 *
 *      // Resize the world to be 2x8
 *      world.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
	void World::resize(int new_width, int new_height) {
		this->currentState.resize(new_width, new_height);
	}

/**
 * World::count_neighbours(x, y, toroidal)
 *
 * Private helper function to count the number of alive neighbours of a cell.
 * The function should not be visible from outside the World class.
 *
 * Neighbours are considered within the 3x3 square centred around the cell at x,y in the current state grid.
 * Ignore the centre coordinate, a cell is not its own neighbour.
 * Attempt to keep the logic as simple, expressive, and readable as possible.
 *
 * If toroidal = false then skip any neighbours that would be outside of the grid,
 * this assumes the grid is Cell::DEAD outside its bounds.
 *
 * If toroidal = true then correctly wrap out of bounds coordinates to the opposite side of the grid.
 *
 * This function is in World and not Grid because the 3x3 sized neighbourhood is specific to Conway's Game of Life,
 * while Grid is more generic to any 2D grid based cellular automaton.
 *
 * @param x
 *      The x coordinate of the centre of the neighbourhood.
 *
 * @param y
 *      The y coordinate of the centre of the neighbourhood.
 *
 * @param toroidal
 *      If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom.
 *
 * @return
 *      Returns the number of alive neighbours.
 */
int World::count_neighbours(int x, int y,bool toroidal) {
	int numNeighbours = 0;
	//applies non torodial rules
	if (toroidal == false) {
		//where it is possible for a neigbouring cell to be alive we check its
		//value and increment neighbours.
		//i.e if we are on left edge we cant check left cell

		//if x > 0 we can check left for neighbour
		if (x > 0) {
			if (this->currentState.get(x-1,y) == ALIVE) {
				numNeighbours++;
			}
		}

		//if x < width we can check right neighbour
		if (x < this->currentState.get_width()-1) {
			if (this->currentState.get(x+1,y) == ALIVE) {
				numNeighbours++;
			}
		}


		//if y > 0 we can check for a top neighbour
		if (y > 0) {
			if (this->currentState.get(x,y-1) == ALIVE) {
				numNeighbours++;
			}
		}

		//if y < height we can check bottom neighbour
		if (y < this->currentState.get_height()-1) {
			if (this->currentState.get(x,y+1) == ALIVE) {
				numNeighbours++;
			}
		}


		//if x >0 and y < height we can check bottom left neighbour
		if (x>0 && y < this->currentState.get_height()-1) {
			if (this->currentState.get(x-1,y+1) == ALIVE) {
				numNeighbours++;
			}
		}

		//if x > width  and y < height we can check bottom right neighbour
		if (x < this->currentState.get_width()-1 && y < this->currentState.get_height()-1) {
			if (this->currentState.get(x+1,y+1) == ALIVE) {
				numNeighbours++;
			}
		}

		//if x > 0  and y > 0 we can check top left neighbour
		if (x > 0 && y > 0) {
			if (this->currentState.get(x-1,y-1) == ALIVE) {
				numNeighbours++;
			}
		}

			//if x <width  and y > 0 we can check top Right neighbour
		if (x < this->currentState.get_width()-1 && y > 0) {
			if (this->currentState.get(x+1,y-1) == ALIVE) {
				numNeighbours++;
			}
		}
		//std::cout << " Num Neighbours = "<< numNeighbours << std::endl;

	} else if(toroidal == true) {
		int width = this->currentState.get_width();
		int height = this->currentState.get_height();

		//uses modulo to ensure we do not read out of bounds
		//i.e loops out of bound read to other end of grid

		//left
		if (this->currentState.get(mod(x-1,width), y) == ALIVE) {
			numNeighbours++;
		}

		//right
		if (this->currentState.get(mod(x+1,width), y) == ALIVE) {
			numNeighbours++;
		}

		//bottom
		if (this->currentState.get(x, mod(y-1,height)) == ALIVE) {
			numNeighbours++;
		}

		//top
		if (this->currentState.get(x, mod(y+1,height)) == ALIVE) {
			numNeighbours++;
		}

		//bottom-left
		if (this->currentState.get(mod(x-1,width), mod(y-1,height)) == ALIVE) {
			numNeighbours++;
		}

		//bottom-right
		if (this->currentState.get(mod(x+1,width), mod(y-1,height)) == ALIVE) {
			numNeighbours++;
		}

		//top-left
		if (this->currentState.get(mod(x-1,width), mod(y+1,height)) == ALIVE) {
			numNeighbours++;
		}

		//top-right
		if (this->currentState.get(mod(x+1,width), mod(y+1,height)) == ALIVE) {
			numNeighbours++;
		}
	}

	return numNeighbours;
}


/**
 * World::step(toroidal)
 *
 * Take one step in Conway's Game of Life.
 *
 * Reads from the current state grid and writes to the next state grid. Then swaps the grids.
 * Should be implemented by invoking World::count_neighbours(x, y, toroidal).
 * Swapping the grids should be done in O(1) constant time, and should not invoke a copy.
 * Try and boil the logic down to the fewest and most simple conditional statements.
 *
 * Rules: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *      - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 *      - Any live cell with two or three live neighbours lives on to the next generation.
 *      - Any live cell with more than three live neighbours dies, as if by overpopulation.
 *      - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */
void World::step(bool toroidal) {
	for (int y = 0; y < this->get_height(); y++) {
		for (int x = 0; x < this->get_width(); x++) {

			//counts number of neighbours of each cell
			int numNeighbours = this->count_neighbours(x,y,toroidal);
			//updates new states grid x,y value depending on number of neighbours
			//underpopulation
			if (this->currentState.get(x,y) == ALIVE && numNeighbours < 2) {
				this->nextState.set(x,y,DEAD);
			}
			//lives on to next generation
			if (this->currentState.get(x,y) == ALIVE && (numNeighbours == 2 || numNeighbours == 3)) {
				this->nextState.set(x,y,ALIVE);
			}

			//overpopulation
			if (this->currentState.get(x,y) == ALIVE && numNeighbours > 3) {
				this->nextState.set(x,y,DEAD);
			}

			//reproduction
			if (this->currentState.get(x,y) == DEAD && numNeighbours == 3) {
				this->nextState.set(x,y,ALIVE);
			}
		}

	}
	//sets currentState to the new state incrementing the game
	this->currentState = this->nextState;
}

/**
 * World::advance(steps, toroidal)
 *
 * Advance multiple steps in the Game of Life.
 * Should be implemented by invoking World::step(toroidal).
 *
 * @param steps
 *      The number of steps to advance the world forward.
 *
 * @param toroidal
 *      Optional parameter. If true then the step will consider the grid as a torus, where the left edge
 *      wraps to the right edge and the top to the bottom. Defaults to false.
 */

 void World::advance(int steps,bool toroidal) {
	 //runs step 'steps' amount of times
	 for (int i = 0; i < steps; i++) {
		 this->step(toroidal);
	 }
 }
