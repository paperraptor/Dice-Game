#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
#include"rock n paper.h"
#include"board.h"
#include"attckBar.h"

const float FPS = 6;			// set frame rate   (60 would be more normal)
      // screen height

int main(int argc, char *argv[]) {
	ALLEGRO_DISPLAY *display = nullptr;
	ALLEGRO_EVENT_QUEUE *event_queue = nullptr;		// add event queue object
	ALLEGRO_TIMER *timer = nullptr;				    // 1. add timer object

	// Initialize Allegro
	al_init();

	// initialize display
	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}
	al_set_window_title(display, "Bunny vs. the World");

   	// Initialize keyboard routines
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}

	// need to add image processor
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	// 2. setup timer
	timer = al_create_timer(1.0 / FPS);
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon

    // load the specific font you want
   ALLEGRO_FONT *font = al_load_ttf_font("ComicRelief.ttf", 15, 0);
   if (!font){
      al_show_native_message_box(display, "Error", "Error", "Could not load comic.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
   }

	// set up event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//al_register_event_source(event_queue, al_get_timer_event_source(timer));			//register timer events

	Grid board[4][4];
	ALLEGRO_BITMAP *bossbmp = {nullptr};
	ALLEGRO_BITMAP *dicebmp[6] = {nullptr};
	ALLEGRO_BITMAP *user = nullptr;
	ALLEGRO_BITMAP *health = nullptr;
	ALLEGRO_BITMAP *bossHpBmp = nullptr;
	ALLEGRO_BITMAP *wonScreen = nullptr;
	ALLEGRO_BITMAP *lossScreen = nullptr;
	ALLEGRO_BITMAP *title = nullptr;

	ALLEGRO_BITMAP *bar = nullptr;
	ALLEGRO_BITMAP *arrow = nullptr;
	ALLEGRO_BITMAP *hit = nullptr;

	ALLEGRO_BITMAP *userHands[3] = {nullptr};
	ALLEGRO_BITMAP *select = nullptr;
	ALLEGRO_BITMAP *bossHands[3] = {nullptr};

	ALLEGRO_BITMAP *eightBall = nullptr;

    srand(time(NULL));

    user = al_load_bitmap("user.png");
    health = al_load_bitmap("user_health.png");
    bossHpBmp = al_load_bitmap("boss_health.png");
    bossbmp = al_load_bitmap("bossBmp.png");
    wonScreen = al_load_bitmap("YouWON.png");
    lossScreen = al_load_bitmap("YouLOST.png");
    title = al_load_bitmap("Title Page.png");

	board[0][0].frame = al_load_bitmap("grid_start.png");
	board[0][0].funcNum = 0;
	board[0][1].frame = al_load_bitmap("grid_safe.png");
	board[0][1].funcNum = 1;
	board[0][2].frame = al_load_bitmap("grid_enemy.png");
	board[0][2].funcNum = 3;
	board[0][3].frame = al_load_bitmap("grid_safe.png");
	board[0][3].funcNum = 1;

	board[1][0].frame = al_load_bitmap("grid_attack.png");
	board[1][0].funcNum = 2;
	board[1][1].frame = al_load_bitmap("grid_safe.png");
	board[1][1].funcNum = 1;
	board[1][2].frame = al_load_bitmap("grid_healthplus.png");
	board[1][2].funcNum = 4;
	board[1][3].frame = al_load_bitmap("grid_enemy.png");
	board[1][3].funcNum = 3;

	board[2][0].frame = al_load_bitmap("grid_safe.png");
	board[2][0].funcNum = 1;
	board[2][1].frame = al_load_bitmap("grid_enemy.png");
	board[2][1].funcNum = 3;
	board[2][2].frame = al_load_bitmap("grid_attack.png");
	board[2][2].funcNum = 2;
	board[2][3].frame = al_load_bitmap("grid_safe.png");
	board[2][3].funcNum = 1;

	board[3][0].frame = al_load_bitmap("grid_attack.png");
	board[3][0].funcNum = 2;
	board[3][1].frame = al_load_bitmap("grid_enemy.png");
	board[3][1].funcNum = 3;
	board[3][2].frame = al_load_bitmap("grid_8ball.png");
	board[3][2].funcNum = 5;
	board[3][3].frame = al_load_bitmap("grid_safe.png");
	board[3][3].funcNum = 1;

    dicebmp[0] = al_load_bitmap("dice_1.png");
	dicebmp[1] = al_load_bitmap("dice_2.png");
	dicebmp[2] = al_load_bitmap("dice_3.png");
	dicebmp[3] = al_load_bitmap("dice_4.png");
	dicebmp[4] = al_load_bitmap("dice_5.png");
	dicebmp[5] = al_load_bitmap("dice_6.png");
	bar = al_load_bitmap("bar.png");
	arrow = al_load_bitmap("arrow.png");
	hit = al_load_bitmap("hit.png");

	userHands[0] = al_load_bitmap("rpsGame_rock.png");
	userHands[1] = al_load_bitmap("rpsGame_paper.png");
	userHands[2] = al_load_bitmap("rpsGame_scissors.png");
	bossHands[0] = al_load_bitmap("Boss_rock.png");
	bossHands[1] = al_load_bitmap("Boss_paper.png");
	bossHands[2] = al_load_bitmap("Boss_scissors.png");
	select = al_load_bitmap("rpsGame_select.png");

	eightBall = al_load_bitmap("8_ball.png");

    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            al_convert_mask_to_alpha(board[x][y].frame, al_map_rgb(0, 255, 0));
        }
    }

    for(int x = 0; x < 6; x++){
        al_convert_mask_to_alpha(dicebmp[x], al_map_rgb(0, 255, 0));
    }

    for(int x = 0; x < 3; x++){
        al_convert_mask_to_alpha(userHands[x], al_map_rgb(0, 255, 0));
        al_convert_mask_to_alpha(bossHands[x], al_map_rgb(0, 255, 0));
    }

    al_convert_mask_to_alpha(user, al_map_rgb(0, 255, 0));
    al_convert_mask_to_alpha(hit, al_map_rgb(0, 255, 0));
    al_convert_mask_to_alpha(arrow, al_map_rgb(0, 255, 0));
    al_convert_mask_to_alpha(bar, al_map_rgb(0, 255, 0));
    al_convert_mask_to_alpha(select, al_map_rgb(0, 255, 0));
    al_convert_mask_to_alpha(health, al_map_rgb(0, 255, 0));
    al_convert_mask_to_alpha(eightBall, al_map_rgb(0, 255, 0));
    al_convert_mask_to_alpha(bossHpBmp, al_map_rgb(0, 255, 0));
    al_convert_mask_to_alpha(bossbmp, al_map_rgb(0, 255, 0));

    FILE *fptr = nullptr;
    FILE *eightB = nullptr;
    Info userinfo;
    int bossHealth = 0;
    char bossHp[5] = {""};
    bool doexit = false;

    int randDie = 1;
    int gridWalked = 0;
    int landOnGrid = 0;

    int select_X = 120, select_Y = 350;
    int userChoose = 0;
    int boss = 13;

    bool draw8ball = false;
    char eightBallforsee[100][100];
    int e = 0, b = 0;

    fptr = fopen("userinfo.txt", "r");
    fscanf(fptr, "%d", &userinfo.health);
    fscanf(fptr, "%d", &userinfo.x);
    fscanf(fptr, "%d", &userinfo.y);
    fscanf(fptr, "%d", &bossHealth);
    fclose(fptr);

    eightB = fopen("8balltext.txt", "r");
    while ((fgets(eightBallforsee[e], 100, eightB)) != NULL){
        e++;
    }

    fclose(eightB);

    //for(int i=0; i<e; i++){
    //    printf("%s\n", eightBallforsee[i]);
    //}
    printf(" Defeat the snake (or worm, if you really want to call it a worm) in the middle.\n Click space to roll the die.\n");

    drawTitle(doexit, event_queue, title);

    while (!doexit) {
        ALLEGRO_EVENT ev;

        al_clear_to_color(al_map_rgb(255 , 255, 255));
        loadBoard(board);
        al_draw_bitmap(dicebmp[randDie - 1], 231, 231, 0);
      	al_draw_bitmap(user, userinfo.x, userinfo.y, 0);
      	drawHeart(userinfo, health);
      	drawbossHeart(bossHealth, bossHpBmp);
      	al_draw_bitmap(bossbmp, 190, 300, 0);
      	if (draw8ball){
            al_draw_bitmap(eightBall, 50, 580, 0);
            al_draw_text(font, al_map_rgb(0,0,0), 320, 620, 0, eightBallforsee[rand()%e]);
      	}
      	//al_draw_text(font, al_map_rgb(0, 0, 0), 200, 620, ALLEGRO_ALIGN_CENTRE, bossHp);
      	al_flip_display();

      	draw8ball = false;

      	al_register_event_source(event_queue, al_get_keyboard_event_source());

      	al_wait_for_event(event_queue,&ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	doexit = true;
      	}else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      	    al_unregister_event_source(event_queue, al_get_keyboard_event_source());
      	    switch(ev.keyboard.keycode) {
      	        case ALLEGRO_KEY_SPACE:
      	            randDie = (rand() % 6 +1);
      	            //printf("%d\n",randDie);
      	            rollDice(randDie, dicebmp, 231, 231);
      	            calUserMove(randDie, userinfo.x, userinfo.y);
      	            landOnGrid = checkLocation(userinfo.x, userinfo.y, board);
      	            switch(landOnGrid){
                        case 1:
                            printf("\n safe - nothing happens, you are safe, right now. \n");
                        break;
                        case 2:
                            boardClear(board, userinfo.x, userinfo.y, user);
                            printf("\n attack bar - click space to attack.\n");
                            attackBar(hit, arrow, bar, event_queue, doexit, bossHealth);
                            al_unregister_event_source(event_queue, al_get_keyboard_event_source());
                        break;
                        case 3:
                            boardClear(board, userinfo.x, userinfo.y, user);
                            printf("\n enemy - use left&right key to select, then use space to confirm. \n");
                            printf("(This is a rock paper scissor game)\n");
                            RpsGame(userHands, select, select_X, select_Y, userChoose, doexit, event_queue, userinfo, bossHands, boss, bossHealth);
                        break;
                        case 4:
                            if(userinfo.health < 3){
                                userinfo.health ++;
                            }
                        break;
                        case 5:
                            printf("\n 8 ball - gives you a prediction.\n");
                            draw8ball = true;
                        break;
                    }
                break;
      	    }
      	}
      	al_clear_to_color(al_map_rgb(255 , 255, 255));
      	if(userinfo.health == 0){
      	    al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(lossScreen, SCREEN_W/2 - 305/2, SCREEN_H/2 - 153/2, 0);
      	    al_flip_display();
            al_rest(3);
            doexit = true;
            printf("\n You DIED!!! \n");
      	}else if(bossHealth == 0){
            al_clear_to_color(al_map_rgb(255 , 255, 255));
      	    al_draw_bitmap(wonScreen, SCREEN_W/2 - 305/2, SCREEN_H/2 - 153/2, 0);
      	    al_flip_display();
            al_rest(3);
      	    doexit = true;
      	    printf("\n\n You WON!!! \n");
      	}

    }
    al_destroy_display(display);
    return 0;
}
