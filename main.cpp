/*
 * main.cpp
 *
 * Omschrijving:	Het entry point en de game loop van ons programma.
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#include <chrono>
#include <cstdio>
#include <unistd.h>

#include "system.h"

#include "src/game.h"
#include "library/ral/ral_display_vga.h"

/**
 * Switch om makkelijk te schakelen tussen een PS2 keyboard en onboard buttons
 **/
#define USE_INPUT_PS2 // comment deze regel uit als je de onboard buttons wilt gebruiken

#ifndef USE_INPUT_PS2
#include "library/ial/ial_device_de2_115.h"
#else
#include "library/ial/ial_device_ps2.h"
#endif
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
#define TICKS_TO_US(tps)	((int)(((float)(1.0f/((float)tps)))*SECONDS_TO_US(1)))

/**
 * Macro voor het omzetten van ticks per seconde naar alt_alarm ticks
 *
 * @param tps		Het aantal ticks per seconden
 **/
#define TPS_TO_TICKS(tps)	((float)((float)((float) alt_ticks_per_second() / (float) tps)))

/**
 * Hoe vaak onze game per seconde updatet
 **/
#define TPS			(8) // updates per seconde

/**
 * Hoeveelheid alt_alarm ticks per seconde.
 **/
#define GAME_TICKS		(TPS_TO_TICKS(TPS))

/**
 * Het tijdstip waarop het computer systeem gegenereerd was.
 **/
#ifdef SYSID_TIMESTAMP // media computer
static const time_t HARDWARE_GEN_TIME = SYSID_TIMESTAMP;
#else // ons computersysteem
static const time_t HARDWARE_GEN_TIME = SYSID_QSYS_0_TIMESTAMP;
#endif

/**
 * Het display waar we naar toe renderen.
 **/
static ral::display *display;
/**
 * Het device wat we als invoerapparaat gebruiken.
 **/
static ial::device *input;
/**
 * De gamesessie.
 **/
static Game *game;

/**
 * De functie die de randapparaten opent en de game initialiseert.
 **/
void init() {
	display = new ral::display_vga();
	display->init();
	LOG_INIT_MSG("Display");

#ifdef USE_INPUT_PS2
	input = new ial::device_ps2();
	LOG_INFO("PS2 toetsenbord wordt als input gebruikt");
#else
	input = new ial::device_de2_115();
	LOG_INFO("Onboard DE2_115 buttons worden als input gebruikt");
#endif
	input->init();
	LOG_INIT_MSG("Input");

	game = new Game(display, input);
	LOG_INIT_MSG("Game");
}

/**
 * Een functie om alle gametaken uit te voeren.
 **/
void iter() {
	LOG_MEASURE(input->poll());

	// If game is running
	if (game->running) {
		LOG_MEASURE(game->tick()); // refresh game logic
	}

	LOG_MEASURE(game->render()); // render to screen
}

/**
 * Eindeloze loop
 **/
void loop() {
	// Onze game gaat eindeloos door..... totdat iemand de stroom er uit trekt.
	while (1) {
		LOG_MEASURE(iter());
	}
}

/**
 * Het entry point van ons programma
 **/
int main() {
	LOG_INFO("Stressvogel op CPU %s\n\tHW datum %s\tSW datum %s",
			ALT_CPU_NAME,
			ctime(&HARDWARE_GEN_TIME),
			__TIMESTAMP__);

	// Initialiseer de randapparaten en de game
	init();

	// Eindeloze loop
	loop();

	// Hier zou het programma niet eens mogen komen...
	LOG_ERROR("Game loop is onderbroken");
	return 0;
}

