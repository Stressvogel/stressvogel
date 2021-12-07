/*
 * flappy.h
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_FLAPPY_H_
#define SOFTWARE_FLAPPY_H_

#include "entity.h"

#define FLAPPY_VELOCITY 1.10

class Flappy : public Entity {
private:
	uint16_t **sprite_buf;
protected:
    uint16_t baseline_x;

public:
    Flappy(uint16_t start_x, uint16_t start_y);

    virtual ~Flappy();

    void set_color(uint16_t color);

    uint16_t get_width();

    uint16_t get_height();

    uint16_t get_x_coord();

    uint16_t get_y_coord();

    void set_height(uint16_t height);

    void set_width(uint16_t width);

    void set_y_coord(uint16_t y_coord);

    void set_x_coord(uint16_t x_coord);

    void render(RAL *display);
};

#endif /* SOFTWARE_FLAPPY_H_ */
