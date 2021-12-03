//
// Created by Aran on 03/12/2021.
//

#include "game.h"
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

Game::Game(RAL *display) {
    this->display = display;
    this->flappy = new Flappy(50, 50);
}

void Game::create_pipe() {
    uint16_t path = rand() % path_max_height + path_min_height;
    create_pipe(path);
}

void Game::create_pipe(uint16_t path) {
    Pipe *upper_pipe = new Pipe(true, path, display->get_width(), display->get_height());
    Pipe *lower_pipe = new Pipe(false, path, display->get_width(), display->get_height());

    entities[0] = upper_pipe;
    entities[1] = lower_pipe;
}

void Game::tick() {
    if (entities[0] == nullptr) {
        create_pipe();
    } else {
    	// TODO linked list maken van entities
        for (uint16_t i = 0; i < 2; ++i) {
            Entity *entity = entities[i];
            uint16_t new_x_coord = entity->get_x_coord() - 10;

            if (new_x_coord == 0) {
                running = false;
                continue;
            }

            entity->set_x_coord(new_x_coord);
        }

        uint16_t flappy_y = this->flappy->get_y_coord();

        printf("prev y: %d\n", flappy_y);
        flappy_y *= FLAPPY_VELOCITY;
        if ((flappy_y + this->flappy->get_height()) >= this->display->get_height()) {
        	printf("*insert coffin dance music*\n"); // TODO debug, remove
        	running = false;
        } else {
        	this->flappy->set_y_coord(flappy_y);
        }
        printf("flappy y: %d\n", flappy_y);
    }
    render();
}

void Game::render() {
    display->ral_clear();
    for (Entity *entity : entities) {
        entity->render(display);
    }
    this->flappy->render(display);
}
