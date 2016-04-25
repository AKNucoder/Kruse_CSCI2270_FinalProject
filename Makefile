OBJS = battleShipBoard.o battleShip.o
CPPFLAGS = -std=c++11
PROG = battleShipGame
CC = g++

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
	
battleShipBoard.o: battleShipBoard.h battleShipBoard.cpp
	$(CC) $(CPPFLAGS) -c battleShipBoard.cpp
	
battleShip.o: battleShip.cpp
	$(CC) $(CPPFLAGS) -c battleShip.cpp
	
clean:
	$(RM) $(PROG) $(OBJS)


