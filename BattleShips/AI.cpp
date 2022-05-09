#include "AI.h"
#include <ctime>

// Init AI Ships and board.
AI::AI()
{

	for (int i = 5; i >= 2; i--)
	{
		AIShips.push_back(Ship(i));
	}
	// For extra ship.
	AIShips.push_back(Ship(3));

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Rows; j++)
		{
			AIBoard[i][j] = EmptySymbol;
		}
	}

	RandomShipPlacement(AIBoard, AIShips);
}

// loops through all ships that need to be placed.
void AI::RandomShipPlacement(char _Board[Rows][Cols], std::vector<Ship> _ShipsVector)
{
	bool ShipPlaced;

	for (auto& _Ship : _ShipsVector)
	{
		ShipPlaced = false;
		while (ShipPlaced != true)
		{
			ShipPlaced = AICheckShipPlacement(_Ship, _Board);
		}
	}
}

// Returns true if the ship has been placed.
bool AI::AICheckShipPlacement(Ship _Ship, char _Board[Rows][Cols])
{
	int x = std::rand() % (Rows - 2) + 1;	//Get random x-coordinate, not from map edges.
	int y = std::rand() % (Cols - 2) + 1;	//Get random y-coordinate, not from map edges.
	bool Dir = std::rand() % 2;
	int Shiplength = _Ship.ShipLength - 1; // Shiplength - 1 as the fist point is 1.

	if (Dir) // Vert
	{
		for (int i = 0; i <= Shiplength; i++)
		{
			if (_Board[x + i][y] != EmptySymbol || (x + i) > Rows - 1) { return(false); } // Rows - 1 as the count starts a 0 not 1.
			if (i == Shiplength)
			{
				for (int j = 0; j <= Shiplength; j++)
				{
					_Board[x + j][y] = ShipSymbol; // Place ship.
				}
				return(true);
			}
		}
	}
	else // Hoz
	{
		for (int i = 0; i <= Shiplength; i++)
		{
			if (_Board[x][y + i] != EmptySymbol || (y + i) > Cols - 1) { return(false); } // Cols - 1 as the count starts a 0 not 1.
			if (i == Shiplength)
			{
				for (int j = 0; j <= Shiplength; j++)
				{
					_Board[x][y + j] = ShipSymbol; // Place ship.
				}
				return(true);
			}
		}
	}
	return(false);
}

// Randomly choose a co-ord and check if its a hit.
void AI::AIAttack(std::vector<Ship> _TargetShips, char _Board[Rows][Cols])
{
	bool hit = false;
	int x, y;

	while (hit != true) // loop until either a ship or empty place has been choosen.
	{

		x = rand() % Rows;
		y = rand() % Cols;

		if (_Board[x][y] == EmptySymbol)
		{
			_Board[x][y] = MissSymbol;
			std::cout << " AI Missed " << std::endl;
			hit = true;

		}
		else if (_Board[x][y] == ShipSymbol)
		{
			_Board[x][y] = HitSymbol;
			std::cout << " AI Hit " << std::endl;
			hit = true;
		}
	}
}

// Returns true it the AI ships have been hit.
bool AI::IsHit(Coord _Coord)
{
	if (AIBoard[_Coord.x][_Coord.y] == ShipSymbol)
	{
		return(true);
	}

	return(false);
}

// Returns the currrent amount of Ship Symbols left.
int AI::CurrentShipCount()
{
	int itter = 0;
	for (int i = 0; i <= Rows; i++)
	{
		for (int j = 0; j <= Cols; j++)
		{
			if (AIBoard[i][j] == ShipSymbol)
			{
				itter++;
			}
		}
	}

	return(itter);
}