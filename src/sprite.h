/*
 * sprite.h
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_SPRITE_H_
#define SOFTWARE_SPRITE_H_


/* -------------------------------------------------------------------------
 * Basiskleuren
 * ------------------------------------------------------------------------- */

#define T 0xDEAD // transparant, wordt niet gerendered.
//#define B 0x0000 // zwart
#define B 0x39C8 // zwart-grijs-achtig
#define W 0xFFFF // wit

/* -------------------------------------------------------------------------
 * Kleuren voor de flappy bird
 * ------------------------------------------------------------------------- */

#define Y 0xFF47 // geel
#define D 0xFE00 // donkergeel
#define O 0xFCC0 // oranje


#define FLAPPY_SPRITE_HEIGHT 12
#define FLAPPY_SPRITE_WIDTH 17

/**
 * Sprite data voor de Flappy Bird.
 *
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

#endif /* SOFTWARE_SPRITE_H_ */
