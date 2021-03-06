/*
 * sprite.h
 *
 * Omschrijving:	Kleuren en sprite data. We hadden geen tijd om deze in de ROM te zetten.
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_SPRITE_H_
#define SOFTWARE_SPRITE_H_


/* -------------------------------------------------------------------------
 * Basiskleuren
 * ------------------------------------------------------------------------- */

#define T			(0xDEAD) // transparant, wordt niet gerendered.
//#define B			(0x0000) // zwart
#define B			(0x39C8) // zwart-grijs-achtig
#define W			(0xFFFF) // wit
#define R			(0xF800) // rood

/* -------------------------------------------------------------------------
 * Kleuren voor de flappy bird
 * ------------------------------------------------------------------------- */

#define Y			(0xFF47) // geel
#define D			(0xFE00) // donkergeel
#define O			(0xFCC0) // oranje

/* -------------------------------------------------------------------------
 * Kleuren voor de pipes
 * ------------------------------------------------------------------------- */
#define G			(0x5403)
#define L			(0xB6AD)


#define FLAPPY_SPRITE_HEIGHT	(12)
#define FLAPPY_SPRITE_WIDTH	(17)

#define GLYPH_SPRITE_HEIGHT	(8)
#define GLYPH_SPRITE_WIDTH	(6)

/**
 * Sprite data voor de Flappy Bird.<br />
 * <br />
 * Het is een array met een lengte van 12 met daarin
 * arrays met lengtes van 17 die de pixels bevatten.
 **/
const uint16_t FLAPPY_SPRITE[FLAPPY_SPRITE_HEIGHT][FLAPPY_SPRITE_WIDTH] = {
		{T, T, T, T, T, T, B, B, B, B, B, B, T, T, T, T, T},
		{T, T, T, T, B, B, Y, Y, Y, Y, B, W, B, T, T, T, T},
		{T, T, T, B, Y, Y, Y, Y, Y, B, W, W, W, B, T, T, T},
		{T, B, B, B, B, Y, Y, Y, Y, B, W, W, B, W, B, T, T},
		{B, W, W, W, W, B, Y, Y, Y, B, W, W, B, W, B, T, T},
		{B, W, W, W, W, W, B, Y, Y, Y, B, W, B, W, B, T, T},
		{B, Y, W, W, Y, B, Y, Y, Y, Y, Y, B, B, B, B, B, T},
		{T, B, Y, Y, Y, B, Y, Y, Y, Y, B, O, O, O, O, O, B},
		{T, T, B, B, B, O, O, O, O, B, O, B, B, B, B, B, T},
		{T, T, T, T, B, O, O, O, O, O, B, O, O, O, O, B, T},
		{T, T, T, T, T, B, B, O, O, O, O, B, B, B, B, B, T},
		{T, T, T, T, T, T, T, B, B, B, B, T, T, T, T, T, T},
};

/**
 * Teken een collision box om een bepaalde regio.
 **/
#define DRAW_HITBOX(display_ptr, x, y, width, height) \
		(display_ptr->draw_box(x, y, width, height, 0xF800, false))

/**
 * Teken een collision box om een bepaalde regio als <b>cond</b> waar is.
 **/
#define DRAW_HITBOX_IF(cond, display_ptr, x, y, width, height) \
		{if (cond) {(DRAW_HITBOX(display_ptr, x, y, width, height));}}

const uint16_t GLYPH_0_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, W, B, W, B, B},
		{B, W, B, W, B, B},
		{B, W, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, B, B, B},
		{T, B, B, B, B, B},
};

const uint16_t GLYPH_1_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, B, W, W, B, B},
		{T, B, W, W, B, B},
		{T, B, W, W, B, B},
		{T, B, W, W, B, B},
		{T, B, B, B, B, B},
		{T, T, B, B, B, B},
};

const uint16_t GLYPH_2_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, B, B, W, B, B},
		{B, W, W, W, B, B},
		{B, W, B, B, B, B},
		{B, W, W, W, B, B},
		{B, B, B, B, B, B},
		{T, B, B, B, B, B},
};


const uint16_t GLYPH_3_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, B, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, B, B, B},
		{T, B, B, B, B, B},
};

const uint16_t GLYPH_4_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, B, W, B, B},
		{B, W, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, W, B, B},
		{T, T, B, W, B, B},
		{T, T, B, B, B, B},
		{T, T, T, B, B, B},
};

const uint16_t GLYPH_5_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, W, B, B, B, B},
		{B, W, W, W, B, B},
		{B, B, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, B, B, B},
		{T, B, B, B, B, B},
};


const uint16_t GLYPH_6_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, W, B, B, B, B},
		{B, W, W, W, B, B},
		{B, W, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, B, B, B},
		{T, B, B, B, B, B},
};

const uint16_t GLYPH_7_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, B, B, W, B, B},
		{T, T, B, W, B, B},
		{T, T, B, W, B, B},
		{T, T, B, W, B, B},
		{T, T, B, B, B, B},
		{T, T, T, B, B, B},
};

const uint16_t GLYPH_8_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, W, B, W, B, B},
		{B, W, W, W, B, B},
		{B, W, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, B, B, B},
		{T, B, B, B, B, B},
};

const uint16_t GLYPH_9_SPRITE[GLYPH_SPRITE_HEIGHT][GLYPH_SPRITE_WIDTH] = {
		{B, B, B, B, B, T},
		{B, W, W, W, B, B},
		{B, W, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, W, B, B},
		{B, W, W, W, B, B},
		{B, B, B, B, B, B},
		{T, B, B, B, B, B},
};

#endif /* SOFTWARE_SPRITE_H_ */

