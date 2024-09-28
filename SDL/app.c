#include "sim.h"

const int MARGIN = 10;

void drawCircle(const int x, const int y, const int radius, const int color) {
    for (int w = -radius; w <= radius; w++) {
        for (int h = -radius; h <= radius; h++) {
            if ((w * w + h * h) <= (radius * radius)) {
                simPutPixel(x + w, y + h, color);
            }
        }
    }
}

int getRadius(const int x, const int y) {
    int maxRadius = x;
    if (SIM_X_SIZE - x < maxRadius) {
        maxRadius = SIM_X_SIZE - x;
    }
    if (y < maxRadius) {
        maxRadius = y;
    }
    if (SIM_Y_SIZE - y < maxRadius) {
        maxRadius = SIM_Y_SIZE - y;
    }
    
    const int minRadius = 2;
    return simRand() % (maxRadius - MARGIN + 1) + minRadius;
}

void app() {
    while (1) {
        const int x = simRand() % (SIM_X_SIZE - MARGIN * 2) + MARGIN;
        const int y = simRand() % (SIM_Y_SIZE - MARGIN * 2) + MARGIN;
        const int color = simRand();
        const int radius = getRadius(x, y);
        drawCircle(x, y, radius, color);
        simFlush();
    }
}
