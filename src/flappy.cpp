/*
 * flappy.cpp
 *
 * Omschrijving:	Implementatie van Flappy Bird logica
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#include <cstdio>

#include "flappy.h"
#include "sprite.h"

/**
 * Constructor die ook de startlocatie van de vogel toewijst.
 *
 * @param start_x	De X-coördinaat van de startpositie
 * @param start_y	De Y-coördinaat van de startpositie
 **/
Flappy::Flappy(uint16_t start_x, uint16_t start_y) {
	// Initialiseer entity members
	this->x_coord = start_x;
	this->y_coord = start_y;
	this->width = FLAPPY_SPRITE_WIDTH;
	this->height = FLAPPY_SPRITE_HEIGHT;

	// Bouw een mutable sprite buffer in memory zodat we hem naar RAL kunnen sturen
	this->sprite_buf = new uint16_t*[height];
	for (int y = 0; y < height; ++y) {
		this->sprite_buf[y] = new uint16_t[width];

		for (int x = 0; x < width; ++x) {
			this->sprite_buf[y][x] = FLAPPY_SPRITE[y][x];
		}
	}
}

Flappy::~Flappy() {}

/**
 * @inheritDoc
 **/
void Flappy::render(ral::display *display) {
	display->draw_sprite(x_coord, y_coord, width, height, &sprite_buf);
}

/**
 * @inheritDoc
 **/
uint16_t Flappy::get_width() {
	return width;
}

/**
 * @inheritDoc
 **/
uint16_t Flappy::get_height() {
	return height;
}

/**
 * @inheritDoc
 **/
uint16_t Flappy::get_x_coord() {
	return x_coord;
}

/**
 * @inheritDoc
 **/
uint16_t Flappy::get_y_coord() {
	return y_coord;
}

/**
 * @inheritDoc
 **/
void Flappy::set_height(uint16_t height) {}

/**
 * @inheritDoc
 **/
void Flappy::set_width(uint16_t width) {}

/**
 * @inheritDoc
 **/
void Flappy::set_y_coord(uint16_t y_coord) {
	this->y_coord = y_coord;
}

/**
 * @inheritDoc
 **/
void Flappy::set_x_coord(uint16_t x_coord) {
	this->x_coord = x_coord;
	this->velocity = STARTING_VELOCITY;
}

/**
 * @inheritDoc
 **/
void Flappy::calc_new_velocity() {
	float new_velocity = this->velocity - GRAVITY;

	if (new_velocity <= MAX_SPEED) {
		new_velocity = MAX_SPEED;
	}

	this->velocity = new_velocity;
}

