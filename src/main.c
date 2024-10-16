#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "util.h"
#include "game.h"

int main(void)
{

    Game_init();

    Game_start();
    
    Game_free();

    return 0;
}