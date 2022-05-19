const int SCREEN_W = 520;
const int SCREEN_H = 730;

struct Grid {
    ALLEGRO_BITMAP *frame;
    int funcNum;
    int x = 0, y = 0;
};

void loadBoard(Grid boardbmp[][4]){
    //int arraySize = sizeof(g1)/sizeof(g1[0]);

    int X1dis = 0, X2dis = 0;
    int Y1dis = 0, Y2dis = 0;

    al_draw_bitmap(boardbmp[0][0].frame, 50, 100, 0);
    boardbmp[0][0].x = 50;
    boardbmp[0][0].y = 100;
    al_draw_bitmap(boardbmp[1][0].frame, 50, 444, 0);
    boardbmp[1][0].x = 50;
    boardbmp[1][0].y = 444;

	for (int x = 1; x < 4; x++){
        X1dis += (al_get_bitmap_width(boardbmp[0][x-1].frame)+7);
        X2dis += (al_get_bitmap_width(boardbmp[1][x-1].frame)+7);
        boardbmp[0][x].x = X1dis+50;
        boardbmp[1][x].x = X2dis+50;
        boardbmp[0][x].y = 100;
        boardbmp[1][x].y = 444;
        al_draw_bitmap(boardbmp[0][x].frame, boardbmp[0][x].x, boardbmp[0][x].y, 0);
        al_draw_bitmap(boardbmp[1][x].frame, boardbmp[1][x].x, boardbmp[1][x].y, 0);
	}

	al_draw_bitmap(boardbmp[2][0].frame, 50, 186, 0);
	boardbmp[2][0].x = 50;
    boardbmp[2][0].y = 186;
	al_draw_bitmap(boardbmp[3][0].frame, 382, 100, 0);
	boardbmp[3][0].x = 382;
    boardbmp[3][0].y = 100;

	for (int y = 1; y < 3; y++){
        Y1dis += (al_get_bitmap_height(boardbmp[2][y-1].frame)+7);
        Y2dis += (al_get_bitmap_height(boardbmp[3][y-1].frame)+7);
        boardbmp[2][y].y = Y1dis+186;
        boardbmp[3][y].y = Y2dis+186;
        boardbmp[2][y].x = 50;
        boardbmp[3][y].x = 382;
        al_draw_bitmap(boardbmp[2][y].frame, 50, boardbmp[2][y].y, 0);
        al_draw_bitmap(boardbmp[3][y].frame, 382, boardbmp[3][y].y, 0);
	}

	al_draw_bitmap(boardbmp[2][3].frame, 382, 186,0);
	boardbmp[2][3].x = 382;
    boardbmp[2][3].y = 186;
}

void calUserMove(int dNum, int &userX, int &userY){
    for(int i = 1; i <= dNum; i++){
        if(userX >= 50 && userX < 382  && userY == 100){
            userX += 83;
        }else if(userY >= 100 && userY < 444 && userX == 382){
            userY += 86;
        }else if(userX > 50 && userX <= 382  && userY == 444){
            userX -= 83;
        }else if(userY > 100 && userY <= 444 && userX == 50 ){
            userY -= 86;
        }
    }
}

void rollDice(int die, ALLEGRO_BITMAP *dice[], int dieX, int dieY){
    for(int i=0; i<10; i++){
        al_draw_bitmap(dice[(rand()%6)], dieX, dieY, 0);
        al_rest(0.1);
        al_flip_display();
    }
}

int checkLocation(int x1, int y1, Grid boardbmp[][4]){
    for (int x = 0; x < 4; x++){
        for (int y = 0; y < 4; y++){
            if (x1 == boardbmp[x][y].x && y1 == boardbmp[x][y].y){
                return boardbmp[x][y].funcNum;
            }
        }
    }
    return 4;
}

void boardClear(Grid bmp[][4], int x, int y, ALLEGRO_BITMAP *u){
    for(int i=0; i<5; i++){
        loadBoard(bmp);
        al_draw_bitmap(u, x, y, 0);
        al_flip_display();
        al_rest(0.13);
        al_clear_to_color(al_map_rgb(255 , 255, 255));
        al_flip_display();
        al_rest(0.13);
    }
}

void drawHeart(Info user, ALLEGRO_BITMAP *heart){
    int x = 0;
    for(int i = 0; i < user.health; i++){
        al_draw_bitmap(heart, 20+x, 20, 0);
        x += 30;
    }
}

void drawbossHeart(int health, ALLEGRO_BITMAP *heart){
    int x = 0;
    for(int i = 0; i < health; i++){
        al_draw_bitmap(heart, SCREEN_W/2-70+x, 400, 0);
        x += 30;
    }
}

void drawTitle(bool &doexit, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_BITMAP *titlePage){

    while (!doexit) {
        ALLEGRO_EVENT ev;
        al_register_event_source(event_queue, al_get_keyboard_event_source());

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_bitmap(titlePage, SCREEN_W/2 - 468/2, SCREEN_H/2 - 597/2, 0);
        al_flip_display();

      	al_wait_for_event_timed(event_queue,&ev, 0.1);
      	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	doexit = true;
      	}else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      	            break;
      	}
    }

}

//void Pp(){
 //   printf("test");
//}
