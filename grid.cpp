/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 963541
 * @date March, 2020
 */

#include "grid.h"

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */
Grid::Grid() : Grid(0) {}


/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(int square_size) : Grid(square_size,square_size) {}


/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
Grid::Grid(int width, int height) {
	this->width = width;
	this->height = height;
	//storing grid as a 2d vector of Cells
	this->grid = std::vector<std::vector<Cell>>(width,std::vector<Cell>(height, DEAD));
}


/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */
int Grid::get_width() const {
	return this->width;
}


/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */
int Grid::get_height() const {
	return this->height;
}


/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
int Grid::get_total_cells() const {
	return (this->get_width() * this->get_height());
}


/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
int Grid::get_alive_cells() const {
	int counter = 0;
	//loop through cells count alive
	for (int x = 0; x < this->get_width(); x++) {
		for (int y = 0; y < this->get_height(); y++) {
			if (this->grid[x][y] == ALIVE) {
				counter++;
			}
		}
	}
	return counter;
 }


/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
 int Grid::get_dead_cells() const {
 	int counter = 0;
	//loop through cells counts dead
 	for (int x = 0; x < this->get_width(); x++) {
 		for (int y = 0; y < this->get_height(); y++) {
 			if (this->grid[x][y] == DEAD) {
 				counter++;
 			}
 		}
 	}

	return counter;
}


/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void Grid::resize(int square_size) {
	resize(square_size, square_size);
}


/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void Grid::resize(int width, int height) {
	//creates temp grid of size parameter and sets all cells to dead.
	std::vector<std::vector<Cell>> gridTemp(width, std::vector<Cell>(height, DEAD));

	//figure out where to stop copying from old grid.
	int stopWidth = std::min(width, this->get_width());
	int stopHeight = std::min(height, this->get_height());

	this->width = width;
	this->height = height;

	for (int x = 0; x < stopWidth; x++) {
		for (int y = 0; y < stopHeight; y++) {
			//copies original grid to new grid.
			gridTemp[x][y] = this->grid[x][y];
		}
	}

	this->grid = gridTemp;
}


/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */
// NOTE: Not applicable


/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
const Cell Grid::get(unsigned int x, unsigned int y) const {
	//catches invalid coordinates
	if (x >= this->grid.size() || y >= this->grid[0].size()) {
		throw std::invalid_argument("Invalid grid location.\n");
	}

	return this->grid[x][y];
}


/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
void Grid::set(unsigned int x, unsigned int y, Cell value) {
	if (x >= this->grid.size() || y >= this->grid[0].size()) {
		throw std::invalid_argument("Invalid grid location.\n");
	}

	this->grid[x][y] = value;
}


/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell& Grid::operator()(unsigned int x, unsigned int y) {
	if (x >= this->grid.size() || y >= this->grid[0].size()) {
		throw std::invalid_argument("Invalid grid location.\n");
	}

	return this->grid[x][y];
}


/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
const Cell& Grid::operator()(unsigned int x, unsigned int y) const {
	if (x >= this->grid.size() || y >= this->grid[0].size()) {
		throw std::invalid_argument("Invalid grid location.\n");
	}

	return this->grid[x][y];
}


/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */

Grid Grid::crop(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) const {
	if (x0 > this->get_width() ||  y0 > this->get_height() || x1 >  this->get_width()||  y1 >  this->get_height()) {
		throw std::invalid_argument("Coordinates outside of grid bounds.\n");
	}
	if(x0 < 0 || x1 < 0 || y0 < 0 || y1 < 0) {
		throw std::invalid_argument("Coordinates outside of grid bounds.\n");
	}

	if (x0 > x1) {
		throw std::invalid_argument("x0 cannot be greater than x1.\n");
	}

	if (y0 > y1) {
		throw std::invalid_argument("y0 cannot be greater than y1.\n");
	}
	//creates a new grid with the desired size of cropped grid
	Grid croppedGrid(x1-x0, y1-y0);

	for (unsigned int x = x0; x < x1; x++) {
		for (unsigned int y = y0; y < y1; y++) {
			//loop through cropped grid setting values of old grid
			croppedGrid(x - x0, y - y0) = this->grid[x][y];
		}
	}

	return croppedGrid;

}


/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge region to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */

void Grid::merge(Grid other,  int x0, int y0, bool alive_only) {

	if (x0<0 || y0 < 0) {
		throw std::invalid_argument("x0 and y0 must be greater than 0.\n");
	}

	if(x0 + other.get_width() > this->get_width() || y0 + other.get_height() > this->get_height()) {
		throw std::invalid_argument("Other grid being placed does not fit within the bounds of the current grid.\n");
	}

	if (alive_only == true) {
		//merge grid from beginning of other grid
		for (unsigned int x = x0; x < other.get_width() + x0; x++) {
			for (unsigned int y = y0; y < other.get_height() + y0; y++) {
				//does not overwrite alive cells in old grid
				if (this->grid[x][y] == DEAD) {
					this->grid[x][y] = other.grid[x - x0][y - y0];
				}
			}
		}
	} else {
		for (unsigned int x = x0; x < other.get_width() + x0; x++) {
			for (unsigned int y = y0; y < other.get_height() + y0; y++) {
					//overwrites all values
					this->grid[x][y] = other.grid[x - x0][y - y0];
			}
		}
	}

}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
// Grid Grid::rotate(int rotation) const {
// 	Grid tempGrid;
// 	if (rotation = 0) {
// 		printf("0");
// 	} else if (rotation > 0) {
// 		for (int i = 0; i < rotation; i++) {
// 			Grid iterGrid;
// 			if (i % 2 != 0) {
// 				iterGrid = Grid(this->get_height(), this->get_width());
// 			} else {
// 				iterGrid = Grid(this->get_width(), this->get_height());
// 			}
//
// 			for (int x = 0; x < this->get_width(); x++) {
// 				for (int y = 0; y < this->get_height(); y++) {
// 					printf("(%d, %d) -> (%d, %d)\n", x, y, tempGrid.get_width() - 1 - y, x);
// 					iterGrid(iterGrid.get_width() - y, x) = this->get(x, y);
// 				}
// 			}
// 		}
// 	}
// return tempGrid;
// }
// Grid Grid::rotate(int rotation) const {
// 	Grid tempGrid = * this;
// 	if (rotation <= 0) {
// 		return *this;
// 	}
// 	Grid iterGrid;
//
//
// 	for (int i = 0; i < rotation; i++) {
//
// 		if (i % 2 != 0) {
// 			iterGrid = Grid(this->get_height(), this->get_width());
// 		} else {
// 			iterGrid = Grid(this->get_width(), this->get_height());
// 		}
//
//
// 		for (int x = 0; x < iterGrid.get_width(); x++) {
// 			for (int y = 0; y < iterGrid.get_height(); y++) {
// 				iterGrid(x,y) = tempGrid.get(y, tempGrid.get_width() );
// 			}
// 		}
//
// 		tempGrid = iterGrid;
// 	}
// 	return tempGrid;
// }

/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */

 std::ostream& operator<<(std::ostream& output_stream, Grid grid) {
	 //first padding char
	 output_stream << "+";
	 for (int i =0; i < grid.get_width(); i++) {
		 output_stream << "-";
	 }
	 output_stream << "+\n";
	 //last padding car
	 //loops through each coord of the grid, adds corresponding
	 // char to output_stream depending on cell status
	 for (int y = 0;y <  grid.get_height(); y ++) {
		 //adds border to beginning of each line
		 output_stream << "|";
		 for (int x = 0;x <  grid.get_width(); x ++) {
			 //determines cell status
			 if (grid.get(x,y) == ALIVE) {
				 output_stream << "#";
			 } else {
				 output_stream << ' ';
			 }
		 }
		  //adds border to end of each line
		 output_stream << "|\n";
	}
	//end border
	output_stream << "+";
	for (int i =0; i < grid.get_width(); i++) {
		output_stream << "-";
	}
	output_stream << "+\n";
	return output_stream;
 }
