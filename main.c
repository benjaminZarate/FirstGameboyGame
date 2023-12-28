#include <gb/gb.h>
#include <gb/font.h>
#include <stdlib.h>
#include <rand.h>
#include <stdio.h>
#include "Character.c"
#include "EntitiesSprite.c"
#include "map_background.c"
#include "backgroundTilesMap.c"

struct Character player;
struct Character enemy1;
struct Character enemy2;
UBYTE spriteSize = 8;
UINT8 enemySpeed = 0;
UBYTE enemyHeight = 0;
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

void MoveCharacter(struct Character* character)
{
    move_sprite(character -> spriteIds[0], character ->X, character ->Y);
    move_sprite(character -> spriteIds[1], character ->X + spriteSize, character ->Y);
    move_sprite(character -> spriteIds[2], character ->X, character ->Y + spriteSize);
    move_sprite(character -> spriteIds[3], character ->X + spriteSize ,character ->Y + spriteSize);
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

    MoveCharacter(&player);
}

void SetupEnemy(struct Character* enemy, UINT8 randY)
{
    enemy->X = SCREENWIDTH;
    enemy->Y = randY;
    enemy->width = 16;
    enemy->height = 16;

    set_sprite_tile(5,5);
    enemy->spriteIds[0] = 5;
    set_sprite_tile(6,6);
    enemy->spriteIds[1] = 6;
    set_sprite_tile(7,7);
    enemy->spriteIds[2] = 7;
    set_sprite_tile(8,8);
    enemy->spriteIds[3] = 8;

    MoveCharacter(&enemy);
}

void SetEnemyPosition(struct Character* enemy, UINT8 yPos)
{
    enemy->X -= 10;

    if(enemyHeight == 0){enemySpeed -= 8;}
    else{enemySpeed += 10;}

    if(enemySpeed >= 20){enemyHeight = 1;}
    else if(enemySpeed < -16){enemyHeight = 0;}
    enemy->Y += enemySpeed;
    if(enemy->X <= 0) 
    {
        enemy->X = SCREENWIDTH; 
        enemy->Y = yPos;
    }
}
UBYTE up = 0;
void main()
{
    printf("\n \n \n  ===PRESS START===");
    waitpad(J_START);
    set_bkg_data(0,6, backgroundTiles);
    set_bkg_tiles(0,0,20,18,MapBackground);
    set_sprite_data(0,9,Entities);
    SetupPlayer();
    SetupEnemy(&enemy1,SCREENHEIGHT / 2);
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while (!checkCollisions(&player, &enemy1))
    {
        scroll_bkg(1,0);
        switch (joypad())
        {
            case J_UP:
                player.Y -= 4;
                break;
            case J_DOWN:
                player.Y += 4;
                break;
        }
        if(player.Y < 24){player.Y = 24;}
        else if(player.Y > SCREENHEIGHT - 20){player.Y = SCREENHEIGHT - 20;}
        if(player.Y >= SCREENHEIGHT / 2){ SetEnemyPosition(&enemy1, player.Y + 10); }
        else{SetEnemyPosition(&enemy1, player.Y - 10);}
        MoveCharacter(&enemy1);
        MoveCharacter(&player);
        PerfomantDelay(5);
    }
    main();
}