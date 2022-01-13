/*
 * pipe.h
 *
 * Omschrijving:	Een pipe obstakel in het speelveld
 * Hoofdauteur:		Aran Kieskamp
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_PIPE_H
#define SOFTWARE_PIPE_H

#include "entity.h"

/**
 * De breedte van een pipe in pixels.
 **/
#define PIPE_WIDTH		(40)

/**
 * De X-offset met de rechterkant van het scherm zodra de pipe spawnt.
 **/
#define PIPE_START_X_RELATIVE	(-10)

/**
 * De hoogte van de opening in vergelijking met Y=0.
 **/
#define PIPE_PATH_HEIGHT	(60)

/**
 * De standaardkleur van een pipe (groen)
 **/
#define PIPE_DEFAULT_COLOR	(0x07E0)

/**
 * Een pipe is een obstakel dat de speler moet vermijden.<br/>
 * <br/>
 * Zodra een pipe aangeraakt wordt zal het spel worden be"eindigd.
 **/
class Pipe : public Entity {
private:
	/**
	 * @ref pipe.h+PIPE_PATH_HEIGHT
	 **/
	uint16_t path_height = PIPE_PATH_HEIGHT;

	/**
	 * Of deze pipe aan het plafond hangt of op de grond staat :)
	 **/
	bool upper;

protected:
	/**
	 * @ref pipe.h+PIPE_DEFAULT_COLOR
	 **/
	uint16_t color = 0x07E0;

public:
	/**
	 * Maak een nieuwe pipe aan met default values.
	 *
	 * @param upper		Of de pipe aan het plafond hangt of op de grond staat
	 * @param path		De hoogte van de doorgang
	 * @param screen_width	De totale breedte van het display
	 * @param screen_height	De totale hoogte van het display
	 **/
	Pipe(bool upper, uint16_t path, uint16_t screen_width, uint16_t screen_height);

	virtual ~Pipe();

	/**
	 * Wijzig de kleur van de pipe.
	 *
	 * @param color		16-bit integer met de RGB565 color value.
	 **/
	void set_color(uint16_t color);

	/**
	 * @inheritDoc
	 **/
	uint16_t get_width();

	/**
	 * @inheritDoc
	 **/
	uint16_t get_height();

	/**
	 * @inheritDoc
	 **/
	uint16_t get_x_coord();

	/**
	 * @inheritDoc
	 **/
	uint16_t get_y_coord();

	/**
	 * @inheritDoc
	 **/
	void set_height(uint16_t height);

	/**
	 * @inheritDoc
	 **/
	void set_width(uint16_t width);

	/**
	 * @inheritDoc
	 **/
	void set_y_coord(uint16_t y_coord);

	/**
	 * @inheritDoc
	 **/
	void set_x_coord(uint16_t x_coord);

	/**
	 * @inheritDoc
	 **/
	void render(ral::display *display);
};


#endif //SOFTWARE_PIPE_H

