//
// Created by Aran on 30/11/2021.
//

#include <cstdio>
#include <unistd.h>

#include "alt_types.h"
#include "system.h"
#include "sys/alt_alarm.h"

#include "library/vga/vga.h"
#include "src/game.h"

/**
 * Switch om makkelijk te schakelen tussen een PS2 keyboard en onboard buttons
 **/
//#define USE_INPUT_PS2 // comment deze regel uit als je de onboard buttons wilt gebruiken

#ifndef USE_INPUT_PS2
#include "library/ial/ial_de2_115.h"
#else
#include "library/ial/ial_ps2.h"
#endif

/**
 * Switch om logging aan/uit te zetten
 **/
#define LOG_ENABLE // comment deze regel uit als je logging niet wilt gebruiken

#include "src/log.h"

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
 * Macro voor het omzetten van ticks per seconde naar alt_alarm ticks
 *
 * @param tps		Het aantal ticks per seconden
 **/
#define TPS_TO_TICKS(tps)		(float)((float)((float) alt_ticks_per_second() / (float) tps))

/**
 * Hoe vaak onze game per seconde updatet
 **/
#define TPS						8 // updates per seconde

/**
 * Hoeveelheid alt_alarm ticks
 **/
#define GAME_TICKS				TPS_TO_TICKS(TPS)

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

static alt_alarm game_tick;

alt_u32 game_tick_cb(void *) {
	input->ial_poll();

	// If game is running
	if (game->running) {
		game->tick(); // refresh game logic
		game->render(); // render to screen
	}

	return GAME_TICKS;
}

/**
 * De functie die de randapparaten opent en de game initialiseert.
 **/
void init() {
    display = new VGA();
    display->ral_init();

#ifdef USE_INPUT_PS2
    input = new ial_ps2();
    LOG_INFO("PS2 toetsenbord wordt als input gebruikt");
#else
    input = new ial_de2_115();
    LOG_INFO("Onboard DE2_115 buttons worden als input gebruikt");
#endif
    input->ial_init();

    game = new Game(display, input);
    LOG_INFO("Game is geinitialiseerd");
}

/**
 * Het entry point van ons programma
 **/
int main() {
	LOG_INFO("Game wordt geinitialiseerd");

	// Initialiseer de randapparaten en de game
    init();

    // Start de gametick timer
    if (alt_alarm_start(&game_tick, GAME_TICKS, game_tick_cb, NULL) < 0) {
    	LOG_ERROR("Fout met initialiseren van systeemklok");
    }

    LOG_INFO("Game tick is gestart");

    // Onze game gaat eindeloos door..... totdat iemand de stroom er uit trekt.
    while (1);
    return 0;
}
