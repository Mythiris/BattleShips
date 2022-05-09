#pragma once
#include <iostream>
#include <vector>

const int Rows = 10, Cols = 10;

const char ShipSymbol = '1', EmptySymbol = '0', HitSymbol = 'X', MissSymbol = '-';
const int ShipLives = 17;

// Holds X and Y coords.
struct Coord
{
	int x, y;

	// Default constructor.
	Coord() 
	{
		x = -1;
		y = -1;
	}
	Coord(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	// Returns false if the coords are out side the range of provided rows and cols.
	bool InRange()
	{
		if (x > Rows || x < 0 || y > Cols || y < 0)
		{
			std::cout << " Error Out of Range" << std::endl;
			return(false);
		}
		return(true);
	}

	// Allows for the comprasion of two coords.
	bool operator==(const Coord& other) const {
		return x == other.x && y == other.y;
	}
};

// Holds length of ship.
struct Ship
{
	int ShipLength;

	Ship(int _ShipLength)
	{
		ShipLength = _ShipLength;
	}
};
