#include "sim.h"

void drawCircle(const int x, const int y, const int radius, const int color) {
    for (int w = -radius; w <= radius; w++) {
        for (int h = -radius; h <= radius; h++) {
            if ((w * w + h * h) <= (radius * radius)) {
                simPutPixel(x + w, y + h, color);
            }
        }
    }
}

void app() {
    const int xCenter = SIM_X_SIZE / 2;
    const int yCenter = SIM_Y_SIZE / 2;
    
    int maxR = SIM_Y_SIZE * 2 / 5;
    if (SIM_X_SIZE < SIM_Y_SIZE) {
        maxR = SIM_X_SIZE * 2 / 5;
    }

    const int NUM_CIRCLES = 20;
    const int radiusDecreaseStep = maxR / NUM_CIRCLES;

    while (1) {
        for (int radius = maxR; radius > 0; radius -= radiusDecreaseStep) {
            const int color = simRand();
            drawCircle(xCenter, yCenter, radius, color);
            simFlush();
        }
    }
}
