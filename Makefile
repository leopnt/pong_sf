# compiler
CXX = g++
CFLAGS = -Wall -g

# console commands variables
RM = rm
CP = cp

### Update the absolute path to your SFML directory here ###
SFML_Static_Path = C:/Users/leopnt/SFML-2.5.1

# g++ project flags
I_FLAG = -I include/ -I $(SFML_Static_Path)/include/
L_FLAG = -L $(SFML_Static_Path)/lib/
LIBS = -lsfml-graphics -lsfml-window -lsfml-system


pong : pong.o ball.o block.o
	@echo "** Building the game"
	$(CXX) $(CFLAGS) -o pong pong.o ball.o block.o $(L_FLAG) $(LIBS)

pong.o : src/pong.cpp
	$(CXX) $(CFLAGS) -c src/pong.cpp $(I_FLAG)

ball.o : src/ball.cpp
	$(CXX) $(CFLAGS) -c src/ball.cpp $(I_FLAG)

block.o : src/block.cpp
	$(CXX) $(CFLAGS) -c src/block.cpp $(I_FLAG)

install:
	@echo "** Copying dlls..."
	$(CP) $(SFML_Static_Path)/bin/sfml-graphics-2.dll ./
	$(CP) $(SFML_Static_Path)/bin/sfml-system-2.dll ./
	$(CP) $(SFML_Static_Path)/bin/sfml-window-2.dll ./

uninstall:
	@echo "** Removing dlls and executable..."
	$(RM) -vr *.dll pong

clean:
	@echo "** Removing object files..."
	$(RM) -vr *.o
