//
// Created by Aran on 03/12/2021.
//

#ifndef SOFTWARE_GAME_H
#define SOFTWARE_GAME_H

#include <list>

#include "../library/ial/ial_device.h"
#include "../library/ral/ral_display.h"
#include "../src/pipe.h"
#include "../src/flappy.h"
#include "../src/glyph.h"

/**
 * Dit object representeert een gamesessie.
 **/
class Game {
private:
    ral::display *display;
    ial::device *input;

    Flappy *flappy;
    std::list<Entity *> entities;
    uint16_t last_pipe = 0;
    uint64_t score = 0;
    Glyph *score_glyph;

    uint16_t path_max_height = 160;
    uint16_t path_min_height = 20;

    /**
     * Spawn een nieuwe pipe met het pad op een willekeurige hoogte
     **/
    void create_pipe();

    /**
     * Spawn een nieuwe pipe met het pad op de hoogte <b>i</b>
     *
     * @param i		De hoogte van het pad
     **/
    void create_pipe(uint16_t i);

public:
    Game(ral::display *display, ial::device *input);

    /**
     * Of de bird alive is.
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
     * @return		Een pointer naar een Flappy object
     **/
    Flappy *get_flappy();
};

#endif //SOFTWARE_GAME_H
