//
// Created by Aran on 30/11/2021.
//

#include <cstdio>
#include <system.h>
#include <unistd.h>
#include "system.h"
#include "library/vga/vga.h"
#include "src/game.h"

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
 * Switch om makkelijk te schakelen tussen een PS2 keyboard en onboard buttons
 **/
#define USE_INPUT_PS2 // comment deze regel uit als je de onboard buttons wilt gebruiken

#ifndef USE_INPUT_PS2
#include "library/ial/ial_de2_115.h"
#else
#include "library/ial/ial_ps2.h"
#endif

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

#ifdef USE_INPUT_PS2
    input = new ial_ps2();
#else
    input = new ial_de2_115();
#endif
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
