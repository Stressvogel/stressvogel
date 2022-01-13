/*
 * glyph.cpp
 *
 * Omschrijving:	Dit representeert een cijfer op het scherm
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#include <array>
#include <cstdio>
#include <math.h>

#include "glyph.h"
#include "sprite.h"

/**
 * Ascii nummers starten op 0x30
 **/
#define GLPYH_INDEX_START_OFFSET	0x30

/**
 * Lijst van pointers naar alle glyphs waarbij '0' start op positie 0.  
 **/
const uint16_t (*GLYPH_INDEX[])[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		&GLYPH_0_SPRITE, &GLYPH_1_SPRITE, &GLYPH_2_SPRITE, &GLYPH_3_SPRITE,
		&GLYPH_4_SPRITE, &GLYPH_5_SPRITE, &GLYPH_6_SPRITE, &GLYPH_7_SPRITE,
		&GLYPH_8_SPRITE, &GLYPH_9_SPRITE
};

/**
 * @inheritDoc
 **/
Glyph::Glyph(uint16_t x, uint16_t y, uint8_t scale) {
	// Initialiseer entity members
	this->x_coord = x;
	this->y_coord = y;
	this->width = GLYPH_SPRITE_WIDTH * scale;
	this->height = GLYPH_SPRITE_HEIGHT * scale;

	// Initialiseer glyph superklasse members
	this->scale = scale;

	// Bouw een mutatable sprite buffer in memory zodat we hem naar RAL kunnen sturen
	// Deze vullen we in ::rebuild()
	this->sprite_buf = new uint16_t*[height];
}

Glyph::~Glyph() {}

/**
 * @inheritDoc
 **/
void Glyph::show_int(char new_char) {
	show_int(new_char - GLPYH_INDEX_START_OFFSET);
}

/**
 * @inheritDoc
 **/
void Glyph::show_int(int new_int) {
	// Bouw een mutatable sprite buffer in memory zodat we hem naar RAL kunnen sturen
	for (int y = 0; y < height; ++y) {
		this->sprite_buf[y] = new uint16_t[width];

		for (int x = 0; x < width; ++x) {
			// Als scale groter is dan 1, dan wordt er hard edge intepoleration
			// voor resampling gebruikt door de dichtstbijzijnde pixel voor
			// de virtuele locatie te vinden
			this->sprite_buf[y][x] = (*GLYPH_INDEX[new_int])[(int) floor(y / scale)][(int) floor(x / scale)];
		}
	}
}

/**
 * @inheritDoc
 **/
void Glyph::render(ral::display *display) {
	// Geef een pointer naar de sprite buffer mee aan de RAL
	display->draw_sprite(x_coord, y_coord, width, height, &sprite_buf);
}

/**
 * @inheritDoc
 **/
uint16_t Glyph::get_width() {
	return width;
}

/**
 * @inheritDoc
 **/
uint16_t Glyph::get_height() {
	return height;
}

/**
 * @inheritDoc
 **/
uint16_t Glyph::get_x_coord() {
	return x_coord;
}

/**
 * @inheritDoc
 **/
uint16_t Glyph::get_y_coord() {
	return y_coord;
}

/**
 * @inheritDoc
 **/
void Glyph::set_height(uint16_t height) {}

/**
 * @inheritDoc
 **/
void Glyph::set_width(uint16_t width) {}

/**
 * @inheritDoc
 **/
void Glyph::set_y_coord(uint16_t y_coord) {
	this->y_coord = y_coord;
}

/**
 * @inheritDoc
 **/
void Glyph::set_x_coord(uint16_t x_coord) {
	this->x_coord = x_coord;
}

