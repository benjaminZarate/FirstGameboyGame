#include <gb/gb.h>
#include <gb/font.h>
#include <stdlib.h>
#include <rand.h>
#include <stdio.h>
#include "Character.c"
#include "EntitiesSprite.c"

struct Character player;
struct Character enemy;
UBYTE spriteSize = 8;

void PerfomantDelay(UBYTE numLoops)
{
    UINT8 i;
    for (i = 0; i < numLoops; i++)
    {
        wait_vbl_done();
    }
    
}

UBYTE checkCollisions(struct Character* one, struct Character* two)
{
    return ((one->X >= two->X && one->X <= two->X + two->width) && (one->Y >= two->Y && one->Y <= two->Y + two->height)) ||
            ((two->X >= one->X && two->X <= one->X + one->width) && (two->Y >= one->Y && two->Y <= one->Y + one->height));
}
void MoveCharacter(struct Character* character, UINT8 x, UINT8 y)
{
    move_sprite(character -> spriteIds[0],x,y);
    move_sprite(character -> spriteIds[1],x + spriteSize,y);
    move_sprite(character -> spriteIds[2],x,y + spriteSize);
    move_sprite(character -> spriteIds[3],x + spriteSize,y + spriteSize);
}

void SetupPlayer()
{
    player.X = 10;
    player.Y = SCREENHEIGHT / 2;
    player.width = 16;
    player.height = 16;

    set_sprite_tile(0,0);
    player.spriteIds[0] = 0;
    set_sprite_tile(1,1);
    player.spriteIds[1] = 1;
    set_sprite_tile(2,2);
    player.spriteIds[2] = 2;
    set_sprite_tile(3,3);
    player.spriteIds[3] = 3;

    MoveCharacter(&player, player.X, player.Y);
}

void SetupEnemy(UINT8 randY)
{
    enemy.X = SCREENWIDTH;
    enemy.Y = randY;
    enemy.width = 16;
    enemy.height = 16;

    set_sprite_tile(5,5);
    enemy.spriteIds[0] = 5;
    set_sprite_tile(6,6);
    enemy.spriteIds[1] = 6;
    set_sprite_tile(7,7);
    enemy.spriteIds[2] = 7;
    set_sprite_tile(8,8);
    enemy.spriteIds[3] = 8;

    MoveCharacter(&enemy, enemy.X, enemy.Y);
}

void main()
{
    set_sprite_data(0,9,Entities);
    SetupPlayer();
    SetupEnemy(player.Y);
    SHOW_SPRITES;
    DISPLAY_ON;

    while (!checkCollisions(&player, &enemy))
    {
        if(joypad() & J_UP)
        {
            player.Y -= 4;
            MoveCharacter(&player, player.X, player.Y);
        }else if(joypad() & J_DOWN)
        {
            player.Y += 4;
            MoveCharacter(&player, player.X, player.Y);
        }
        enemy.X -= 10;
        if(enemy.X <= 0) 
        {
            enemy.X = SCREENWIDTH; 
            enemy.Y = player.Y;
        }
        MoveCharacter(&enemy, enemy.X, enemy.Y);
        PerfomantDelay(5);
    }
    printf("===Game Over===");
}