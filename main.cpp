//
// Created by Aran on 30/11/2021.
//


#include <cstdio>
#include <system.h>
#include <unistd.h>
#include "system.h"
#include "library/vga/vga.h"

RAL *display;

void init() {
    printf("Hello from Media Computer!\n");
    display = new VGA();
    display->ral_init();
}

void game() {

}

int main() {
    init();
    while (true) {
        game();
    }
}
