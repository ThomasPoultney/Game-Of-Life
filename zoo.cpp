/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 963541
 * @date March, 2020
 */
#include "zoo.h"

// int main(int argc, char const *argv[]) {
// 	Grid grid(6);
// 	grid.set(2, 1, Cell::ALIVE);
// 	grid.set(3, 2, Cell::ALIVE);
// 	grid.set(1, 3, Cell::ALIVE);
// 	grid.set(2, 3, Cell::ALIVE);
// 	grid.set(3, 3, Cell::ALIVE);
// 	Zoo::save_binary("test.bgol", grid);
//
// 	grid = Zoo::load_binary("test.bgol");
//
// 	return 0;
// }

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider() {
 	Grid grid(3, 3);
 	grid.set(0, 2, ALIVE);
	grid.set(1, 2, ALIVE);
	grid.set(2, 2, ALIVE);
	grid.set(2, 1, ALIVE);
	grid.set(1, 0, ALIVE);

	return grid;

}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */

 Grid Zoo::r_pentomino() {
  	Grid grid(3, 3);
	//hard_code values for pentomino
  	grid.set(1, 0, ALIVE);
 	grid.set(2, 0, ALIVE);
 	grid.set(0, 1, ALIVE);
 	grid.set(1, 1, ALIVE);
 	grid.set(1, 2, ALIVE);

 	return grid;

 }

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */

 Grid Zoo::light_weight_spaceship() {
    Grid grid(5, 4);
	//hard_code values for light_weight_spaceship
    grid.set(1, 0, ALIVE);
    grid.set(4, 0, ALIVE);
    grid.set(0, 1, ALIVE);
    grid.set(0, 2, ALIVE);
    grid.set(4, 2, ALIVE);
	grid.set(0, 3, ALIVE);
    grid.set(1, 3, ALIVE);
    grid.set(2, 3, ALIVE);
    grid.set(3, 3, ALIVE);

    return grid;

 }

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */

Grid Zoo::load_ascii(std::string path) {
	std::ifstream inputFile;
	inputFile.exceptions (std::ifstream::badbit);
	Grid parsedGrid;
	try {
    	inputFile.open(path);
		char widthChar;
		char heightChar;
		//first get width and height chars
		widthChar = inputFile.get();
		inputFile.get();
		heightChar = inputFile.get();


    	// while (!inputFile.eof()) {
		// 	std::string line;
		//
		// 	getline(inputFile,line);
		//  	std::cout << line << '\n';
		//
		//  }
		char buffer;
		//converts width char from ascii to actual int value
		int width = (int)widthChar - (int)'0' ;
		int height = (int)heightChar - (int)'0';

		if (width < 0 || height < 0) {
			//invalid coords.
			throw std::runtime_error("invalid width or height (<0)");
		}
		inputFile.get();
		//make grid correct size
 	 	parsedGrid.resize(width, height);

		for(int y = 0; y < height; y++) {
			for(int x = 0; x < width; x++) {
				buffer = inputFile.get();
				//for each coord in grid retrieve value from text file
				if (buffer == '#') {
					//set cell to correct state
					parsedGrid.set(x,y,ALIVE);
				} else if ( buffer == ' ')  {
					//a bit redundant but makes code clearer
					parsedGrid.set(x,y,DEAD);
				} else {
					// throws exception if any other char is present
					throw std::runtime_error("invalid cell status/char");
				}
			}

			buffer =inputFile.get();
			//if buffer is not a line width is set incorrectly.
			if (buffer != '\n') {
				throw std::runtime_error("invalid charecter at end of line should be \n");
			}
		}

		 inputFile.close();

  		}
  	catch (std::ifstream::failure e) {
    	std::cerr << "Exception opening/reading/closing file\n";
  	}
	return parsedGrid;



}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

void Zoo::save_ascii(std::string path,Grid grid) {
	 std::ofstream writefile(path);
	 if (writefile.fail()) {
		 throw std::runtime_error("failed to open output file");

	 }

	//writes height and width of grid to file
	 writefile<< grid.get_width() << " " << grid.get_height() << '\n';

	 for(int y = 0; y < grid.get_height(); y++) {
		 for(int x = 0; x < grid.get_height(); x++) {
			 //loop through grid adding cell value to file.
			 if (grid.get(x,y) == ALIVE) {
				 writefile << "#";
			 } else if (grid.get(x,y) == DEAD) {
				 writefile << " ";
			 }
		 }
		 writefile << '\n';
	 }

	 writefile.close();
}

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */

Grid Zoo::load_binary(std::string path) {
	int width, height;
	Grid loadGrid;

	std::ifstream inputFile(path.c_str(), std::ios::in | std::ios::binary);
	if (!inputFile) {
		throw std::runtime_error("Failed to open binary file.");
	}

	try {
		//read in height and width from file and create blank grid of that size
		inputFile.read((char*)&width, sizeof(int));
		inputFile.read((char*)&height, sizeof(int));
		loadGrid = Grid(width, height);

		//read in bytes from binary file.
		int numBytes = ((height*width)+((height*width)%8))/8;
		unsigned char cellBytes[numBytes] = {0};
		inputFile.read((char*)&cellBytes, sizeof(char)*numBytes);

		//convert bytes array to cells and add to grid.
		for (int i = 0; i < numBytes; i++) {
			for (int j = 0; j < 8; j++) {
				//check if we have run out of bits
				int curBit = i*8 + j;
				if (curBit >= height*width) {
					break;
				}
				//calculate 2D grid location from current bit number(1D)
				int x = (curBit%width);
				int y = (int)curBit/(width);

				if (cellBytes[i] & (1 << j)) {
					loadGrid.set(x, y, Cell::ALIVE);
				}

			}
		}
	} catch (std::exception e) {
		throw std::runtime_error("Failed to read from binary file (incorrect format?).");
	}

	inputFile.close();

	return loadGrid;
}


/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

 void Zoo::save_binary(std::string path, Grid grid) {
	//open/create the file to be written to
	std::ofstream outputFile (path, std::ios::out | std::ios::binary);
	if (!outputFile.is_open()) {
		throw std::runtime_error("Failed to open output file.");
	}

	//get grid width and height
	int width = grid.get_width();
	int height = grid.get_height();

	//explicitly creating byte array for first the height and width integers
	unsigned char headBytes[sizeof(int)*2];
	headBytes[0] = (char)(width  << 0);
	headBytes[1] = (char)(width  << 8);
	headBytes[2] = (char)(width  << 16);
	headBytes[3] = (char)(width  << 24);
	headBytes[4] = (char)(height << 0);
	headBytes[5] = (char)(height << 8);
	headBytes[6] = (char)(height << 16);
	headBytes[7] = (char)(height << 24);

	//initialise the correct byte size for the grid
	int numBytes = ((height*width)+((height*width)%8))/8;
	unsigned char gridBytes[numBytes] = {0};

	//assign values to the grid bytes
	for (int i = 0; i < numBytes; i++) {
		for (int j = 0; j < 8; j++) {
			// Check if we have finished writing headBytes
			int curBit = i*8 + j;
			if (curBit >= height*width) {
				break;
			}

			//Calculate the 2d grid location of the next bit to be written
			int x = curBit%width;
			int y = (int)curBit/width;

			//0010 0110
			//|
			//0100 0000
			//0110 0110

			//If it's an alive cell, assign the bit as 1
			if (grid(x, y) == Cell::ALIVE) {
				gridBytes[i] = gridBytes[i] | (1 << j);
			}
		}
	}

	//Write to file
	outputFile.write((char*)&headBytes, sizeof(int)*2);
	outputFile.write((char*)&gridBytes, sizeof(char)*numBytes);
 }
