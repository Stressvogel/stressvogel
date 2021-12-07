/*
 * flappy.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#include "flappy.h"
#include <cstdio>

Flappy::Flappy(uint16_t start_x, uint16_t start_y) {
	this->x_coord = start_x;
	this->y_coord = start_y;
	this->width = 20;
	this->height = 20;
	this->color = 0xFFE0;
}

Flappy::~Flappy() {

}

void Flappy::render(RAL *display) {
    uint16_t height = this->height;
    if (y_coord + height > display->get_height()) {
        height = display->get_height() - y_coord;
    }
    display->ral_draw_box(x_coord, y_coord, width, height, color);
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
