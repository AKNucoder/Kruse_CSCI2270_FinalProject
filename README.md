# Kruse_CSCI2270_FinalProject
CSCI 2270 final project. V1.0

Phase 1 - Description:
A game of battleship played in the Terminal. Program will use a n-ary tree with nodes that designate locations of battleships and whether or not a node has been struck or not. A class will handle all methods related to storing coordinates and battleship properties (e.g. size, damaged/intact coordinates, print coordinate map). A driver file will handle other properties, such as the main menu, and certain functionalities such as receiving user input to determine which functions to call in the class.

Phase 2:

Project Summary:
This game is a software Terminal emulation of the well-known Battleship (copyright Hasbro) board game. The game involves two-players with having five ships each hidden on a 10x10 grid. Each player takes turns guessing the location of their opponent's hidden ships until a player sinks all ships of their opponent. Whereas players manually place their ships on their grid, as in the original game, this Terminal allows an additional feature that randomly places ships, to expedite play. The n-ary tree data structure is used to store coordinates of ship positions and direct hits and misses.

How to Run:
To initialize program, either compile battleShipBoard.h,battleShipBoard.cpp and battleShip.cpp, or run the Makefile which will create an executable. For example, to run the Makefile in a Linux/Mac Terminal, first make sure you are in the directory of the provided Makefile, and then type in (ignore quotations) "make" in Terminal to create a "./battleShipGame" executable. To run the executable in Terminal, make sure you are located in the directory of the executable, then type (ignore quotations) "./battleShipGame". Once the program is running, follow the on-screen instructions to play the game between you and your opponent. It is recommended to run your viewing window at full screen to ensure that the Battleship map fits on your screen. If the map still does not fit during run time, look under your Terminal preferences to reduce font size. (Note: the battleShip.cpp file is the driver file for the class files battleShipBoard.h and battleShipBoard.cpp).

Dependencies:
Runs on c++11. Incorporates basic c++ libraries, such as iostream, iomanip, ctime, funtional and the cstdlib.

System Requirements:
Program runs in a Terminal c++11 compiler shell. Program works in Mac and Linux with the gcc compiler and can work in Windows once a c++11 compiler in the Command Prompt is configured.

Group Members:
Johnathan Kruse

Contributors:
Johnathan Kruse

Open issues/bugs:
Awaiting beta test feedback.
