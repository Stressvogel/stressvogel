//
// Created by Aran on 03/12/2021.
//

#include "game.h"

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cmath>

#include "sprite.h"

#define LOG_ENABLE
#include "log.h"

/**
 * Hoeveel pixels de pipes met elke gametick opschuiven.
 **/
#define PIPE_VELOCITY			-5
/**
 * Om de hoeveel pixels er een nieuwe pipe gegenereerd moet worden.
 **/
#define PIPE_INTERVAL			160
/**
 * De minimale stretch voordat een pipe verwijderd wordt.
 **/
#define PIPE_MIN_STRETCH_WIDTH	5

/**
 * Startpositie van de flappy (X-coordinaat)
 **/
#define FLAPPY_START_X			50
/**
 * Startpositie van de flappy (Y-coordinaat)
 **/
#define FLAPPY_START_Y			150
/**
 * De snelheid met waarmee de flappy omhoog gaat zodra er op de button wordt gedrukt.
 **/
#define FLAPPY_LAUNCH_VELOCITY	10
/**
 * De height waarop de score glyph gerendered wordt
 **/
#define SCORE_GLYPH_Y			25
/**
 * De vergroting van de glyph
 **/
#define SCORE_GLYPH_SCALE		3

/**
 * Welke button we gebruiken.
 **/
#define BUTTON_ID				0
/**
 * Welke priority onze callback heeft binnen IAL.
 **/
#define BUTTON_PRIORITY			0

/**
 * Onnauwkeurige division macro
 */
#define APPROX_DIV(num, div)	((int) floor(num / div))

/**
 * De callback functie die wordt aangeroepen zodra er button input is.
 **/
static void button_pressed_cb(bool is_pressed, void *user_data);

Game::Game(RAL *display, ial *input) : display(display), input(input) {
    this->flappy = new Flappy(FLAPPY_START_X, FLAPPY_START_Y);
    this->score_glyph = new Glyph(APPROX_DIV(display->get_width(), 2) - APPROX_DIV(GLYPH_SPRITE_WIDTH, 1), SCORE_GLYPH_Y, SCORE_GLYPH_SCALE);
    this->score_glyph->show_int((int) 0);
    this->score = 0;
    this->input->ial_register_button_callback(BUTTON_ID, BUTTON_PRIORITY, &button_pressed_cb, this);
}

/**
 * @inheritDoc
 **/
void Game::create_pipe() {
    uint16_t path = rand() % path_max_height + path_min_height;
    create_pipe(path);
}

/**
 * @inheritDoc
 **/
void Game::create_pipe(uint16_t path) {
    entities.push_back(new Pipe(true, path, display->get_width(), display->get_height()));
    entities.push_back(new Pipe(false, path, display->get_width(), display->get_height()));
}

/**
 * @inheritDoc
 **/
void Game::tick() {
	// Maak een nieuwe pipe aan als de laatste pipe X pixels bewogen is
	if (this->last_pipe <= (display->get_width() - PIPE_INTERVAL)) {
		this->last_pipe = display->get_width();
		create_pipe();
	}
	this->last_pipe += PIPE_VELOCITY;

	// Verschuif de pipes, en delete ze zodra ze links weg zijn
	bool crossed_pipe = false;
	for (std::list<Entity *>::iterator it = entities.begin(); it != entities.end();) {
		Entity *entity = *it;
		uint16_t new_x_coord = entity->get_x_coord() + PIPE_VELOCITY;

		// als de flappy in aanraking komt met deze pipe
		if (flappy->get_x_coord() < entity->get_x_coord() + entity->get_width() &&
		    flappy->get_x_coord() + flappy->get_width() > entity->get_x_coord() &&
		    flappy->get_y_coord() < entity->get_y_coord() + entity->get_height() &&
		    flappy->get_y_coord() + flappy->get_height() > entity->get_y_coord()) {

		    this->running = false;
		    return;
		}

		// als deze pipe nog binnen het speelveld is
		if (new_x_coord > 0) {
			entity->set_x_coord(new_x_coord);
			++it;
		} else if (entity->get_width() > PIPE_MIN_STRETCH_WIDTH) {
			entity->set_width(entity->get_width() + PIPE_VELOCITY);
			++it;
		} else {
			crossed_pipe = true;
			it = entities.erase(it);
			delete entity;
		}
	}

	// Verhoog de score als de flappy veilig door een pipe heen is gevlogen
	if (crossed_pipe) {
		this->score_glyph->show_int((int) ++score);
	}

	// Update flappy bird position and stop game if he touches the ground
	uint16_t flappy_y = this->flappy->get_y_coord();
    flappy_y -= flappy->velocity;

	if ((flappy_y + this->flappy->get_height()) >= this->display->get_height()) { // TODO swapfix
		LOG_INFO("*insert coffin dance music here*");
		running = false;
		if (flappy_y > 9999) {
			this->flappy->set_y_coord(0); // TODO swapfix
		} else {
			this->flappy->set_y_coord(this->display->get_height() - this->flappy->get_height()); // TODO swapfix
		}
	} else {
        this->flappy->set_y_coord(flappy_y);
        this->flappy->calc_new_velocity();
    }
}

/**
 * @inheritDoc
 **/
void Game::render() {
    for (Entity *entity : entities) {
        entity->render(display);
    }

    this->flappy->render(display);

    this->score_glyph->render(display);

    display->ral_clear();
}

/**
 * @inheritDoc
 **/
void Game::reset() {
	for (std::list<Entity *>::iterator it = entities.begin(); it != entities.end();) {
		Entity *entity = *it;
		it = entities.erase(it);
		delete entity;
	}
	this->last_pipe = 0;
	this->flappy->set_x_coord(FLAPPY_START_X);
	this->flappy->set_y_coord(FLAPPY_START_Y);
	this->running = true;
	this->score = 0;
	this->score_glyph->show_int((int) this->score);
}

/**
 * @inheritDoc
 **/
Flappy *Game::get_flappy() {
	return this->flappy;
}

/**
 * @inheritDoc
 **/
static void button_pressed_cb(bool is_pressed, void *user_data) {
	Game *game = (Game *) user_data;

	// button is losgelaten, doe niks.
	if (!is_pressed) return;

	if (game->running) {
		game->get_flappy()->velocity = FLAPPY_LAUNCH_VELOCITY;
	} else {
		game->reset();
	}
}
