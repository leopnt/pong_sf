pong : pong.o ball.o block.o
	@echo "** Building the game"
	$(CXX) $(CFLAGS) -o bin/pong pong.o ball.o block.o $(L_FLAG) $(LIBS)

pong.o : src/pong.cpp
	$(CXX) $(CFLAGS) -c src/pong.cpp $(I_FLAG)

ball.o : src/ball.cpp
	$(CXX) $(CFLAGS) -c src/ball.cpp $(I_FLAG)

block.o : src/block.cpp
	$(CXX) $(CFLAGS) -c src/block.cpp $(I_FLAG)

clean:
	@echo "** Removing object files and executable..."
	$(RM) -vr *.o bin/pong


CXX = g++
CFLAGS = -Wall -g

# commands variables
RM = rm

# g++ project flags
I_FLAG = -I include/
L_FLAG = -L lib/
LIBS = -lsfml-graphics -lsfml-window -lsfml-system