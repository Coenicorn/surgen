#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>

#include "config.h"
#include "util.h"
#include "game.h"
#include "level.h"
#include "draw.h"
#include "player.h"

static Level level;

static Player player;

static float lastFrameTime = 0.f;

static RenderTexture2D renderTexture;

void resetPlayer()
{

    player.y = 0;
    player.x = (N_TILES_WIDTH * TILESIZE_PIXELS) / 2;

    player.width = PLAYERWIDTH;
    player.height = PLAYERHEIGHT;

    player.vx = 0;
    player.vy = 0;

    player.lastX = 0;
    player.lastY = 0;

    player.onGround = 0;
    player.chargingJump = 0;

}

void Game_init()
{
    InitWindow(CONFIG_WINDOW_WIDTH, CONFIG_WINDOW_HEIGHT, "surgen");
    SetTargetFPS(TARGET_FPS);

    renderTexture = LoadRenderTexture(N_TILES_WIDTH * TILESIZE_PIXELS, N_TILES_HEIGHT * TILESIZE_PIXELS);

    Level_initEmpty(&level);

    resetPlayer();
}

void collideWithLevel()
{
    // get tile player is in
    // convert player position to tile index coordinates
    float 
        playerTileX = ((player.x + PLAYERWIDTH / 2) / TILESIZE_PIXELS),
        playerTileY = ((player.y + PLAYERHEIGHT / 2) / TILESIZE_PIXELS);

    // get surrounding tiles
    Tile *tilesToCheck[9];
    unsigned int i = 0;

    for (int x = -1; x < 2; x++)
    {
        for (int y = -1; y < 2; y++)
        {

            float tileX = playerTileX + x;
            float tileY = playerTileY + y;

            tilesToCheck[i++] = Level_getTile(&level, floor(tileX), floor(tileY));

        }
    }

    AABB playerBounds = (AABB){ p1x: player.x, p1y: player.y, p2x: player.x + player.width, p2y: player.y + player.height };

    // store the most important change
    float store_lrOverlap = 0, store_btOverlap = 0;
    int bottom = 0, left = 0;

    // just do aabb collision detection on each rectangle
    for (int i = 0; i < 9; i++)
    {
        Tile *t = tilesToCheck[i];

        if (t == NULL || t->type != TILE_SOLID) continue;

        AABB tileBounds = (AABB){ p1x: t->x * TILESIZE_PIXELS, p1y: t->y * TILESIZE_PIXELS, p2x: t->x * TILESIZE_PIXELS + TILESIZE_PIXELS, p2y: t->y * TILESIZE_PIXELS + TILESIZE_PIXELS };

        if (!AABB_overlap(playerBounds, tileBounds)) continue;



        float dP1Q2 = (tileBounds.p2x - playerBounds.p1x);
        float dQ1P2 = (playerBounds.p2x - tileBounds.p1x);

        float dP1Q3 = (playerBounds.p2y - tileBounds.p1y);
        float dP3Q1 = (tileBounds.p2y - playerBounds.p1y);

        float lrOverlap = (dP1Q2 > dQ1P2) ? dQ1P2 : dP1Q2;
        float btOverlap = (dP1Q3 > dP3Q1) ? dP3Q1 : dP1Q3;

        if (lrOverlap > btOverlap)
        {
            if (btOverlap > store_btOverlap) store_btOverlap = btOverlap;
            else continue;

            // collision is on the top or bottom
            if (dP3Q1 < dP1Q2)
            {
                // collision is on the bottom
                bottom = 1;
            } else {
                // collision is on the top
                bottom = 0;
            }
        } else {
            if (lrOverlap > store_lrOverlap) store_lrOverlap = lrOverlap;
            else continue;

            // collision is on the left or right
            if (dQ1P2 < dP1Q2)
            {
                left = 1;
                // collision is on the left
            } else {
                // collision is on the right
                left = 0;
            }
        }
    }

    if (store_lrOverlap == 0 && store_btOverlap == 0) return;

    if (store_lrOverlap < store_btOverlap)
    {
        if (bottom) player.y += store_btOverlap;
        else {
            player.y -= store_btOverlap;
            player.onGround = 1;
        }
    } else {
        if (left) player.x -= store_lrOverlap;
        else player.x += store_lrOverlap;
    }
}

void handleInput()
{

    if (IsKeyDown(KEY_LEFT)) player.vx = -WALKING_SPEED;
    if (IsKeyDown(KEY_RIGHT)) player.vx = WALKING_SPEED;
    if (IsKeyDown(KEY_UP) && player.onGround) {
        player.vy = JUMP_ACCELERATION;
        player.onGround = 0;
    }

}

void physics_update()
{

    player.lastX = player.x;
    player.lastY = player.y;

    // player gravity physics
    player.vy += GRAVITY;
    // cap gravity
    if (player.vy >= GRAVITY_CAP) player.vy = GRAVITY_CAP;

    player.x += player.vx;
    player.y += player.vy;

    collideWithLevel();

    if (player.onGround) {
        player.vy = 0;
        player.vx = 0;
    }
    else player.vx *= AIR_FRICTION;

}

void Game_start()
{

    while (!WindowShouldClose())
    {

        lastFrameTime = GetFrameTime();

        handleInput();

        physics_update();

        BeginTextureMode(renderTexture);

            ClearBackground(BACKGROUND_COLOR);

            Draw_renderLevel(&level);

        EndTextureMode();

        BeginDrawing();

            ClearBackground(BLACK);

            DrawTexturePro(renderTexture.texture, (Rectangle){0, 0, renderTexture.texture.width, -renderTexture.texture.height}, (Rectangle){0, 0, CONFIG_WINDOW_WIDTH, CONFIG_WINDOW_HEIGHT}, (Vector2){renderTexture.texture.width / 2, renderTexture.texture.height / 2}, 0, WHITE);


        EndDrawing();

    }

}

void Game_free()
{
    CloseWindow();
    Level_free(&level);
}