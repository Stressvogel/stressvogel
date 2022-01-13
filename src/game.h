/*
 * game.h
 *
 * Omschrijving:	Klasse die de game state beheert
 * Hoofdauteur:		Aran Kieskamp
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_GAME_H
#define SOFTWARE_GAME_H

#include <list>

#include "pipe.h"
#include "flappy.h"
#include "glyph.h"

#include "../library/ial/ial_device.h"
#include "../library/ral/ral_display.h"

/**
 * De maximum Y-coördinaat waarop het pad tussen de pipes kan spawnen.
 **/
#define PIPE_PATH_MAX_HEIGHT	160
/**
 * De minimum Y-coördinaat waarop het pad tussen de pipes kan spawnen.
 **/
#define PIPE_PATH_MIN_HEIGHT	20

/**
 * Dit object representeert een gamesessie.<br />
 * <br />
 * Het is mutable en kan gereset worden om een nieuwe sessie te beginnen.
 **/
class Game {
private:
	/**
	 * Het display waar het spel naar toe wordt getekend.
	 **/
	ral::display *display;

	/**
	 * Het invoerapparaat dat gebruikt wordt om het spel te besturen.
	 **/
	ial::device *input;

	/**
	 * Een doubly linked list met verwijzingen naar alle
	 * entities in het speelveld.
	 **/
	std::list<Entity *> entities;
	Flappy *flappy;
	Glyph *score_glyph;
	uint64_t score = 0;

	/**
	 * Hoe ver de laatst gespawnde pipe van de rechterkant
	 * van het scherm verwijderd is.
	 **/
	uint16_t last_pipe = 0;
	
	/**
	 * @ref game.h+PIPE_PATH_MAX_HEIGHT
	 **/
	uint16_t path_max_height = PIPE_PATH_MAX_HEIGHT;

	/**
	 * @ref game.h+PIPE_PATH_MIN_HEIGHT
	 **/
	uint16_t path_min_height = PIPE_PATH_MIN_HEIGHT;

	/**
	 * Spawn een nieuwe pipe met het pad op een willekeurige hoogte
	 **/
	void create_pipe();

	/**
	 * Spawn een nieuwe pipe met het pad op de hoogte <b>i</b>
	 *
	 * @param i	De hoogte van het pad
	 **/
	void create_pipe(uint16_t i);

public:
	Game(ral::display *display, ial::device *input);

	/**
	 * Of de flappy bird in leven is.
	 **/
	bool running = true;

	/**
	 * Of de collision boundaries worden gerenderd.
	 **/
	bool show_hitboxes = false;

	/**
	 * Verwerk de input en update de game state.
	 **/
	void tick();

	/**
	 * Render het speelveld naar het display.
	 **/
	void render();

	/**
	 * Reset de state van de game entities.
	 **/
	void reset();

	/**
	 * Verkrijg het huidige Flappy object.
	 *
	 * @return	Een pointer naar een Flappy object
	 **/
	Flappy *get_flappy();
};

#endif //SOFTWARE_GAME_H

