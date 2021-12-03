//
// Created by Aran on 30/11/2021.
//


#include <cstdio>
#include <system.h>
#include <unistd.h>
#include "system.h"
#include "library/vga/vga.h"

ral *display;

void init() {
    printf("Hello from Media Computer!\n");
    display = new VGA();
    display->ral_init();
}

void test() {
    for (int i = 0; i < 120; ++i) {
        display->ral_clear();
        display->ral_draw_box(0 + i, 0 + i, 320 - 2 * i, 240 - 2 * i, 0x07E0);
//        alt_up_video_dma_draw_string(pixel_buffer, "Green", 160,120,0);
        usleep(250000);
    }
}

int main() {
    init();
    test();
}
