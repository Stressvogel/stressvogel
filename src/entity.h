/*
 * entity.h
 *
 * Omschrijving:	Een object in het speelveld
 * Hoofdauteur:		Aran Kieskamp
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_ENTITY_H
#define SOFTWARE_ENTITY_H

#include "../library/ral/ral_display.h"

/**
 * Een "entiteit" in ons speelveld, bijvoorbeeld de Flappy Bird of een pipe.<br/>
 * <br/>
 * Het is een pure virtual class (aka interface)
 **/
class Entity {
protected:
	/**
	 * De breedte van de entity in pixels
	 **/
	uint16_t width;

	/**
	 * De hoogte van de entity in pixels
	 **/
	uint16_t height;

	/**
	 * Het huidige X-coordinaat van de entity in pixels
	 **/
	uint16_t x_coord;

	/**
	 * Het huidige Y-coordinaat van de entity in pixels
	 **/
	uint16_t y_coord;

public:
	/**
	 * @private
	 **/ 
	virtual ~Entity() = default;

	/**
	 * Verkrijg de breedte van de entity in pixels
	 **/
	virtual uint16_t get_width() = 0;

	/**
	 * Verkrijg de hoogte van de entity in pixels
	 **/
	virtual uint16_t get_height() = 0;

	/**
	 * Verkrijg het huidige X-coordinaat van de entity in pixels
	 **/
	virtual uint16_t get_x_coord() = 0;

	/**
	 * Verkrijg het huidige Y-coordinaat van de entity in pixels
	 **/
	virtual uint16_t get_y_coord() = 0;

	/**
	 * Set de breedte van de entity in pixels
	 **/
	virtual void set_width(uint16_t width) = 0;

	/**
	 * Set de hoogte van de entity in pixels
	 **/
	virtual void set_height(uint16_t height) = 0;

	/**
	 * Set het huidige X-coordinaat van de entity in pixels
	 **/
	virtual void set_x_coord(uint16_t x_coord) = 0;

	/**
	 * Verkrijg het huidige Y-coordinaat van de entity in pixels
	 **/
	virtual void set_y_coord(uint16_t y_coord) = 0;

	/**
	 * Teken het speelveld in een display buffer
	 **/
	virtual void render(ral::display *display) = 0;

};

#endif //SOFTWARE_ENTITY_H

