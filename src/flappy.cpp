/*
 * flappy.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#include <cstdio>

#include "flappy.h"
#include "sprite.h"

Flappy::Flappy(uint16_t start_x, uint16_t start_y) : baseline_x(start_x) {
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

void Flappy::render(RAL *display) {
    display->ral_draw_sprite(x_coord, y_coord, width, height, &sprite_buf);
}

void Flappy::set_color(uint16_t color) {

}

uint16_t Flappy::get_width() {
    return width;
}

uint16_t Flappy::get_height() {
    return height;
}

uint16_t Flappy::get_x_coord() {
    return x_coord;
}

uint16_t Flappy::get_y_coord() {
    return y_coord;
}

void Flappy::set_height(uint16_t height) {}

void Flappy::set_width(uint16_t width) {}

void Flappy::set_y_coord(uint16_t y_coord) {
	this->y_coord = y_coord;
}

void Flappy::set_x_coord(uint16_t x_coord) {
    this->x_coord = x_coord;
}
