#include <stdio.h>

#include "draw.h"
#include "level.h"

void Draw_renderLevel(Level *l)
{
    // draw individual tiles
    // only draw outline for now
    for (int i = 0; i < N_TILES; i++)
    {
        Tile t = l->tiles[i];
        Color c = BLUE;
        if (t.type == TILE_EMPTY) continue;
        DrawRectangleLines(t.x * TILESIZE_PIXELS, t.y * TILESIZE_PIXELS, TILESIZE_PIXELS, TILESIZE_PIXELS, BLUE);
    }
}