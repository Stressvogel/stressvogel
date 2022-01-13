/*
 * pipe.cpp
 *
 * Omschrijving:	Een pipe obstakel in het speelveld
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#include <cmath>

#include "pipe.h"
#include "sprite.h"

#define PIPE_HEAD_BORDER_SIZE				(1)
#define PIPE_HEAD_HEIGHT				(18)
#define PIPE_TAIL_OFFSET				(1 + PIPE_HEAD_BORDER_SIZE)
#define PIPE_TAIL_BORDER_SIZE				(1)
#define PIPE_TAIL_GRADIENT_SPLIT_X			(10)

// De Altera resampler header heeft andere dependencies die wij niet nodig hebben,
// dus we hebben alleen de nodige macro´s gekopieerd.

#define ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_R(c)	((c >> 11) & 0x1F)
#define ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_G(c)	((c >>  5) & 0x3F)
#define ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_B(c)	((c >>  0) & 0x1F)
#define ALT_UP_VIDEO_RESAMPLE_RGB_TO_30BIT_RGB(r,g,b)	((r << 20) | (g << 10) | (b << 0))
#define ALT_UP_VIDEO_RESAMPLE_RGB_TO_16BIT_RGB(r,g,b)	((b << 11) | (g << 5) | (r << 0))
#define ALT_UP_VIDEO_RESAMPLE_RGB_30BIT_TO_16BIT(c)	(((c >>  8) & 0x0000F800) | ((c >>  5) & 0x000007E0) | ((c >> 3) & 0x0000001F))

#define CHECK_INTEGER_OVERFLOW(val)			(val = (val > 9999 ? 0 : val))

/**
 * Functie die een horizontale gradient tekent.
 **/
static void _ral_draw_hz_gradient(ral::display *display, uint16_t x, uint16_t y,
				  uint16_t width, uint16_t height, uint16_t start_color, uint16_t end_color);

Pipe::Pipe(bool upper, uint16_t path, uint16_t screen_width, uint16_t screen_height) : upper(upper) {
    this->width = PIPE_WIDTH;
    this->x_coord = screen_width + (PIPE_START_X_RELATIVE);

    // Is deze pipe bovenaan of onderaan het scherm gespawned?
    if (upper) {
    	this->y_coord = 0;
    	this->height = path;
    } else {
    	this->y_coord = path + this->path_height;
    	this->height = screen_height - this->y_coord;
    }
}

Pipe::~Pipe() {}

/**
 * @inheritDoc
 **/
void Pipe::render(ral::display *display) {
	uint16_t width = this->width;
	
	// Voorkom dat een deel van de rechterkant van de pipe naast het scherm wordt getekend
	if (this->x_coord + width > display->get_width()) {
		width = display->get_width() - this->x_coord;
	}

	// Tail border
	display->draw_box(
		this->x_coord + PIPE_TAIL_OFFSET,
		this->y_coord, width - (PIPE_TAIL_OFFSET * 2),
		this->height,
		B,
		false
	);

	// Tail gradient links van de split
	_ral_draw_hz_gradient(
		display,
		this->x_coord + PIPE_TAIL_OFFSET + PIPE_TAIL_BORDER_SIZE,
		this->y_coord,
		width < PIPE_TAIL_GRADIENT_SPLIT_X ? width : PIPE_TAIL_GRADIENT_SPLIT_X,
		this->height,
		G,
		L
	);
	// Tail gradient rechts van de split
	_ral_draw_hz_gradient(
		display,
		this->x_coord + PIPE_TAIL_OFFSET + PIPE_TAIL_BORDER_SIZE + PIPE_TAIL_GRADIENT_SPLIT_X,
		this->y_coord,
		width - (PIPE_TAIL_OFFSET * 2) - (PIPE_TAIL_BORDER_SIZE * 2) - (PIPE_TAIL_GRADIENT_SPLIT_X),
		this->height,
		L,
		G
	);

	// Als de pipe een upper pipe is moeten we de head onderaan de tail tekenen
	// en als het een lower pipe is moeten we de head bovenaan de tail tekenen
	if (this->upper) {
		// Teken de border van het hoofd van de pipe onderaan de tail
		display->draw_box(
			this->x_coord,
			this->y_coord + this->height - PIPE_HEAD_HEIGHT,
			width,
			PIPE_HEAD_HEIGHT,
			B,
			false
		);

		// Teken een gradient van de head
		_ral_draw_hz_gradient(
			display,
			this->x_coord + PIPE_HEAD_BORDER_SIZE,
			this->y_coord + this->height - PIPE_HEAD_HEIGHT + PIPE_HEAD_BORDER_SIZE,
			width - (PIPE_HEAD_BORDER_SIZE * 2),
			PIPE_HEAD_HEIGHT - (PIPE_HEAD_BORDER_SIZE * 2),
			L,
			G
		);
	} else {
		// Teken de border van het hoofd van de pipe bovenaan de tail
		display->draw_box(this->x_coord, this->y_coord, width, PIPE_HEAD_HEIGHT, B, false);

		// Teken een gradient van de head
		_ral_draw_hz_gradient(
				display,
				this->x_coord + PIPE_HEAD_BORDER_SIZE,
				this->y_coord + PIPE_HEAD_BORDER_SIZE,
				width - (PIPE_HEAD_BORDER_SIZE * 2),
				PIPE_HEAD_HEIGHT - (PIPE_HEAD_BORDER_SIZE * 2),
				L,
				G
		);
	}
}

/**
 * @inheritDoc
 **/
void Pipe::set_color(uint16_t color) {}

/**
 * @inheritDoc
 **/
uint16_t Pipe::get_width() {
	return this->width;
}

/**
 * @inheritDoc
 **/
uint16_t Pipe::get_height() {
	return this->height;
}

/**
 * @inheritDoc
 **/
uint16_t Pipe::get_x_coord() {
	return this->x_coord;
}

/**
 * @inheritDoc
 **/
uint16_t Pipe::get_y_coord() {
	return this->y_coord;
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

/**
 * @inheritDoc
 **/
static void _ral_draw_hz_gradient(ral::display *display, uint16_t x, uint16_t y,
				  uint16_t width, uint16_t height, uint16_t start_color, uint16_t end_color) {

	CHECK_INTEGER_OVERFLOW(width);
	CHECK_INTEGER_OVERFLOW(height);
	CHECK_INTEGER_OVERFLOW(x);
	CHECK_INTEGER_OVERFLOW(y);

	// We moeten R, G, B splitsen... zie het Technisch Ontwerp

	float	r_start = ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_R(start_color),
			g_start = ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_G(start_color),
			b_start = ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_B(start_color),
			r_end = ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_R(end_color),
			g_end = ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_G(end_color),
			b_end = ALT_UP_VIDEO_RESAMPLE_RGB_16BIT_EXTRACT_B(end_color);
	float	r_increment = ((r_end - r_start) / width),
			g_increment = ((g_end - g_start) / width),
			b_increment = ((b_end - b_start) / width),
			r_current = r_start,
			g_current = g_start,
			b_current = b_start;

	for (uint16_t i = 0; i < width; ++i) {
		display->draw_box(x + i, y, 1, height, ALT_UP_VIDEO_RESAMPLE_RGB_TO_16BIT_RGB((int)r_current, (int)g_current, (int)b_current));
		r_current += r_increment;
		g_current += g_increment;
		b_current += b_increment;
	}
}
