//#include"Bunny vs. The World.cpp"


void boundingBox(ALLEGRO_BITMAP *bmp1, ALLEGRO_BITMAP *bmp2,
        float x1, float y1, float x2, float y2, int &boss){
    int height;
    int width;
    int height2;
    int width2;

    height = al_get_bitmap_height(bmp1);
    width = al_get_bitmap_width(bmp1);
    height2 = al_get_bitmap_height(bmp2);
    width2 = al_get_bitmap_width(bmp2);

    if (x1 + width/2 > x2 && x1 + width/2 < x2 + width2){
        printf("You Hit HARD!!!");
        boss --;
    }
    else{
        printf("Missed");
    }
}

void attackBar(ALLEGRO_BITMAP *hit, ALLEGRO_BITMAP *arrow, ALLEGRO_BITMAP *bar, ALLEGRO_EVENT_QUEUE *event_queue, bool &doexit, int &boss){

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    int randomX = 0;
    randomX = (rand() % (al_get_bitmap_width(bar) - al_get_bitmap_width(hit)) + SCREEN_W/11);
    al_clear_to_color(al_map_rgb(255 , 255, 255));
    al_draw_bitmap(bar, SCREEN_W/11, SCREEN_H/2, 0);

    int x = 0;
    bool exitWithin = false;
    doexit = false;

	while(doexit == false && exitWithin == false){
        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.001);

        if(x < 480){
            for (x = 40; x<480; x++) {
                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_bitmap(bar, SCREEN_W/11, SCREEN_H/2, 0);
                al_draw_bitmap(arrow, x, SCREEN_H/2 - 35, 0);
                al_draw_bitmap(hit, randomX, SCREEN_H/2 + 23, 0);
                al_flip_display();

                al_rest(.001);

                al_wait_for_event_until(event_queue, &ev, &timeout);
                if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    doexit = true;
                } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
                        exitWithin = true;
                        boundingBox(arrow, hit, x, SCREEN_H/2 - 35, randomX, SCREEN_H/2 + 23, boss);
                        al_rest(2);
                        break;
                    }
                }
            }
        }
        else if (x >= 480){
            for (x = 480; x > 40; x--) {
                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_bitmap(bar, SCREEN_W/11, SCREEN_H/2, 0);
                al_draw_bitmap(arrow, x, SCREEN_H/2 - 35, 0);
                al_draw_bitmap(hit, randomX, SCREEN_H/2 + 23, 0);
                al_flip_display();
                al_rest(.001);

                al_wait_for_event_until(event_queue, &ev, &timeout);
                if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    doexit = true;
                } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE){
                        exitWithin = true;
                        boundingBox(arrow, hit, x, SCREEN_H/2 - 35, randomX, SCREEN_H/2 + 23, boss);
                        al_rest(3);
                        break;
                    }
                }
            }
        }

	}
}
