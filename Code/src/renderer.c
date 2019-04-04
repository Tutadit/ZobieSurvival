#include "global.h"
#include "player_b.h"
#include "zombie_b.h"
#include "misc_b.h"
#include "raster.h"
#include "model.h"
#include "font.h"

void render_button(const struct Button *button, UINT32 *base) {
    UINT32 *bitmap_a = button->bitmap_a;
    UINT32 *bitmap_b = button->bitmap_b;
    UINT32 bitmap_a_opp[BUTTON_HEIGHT];
    UINT32 bitmap_b_opp[BUTTON_HEIGHT];
    int i;
    if ( button_hover(button) ) {
        for ( i = 0; i < button->height; i++ ) {
            bitmap_a_opp[i] = ~bitmap_a[i];
            bitmap_b_opp[i] = ~bitmap_b[i];
        }
        bitmap_a = bitmap_a_opp;
        bitmap_b = bitmap_b_opp;
    }
    plot_bitmap_64(base,
                   button->position_x,
                   button->position_y,
                   bitmap_a,
                   bitmap_b,
                   button->height);
}

void render_stats(const struct Player *player,
                  const struct Game *game,
                  UINT32 *base) {

    UINT8 *base8 = (UINT8 *)base;
    plot_number(base8, 10, 10, player->health);
    plot_number(base8, 598, 382, player->magazine);
    plot_chars(base8, 606, 382, "/",1);
    plot_number(base8, 614, 382, player->ammo);
    plot_number(base8, 614,10,player->score);
    plot_number(base8, 10,382,game->wave);
}

void render_player(const struct Player *player, UINT32 *base) {
    if (player->health > 0) {
        plot_bitmap_32(base,
                       player->position_x,
                       player->position_y,
                       PLAYER_BODY[player->aim_direction],
                       PLAYER_BODY_HEIGHT);
        plot_bitmap_32(base,
                       player->position_x,
                       player->position_y+PLAYER_BODY_HEIGHT,
                       PLAYER_STEP[player->move_direction][player->step],
                       PLAYER_LEGS_HEIGHT);
    } else {
        plot_bitmap_32(base,
                       player->position_x,
                       player->position_y,
                       PLAYER_DEAD,
                       10);
    }
}

void render_zombie(const struct Zombie *zombie, UINT32 *base) {
    if (zombie->health > 0){
        plot_bitmap_32(base,
                       zombie->position_x,
                       zombie->position_y,
                       ZOMBIE_DIRECTION_STEP[zombie->direction][zombie->step],
                       ZOMBIE_HEIGHT);
    }
}

void render_cursor(const struct Cursor *cursor, UINT32 *base) {
    plot_bitmap_8((UINT8 *)base,
                  cursor->position_x - 1,
                  cursor->position_y + 1,
                  CURSOR,
                  CURSOR_HEIGHT);
}

void render_bullet(const struct Bullet *bullet, UINT32 *base) {
    plot_pixel((UINT8 *)base,
               bullet->position_x,
               bullet->position_y);
}
