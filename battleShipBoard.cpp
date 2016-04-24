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

	BattleShip *testShipHoriz = new BattleShip(5,5);
	BattleShip *testShipVertical = new BattleShip(5,5);

	//i<=10 to have a null row of battleships at bottom, for printing purposes.
	for (int i=0; i<=10;i++){
		for (int j=0; j<10; j++){
			createNodeRow->next = new BattleShipNode;
			previous = createNodeRow;

			///*
			if (i==3 && (j==2 || j==3 || j==4 || j==5 || j==6)){
				createNodeRow->hitBattleShip = true;
				//createNodeRow->battleShip = testShip;
				createNodeRow->battleShip = testShipHoriz;
			}
			 //*/

			if (j==3 && (i==7 || i==8 || i==9)){
				createNodeRow->hitBattleShip = true;
				//createNodeRow->battleShip = testShip;
				createNodeRow->battleShip = testShipVertical;
				createNodeRow->test = ":0";
			}

			createNodeRow = createNodeRow->next;
			createNodeRow->previous = previous;
			
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

	//i<=10 to make sure if there is a battleship touching this edge, it will be printed.
	for (int i=0; i<=10;i++){
		printRowBorder(searchNodeRow, i);
		
		if (i<10){
			cout << columnLabel++ << " |";

			printRow(searchNodeRow);

			searchNodeCol = searchNodeCol->child;
			searchNodeRow = searchNodeCol;
		}
	}
	cout << endl;
}

//Print borders between rows
void BattleShipBoard::printRowBorder(BattleShipNode* _nodeAtBegginingOfRow, int row){
	//Search row of nodes
	BattleShipNode* searchNodeRow = _nodeAtBegginingOfRow;
	cout << endl << "  ";
	for (int j =0; j<10; j++){
		//If the last edge of the board or a battleship exists at this location and it has been discovered (completely hit).
		if (row==10 || (searchNodeRow!=NULL && searchNodeRow->battleShip!=NULL && searchNodeRow->battleShip->size == searchNodeRow->battleShip->hit && !battleShipIsHorizontal(searchNodeRow))){
			printVerticalBattleShip(searchNodeRow,row,j);
		}
		else {
			cout << setw(6) << "|-----";
		}
		searchNodeRow = searchNodeRow->next;
	}
	cout << "|" << endl;
}

void BattleShipBoard::printRow(BattleShipNode* _searchNodeRow){
	for (int j=0; j<10; j++){
		if ((!_searchNodeRow->hitBattleShip && !_searchNodeRow->hitNoDamage)){
			cout << setw(6) << "|";
			//cout << setw(5) << _searchNodeRow->test << "|";
		}
		else if (_searchNodeRow->hitBattleShip){
			if (_searchNodeRow->battleShip->hit == _searchNodeRow->battleShip->size){
				
				if (battleShipIsHorizontal(_searchNodeRow)){
					printHorizontalBattleShip(_searchNodeRow);
				}
				else{
					cout << setw(4) << "[ ]" << setw(2) << "|";
				}
			}
			else{
				cout << setw(4) << "O" << setw(2) << "|";
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
	//If tail of battleship
	if (isTailOfHorizBattleShip(_searchNodeRow)){
		cout << setw(4) << "=[ ]>" << setw(1) << "|";
	}
	//Else if head of  battleship
	else if (isHeadOfHorizBattleShip(_searchNodeRow)){
		cout << setw(4) << "<[ ]" << setw(1) << "==";
	}
	//Else if a middle piece of battleship.
	else {
		cout << setw(4) << "=[ ]" << setw(2) << "==";
	}
}

//Prints part of a battleship if it is vertical
void BattleShipBoard::printVerticalBattleShip(BattleShipNode* _searchNodeRow,int row, int column){
	//If tail of battleship
	if (isTailOfVerticalBattleShip(_searchNodeRow,row,column)){
		cout << setw(6) << "|--v--";
	}
	//Else if head of  battleship
	else if (isHeadOfVerticalBattleShip(_searchNodeRow,row,column)){
		cout << setw(6) << "|--^--";
	}
	//Else if bottom edge of battleship board
	else if (row==10){
		cout << setw(6) << "|-----";
	}
	//Else if a middle piece of battleship.
	else{
		cout << setw(6) << "|-|||-";
	}
}

//Returns yes, if a node is the head of a battleship
bool BattleShipBoard::isHeadOfHorizBattleShip(BattleShipNode* _searchNodeRow){
	//Two-line if statement, if previous is not part of the battleship, but next is, then it is a head.
	if ( ((_searchNodeRow->previous!=NULL && _searchNodeRow->previous->battleShip != _searchNodeRow->battleShip) || (_searchNodeRow->previous==NULL))
	    && (_searchNodeRow->next!=NULL && _searchNodeRow->next->battleShip == _searchNodeRow->battleShip)){
		return true;
	}
	else{
		return false;
	}
}

//Return Yes, if a node is the tail of a battleship.
bool BattleShipBoard::isTailOfHorizBattleShip(BattleShipNode* _searchNodeRow){
	//Two-line if statement, if next is not part of the battleship, but previous is, then it is a tail.
	if ( ((_searchNodeRow->next!=NULL && _searchNodeRow->next->battleShip != _searchNodeRow->battleShip) || (_searchNodeRow->next==NULL))
	    && (_searchNodeRow->previous!=NULL && _searchNodeRow->previous->battleShip == _searchNodeRow->battleShip)){
		return true;
	}
	else{
		return false;
	}
}

//Returns yes, if a node is the head of a battleship
bool BattleShipBoard::isHeadOfVerticalBattleShip(BattleShipNode* _searchNodeRow,int row, int column){
	BattleShipNode* battleShipAbove = searchCoordinate(row-1,column);
	BattleShipNode* battleShipBelow = searchCoordinate(row+1,column);
	
	//Two-line if statement, if above node is not part of the battleship, but the node below is, then it is a head.
	if ( ((battleShipAbove!=NULL && _searchNodeRow->battleShip != battleShipAbove->battleShip) || battleShipAbove==NULL)
		&& (battleShipBelow!=NULL && _searchNodeRow->battleShip == battleShipBelow->battleShip && _searchNodeRow->battleShip!=NULL) ){
		return true;
	}
	else {
		return false;
	}
}

//Return Yes, if a node is the tail of a battleship.
bool BattleShipBoard::isTailOfVerticalBattleShip(BattleShipNode* _searchNodeRow,int row, int column){
	BattleShipNode* battleShipAbove = searchCoordinate(row-1,column);
	BattleShipNode* battleShipTwoRowsAbove = searchCoordinate(row-2,column);
	//BattleShipNode* battleShipBelow = searchCoordinate(row+1,column);

	//Two-line if statement, if the node is not part of the above node which is the same battleship as the node above that, then it is a tail.
	if (battleShipTwoRowsAbove!=NULL && battleShipAbove!=NULL && battleShipTwoRowsAbove->battleShip!=NULL && battleShipAbove->battleShip == battleShipTwoRowsAbove->battleShip
		&& _searchNodeRow->battleShip != battleShipAbove->battleShip){	
		return true;
	}
	else {
		return false;
	}
}

//Returns yes if a battleship is horzonal, or false if vertical
bool BattleShipBoard::battleShipIsHorizontal(BattleShipNode* _searchNodeRow){
	bool isHorizontal = false;

	if (_searchNodeRow->next != NULL && _searchNodeRow->battleShip == _searchNodeRow->next->battleShip){
		isHorizontal = true;
	}
	else if (_searchNodeRow->previous != NULL && _searchNodeRow->battleShip == _searchNodeRow->previous->battleShip){
		isHorizontal = true;
	}
	return isHorizontal;
}

BattleShipNode* BattleShipBoard::searchCoordinate(int row, int column){
	BattleShipNode* searchNodeRow = root;
	BattleShipNode* searchNodeCol = root;
	if (0<=row && row<10 && 0<=column && column<10){
		for (int i=0; i<=row; i++){
			for (int j=0; j<column; j++){
				searchNodeRow = searchNodeRow->next;
			}
			searchNodeCol = searchNodeCol->child;
			if (i!=row){
				searchNodeRow = searchNodeCol;
			}
		}
	}
	else{
		searchNodeRow = NULL;
	}
	//cout << searchNodeRow->test;
	return searchNodeRow;
}

//Create 5 ships (standard game)
void BattleShipBoard::createShips(){

}