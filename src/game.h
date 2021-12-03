//
// Created by Aran on 03/12/2021.
//

#ifndef SOFTWARE_GAME_H
#define SOFTWARE_GAME_H

#include "../src/pipe.h"

class Game {
private:
    RAL *display;
    Entity *entities[2] = {nullptr, nullptr};
    uint16_t path_max_height = 160;
    uint16_t path_min_height = 20;

    void create_pipe();

    void create_pipe(uint16_t i);

    void render();

public:
    Game(RAL *display);

    bool running = true;

    void tick();
};


#endif //SOFTWARE_GAME_H
