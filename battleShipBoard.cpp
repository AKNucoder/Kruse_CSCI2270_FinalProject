#include "BattleShipBoard.h"
#include <iostream>
#include <iomanip> //For printing format of board
#include <ctime>
#include <sstream>

using namespace std;
int const ROW_SIZE =10;
int const COLUMN_SIZE = 10;
string const struckSymbol = "X";
string const missSymbol = "O";

//Constructor initailize root -main node and initializes battleships.
BattleShipBoard::BattleShipBoard(){
	root = new BattleShipNode;
	
	airCraftCarrier = new BattleShip(5,0); //5 piece vessel
	battleShip = new BattleShip(4,0);	  //4 piece vessel
	submarine = new BattleShip(3,0);  	  //3 piece vessel
	destroyer = new BattleShip(3,0);;	  //3 piece vessel
	patrolBoat = new BattleShip(2,0);	  //2 piece vessels

	//Called once, used for randomizing ships if user selects to randomize.
	srand(time(NULL));
}

//Destructor deletes all nodes before exiting program.
BattleShipBoard::~BattleShipBoard(){
	BattleShipNode* nodeToDelete;

	//Delete board
	for (int i = 0; i<=ROW_SIZE; i++){
		for (int j = 1; j<=COLUMN_SIZE; j++){
			nodeToDelete = searchCoordinateToDelete(ROW_SIZE-i,COLUMN_SIZE-j);
			nodeToDelete->battleShip=NULL;
			if (nodeToDelete->previous!=NULL){
				if (nodeToDelete == nodeToDelete->previous->child){
					nodeToDelete->previous->child = NULL;
				}
				else{
					nodeToDelete->previous->next = NULL;
				}
			}
			delete nodeToDelete;
		}
	}

	//Delete boats
	delete airCraftCarrier;
	delete battleShip;
	delete submarine;
	delete destroyer;
	delete patrolBoat;
}

//Assemble the board size for standard battleship coordinates
void BattleShipBoard::assembleBoard(){
	//Create row of nodes
	BattleShipNode* createNodeRow = root;
	//Create columns of nodes
	BattleShipNode* createNodeCol= root;
	BattleShipNode* previous = new BattleShipNode;

	//i<=10 to have a null row of battleships at bottom, for printing purposes.
	for (int i=0; i<=ROW_SIZE;i++){
		for (int j=0; j<COLUMN_SIZE; j++){
			createNodeRow->next = new BattleShipNode;
			previous = createNodeRow;
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
bool BattleShipBoard::strike(){
	bool enteredCorrectCoordinate = false;
	bool hitBattleShip = false;

	while (!enteredCorrectCoordinate){
		int column = retrieveColumnCoordinate();
		int row    = retrieveRowCoordinate();
		BattleShipNode* coordinateToStrike = searchCoordinate(row,column);

		//If the coordinate has already been hit tell the user
		if (coordinateToStrike->hitNoDamage || coordinateToStrike->hitBattleShip){
			cout << "You have already fired at this coordinate. Please select a new one." << endl;
			enteredCorrectCoordinate = false;
		}
		else if(coordinateToStrike->battleShip!=NULL){
			//update how much of the battlship has been hit and the coordinate.
			coordinateToStrike->battleShip->hit++;
			coordinateToStrike->hitBattleShip = true;
			hitBattleShip = true;
			enteredCorrectCoordinate = true;

			if (coordinateToStrike->battleShip->hit == coordinateToStrike->battleShip->size){
				cout << endl << "You have SUNK an ENEMY vessel!!!" << endl;
			}
			
		}
		else{
			//Coordincate has been hit, but no damage to any battleships.
			coordinateToStrike->hitNoDamage = true;
			cout << endl << "You have missed." << endl;
			pauseDialog();
			enteredCorrectCoordinate = true;
		}
	}

	return hitBattleShip;
}

//Print the board to terminal
void BattleShipBoard::printBoard(){
	//Search row of nodes
	BattleShipNode* searchNodeRow = root;
	//Search column of nodes
	BattleShipNode* searchNodeCol= root;
	char columnLabel = 65;

	printColumnLabels();

	//i<=10 to make sure if there is a battleship touching this edge, it will be printed.
	for (int i=0; i<=ROW_SIZE;i++){
		printRowBorder(searchNodeRow, i);
		
		if (i<ROW_SIZE){
			cout << columnLabel++ << " |";

			printRow(searchNodeRow);

			searchNodeCol = searchNodeCol->child;
			searchNodeRow = searchNodeCol;
		}
	}
	cout << endl;
}

//Instead of printing what the user has struck, it will print their own board of what their opponent has struck.
void BattleShipBoard::printMyCurrentBoard(){
	//Search row of nodes
	BattleShipNode* searchNodeRow = root;
	//Search column of nodes
	BattleShipNode* searchNodeCol= root;
	char columnLabel = 65;

	printColumnLabels();

	//i<=10 to make sure if there is a battleship touching this edge, it will be printed.
	for (int i=0; i<=ROW_SIZE;i++){
		printWholeRowBorder(searchNodeRow, i);
		
		if (i<ROW_SIZE){
			cout << columnLabel++ << " |";

			printWholeRow(searchNodeRow);

			searchNodeCol = searchNodeCol->child;
			searchNodeRow = searchNodeCol;
		}
	}
	cout << endl;
}

//Create 5 ships (standard game)
void BattleShipBoard::createShips(){
	cout << endl;
	cout << "You have 5 military vessels listed below:" << endl;

	//Text shows user the boats
	createShipsBattleShipText();
	createShipsBattleShipText();
	createShipsDestroyerText();
	createShipsSubmarineText();
	createShipsPatrolBoatText();
	
	cout << endl;
	
	pauseDialog();
	printBoard();
	cout << "In the grid above, you must try to hide these ships from your opponent." << endl << "You cannot have more than one ship on the same coordinate." << endl;
	pauseDialog();

	for (int i=0;i<5;i++){
		printMyCurrentBoard();
		cout << "Now, you will position your:" << endl;
		switch (i){
			case 0:
				 createShipsAircraftCarrierText();
				 positionBoat(airCraftCarrier);
				break;
			case 1:
				createShipsBattleShipText();
				positionBoat(battleShip);
				break;
			case 2:
				createShipsDestroyerText();
				positionBoat(destroyer);
				break;
			case 3:
				createShipsSubmarineText();
				positionBoat(submarine);
				break;
			case 4:
				createShipsPatrolBoatText();
				positionBoat(patrolBoat);
				break;
		}
	}
}

//Asks the user for a column coordinate
int BattleShipBoard::retrieveColumnCoordinate(){
	bool correctColumnResponse = false;
	string userInput;

	//Do not continue until the user enters an acceptable number.
	while (!correctColumnResponse){
		cout << "Please enter a column(1-10):";
		cin >> userInput;
		if (isInt(userInput) && 1<=stoi(userInput) && stoi(userInput)<=10){
			correctColumnResponse = true;
		}
		else{
			cout << "Error: Please enter a whole number from 1 to 10." << endl;
		}
	}

	//column - 1 becuase the columnsare storedd from 0 to 9
	int columnIntValue = stoi(userInput)-1;

	return columnIntValue;
}

//Asks the user for a row coordinate
int BattleShipBoard::retrieveRowCoordinate(){
	bool correctRowResponse = false;
	string row;
	unsigned char rowUpperCase;

	while(!correctRowResponse){
		cout << "Please enter a row(A-J):";
		cin >> row;
		//Convert to upper case to allow lower and upper.
		rowUpperCase = toupper(row.at(0));
		//If the input is between A and J (upper or lower case).
		if (row.length()==1 && ((rowUpperCase>=65 && rowUpperCase<=74) || ( rowUpperCase>=141 && rowUpperCase<=152)) ){
			correctRowResponse = true;
			row = rowUpperCase;
		}
		else{
			cout << "Error: Please enter a single letter from A to J." << endl;
		}
	}
	//subtract 65, since the ascii value of A is 65 and rows are stored starting at 0.
	int rowIntValue = rowUpperCase-65;  

	return rowIntValue; 
}

//This function calls on another function to assign coordinates to each ship
void BattleShipBoard::randomizeBoatPositions(){
	randomizeBoatPositionsPlaceBoats(airCraftCarrier);
	randomizeBoatPositionsPlaceBoats(battleShip);
	randomizeBoatPositionsPlaceBoats(submarine);
	randomizeBoatPositionsPlaceBoats(destroyer);
	randomizeBoatPositionsPlaceBoats(patrolBoat);
}

void BattleShipBoard::pauseDialog(){
	string key = " ";
	
	while (key!="c" && key!="C"){
		cout << "Please press (c) then Enter to continue...";
		cin >> key;
	}
}

//Retruns true if all battlehips have been sunk, otherwise false;
bool BattleShipBoard::allShipsSunk(){
	//If all boats have been completely hit, return true
	if (airCraftCarrier->hit == airCraftCarrier->size && battleShip->hit == battleShip->size && submarine->hit == submarine->size && destroyer->hit == destroyer->size && patrolBoat->hit == patrolBoat->size){
		return true;
	}
	else {
		return false;
	}	
}

//Just moves terminal screeen far down by printing many character returns, so user does not accidentally see the information printed above.
void BattleShipBoard::clearTerminalScreen(){
	for (int i=0;i<1000; i++){
		cout << "\n";
	}
}

//Tells user they won
void BattleShipBoard::congratsOnWinning(string winnerName, string loserName){
	cout << endl << "Congrats " << winnerName << " you have won the battle! " << loserName << " has lost." <<endl;  
}


//*******************************************BELOW FUNCTIONS ARE PRIVATE**************************************************


//*******************************************FOLLOWING FUNCTIONS: Print row/row border and prints battleships that have been sunk (not partially hit).*********************************************************************

void BattleShipBoard::printRow(BattleShipNode* _searchNodeRow){
	for (int j=0; j<COLUMN_SIZE; j++){
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
					cout << setw(2) << "[" << struckSymbol << "]" << setw(2) << "|";
				}
			}
			else{
				cout << setw(3) << struckSymbol << setw(3) << "|";
			}
		}
		else{
			cout << setw(3) << missSymbol << setw(3) << "|";
		}
		_searchNodeRow = _searchNodeRow->next;
	}
}
//Print borders between rows
void BattleShipBoard::printRowBorder(BattleShipNode* _nodeAtBegginingOfRow, int row){
	//Search row of nodes
	BattleShipNode* searchNodeRow = _nodeAtBegginingOfRow;
	cout << endl << "  ";
	for (int j =0; j<COLUMN_SIZE; j++){
		//If the last edge of the board or a battleship exists at this location and it has been discovered (completely hit).
		bool shipIsSunk = false;
		if (searchNodeRow!=NULL){
			shipIsSunk = battleShipIsVerticalAndSunk(searchNodeRow,row,j);
		}

		if ((row==ROW_SIZE && shipIsSunk) || (searchNodeRow!=NULL && shipIsSunk)){
			printVerticalBattleShip(searchNodeRow,row,j);
		}
		else {
			cout << setw(6) << "|-----";
		}
		searchNodeRow = searchNodeRow->next;
	}
	cout << "|" << endl;
}
//********************************************************************************************************************************************************************


//*******************************************FOLLOWING FUNCTIONS: Prints whole row/row border regardless of it battleships have been sunk or not.******************************************************
//Prints row regarldes of battleship sunk status
void BattleShipBoard::printWholeRow(BattleShipNode* _searchNodeRow){
	for (int j=0; j<COLUMN_SIZE; j++){
		if (_searchNodeRow->battleShip!=NULL && battleShipIsHorizontal(_searchNodeRow)){
				printHorizontalBattleShip(_searchNodeRow);
		}
		else if (_searchNodeRow->battleShip!=NULL && _searchNodeRow->hitBattleShip){
				cout << setw(2) << "[" << struckSymbol << "]" << setw(2) << "|";
		}
		else if (_searchNodeRow->battleShip!=NULL){
				cout << setw(4) << "[ ]" << setw(2) << "|";
		}
		else if (_searchNodeRow->hitNoDamage){
			cout << setw(3) << missSymbol << setw(3) << "|";
		}
		else {
			cout << setw(6) << "|";
		}
		_searchNodeRow = _searchNodeRow->next;
	}
}
//Print borders between rows
void BattleShipBoard::printWholeRowBorder(BattleShipNode* _nodeAtBegginingOfRow, int row){
	//Search row of nodes
	BattleShipNode* searchNodeRow = _nodeAtBegginingOfRow;
	cout << endl << "  ";
	for (int j =0; j<COLUMN_SIZE; j++){
		//If the last edge of the board or a battleship exists at this location and it has been discovered (completely hit).
		//if (row==ROW_SIZE || (searchNodeRow!=NULL && searchNodeRow->battleShip!=NULL && (!battleShipIsHorizontal(searchCoordinate(row-1,j)) || !battleShipIsHorizontal(_nodeAtBegginingOfRow))) ){
		if (row==ROW_SIZE || battleShipIsVertical(searchNodeRow,row,j)){//} || !battleShipIsHorizontal(_nodeAtBegginingOfRow)))){
			printVerticalBattleShip(searchNodeRow,row,j);
		}
		else {
			cout << setw(6) << "|-----";
		}
		searchNodeRow = searchNodeRow->next;
	}
	cout << "|" << endl;
}
//********************************************************************************************************************************************************************


//Print the board numbers for the columns
void BattleShipBoard::printColumnLabels(){
	//Couple of spaces to accound for row labels which take up space.
	cout << "  ";
	for (int i =0; i<ROW_SIZE; i++){
		cout << setw(4) << i+1 << "  ";
	}
}

//Finds a battleship node given coordinates and returns a pointer to the node
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

//Finds a battleship node given coordinates and returns a pointer to the node to delete (there is an extra line of empty nodes to be deleted at the bottom of the graph)
BattleShipNode* BattleShipBoard::searchCoordinateToDelete(int row, int column){
	BattleShipNode* searchNodeRow = root;
	BattleShipNode* searchNodeCol = root;
	if (0<=row && row<=10 && 0<=column && column<10){
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

//*******************************************FOLLOWING FUNCTIONS: Print boat either as horizontal/vertical******************************************************
//Prints part of a battleship if it is horizontal
void BattleShipBoard::printHorizontalBattleShip(BattleShipNode* _searchNodeRow){
	string symbolInside= " ";

	//Shows if battleship has been hit.
	if (_searchNodeRow->hitBattleShip){
		symbolInside = struckSymbol;
	}

	//If tail of battleship
	if (isTailOfHorizBattleShip(_searchNodeRow)){
		cout << setw(2) << "=[" << setw(1) << symbolInside << setw(2) << "]>" << setw(1) << "|";
	}
	//Else if head of  battleship
	else if (isHeadOfHorizBattleShip(_searchNodeRow)){
		cout << setw(2) << "<[" << setw(1) << symbolInside << setw(1) << "]" << setw(2) << "==";
	}
	//Else if a middle piece of battleship.
	else {
		cout << setw(2) << "=[" << setw(1) << symbolInside << setw(1) << "]" << setw(2) << "==";
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
	else if (row==ROW_SIZE){
		cout << setw(6) << "|-----";
	}
	//Else if a middle piece of battleship.
	else{
		cout << setw(6) << "|-|||-";
	}
}
//********************************************************************************************************************************************************************


//*******************************************FOLLOWING FUNCTIONS: Check if boat is either horizontal of vertical******************************************************
//Returns yes if a battleship is horzonal, or false if vertical
bool BattleShipBoard::battleShipIsHorizontal(BattleShipNode* _searchNodeRow){
	bool isHorizontal = false;

	if (_searchNodeRow!=NULL){
		if (_searchNodeRow->next != NULL && _searchNodeRow->battleShip == _searchNodeRow->next->battleShip){
			isHorizontal = true;
		}
		//Make sure that pevious isnt referring to a parent (first column previous is parent)
		else if (_searchNodeRow->previous != NULL && _searchNodeRow->battleShip == _searchNodeRow->previous->battleShip && _searchNodeRow->previous->child != _searchNodeRow){
			isHorizontal = true;
		}
	}
	return isHorizontal;
}
bool BattleShipBoard::battleShipIsVertical(BattleShipNode* _searchNodeRow, int row, int column){
	if (isTailOfVerticalBattleShip(_searchNodeRow,row,column) || isHeadOfVerticalBattleShip(_searchNodeRow,row,column) || (!battleShipIsHorizontal(_searchNodeRow) && _searchNodeRow->battleShip!=NULL)){
		return true;
	}
	else{
		return false;
	}

}
//Checks if boat is vertical and sunk
bool BattleShipBoard::battleShipIsVerticalAndSunk(BattleShipNode* _searchNodeRow, int row, int column){
	BattleShipNode* battleShipAbove = searchCoordinate(row-1,column);
	BattleShipNode* battleShipBelow = searchCoordinate(row+1,column);
	bool isVerticalSunk = false;

	if (battleShipIsVertical(_searchNodeRow,row,column)){
		if (_searchNodeRow->battleShip!=NULL &&  _searchNodeRow->battleShip->size == _searchNodeRow->battleShip->hit && (battleShipAbove!=NULL && battleShipAbove->battleShip == _searchNodeRow->battleShip)){
			isVerticalSunk = true;
		}
		else if(_searchNodeRow->battleShip!=NULL &&  _searchNodeRow->battleShip->size == _searchNodeRow->battleShip->hit && (battleShipBelow!=NULL && battleShipBelow->battleShip == _searchNodeRow->battleShip)){
			isVerticalSunk = true;
		}
		else if(isTailOfVerticalBattleShip(_searchNodeRow,row,column) && battleShipAbove->battleShip->size == battleShipAbove->battleShip->hit){
			isVerticalSunk = true;
		}
	}
	return isVerticalSunk;
}
//******************************************************************************************************************************


//*******************************************FOLLOWING FUNCTIONS: Check if node is a head/tail of a horiz/vertical boat.******************************************************
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
//******************************************************************************************************************************


//Asks user to manually position baots.
void BattleShipBoard::positionBoat(BattleShip* _battleShipToPosition){
	string userInput = " ";
	int row = 0;
	int column = 0;
	bool boatPositioned = false;
	bool boatVertical = false;

	while(!boatPositioned){
		//72 = V and 86 = H
		while (userInput!="V" && userInput!="v" && userInput!="H" && userInput!="h"){
			cout << "Do you want this boat Vertical (v) or Horizontal (h) in the grid? ";
			cin >> userInput;
			cout << endl;
		}

		if (toupper(userInput[0]) == 'V'){
			boatVertical = true;
		}

		cout << "Please select where the start (head) of the boat should be placed." << endl;
		column = retrieveColumnCoordinate();
		row = retrieveRowCoordinate();

		boatPositioned = placeBoat(_battleShipToPosition,row,column,boatVertical);


		if (!boatPositioned){
			cout << endl << "Error. Please re-select the coordinate and make sure that it can fit on the grid or that another boat is not already located there." << endl;
		}
	}

	cout << "Boat placed successfully!" << endl;
}

//Checks if string is an int.
bool BattleShipBoard::isInt(string stringToCheck){
	bool isAnInt = true;

	for (int i=0; i<stringToCheck.length(); i++){
		if (!isdigit(stringToCheck[i])){
			isAnInt = false;
		}
	}

	return isAnInt;
}

//Returns true if a boat can and thus is place on board, otherwise false if there is not enough room or boats in the way.
bool BattleShipBoard::placeBoat(BattleShip* _battleShipToPosition, int row, int column, bool _boatVertical){
	bool boatPositioned = false;
	
	if ( (_boatVertical && enoughVerticalRoom(_battleShipToPosition,row,column)) || (!_boatVertical && enoughHorizontalRoom(_battleShipToPosition,row,column)) ){
		boatPositioned = true;
	}
	
	if (boatPositioned){
		BattleShipNode* searchedCoordinate;
		if (_boatVertical==true){
			for (int i=0; i<_battleShipToPosition->size; i++){
				searchedCoordinate = searchCoordinate(row+i,column);
				searchedCoordinate->battleShip = _battleShipToPosition;
			}
		}
		else{
			for (int i=0; i<_battleShipToPosition->size; i++){
				searchedCoordinate = searchCoordinate(row,column+i);
				searchedCoordinate->battleShip = _battleShipToPosition;
			}
		}
	}

	return boatPositioned;
}


//*************************************Makes sure there is enough room on board for a battleship to be placed at desired coordinates horz/vert***********************************
//Checks to see if a boat has enough room to be placed at a location vertically.
bool BattleShipBoard::enoughVerticalRoom(BattleShip* _battleShipToPosition, int row, int column){
	BattleShipNode* searchedCoordinate;
	bool isEnoughRoom = true;

	for (int i=0; i<_battleShipToPosition->size; i++){
		searchedCoordinate = searchCoordinate(row+i,column);
		//If the search coordinate does not exist, of if there is a battleship located here, then a battleship cannon be placed here.
		if (searchedCoordinate==NULL || (searchedCoordinate!=NULL && searchedCoordinate->battleShip!=NULL)){
			isEnoughRoom = false;
		}
	}
	return isEnoughRoom;

}
//Checks to see if a boat has enough room to be placed at a location horizontally.
bool BattleShipBoard::enoughHorizontalRoom(BattleShip* _battleShipToPosition, int row, int column){
	BattleShipNode* searchedCoordinate;
	bool isEnoughRoom = true;

	for (int i=0; i<_battleShipToPosition->size; i++){
		searchedCoordinate = searchCoordinate(row,column+i);
		//If the search coordinate does not exist, of if there is a battleship located here, then a battleship cannon be placed here.
		if (searchedCoordinate==NULL || (searchedCoordinate!=NULL && searchedCoordinate->battleShip!=NULL)){
			isEnoughRoom = false;
		}
	}
	return isEnoughRoom;
}
//*****************************************************************************************************************************************************************************


//Computer randomly assigns boat positions
void BattleShipBoard::randomizeBoatPositionsPlaceBoats(BattleShip* _currentBoat){
	int row; 
	int column; 
	bool boatVertical = false;
	bool boatPositioned = false;

	while(!boatPositioned){
		row = rand()%10;
		column = rand()%10;
		if (rand()%100 <50){
			boatVertical = true;
		}
		boatPositioned = placeBoat(_currentBoat,row, column, boatVertical);
	}
}


//*************************************************Following functions just output text statements***************************************************
void BattleShipBoard::createShipsAircraftCarrierText(){
	cout << setw(18) << "Aircraft Carrier: " << "<[ ]===[ ]===[ ]===[ ]===[ ]>" << endl;
}

void BattleShipBoard::createShipsBattleShipText(){
	cout << setw(18) << "Battleship: " <<  "<[ ]===[ ]===[ ]===[ ]>" << endl;
}

void BattleShipBoard::createShipsSubmarineText(){
	cout << setw(18) << "Submarine: " <<   "<[ ]===[ ]===[ ]>" << endl;
}

void BattleShipBoard::createShipsDestroyerText(){
	cout << setw(18) << "Destroyer: " <<   "<[ ]===[ ]===[ ]>" << endl;
}

void BattleShipBoard::createShipsPatrolBoatText(){
	cout << setw(18) << "Patrol Boat: " << "<[ ]===[ ]>" << endl;
}
//***************************************************************************************************************************************************