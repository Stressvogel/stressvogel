/*
 * game.cpp
 *
 * Omschrijving:	Klasse die de game state beheert
 * Hoofdauteur:		Aran Kieskamp
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

#include "game.h"
#include "sprite.h"
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
#define PIPE_MIN_STRETCH_WIDTH		5

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
#define FLAPPY_LAUNCH_VELOCITY		10
/**
 * De height waarop de score glyph gerendered wordt
 **/
#define SCORE_GLYPH_Y			25
/**
 * De vergroting van de glyph
 **/
#define SCORE_GLYPH_SCALE		3

/**
 * Welke button we gebruiken om de bird te laten vliegen
 **/
#define FLY_BUTTON_ID			0
/**
 * Welke button we gebruiken om collision borders te toggelen
 **/
#define HITBOX_BUTTON_ID		10
/**
 * Welke priority onze callback heeft binnen IAL.
 **/
#define BUTTON_PRIORITY			0

/**
 * Onnauwkeurige division macro
 **/
#define APPROX_DIV(num, div)		((int) floor(num / div))

/**
 * Een callback functie die wordt aangeroepen zodra er button input is.
 **/
static void fly_button_pressed_cb(bool is_pressed, void *user_data),
	    hitbox_button_pressed_cb(bool is_pressed, void *user_data);

/**
 * Construct en initialiseer de game met de default state.
 **/
Game::Game(ral::display *display, ial::device *input) : display(display), input(input), score(0) {
	// Initialiseer de flappy bird en plaats hem op de startpositie
	this->flappy = new Flappy(FLAPPY_START_X, FLAPPY_START_Y);

	// Initialiseer de score glyph
	this->score_glyph = new Glyph(
			APPROX_DIV(display->get_width(), 2) - APPROX_DIV(GLYPH_SPRITE_WIDTH, 1),
			SCORE_GLYPH_Y,
			SCORE_GLYPH_SCALE
	);
	this->score_glyph->show_int((int) 0);
	this->score = 0;

	// Registreer button callbacks in de IAL
	this->input->register_button_callback(FLY_BUTTON_ID, BUTTON_PRIORITY, &fly_button_pressed_cb, this);
	this->input->register_button_callback(HITBOX_BUTTON_ID, BUTTON_PRIORITY, &hitbox_button_pressed_cb, this);
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
	this->entities.push_back(new Pipe(true, path, display->get_width(), display->get_height()));
	this->entities.push_back(new Pipe(false, path, display->get_width(), display->get_height()));
}

/**
 * @inheritDoc
 **/
void Game::tick() {
	// Maak een nieuwe pipe aan als de laatste pipe X pixels bewogen is
	if (this->last_pipe <= (display->get_width() - PIPE_INTERVAL)) {
		this->last_pipe = display->get_width();
		this->create_pipe();
	}
	this->last_pipe += PIPE_VELOCITY;

	// Verschuif de pipes, en delete ze zodra ze links weg zijn
	bool crossed_pipe = false;
	for (std::list<Entity *>::iterator it = entities.begin(); it != entities.end();) {
		Entity *entity = *it;
		uint16_t new_x_coord = entity->get_x_coord() + PIPE_VELOCITY;

		// Voer AABB collision detection uit tussen de flappy en de pipe
		// Stop het spel als de flappy in aanraking komt met deze pipe
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

	// Check of de flappy bird buiten de speelzone is
	if ((flappy_y + this->flappy->get_height()) >= this->display->get_height()) {
		LOG_INFO("*insert coffin dance music here*");
		running = false;
		if (flappy_y > 9999) {
			this->flappy->set_y_coord(0);
		} else {
			this->flappy->set_y_coord(this->display->get_height() - this->flappy->get_height());
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
	// Teken alle entities
	for (Entity *entity : this->entities) {
		entity->render(this->display);
		DRAW_HITBOX_IF(this->show_hitboxes, this->display, entity->get_x_coord(), entity->get_y_coord(), entity->get_width(), entity->get_height());
	};

	// Teken de flappy bird
	LOG_MEASURE(this->flappy->render(this->display));
	DRAW_HITBOX_IF(this->show_hitboxes, this->display, flappy->get_x_coord(), flappy->get_y_coord(), flappy->get_width(), flappy->get_height());

	// Teken de huidige score
	this->score_glyph->render(this->display);

	// Clear het scherm + wacht op buffer swap
	LOG_MEASURE(this->display->clear());
}

/**
 * @inheritDoc
 **/
void Game::reset() {
	// Delete alle entities uit de entity list
	for (std::list<Entity *>::iterator it = entities.begin(); it != entities.end();) {
		Entity *entity = *it;
		it = entities.erase(it);
		delete entity;
	}

	// Reset de game state
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
static void fly_button_pressed_cb(bool is_pressed, void *user_data) {
	Game *game = (Game *) user_data;

	// Button is ingedrukt, doe niks.
	if (!is_pressed) return;

	// Als de game loopt, laat de bird vliegen.
	// Als de game voorbij is, reset de game.
	if (game->running) {
		game->get_flappy()->velocity = FLAPPY_LAUNCH_VELOCITY;
	} else {
		game->reset();
	}
}


/**
 * @inheritDoc
 **/
static void hitbox_button_pressed_cb(bool is_pressed, void *user_data) {
	// Button is ingedrukt, doe niks.
	if (!is_pressed) return;

	((Game *) user_data)->show_hitboxes ^= true;
}
