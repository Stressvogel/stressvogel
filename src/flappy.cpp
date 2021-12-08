/*
 * flappy.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#include <cstdio>

#include "flappy.h"
#include "sprite.h"

Flappy::Flappy(uint16_t start_x, uint16_t start_y) {
	// Initialize entity member
	this->x_coord = start_x;
	this->y_coord = start_y;
	this->width = FLAPPY_SPRITE_WIDTH;
	this->height = FLAPPY_SPRITE_HEIGHT;

	// Bouw een mutatable sprite buffer in memory zodat we hem naar RAL kunnen sturen
	this->sprite_buf = new uint16_t*[height];
	for (int y = 0; y < height; ++y) {
		this->sprite_buf[y] = new uint16_t[width];
	    for (int x = 0; x < width; ++x) {
	    	this->sprite_buf[y][x] = FLAPPY_SPRITE[y][x];
	    }
	}
}

Flappy::~Flappy() {

}

/**
 * @inheritDoc
 **/
void Flappy::render(RAL *display) {
    display->ral_draw_sprite(x_coord, y_coord, width, height, &sprite_buf);
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
}

/**
 * @inheritDoc
 **/
void Flappy::calc_new_velocity() {
    float new_velocity = velocity - GRAVITY;
    if (new_velocity <= MAX_SPEED) {
        new_velocity = MAX_SPEED;
    }
    velocity = new_velocity;
}
