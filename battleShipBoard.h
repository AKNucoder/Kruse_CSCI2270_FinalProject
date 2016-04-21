#ifndef BATTLESHIPBOARD_H
#define BATTLESHIPBOARD_H
//For std namespace
#include <functional>

//Actual battlships, used to record each individual battleship if it has been hit.
struct BattleShip{
	int size; //size of battleship
	int hit;  //Amount of battleship that has been hit.

	//Initialize properties to 0
	BattleShip(){
		size = 0;
		hit = 0;
	};
};

//N-array tree using linked pointers
struct BattleShipNode{
	BattleShipNode *next;  //rows
	BattleShipNode *child; //column
	bool struck;
	bool hit;
	BattleShip *battleShip;

	//Initialize properties to null and false
	BattleShipNode(){
		next = nullptr;
		child = nullptr;
		struck = false;
		hit = false;
		battleShip = nullptr;
	};
};

class BattleShipBoard{
	public:
		BattleShipBoard();
		~BattleShipBoard();
		//Assemble the board size for standard battleship coordinates
		void assembleBoard();
		//Strike a coordinate with a missile -- also see if it has been hit already
		void strike(std::string coordinate);
		//Print the board to terminal
		void printBoard();
		//Create 5 ships (standard game)
		void createShips();
	
	private:
		BattleShipNode* root;
		void printRow(BattleShipNode* searchNodeRow);
		void printRowBorder();
		BattleShipNode* searchCoordinate(int row, int column);
};
#endif //BATTLESHIPBOARD_H
