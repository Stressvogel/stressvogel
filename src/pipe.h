//
// Created by Aran on 03/12/2021.
//

#ifndef SOFTWARE_PIPE_H
#define SOFTWARE_PIPE_H

#include "entity.h"

/**
 * De breedte van een pipe in pixels
 **/
#define PIPE_WIDTH				40
/**
 * De X-offset met de rechterkant van het scherm zodra de pipe spawnt.
 **/
#define PIPE_START_X_RELATIVE	-10

/**
 * Een pipe is een obstakel dat de speler moet vermijden.<br/>
 * <br/>
 * Zodra een pipe aangeraakt wordt zal het spel worden be"eindigd.
 **/
class Pipe : public Entity {
private:
    /**
     * De hoogte van de opening in vergelijking met Y=0.
     **/
    uint16_t path_height = 60;

    bool upper;

protected:
    /**
     * De kleur van de pipe.
     **/
    uint16_t color = 0x07E0;

public:
    Pipe(bool upper, uint16_t path, uint16_t screen_width, uint16_t screen_height);

    virtual ~Pipe();

    /**
     * Wijzig de kleur van de pipe.
     *
     * @param color		16-bit integer met de RGB565 color value.
     **/
    void set_color(uint16_t color);

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


#endif //SOFTWARE_PIPE_H
