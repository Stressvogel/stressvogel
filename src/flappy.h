/*
 * flappy.h
 *
 * Omschrijving:	Het hoofdkarakter van de game dat de user bestuurt
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_FLAPPY_H_
#define SOFTWARE_FLAPPY_H_

#include <cstdlib>

#include "entity.h"

#define STARTING_VELOCITY	10
#define GRAVITY			1.5
#define MAX_SPEED		-20

/**
 * Een flappy bird entity, het hoofdkarakter van de game.
 **/
class Flappy : public Entity {
private:
	/**
	 * Een mutable buffer met de sprite data.<br/>
	 * <br/>
	 * Deze sturen we naar de RAL als we de sprite willen renderen.
	 **/
	uint16_t **sprite_buf;

public:
	/**
	 * De huidige upwards/downwards snelheid van de vogel.
	 **/
	float velocity = STARTING_VELOCITY;

	Flappy(uint16_t start_x, uint16_t start_y);

	virtual ~Flappy();

	/**
	 * @inheritDoc
	 **/
	uint16_t get_width();

	/**
	 * @inheritDoc
	 **/
	uint16_t get_height();

	/**
	 * @inheritDoc
	 **/
	uint16_t get_x_coord();

	/**
	 * @inheritDoc
	 **/
	uint16_t get_y_coord();

	/**
	 * @inheritDoc
	 **/
	void set_height(uint16_t height);

	/**
	 * @inheritDoc
	 **/
	void set_width(uint16_t width);

	/**
	 * @inheritDoc
	 **/
	void set_y_coord(uint16_t y_coord);

	/**
	 * @inheritDoc
	 **/
	void set_x_coord(uint16_t x_coord);

	/**
	 * @inheritDoc
	 **/
	void render(ral::display *display);

	/**
	 * Bereken de nieuwe velocity.<br/>
	 * <br/>
	 * De velocity zal afnemen omdat de zwaartekracht er invloed op heeft.
	 **/
	void calc_new_velocity();

};

#endif /* SOFTWARE_FLAPPY_H_ */

