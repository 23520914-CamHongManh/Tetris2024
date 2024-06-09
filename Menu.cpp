#include "Tetris.h"
#include "Util.h"


void Tetris::menu()
{
    Util.backgroundAudio("res/audio/music/HQ _ Fish-Man Island Stage Theme (SoundTrack) - One Piece Bounty Rush.mp3",25);
    backgroundMenu = Util.loadTexture("res/demo image/bgf.jpg", Util.renderer);
    play = Util.loadTexture("res/demo image/play.png", Util.renderer);
    play_light = Util.loadTexture("res/demo image/play_light.png", Util.renderer);
    lv1 = Util.loadTexture("res/demo image/level_1.png", Util.renderer);
    lv2 = Util.loadTexture("res/demo image/level_2.png", Util.renderer);
    lv3 = Util.loadTexture("res/demo image/level_3.png", Util.renderer);
    music =Util.loadTexture("res/gfx/Button/music.png",Util.renderer);
    infor = Util.loadTexture("res/gfx/Button/information.png",Util.renderer);
	nameframe=Util.loadTexture("res/demo image/nameframe.png",Util.renderer);
	cup=Util.loadTexture("res/demo image/cup.png",Util.renderer);
}
int Tetris::showmenu() {
    while (true) {
	SDL_RenderClear(Util.renderer);
    SDL_RenderCopy(Util.renderer, backgroundMenu, NULL, NULL);
    if(!Checkmouse[playgame]) SDL_RenderCopy(Util.renderer, play, NULL, &playRect);
    else SDL_RenderCopy(Util.renderer, play_light, NULL, &playRect);
    SDL_RenderCopy(Util.renderer, music, &sRectmu, &dRectmu);
    SDL_RenderCopy(Util.renderer, infor, &sRectin, &dRectin);
    if(level == 1)
    {
        SDL_RenderCopy(Util.renderer, lv1, NULL, &levelRect);
    }
    else if(level == 2)
    {
        SDL_RenderCopy(Util.renderer, lv2, NULL, &levelRect);
    }
    else if(level == 3)
    {
        SDL_RenderCopy(Util.renderer, lv3, NULL, &levelRect);
    }
    SDL_RenderCopy(Util.renderer, nameframe, NULL, &dnamef);
	name=Util.Text(namep,335,180,Util.renderer,{0,0,0},30,dname);
	SDL_RenderCopy(Util.renderer, name, NULL, &dname);
	SDL_RenderCopy(Util.renderer, cup, NULL, &dcup);
	SDL_RenderPresent(Util.renderer);
	// 	SDL_RenderCopy(Game::renderer, menu, NULL, NULL);
	// 	SDL_RenderCopy(Game::renderer, play, &src_menu[PLAY_GAME], &pos_menu[PLAY_GAME]); 
	// 	SDL_RenderCopy(Game::renderer, exit, &src_menu[EXIT], &pos_menu[EXIT]); 
	// 	SDL_RenderCopy(Game::renderer, infor, &src_menu[INFOR], &pos_menu[INFOR]);
	// 	SDL_RenderCopy(Game::renderer, credits, &src_menu[CREDITS], &pos_menu[CREDITS]);
	// 	SDL_RenderCopy(Game::renderer, music, &src_menu[MUSIC], &pos_menu[MUSIC]);
	// 	SDL_RenderPresent(Game::renderer);
    SDL_Event e;
		while (SDL_PollEvent(&e)) {
            		int xm ;
					int ym ;
			switch(e.type) {
				case SDL_QUIT: 
                    // SDL_DestroyTexture(background);
                    // SDL_DestroyTexture(gamebg);
                    // SDL_DestroyTexture(block);
                    SDL_DestroyTexture(backgroundMenu);
                    SDL_DestroyTexture(play);
                    SDL_DestroyTexture(play_light);
                    SDL_DestroyTexture(lv1);
                    SDL_DestroyTexture(lv2);
                    SDL_DestroyTexture(lv3);
                    SDL_DestroyTexture(music);
                    SDL_DestroyTexture(infor);
					return 10;   
				case SDL_MOUSEMOTION: 
					xm = e.motion.x; 
					ym = e.motion.y;
					if (selectRect(playRect,xm,ym)) {
						if (!Checkmouse[playgame]) {
							Checkmouse[playgame] = 1; 
						}
					}
					else {
						if (Checkmouse[playgame]) {
							Checkmouse[playgame] = 0; 
						}
					}

					if (selectRect(dRectin ,xm,ym)) {
						if (!Checkmouse[inforcheck]) {
							Checkmouse[inforcheck] = 1; 
							sRectin={0, 0, 64, 64};
						}
					}
					else {
						if (Checkmouse[inforcheck]) {
							Checkmouse[inforcheck] = 0; 
							sRectin={64, 0, 64, 64};
						}
					}
					break;

				case SDL_MOUSEBUTTONDOWN: 
					xm = e.button.x; 
					ym = e.button.y;
					if (selectRect(playRect,xm,ym)) {
                        Util.effectAudio("res/audio/music/hardDrop.wav",90);
                        running = true;
						return 0; 
					}
					if (selectRect(dRectin,xm,ym)) { 
						return 1; 
					}
					if (selectRect(dnamef,xm,ym)) { 
						// SDL_StartTextInput(); // Bắt đầu chế độ nhập văn bản
						// // while (1) {
						// 	SDL_Event event;
						// 	while (SDL_WaitEvent(&event)) {
						// 		if (event.type == SDL_QUIT) break;
						// 		else if (event.type == SDL_TEXTINPUT)
						// 			// Xử lý văn bản nhập vào
						// 			{namep+=event.text.text;
						// 			SDL_RenderCopy(Util.renderer, name, NULL, &dname);
						// 			SDL_RenderPresent(Util.renderer);
						// 			}
						// 		else if (event.type == SDL_TEXTEDITING) 
						// 			{namep=event.text.text;
						// 			SDL_RenderCopy(Util.renderer, name, NULL, &dname);
						// 			SDL_RenderPresent(Util.renderer);
						// 			}
						// 		else if(event.type==SDL_KEYDOWN)
						// 		{
						// 			// if(event.key.keysym.sym==SDLK_KP_ENTER) break;
						// 			 if(event.key.keysym.sym==SDLK_ESCAPE) break;
						// 		}
						// 	}
						// // }

						// SDL_StopTextInput(); // Kết thúc chế độ nhập văn bản
						// // return 9;
						rendername();
					}
                    if(selectRect(levelRect, xm, ym))
                    {
                        Util.effectAudio("res/audio/music/hardDrop.wav",90);
                        if(level == 1)
                            level++;
                        else if(level == 2)
                            level++;
                        else if(level == 3)
                            level -= 2;
                    }
					if (selectRect(dRectmu,xm,ym)) {
						if (!Checkmouse[switchmusic]) {
							Checkmouse[switchmusic] = 1; 
							sRectmu={32,0,32,32};
							Util.pause(); 
						}
                    
					else if (Checkmouse[switchmusic]) {
							Checkmouse[switchmusic] = 0; 
							sRectmu={0,0,32,32};
							Util.resume(); 
						}
                    }
					break;
				case SDL_KEYDOWN: 
					if (e.key.keysym.sym == SDLK_ESCAPE) {
						return 9; 
					}
				default: 
					break; 
			}
		}
	}
}
void Tetris::rendername()
{
	SDL_StartTextInput(); 
	// Bắt đầu chế độ nhập văn bản
						while (1) {
							SDL_Event event;
							SDL_RenderClear(Util.renderer);
									SDL_RenderCopy(Util.renderer, backgroundMenu, NULL, NULL);
									if(!Checkmouse[playgame]) SDL_RenderCopy(Util.renderer, play, NULL, &playRect);
									else SDL_RenderCopy(Util.renderer, play_light, NULL, &playRect);
									SDL_RenderCopy(Util.renderer, music, &sRectmu, &dRectmu);
									SDL_RenderCopy(Util.renderer, infor, &sRectin, &dRectin);
									if(level == 1)
									{
										SDL_RenderCopy(Util.renderer, lv1, NULL, &levelRect);
									}
									else if(level == 2)
									{
										SDL_RenderCopy(Util.renderer, lv2, NULL, &levelRect);
									}
									else if(level == 3)
									{
										SDL_RenderCopy(Util.renderer, lv3, NULL, &levelRect);
									}
									SDL_RenderCopy(Util.renderer, nameframe, NULL, &dnamef);
									name=Util.Text(namep,335,180,Util.renderer,{0,0,0},30,dname);
									SDL_RenderCopy(Util.renderer, name, NULL, &dname);
									SDL_RenderCopy(Util.renderer, cup, NULL, &dcup);
									SDL_RenderPresent(Util.renderer);
							while (SDL_PollEvent(&event)) {
								if (event.type == SDL_QUIT) return;
								else if (event.type == SDL_TEXTINPUT)
									// Xử lý văn bản nhập vào
									{namep+=event.text.text;
									name=Util.Text(namep,335,180,Util.renderer,{0,0,0},30,dname);
									}
								else if (event.type == SDL_KEYDOWN) 
									{
										if(event.key.keysym.sym==SDLK_BACKSPACE&&!namep.empty())
										{
											namep.pop_back();
										}
										// else if(event.key.keysym.sym==SDLK_) return;
									 else if(event.key.keysym.sym==SDLK_ESCAPE) return;
									}
								else if(event.type==SDL_MOUSEBUTTONDOWN) return;
							}
						}

						SDL_StopTextInput(); // Kết thúc chế độ nhập văn bản
						// return 9;
}