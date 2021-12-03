//
// Created by Aran on 03/12/2021.
//

#ifndef SOFTWARE_OBJECT_H
#define SOFTWARE_OBJECT_H

#include "../library/ral/ral.h"

class Entity {
protected:
    uint16_t width;
    uint16_t height;
    uint16_t x_coord;
    uint16_t y_coord;

public:
    virtual uint16_t get_width() = 0;

    virtual uint16_t get_height() = 0;

    virtual uint16_t get_x_coord() = 0;

    virtual uint16_t get_y_coord() = 0;


    virtual void set_width(uint16_t width) = 0;

    virtual void set_height(uint16_t height) = 0;

    virtual void set_x_coord(uint16_t x_coord) = 0;

    virtual void set_y_coord(uint16_t y_coord) = 0;


    virtual void render(RAL *display) = 0;
};


#endif //SOFTWARE_OBJECT_H
