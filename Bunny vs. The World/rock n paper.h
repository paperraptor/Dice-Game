struct Info {
    //int coin;
    int health;
    int x, y;
};

void drawRpsGame(ALLEGRO_BITMAP *userChoice[], ALLEGRO_BITMAP *selectbmp, int sx, int sy){
    int between = 0;
    for(int i = 0; i < 3; i++){
        al_draw_bitmap(userChoice[i], 120+between, 350, 0);
        between += 120;
    }
    al_draw_bitmap(selectbmp, sx, sy, 0);
    al_flip_display();
}

void drawBoss(ALLEGRO_BITMAP *bossChoice[], int &Choice){

    al_draw_bitmap(bossChoice[rand()%3], 240, 230, 0);
    al_flip_display();
    al_rest(0.06);
    Choice = rand()%3;
}

void RpsGame(ALLEGRO_BITMAP *userChoice[], ALLEGRO_BITMAP *selectbmp, int &sx, int &sy, int &userChoose,
                bool &doexit, ALLEGRO_EVENT_QUEUE *event_queue, Info &user,
                ALLEGRO_BITMAP *bossChoice[], int &Choice, int &boss){
    bool exitWithin = false;
    doexit = false;

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    srand(time(NULL));

    while(doexit == false && exitWithin == false){
        ALLEGRO_EVENT ev;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.001);

        al_clear_to_color(al_map_rgb(255 , 255, 255));
        drawRpsGame(userChoice, selectbmp, sx, sy);
        drawBoss(bossChoice, Choice);
        al_flip_display();

        //al_wait_for_event(event_queue, &ev);

        al_wait_for_event_until(event_queue, &ev, &timeout);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                    if(sx == 120){
                        userChoose = 0;
                    }else if (sx == 240){
                        userChoose = 1;
                    }else if (sx == 360){
                        userChoose = 2;
                    }
                    al_draw_bitmap(bossChoice[Choice], 240, 300, 0);
                    if (userChoose == 0 && Choice == 2){
                        printf("\nwin\n");
                        boss --;
                    }else if (userChoose == 1 && Choice == 0){
                        printf("\nwin\n");
                        boss --;
                    }else if (userChoose == 2 && Choice == 1){
                        printf("\nwin\n");
                        boss --;
                    }else if (userChoose == Choice){
                        printf("no win");
                    }else{
                        user.health --;
                        printf("\nloss\n");
                    }
                    al_clear_to_color(al_map_rgb(255 , 255, 255));
                    drawRpsGame(userChoice, selectbmp, sx, sy);
                    al_draw_bitmap(bossChoice[Choice], 240, 230, 0);
                    al_flip_display();
                    al_rest(2);
                    exitWithin = true;
                break;
                case ALLEGRO_KEY_RIGHT:
                    if(sx == 240 || sx == 120){
                       sx += 120;
                    }
                break;
                case ALLEGRO_KEY_LEFT:
                    if(sx == 240 || sx == 360){
                       sx -= 120;
                    }
                break;
            }
        }


    }
}

