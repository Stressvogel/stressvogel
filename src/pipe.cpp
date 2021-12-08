//
// Created by Aran on 03/12/2021.
//

#include "pipe.h"

Pipe::~Pipe() {}

Pipe::Pipe(bool upper, uint16_t path, uint16_t screen_width, uint16_t screen_height) {
    width = PIPE_WIDTH;
    x_coord = screen_width + (PIPE_START_X_RELATIVE);

    // Is deze pipe bovenaan of onderaan het scherm gespawned?
    if (upper) {
        y_coord = 0;
        height = path;
    } else {
        y_coord = path + path_height;
        height = screen_height - y_coord;
    }
}

/**
 * @inheritDoc
 **/
void Pipe::render(RAL *display) {
    uint16_t width = this->width;

    // Voorkom dat een deel van de rechterkant van de pipe naast het scherm wordt getekend
    if (x_coord + width > display->get_width()) {
        width = display->get_width() - x_coord;
    }

    display->ral_draw_box(x_coord, y_coord, width, height, color);
}

/**
 * @inheritDoc
 **/
void Pipe::set_color(uint16_t color) {}

/**
 * @inheritDoc
 **/
uint16_t Pipe::get_width() {
    return width;
}

/**
 * @inheritDoc
 **/
uint16_t Pipe::get_height() {
    return height;
}

/**
 * @inheritDoc
 **/
uint16_t Pipe::get_x_coord() {
    return x_coord;
}

/**
 * @inheritDoc
 **/
uint16_t Pipe::get_y_coord() {
    return y_coord;
}

/**
 * @inheritDoc
 **/
void Pipe::set_height(uint16_t height) {}

/**
 * @inheritDoc
 **/
void Pipe::set_width(uint16_t width) {
	this->width = width;
}

/**
 * @inheritDoc
 **/
void Pipe::set_y_coord(uint16_t y_coord) {}

/**
 * @inheritDoc
 **/
void Pipe::set_x_coord(uint16_t x_coord) {
    this->x_coord = x_coord;
}
