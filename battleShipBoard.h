//Johnathan Kruse
//CSCI 2270 Final Project
//Instructor Hoenigman
//Terminal Battleship
#ifndef BATTLESHIPBOARD_H
#define BATTLESHIPBOARD_H
//For std namespace
#include <functional>
#include <string>

//Actual battlships, used to record each individual battleship if it has been hit.
struct BattleShip{
	int size; //size of battleship
	int hit;  //Amount of battleship that has been hit.

	//Initialize properties
	BattleShip(){
		size = -1;
		hit = 0;
	};
	BattleShip(int _size, int _hit){
		size = _size;
		hit = _hit;
	};
};

//N-ary tree using linked pointers
struct BattleShipNode{
	BattleShipNode *next;  //rows
	BattleShipNode *child; //column
	BattleShipNode *previous; //column
	bool hitNoDamage;
	bool hitBattleShip;
	std::string test;
	BattleShip *battleShip;

	//Initialize properties to null and false
	BattleShipNode(){
		next = nullptr;
		child = nullptr;
		previous = nullptr;
		hitNoDamage = false;
		hitBattleShip = false;
		battleShip = nullptr;
		test = ":p";
	};
};

class BattleShipBoard{
	public:
		BattleShipBoard();
		~BattleShipBoard();
		//Assemble the board size for standard battleship coordinates, using the n-ary tree data structure
		void assembleBoard();
		//Strike a coordinate with a missile -- if battleship hit, returns true
		bool strike();
		//Print the board to terminal
		void printBoard();
		//Instead of printing what the user has struck, it will print their own board of what their opponent has struck.
		void printMyCurrentBoard();
		//Create 5 ships (standard game)
		void createShips();
		//Retreives column coordinate from user, ensuring correct data value
		int retrieveColumnCoordinate();
		//Retreives row coordinate from user, ensuring correct data value
		int retrieveRowCoordinate();
		//Automatically determines where to place boats.
		void randomizeBoatPositions();
		//Used to pause the screen by asking the user to enter a character to continue.
		void pauseDialog();
		//Used to determine if a player has lost the game and all ships have been sunk.
		bool allShipsSunk();
		//Just moves terminal screeen far down by printing many character returns, so user does not accidentally see the information printed above.
		void clearTerminalScreen();
		//Tells user they won
		void congratsOnWinning(std::string winnerName, std::string loserName);

	private:
		
		//Main node of n-ary tree data structure
		BattleShipNode* root;

		//Prints row/row border and prints battleships that have been sunk (not partially hit).
		void printRow(BattleShipNode* searchNodeRow);
		void printRowBorder(BattleShipNode* _nodeAtBegginingOfRow,int row);
		
		//Prints whole row/row border regardless of it battleships have been sunk or not.
		void printWholeRow(BattleShipNode* searchNodeRow);
		void printWholeRowBorder(BattleShipNode* _nodeAtBegginingOfRow,int row);

		//print column labels.
		void printColumnLabels();

		//Searches for a node, given coordinates, and returns the pointer to the node.
		BattleShipNode* searchCoordinate(int row, int column);
		//Finds a battleship node given coordinates and returns a pointer to the node to delete (there is an extra line of empty nodes to be deleted at the bottom of the graph)
		BattleShipNode* searchCoordinateToDelete(int row, int column);
		
		//Prints boat either as horizontal/vertical
		void printHorizontalBattleShip(BattleShipNode* _searchNodeRow);
		void printVerticalBattleShip(BattleShipNode* _searchNodeRow,int row, int column);
		
		//Checks if boat is either horizontal of vertical
		bool battleShipIsHorizontal(BattleShipNode* _searchNodeRow);
		bool battleShipIsVertical(BattleShipNode* _searchNodeRow, int row, int column);
		
		//Checks if boat is vertical and sunk
		bool battleShipIsVerticalAndSunk(BattleShipNode* _searchNodeRow, int row, int column);

		//Checks if node is a head/tail of a horiz/vertical boat.
		bool isHeadOfHorizBattleShip(BattleShipNode* _searchNodeRow);
		bool isTailOfHorizBattleShip(BattleShipNode* _searchNodeRow);
		bool isHeadOfVerticalBattleShip(BattleShipNode* _searchNodeRow, int row, int column);
		bool isTailOfVerticalBattleShip(BattleShipNode* _searchNodeRow, int row, int column);
		
		//Asks user to manually position baots.
		void positionBoat(BattleShip* _battleShipToPosition);
		
		//Checks if string is an int.
		bool isInt(std::string stringToCheck);
		
		//Assign boat to coordinates
		bool placeBoat(BattleShip* _battleShipToPosition, int row, int column, bool _boatVertical);

		//makes sure there is enough room on board for a battleship to be placed at desired coordinates horz/vert
		bool enoughVerticalRoom(BattleShip* _battleShipToPosition, int row, int column);
		bool enoughHorizontalRoom(BattleShip* _battleShipToPosition, int row, int column);

		//Computer randomly assigns boat positions
		void randomizeBoatPositionsPlaceBoats(BattleShip* _currentBoat);

		//Following functions just output text statements
		void createShipsAircraftCarrierText();
		void createShipsBattleShipText();
		void createShipsSubmarineText();
		void createShipsDestroyerText();
		void createShipsPatrolBoatText();

		//Battleship Boats
		BattleShip* airCraftCarrier; //5 piece vessel
		BattleShip* battleShip;		//4 piece vessel
		BattleShip* submarine;		//3 piece vessel
		BattleShip* destroyer;		//3 piece vessel
		BattleShip* patrolBoat;		//2 piece vessel
};
#endif //BATTLESHIPBOARD_H
