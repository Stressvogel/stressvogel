//
// Created by Aran on 03/12/2021.
//

#include "pipe.h"

Pipe::~Pipe() {

}

Pipe::Pipe(bool upper, uint16_t path, uint16_t screen_width, uint16_t screen_height) {
    width = 40;
    x_coord = screen_width - 10;
    if (upper) {
        y_coord = 0;
        height = path;
    } else {
        y_coord = path + path_height;
        height = screen_height - y_coord;
        color = 0x001F;
    }
}

void Pipe::render(RAL *display) {
    uint16_t width = this->width;

    if (x_coord + width > display->get_width()) {
        width = display->get_width() - x_coord;
    }

    display->ral_draw_box(x_coord, y_coord, width, height, color);
}

void Pipe::set_color(uint16_t color) {}

uint16_t Pipe::get_width() {
    return width;
}

uint16_t Pipe::get_height() {
    return height;
}

uint16_t Pipe::get_x_coord() {
    return x_coord;
}

uint16_t Pipe::get_y_coord() {
    return y_coord;
}

void Pipe::set_height(uint16_t height) {}

void Pipe::set_width(uint16_t width) {
	this->width = width;
}

void Pipe::set_y_coord(uint16_t y_coord) {}

void Pipe::set_x_coord(uint16_t x_coord) {
    this->x_coord = x_coord;
}
