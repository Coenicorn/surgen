#ifndef CONFIG_H
#define CONFIG_H

#include <raylib.h>

#define DEBUG

#define BACKGROUND_COLOR BLACK

#define CONFIG_WINDOW_WIDTH 800
#define CONFIG_WINDOW_HEIGHT 800

#define N_TILES_WIDTH 12
#define N_TILES_HEIGHT 12
#define N_TILES (N_TILES_WIDTH * N_TILES_HEIGHT)

#define TILESIZE_PIXELS 4

#define TARGET_FPS 120

#define GRAVITY .1f /* velocity impaired per second */
#define GRAVITY_CAP 5.f

#define PLAYERWIDTH (TILESIZE_PIXELS)
#define PLAYERHEIGHT (TILESIZE_PIXELS)

#define WALKING_SPEED 1.f

#define AIR_FRICTION 0.7
#define JUMP_ACCELERATION -2


#ifdef DEBUG

#define DEBUG_PLAYER_BOUNDS_COLOR GREEN

#endif // DEBUG

#endif // CONFIG_H
