/*
 * glyph.h
 *
 *  Created on: Dec 10, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_GLYPH_H_
#define SOFTWARE_GLYPH_H_

#include "entity.h"
#include <stdlib.h>

/**
 * Een letter of nummer die verbonden is aan een sprite.
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
    Glyph(uint16_t x, uint16_t y, uint8_t scale);

    virtual ~Glyph();

    void show_int(char new_char);

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
