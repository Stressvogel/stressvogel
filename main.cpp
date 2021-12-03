//
// Created by Aran on 30/11/2021.
//


#include <cstdio>
#include <system.h>
#include <unistd.h>
#include "system.h"
#include "library/vga/vga.h"
#include "src/game.h"

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
        usleep(1000000);
    }
}
