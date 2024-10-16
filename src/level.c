#include <stdlib.h>

#include "level.h"
#include "texture.h"

void Level_initEmpty(Level *l)
{
    l->tiles = malloc(sizeof(Tile) * N_TILES);

    // fill level with empty tiles
    for (int x = 0; x < N_TILES_WIDTH; x++)
    {
        for (int y = 0; y < N_TILES_HEIGHT; y++)
        {

            unsigned int i = x + y * N_TILES_WIDTH;

            l->tiles[i] = (Tile) {

                x: x, y: y,
                textureid: TEXTURE_EMPTY,
                type: TILE_EMPTY

            };

            if (y == N_TILES_HEIGHT - 1) l->tiles[i].type = TILE_SOLID;
        }
    }
}

void Level_free(Level *l)
{
    free(l->tiles);
}

Tile* Level_getTile(Level *l, int x, int y)
{
    if (x < 0 || x >= N_TILES_WIDTH || y < 0 || y >= N_TILES_WIDTH) return NULL;
    return &l->tiles[x + y * N_TILES_WIDTH];
}