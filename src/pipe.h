//
// Created by Aran on 03/12/2021.
//

#ifndef SOFTWARE_PIPE_H
#define SOFTWARE_PIPE_H

#include "entity.h"

class Pipe : public Entity {
private:
    uint16_t path_height = 60;
protected:
    uint16_t color = 0x07E0;

public:
    Pipe(bool upper, uint16_t path, uint16_t screen_width, uint16_t screen_height);

    virtual ~Pipe();

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


#endif //SOFTWARE_PIPE_H
