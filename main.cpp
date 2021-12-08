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
/**
 * Macro voor het converteren van seconden naar microseconden
 *
 * @param second 	Een heel aantal seconden
 **/
#define SECONDS_TO_US(second)	(second * 1000000)
/**
 * Macro voor het converteren van ticks per seconden naar delaytime in microseconden
 *
 * @param tps		Het aantal ticks per seconden
 **/
#define TICKS_TO_US(tps)		((int)(((float)(1.0f/((float)tps)))*SECONDS_TO_US(1)))

/**
 * Het display waar we naar toe renderen.
 **/
static RAL *display;
/**
 * Het device wat we als invoerapparaat gebruiken.
 **/
static ial *input;
/**
 * De gamesessie.
 **/
static Game *game;

/**
 * De functie die de randapparaten opent en de game initialiseert.
 **/
void init() {
    printf("Flappy Bird!\n");

    display = new VGA();
    display->ral_init();

    input = new ial_de2_115();
    input->ial_init();

    printf("Creating game\n");

    game = new Game(display, input);
}

/**
 * Het entry point van ons programma
 **/
int main() {
	// Initialiseer de randapparaten en de game
    init();

    // Onze game gaat eindeloos door..... totdat iemand de stroom er uit trekt.
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
