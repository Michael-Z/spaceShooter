all:
	g++ main.cpp init.cpp globals.cpp functions.cpp ship.cpp player.cpp timer.cpp projectile.cpp grunt.cpp stealth.cpp carrier.cpp explosion.cpp boomer.cpp button.cpp menus.cpp tooltip.cpp arcadeMode.cpp mainGame.cpp draw_circle.cpp -o starArena -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf -lSDL_mixer -Wall
