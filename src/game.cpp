//
// Created by Aran on 03/12/2021.
//

#include "game.h"
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#define PIPE_VELOCITY -5 // pipes bewegen met -10 pixels per tick
#define PIPE_INTERVAL 160 // elke 100 pixels een nieuwe pipe

static void button_pressed_cb(bool is_pressed, void *user_data);

Game::Game(RAL *display, ial *input) : display(display), input(input) {
    this->flappy = new Flappy(50, 150);
    this->input->ial_register_button_callback(0, 0, &button_pressed_cb, this);
}

void Game::create_pipe() {
    uint16_t path = rand() % path_max_height + path_min_height;
    create_pipe(path);
}

void Game::create_pipe(uint16_t path) {
    entities.push_back(new Pipe(true, path, display->get_width(), display->get_height()));
    entities.push_back(new Pipe(false, path, display->get_width(), display->get_height()));
}

void Game::tick() {
	// Maak een nieuwe pipe aan als de laatste pipe X pixels bewogen is
	if (this->last_pipe <= (display->get_width() - PIPE_INTERVAL)) {
		this->last_pipe = display->get_width();
		create_pipe();
	}
	this->last_pipe += PIPE_VELOCITY;

	// Verschuif de pipes, en delete ze zodra ze links weg zijn
	for (std::list<Entity *>::iterator it = entities.begin(); it != entities.end();) {
		Entity *entity = *it;
		uint16_t new_x_coord = entity->get_x_coord() + PIPE_VELOCITY;

		// als entity nog binnen het speelveld is
		if (new_x_coord > 0) {
			entity->set_x_coord(new_x_coord);
			++it;
		} else if (entity->get_width() > 5) {
			entity->set_width(entity->get_width() + PIPE_VELOCITY);
			++it;
		} else {
			it = entities.erase(it);
			delete entity;
		}
	}

	// Update flappy bird position and stop game if he touches the ground
	uint16_t flappy_y = this->flappy->get_y_coord();
    flappy_y -= flappy->velocity;
	if ((flappy_y + this->flappy->get_height()) >= this->display->get_height()) {
		printf("*insert coffin dance music*\n"); // TODO debug, remove
		running = false;
	} else {
        if (flappy_y > 200) {
            flappy_y = 150;
            flappy->velocity = 10;
        }
        this->flappy->set_y_coord(flappy_y);
        this->flappy->calc_new_velocity();
    }
}

void Game::render() {
    display->ral_clear();

    for (Entity *entity : entities) {
        entity->render(display);
    }

    this->flappy->render(display);
}

Flappy *Game::get_flappy() {
	return this->flappy;
}

static void button_pressed_cb(bool is_pressed, void *user_data) {
	((Game *) user_data)->get_flappy()->velocity = 10;
}
