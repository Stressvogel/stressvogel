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

class Game {
private:
    RAL *display;
    ial *input;

    Flappy *flappy;
    std::list<Entity *> entities;
    uint16_t last_pipe = 0;

    uint16_t path_max_height = 160;
    uint16_t path_min_height = 20;

    void create_pipe();

    void create_pipe(uint16_t i);

public:
    Game(RAL *display, ial *input);

    bool running = true;

    void tick();

    void render();

    void reset();

    Flappy *get_flappy();
};

#endif //SOFTWARE_GAME_H
