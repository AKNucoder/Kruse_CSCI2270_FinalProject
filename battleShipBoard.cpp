#include "BattleShipBoard.h"
#include <iostream>
#include <iomanip> //For printing format of board
using namespace std;

BattleShipBoard::BattleShipBoard(){
	root = new BattleShipNode;
}

BattleShipBoard::~BattleShipBoard(){

}

//Assemble the board size for standard battleship coordinates
void BattleShipBoard::assembleBoard(){
	//Create row of nodes
	BattleShipNode* createNodeRow = root;
	//Create columns of nodes
	BattleShipNode* createNodeCol= root;
	for (int i=0; i<10;i++){
		for (int j=0; j<10; j++){
			createNodeRow->next = new BattleShipNode;
			createNodeRow = createNodeRow->next;
		}
		createNodeCol->child = new BattleShipNode();
		createNodeCol = createNodeCol->child;
		createNodeRow = createNodeCol;
	}
}

//Strike a coordinate with a missile -- also see if it has been hit already
void BattleShipBoard::strike(string coordinate){

}

//Print the board to terminal
void BattleShipBoard::printBoard(){
	//Search row of nodes
	BattleShipNode* searchNodeRow = root;
	//Search column of nodes
	BattleShipNode* searchNodeCol= root;
	char columnLabel = 65;

	for (int i=0; i<10;i++){
		printRowBorder();
		cout << columnLabel++ << " |";

		
		printRow(searchNodeRow);

		searchNodeCol = searchNodeCol->child;
		searchNodeRow = searchNodeCol;
	}
	printRowBorder();
	cout << endl;
}

void BattleShipBoard::printRow(BattleShipNode* _searchNodeRow){
	for (int j=0; j<10; j++){
		if (!_searchNodeRow->struck && !_searchNodeRow->hit){
			cout << setw(6) << "|";
		}
		else if (!_searchNodeRow->hit){
			cout << setw(4) << ":)" << setw(2) << "|";
		}
		else{
			cout << setw(4) << "X" << setw(2) << "|";
		}
		_searchNodeRow = _searchNodeRow->next;
	}

}

//Print borders between rows
void BattleShipBoard::printRowBorder(){
	cout << endl << "  ";
	for (int j =0; j<10; j++){
		cout << setw(6) << "|-----";
	}
	cout << "|" << endl;
}

BattleShipNode* BattleShipBoard::searchCoordinate(int row, int column){
	BattleShipNode* searchNodeRow = root;
	BattleShipNode* searchNodeCol = root;

	for (int i=1; i<row; i++){
		for (int j=1; j<column; j++){
			searchNodeRow = searchNodeRow->next;
		}
		searchNodeCol = searchNodeCol->child;
		if (i!=row-1){
			searchNodeRow = searchNodeCol;
		}
	}
	return searchNodeRow;
}

//Create 5 ships (standard game)
void BattleShipBoard::createShips(){

}