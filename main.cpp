//
// Created by Aran on 30/11/2021.
//


#include <cstdio>
#include <system.h>
#include <unistd.h>
#include "system.h"
#include "library/vga/vga.h"
#include "src/game.h"

// sterkte met het simpeler maken van deze macro's
#define SECONDS_TO_US(second)	(second * 1000000)
#define TICKS_TO_US(fps)		((int)(((float)(1.0f/((float)fps)))*SECONDS_TO_US(1)))

RAL *display;
Game *game;

void init() {
    printf("Hello from Media Computer!\n");
    display = new VGA();
    display->ral_init();
    game = new Game(display);
}


int main() {
    init();
    while (game->running) {
        game->tick();
        usleep(TICKS_TO_US(5)); // zoveel ticks per seconde... hier kun je gwn de float van de
    }
}
