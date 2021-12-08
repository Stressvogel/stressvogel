//
// Created by Aran on 03/12/2021.
//

#ifndef SOFTWARE_GAME_H
#define SOFTWARE_GAME_H

#include <list>

#include "../library/ial/ial.h"
#include "../library/ral/ral.h"

#include "../src/pipe.h"
#include "../src/flappy.h"

/**
 * Dit object representeert een gamesessie.
 **/
class Game {
private:
    RAL *display;
    ial *input;

    Flappy *flappy;
    std::list<Entity *> entities;
    uint16_t last_pipe = 0;

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
    Game(RAL *display, ial *input);

    bool running = true;

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
