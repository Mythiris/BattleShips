#pragma once
#include "Utils.h"
#include <windows.h>
#include<conio.h>

class AI
{
public:

	// Init AI Ships and board.
	AI();

	// loops through all ships that need to be placed.
	void RandomShipPlacement(char _Board[Rows][Cols], std::vector<Ship> _ShipsVector);
	// Randomly choose a co-ord and check if its a hit.
	void AIAttack(std::vector<Ship> _TargetShips, char _Board[Rows][Cols]);
	// Returns true it the AI ships have been hit.
	bool IsHit(Coord _Coord);

	// Returns the currrent amount of Ship Symbols left.
	int CurrentShipCount();

private:

	//	Holds the location of the AI's ships.
	char AIBoard[Rows][Cols];
	// vector of the AI's ships.
	std::vector<Ship> AIShips;

	// Returns true if the ship has been placed.
	bool AICheckShipPlacement(Ship _Ship, char _Board[Rows][Cols]);
};

