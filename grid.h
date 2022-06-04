/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 963541
 * @date March, 2020
 */
#pragma once

#include <vector>
#include <cmath>
#include <stdio.h>
#include <iostream>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
public:
	Grid();
	Grid(int square_size);
	Grid(int width, int height);

	int get_width() const;
	int get_height() const;

	int get_total_cells() const;
	int get_alive_cells() const;
	int get_dead_cells() const;

	void resize(int square_size);
	void resize(int width, int height);

	const Cell get(unsigned int x, unsigned int y) const;
	void set(unsigned int x, unsigned int y, Cell value);

	Cell& operator()(unsigned int x, unsigned int y);
	const Cell& operator()(unsigned int x, unsigned int y) const;

	Grid crop(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1) const;
	void merge(Grid other, int x0, int y0, bool alive_only = false);

	Grid rotate(int rotation) const;
 	friend std::ostream& operator<<(std::ostream& output_stream, Grid grid);


private:
	int width, height;
	std::vector<std::vector<Cell>> grid;

};
