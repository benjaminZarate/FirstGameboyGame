#include <gb/gb.h>
#include <stdio.h>
#include "PlanceSprite.c"
#include "backgroundTilesMap.c"
#include "backgroundMap.c"

void main()
{

    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;

    set_bkg_data(0,7, backgroundTiles);
    set_bkg_tiles(0,0,40,18,backgroundMap);
    set_sprite_data(0,0,Plane);
    set_sprite_data(0,1,Plane);
    set_sprite_data(0,2,Plane);
    set_sprite_data(0,3,Plane);
    set_sprite_tile(0,1);
    set_sprite_tile(1,0);
    set_sprite_tile(2,3);
    set_sprite_tile(3,2);
    move_sprite(0,10,(SCREENHEIGHT / 2) + 8);
    move_sprite(1,10,SCREENHEIGHT / 2);
    move_sprite(2,18,(SCREENHEIGHT / 2) + 8);
    move_sprite(3,18,SCREENHEIGHT / 2);
    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
    while (1)
    {
        switch (joypad())
        {
        case J_LEFT:
            scroll_sprite(0,-10,0);
            scroll_sprite(1,-10,0);
            scroll_sprite(2,-10,0);
            scroll_sprite(3,-10,0);
            break;
        case J_RIGHT:
            scroll_sprite(0,10,0);
            scroll_sprite(1,10,0);
            scroll_sprite(2,10,0);
            scroll_sprite(3,10,0);
            break;
        case J_UP:
            scroll_sprite(0,0,-10);
            scroll_sprite(1,0,-10);
            scroll_sprite(2,0,-10);
            scroll_sprite(3,0,-10);
            break;
        case J_DOWN:
            scroll_sprite(0,0,10);
            scroll_sprite(1,0,10);
            scroll_sprite(2,0,10);
            scroll_sprite(3,0,10);
            break;
        default:
            break;
        }
        scroll_bkg(1,0);
        delay(100);
    }
    
}