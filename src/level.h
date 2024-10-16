#ifndef LEVEL_H
#define LEVEL_H

#include <inttypes.h>

#include "config.h"
#include "util.h"
#include "texture.h"

#define XYTOI(_X, _Y) (_X + _Y * N_TILES_WIDTH)

typedef enum TileType {

    TILE_EMPTY = 0,
    TILE_DEBUG,
    TILE_SOLID

} TileType;

typedef struct Tile {
    TileType type;

    unsigned int x, y; /* Index in twodimensional tile array, not actual coordinates */
    short int normalX, normalY; /* Tile normal */

    TextureId textureid;
} Tile;

typedef struct Level {

    Tile *tiles; /* of size N_TILES */

} Level;

void Level_initEmpty(Level *l);
void Level_free(Level *l);
Tile* Level_getTile(Level *l, int x, int y);

#endif // LEVEL_H