#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include<windows.h>

#include "Utils.h"
#include "AI.h"

// Prototypes
void ClearBoard(); // Set all board locations to EmptySymbol
void DisplayBoard(char _Board[Rows][Cols]); // Print board.

void InitShips(); // Add ships to the vector PlayersShips.
void InitGame(); // Check if player wants manually place ships. 

void PlaceShip(); // Take the players input and place ship.
bool AcceptablePlacement(Coord _Start, Coord _End, int _shipSize); // Check if the ship can be placed at the given Coords.

void PlayerAttack(); // Take players input and check agaist the AI's ship locations.
int CurrentShipCount(); // Return current ship lives.

void PlayGame(); // Run the battle ship game.
void ChangeDisplyColor(char _Character); // Change text color.

// Variables 

char PlayerBoard[Rows][Cols];
char EmptyBoard[Rows][Cols];

int AIShipLives = ShipLives;

std::vector<Ship> PlayersShips;
AI _AI;

int main()
{
	// Use current time as seed for random generator.
	std::srand((unsigned int)std::time(nullptr));

	PlayGame();

	system("pause");
	return(0);
}

// Functions

// Set all board locations to EmptySymbol.
void ClearBoard()
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			PlayerBoard[i][j] = EmptySymbol; // Replace current value with emptySymbol.
			EmptyBoard[i][j]  = EmptySymbol; // Replace current value with emptySymbol.
		}
	}
}

// Print board.
void DisplayBoard(char _Board[Rows][Cols])
{
	std::cout << std::endl;
	std::cout << " "; // For even spacing.
	for (int i = 0; i < Cols; i++)
	{
		std::cout << " " << i; // lable cols.
	}
	std::cout << std::endl;
	for (int i = 0; i < Rows; i++)
	{
		std::cout << char(65 + i); // label Rows.
		for (int j = 0; j < Cols; j++)
		{
			ChangeDisplyColor(_Board[i][j]);

			std::cout << " "<< _Board[i][j]; // Print value from board.
		}
		std::cout << std::endl;

		// Ensure text color is set back to deafult.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

// Add ships to the vector PlayersShips.
void InitShips()
{
	PlayersShips.clear(); // Empty the vector.
	PlayersShips.push_back(Ship(2)); // Patrol Boat.
	PlayersShips.push_back(Ship(3)); // Submarine.
	PlayersShips.push_back(Ship(3)); // Destroyer.
	PlayersShips.push_back(Ship(4)); // Battleship.
	PlayersShips.push_back(Ship(5)); // Carrier.

}

// Take the players input and place ship.
void PlaceShip()
{
	char Input[100];
	char* next_token;
	char* Letter, * Number;
	Coord Start, End;
	bool IsShipPlaced;

	DisplayBoard(PlayerBoard);

	for (auto _Ships : PlayersShips)
	{
		IsShipPlaced = false;
		while (IsShipPlaced != true)
		{
			std::cout << " Ship length: " << _Ships.ShipLength << std::endl;
			std::cout << " Input Start Co-ordinate (eg, A-1)" << std::endl;
			std::cin >> Input;

			// Break input using - as the divider.
			Letter = strtok_s(Input, "-", &next_token);
			Number = strtok_s(NULL, "-", &next_token);

			// Change input to the range of 0-9.
			Start.x = *Letter - 65;
			Start.y = *Number - 48;

			std::cout << " Input End Co-ordinate (eg, A-1)" << std::endl;
			std::cin >> Input;

			// Break input using - as the divider.
			Letter = strtok_s(Input, "-", &next_token);
			Number = strtok_s(NULL, "-", &next_token);

			// Change input to the range of 0-9.
			End.x = *Letter - 65;
			End.y = *Number - 49;

			// Check if ship can be placed at the given coords.
			if (AcceptablePlacement(Start, End, _Ships.ShipLength))
			{
				DisplayBoard(PlayerBoard);
				IsShipPlaced = true;
			}
		}
	}
}

// Check if the ship can be placed at the given Coords.
bool AcceptablePlacement(Coord _Start, Coord _End, int _shipSize)
{
	// Check if Coords are in range of rows & cols.
	if (!_Start.InRange()) { return(false); }
	if (!_End.InRange()) { return(false); }

	if (_Start.x > _End.x)
	{
		// Check that the ship is in the same row.
		if (_Start.y != _End.y) { std::cout << "Failed" << std::endl; return(false); }
		// Check if the ship fits.
		if (_Start.x - _shipSize - 1 != _End.x) { std::cout << "Failed" << std::endl; return(false); }

		for (int i = _End.x; i <= _Start.x; i++) // Check if another ship is in the way.
		{
			if (PlayerBoard[i][_End.y] == ShipSymbol) std::cout << "Failed" << std::endl; return(false);
		}

		std::cout << "Accepted" << std::endl;

		// Place Ship.
		for (int i = _End.x; i <= _Start.x; i++)
		{
			PlayerBoard[i][_End.y] = ShipSymbol;
		}
		return(true);
	}
	else if (_Start.y > _End.y)
	{
		// Check that the ship is in the same col.
		if (_Start.x != _End.x) { std::cout << "Failed" << std::endl; return(false); }
		// Check if the ship fits.
		if (_Start.y - _shipSize - 1 != _End.y) { std::cout << "Failed" << std::endl; return(false); }

		for (int i = _End.y; i <= _Start.y; i++) // Check if another ship is in the way.
		{
			if (PlayerBoard[i][_End.y] == ShipSymbol) std::cout << "Failed" << std::endl; return(false);
		}

		std::cout << "Accepted" << std::endl;

		// Place Ship.
		for (int i = _End.y; i <= _Start.y; i++)
		{
			PlayerBoard[i][_End.y] = ShipSymbol;
		}
		return(true);
	}
	else if (_Start.x < _End.x)
	{
		// Check that the ship is in the same row.
		if (_Start.y != _End.y) { std::cout << "Failed" << std::endl; return(false); }
		// Check if the ship fits.
		if (_Start.x + _shipSize - 1 != _End.x) { std::cout << "Failed" << std::endl; return(false); }

		for (int i = _End.x; i <= _Start.x; i++) // Check if another ship is in the way.
		{
			if (PlayerBoard[i][_End.y] == ShipSymbol) std::cout << "Failed" << std::endl; return(false);
		}

		std::cout << "Accepted" << std::endl;

		// Place Ship.
		for (int i = _End.x; i <= _Start.x; i++)
		{
			PlayerBoard[i][_End.y] = ShipSymbol;
		}
		return(true);
	}
	else if (_Start.y < _End.y)
	{
		// Check that the ship is in the same col.
		if (_Start.x != _End.x) { std::cout << "Failed" << std::endl; return(false); }
		// Check if the ship fits.
		if (_Start.y + _shipSize - 1 != _End.y) { std::cout << "Failed" << std::endl; return(false); }

		for (int i = _End.y; i <= _Start.y; i++) // Check if another ship is in the way.
		{
			if (PlayerBoard[i][_End.y] == ShipSymbol) std::cout << "Failed" << std::endl; return(false);
		}

		std::cout << "Accepted" << std::endl;

		// Place Ship.
		for (int i = _End.y; i <= _Start.y; i++)
		{
			PlayerBoard[i][_End.y] = ShipSymbol;
		}
		return(true);
	}
	return(false);
}

// Take players input and check agaist the AI's ship locations.
void PlayerAttack()
{
	char Input[100];
	char* next_token;
	char* Letter, * Number;
	Coord Target;

	std::cout << std::endl << std::endl;
	DisplayBoard(EmptyBoard);

	std::cout << " Enter Co-ordinate to fire at (eg, A-1)" << std::endl;

	std::cin >> Input;
	std::cout << std::endl;

	// Break input using - as the divider.
	Letter = strtok_s(Input, "-", &next_token);
	Number = strtok_s(NULL, "-", &next_token);

	// Change input to the range of 0-9.
	Target.x = *Letter - 65;
	Target.y = *Number - 48;

	if (_AI.IsHit(Target) == true)
	{
		EmptyBoard[Target.x][Target.y] = HitSymbol;
		AIShipLives--; // Remove one life from totalShips lives.
		std::cout << " Target Hit " << std::endl;
	}
	else
	{
		EmptyBoard[Target.x][Target.y] = MissSymbol;
		std::cout << " Target Missed " << std::endl;
	}

	DisplayBoard(EmptyBoard);
}

// Check if player wants manually place ships. 
void InitGame()
{
	bool AcceptableInput = false;

	InitShips();
	ClearBoard();

	while (AcceptableInput != true)
	{
		int Input;
		std::cout << " Welcome to BattleShips" << std::endl << std::endl;
		std::cout << " 1) Manually Palce Ships" << std::endl;
		std::cout << " 2) Random Ship placement" << std::endl;
		std::cout << " 3) Quit" << std::endl;
		std::cin >> Input;

		switch (Input)
		{
		case 1: // Manually Palce Ships.
		{
			PlaceShip();
			AcceptableInput = true;
			break;
		}
		case 2: // Random Ship placement.
		{
			_AI.RandomShipPlacement(PlayerBoard, PlayersShips);
			AcceptableInput = true;
			break;
		}
		case 3: // Quit.
		{
			AcceptableInput = true;
			exit(0);
			break;
		}
		default:
			break;
		}
	}
}

// Return current ship lives.
int CurrentShipCount()
{
	int itter = 0;
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			if (PlayerBoard[i][j] == ShipSymbol)
			{
				itter++;
			}
		}
	}

	return(itter);
}

// Run the battle ship game.
void PlayGame()
{
	bool IsGameOver = false;

	InitGame();

	while (IsGameOver != true)
	{
		PlayerAttack();

		std::cout << std::endl << " AI's Turn " << std::endl;

		Sleep(3000); // Delay so the player can read their board.

		_AI.AIAttack(PlayersShips, PlayerBoard);
		DisplayBoard(PlayerBoard);

		if (_AI.CurrentShipCount() <= 0)
		{
			std::cout << " Game Over " << std::endl;
			std::cout << " AI Has Won " << std::endl;
		}
		else if (CurrentShipCount() <= 0)
		{
			std::cout << " Game Over " << std::endl;
			std::cout << " You Have Won " << std::endl;
		}

	}
}

// Change text color.
void ChangeDisplyColor(char _Character)
{
	switch (_Character)
	{
	case ShipSymbol:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); // Green.
		break;
	case HitSymbol:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Red.
		break;
	case MissSymbol:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // Yellow.
		break;
	default:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // White.
		break;
	}
}