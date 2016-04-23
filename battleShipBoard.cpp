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
	BattleShipNode* previous = new BattleShipNode;

	BattleShip *testShip = new BattleShip(5,5);

	for (int i=0; i<10;i++){
		for (int j=0; j<10; j++){
			createNodeRow->next = new BattleShipNode;
			previous = createNodeRow;
			createNodeRow = createNodeRow->next;
			createNodeRow->previous = previous;

			// /*
			if (i==3 && (j==2 || j==3 || j==4 || j==5 || j==6)){
				createNodeRow->hitBattleShip = true;
				//createNodeRow->battleShip = testShip;
				createNodeRow->battleShip = testShip;
			}
			 // */
		}
		createNodeCol->child = new BattleShipNode();
		previous = createNodeCol;
		createNodeCol = createNodeCol->child;
		createNodeRow = createNodeCol;
		createNodeRow->previous = previous;
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
		if (!_searchNodeRow->hitBattleShip && !_searchNodeRow->hitNoDamage){
			cout << setw(6) << "|";
		}
		else if (_searchNodeRow->hitBattleShip){
			if (_searchNodeRow->battleShip->hit == _searchNodeRow->battleShip->size){
				printHorizontalBattleShip(_searchNodeRow);
			}
			else{
				cout << setw(4) << ":)" << setw(2) << "|";
			}
		}
		else{
			cout << setw(4) << "X" << setw(2) << "|";
		}
		_searchNodeRow = _searchNodeRow->next;
	}

}

//Prints part of a battleship if it is horizontal
void BattleShipBoard::printHorizontalBattleShip(BattleShipNode* _searchNodeRow){
	//If end of battleship
	if (_searchNodeRow->previous!=NULL && _searchNodeRow->previous->battleShip == _searchNodeRow->battleShip && (_searchNodeRow->next!=NULL && _searchNodeRow->next->battleShip != _searchNodeRow->battleShip)){
					cout << setw(4) << "=[ ]>" << setw(1) << "|";
	}
	//Else if head of  battleship
	else if (_searchNodeRow->previous!=NULL && _searchNodeRow->previous->battleShip != _searchNodeRow->battleShip && (_searchNodeRow->next!=NULL && _searchNodeRow->next->battleShip == _searchNodeRow->battleShip)){
		cout << setw(4) << "<[ ]" << setw(1) << "==";
	}
	//Else if a middle piece of battleship.
	else if (_searchNodeRow->next!=NULL && _searchNodeRow->next->battleShip == _searchNodeRow->battleShip){
		cout << setw(4) << "=[ ]" << setw(2) << "==";
	}
}

//Prints part of a battleship if it is horizontal
void BattleShipBoard::printVerticalBattleShip(BattleShipNode* _searchNodeRow){
	//If end of battleship
	if (_searchNodeRow->previous!=NULL && _searchNodeRow->previous->battleShip == _searchNodeRow->battleShip && (_searchNodeRow->next!=NULL && _searchNodeRow->next->battleShip != _searchNodeRow->battleShip)){
					cout << setw(4) << "=[ ]>" << setw(1) << "|";
	}
	//Else if head of  battleship
	else if (_searchNodeRow->previous!=NULL && _searchNodeRow->previous->battleShip != _searchNodeRow->battleShip && (_searchNodeRow->next!=NULL && _searchNodeRow->next->battleShip == _searchNodeRow->battleShip)){
		cout << setw(4) << "<[ ]" << setw(1) << "==";
	}
	//Else if a middle piece of battleship.
	else if (_searchNodeRow->next!=NULL && _searchNodeRow->next->battleShip == _searchNodeRow->battleShip){
		cout << setw(4) << "=[ ]" << setw(2) << "==";
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