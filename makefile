all:
	g++ main.cpp globals.cpp functions.cpp ship.cpp player.cpp timer.cpp projectile.cpp -o game -lSDL -lSDL_image -lSDL_gfx
