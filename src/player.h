#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"

typedef struct Player {

    float x, y; /* in pixels */
    float lastX, lastY; /* in pixels */
    int width, height;
    int onGround;
    int chargingJump;

    float vx, vy; /* velocity */

    TextureId textureid;

} Player;

#endif // PLAYER_H