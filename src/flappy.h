/*
 * flappy.h
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_FLAPPY_H_
#define SOFTWARE_FLAPPY_H_

#include "entity.h"
#include <stdlib.h>

#define GRAVITY 1.5
#define MAX_SPEED -20

class Flappy : public Entity {
private:
    uint16_t **sprite_buf;
protected:
    uint16_t baseline_x;

public:
    float velocity = 10;

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

    void calc_new_velocity();
};

#endif /* SOFTWARE_FLAPPY_H_ */
