//
// Created by Aran on 30/11/2021.
//


#include <cstdio>
#include <system.h>
#include <unistd.h>
#include "system.h"
#include "library/vga/vga.h"
#include "library/ial/ial_de2_115.h"
#include "src/game.h"

// sterkte met het simpeler maken van deze macro's
#define SECONDS_TO_US(second)	(second * 1000000)
#define TICKS_TO_US(fps)		((int)(((float)(1.0f/((float)fps)))*SECONDS_TO_US(1)))

RAL *display;
ial *input;
Game *game;

void init() {
    printf("Flappy Bird!\n");

    display = new VGA();
    display->ral_init();

    input = new ial_de2_115();
    input->ial_init();

    printf("Creating game\n");

    game = new Game(display, input);
}

int main() {
    init();

    while (true) {
    	// Fetch input
    	input->ial_poll();

    	// If game is running
    	if (game->running) {
    		game->tick(); // refresh game logic
    		game->render(); // render to screen
        	usleep(TICKS_TO_US(10)); // zoveel ticks per seconde... hier kun je gwn de float van de heartbeat sensor aan koppelen
    	}
    }
}
