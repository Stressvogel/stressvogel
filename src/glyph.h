/*
 * glyph.h
 *
 * Omschrijving:	Dit representeert een cijfer op het scherm
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_GLYPH_H_
#define SOFTWARE_GLYPH_H_

#include <stdlib.h>

#include "entity.h"

/**
 * Een letter of nummer die verbonden is aan een sprite.<br />
 * <br />
 * De sprite kan ook vergroot worden met een arbitraire schaal.
 **/
class Glyph : public Entity {
private:
	/**
	 * De upscale factor van de sprite
	 **/
	uint8_t scale;

	/**
	 * Een mutable buffer met de sprite data.<br/>
	 * <br/>
	 * Deze sturen we naar de RAL als we de sprite willen renderen.
	 **/
	uint16_t **sprite_buf;

public:
	/**
	 * Constructor van een Glyph.<br />
	 * <br />
	 * Initialiseert de positie van de glyph naar <i>x</i>, <i>y</i>.<br />
	 * <br />
	 * Het argument <i>scale</i> bepaalt met welke factor hij vergroot wordt.
	 *
	 * @param x	Horizontale positie op het scherm
	 * @param y	Verticale positie op het scherm
	 * @param scale	De vergroting van het cijfer
	 **/
	Glyph(uint16_t x, uint16_t y, uint8_t scale);

	virtual ~Glyph();

	/**
	 * Verander de waarde van de glyph en refresh de sprite buffer.
	 *
	 * @param new_char	Het nieuwe karakter dat getoond moet worden
	 **/
	void show_int(char new_char);

	/**
	 * Verander de waarde van de glyph en refresh de sprite buffer.
	 *
	 * @param new_int	Het nieuwe getal dat getoond moet worden
	 **/
	void show_int(int new_int);

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
};

#endif /* SOFTWARE_GLYPH_H_ */

