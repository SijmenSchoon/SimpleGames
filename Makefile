CXX=clang++
CXXFLAGS=-std=c++14 -O3
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

pong: pong.o
	curl 'https://raw.githubusercontent.com/lambdaloop/bomberman/master/fonts/Square.ttf' -o Square.ttf
	$(CXX) -o pong pong.o $(CXXFLAGS) $(LDFLAGS)

breakout: breakout.o
	$(CXX) -o breakout breakout.o $(CXXFLAGS) $(LDFLAGS)

clean:
	-rm *.o
	-rm pong
	-rm breakout
	-rm *.ttf
