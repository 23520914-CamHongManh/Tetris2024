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
	recordboard=Util.loadTexture("res/demo image/bgrecord.png",Util.renderer);
	cupdark=Util.loadTexture("res/demo image/cupblack.png",Util.renderer);
	ifstream p;
	string c;
	p.open("Highestscore.txt");
    if(!p) cerr<<"Can't open file"<<endl;
	for(int i=0;i<3;i++)
            {
                p>>a[i];
				 getline(p,c);
				getline(p,recordname[i]);
            }
			
    p.close();
}
int Tetris::showmenu() {
    while (true) {
	SDL_RenderClear(Util.renderer);
    SDL_RenderCopy(Util.renderer, backgroundMenu, NULL, NULL);
    if(!Checkmouse[playgame]) SDL_RenderCopy(Util.renderer, play, NULL, &playRect);
    else SDL_RenderCopy(Util.renderer, play_light, NULL, &playRect);
	if(!Checkmouse[cupblack]) SDL_RenderCopy(Util.renderer, cup, NULL, &dcup);
    else SDL_RenderCopy(Util.renderer, cupdark, NULL, &dcup);
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
	name=Util.Text(namep,332,185,Util.renderer,"res/font/Pixellettersfull-BnJ5.ttf",{0,0,0},30,dname);
	SDL_RenderCopy(Util.renderer, name, NULL, &dname);
	SDL_DestroyTexture(name);
	SDL_RenderPresent(Util.renderer);
    SDL_Event e;
		while (SDL_PollEvent(&e)) {
            		int xm ;
					int ym ;
			switch(e.type) {
				case SDL_QUIT: 
                    clean1();
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
					if (selectRect(dcup,xm,ym)) {
						if (!Checkmouse[cupblack]) {
							Checkmouse[cupblack] = 1; 
						}
					}
					else {
						if (Checkmouse[cupblack]) {
							Checkmouse[cupblack] = 0; 
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
						Util.effectAudio("res/audio/music/maylaai.wav",90);
						rendername();
					}
					if (selectRect(dcup,xm,ym)) { 
						return 2;
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
	Uint32 start,end;
	bool point;
	int delaypoint=500;
						while (1) {
							SDL_Event event;
							start=SDL_GetTicks();
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
									name=Util.Text(namep,332,185,Util.renderer,"res/font/Pixellettersfull-BnJ5.ttf",{0,0,0},30,dname);
									SDL_RenderCopy(Util.renderer, name, NULL, &dname);
									SDL_DestroyTexture(name);
									SDL_RenderCopy(Util.renderer, cup, NULL, &dcup);
									SDL_RenderPresent(Util.renderer);
							while (SDL_PollEvent(&event)) {
								if (event.type == SDL_QUIT) return;
								else if (event.type == SDL_TEXTINPUT)
									// Xử lý văn bản nhập vào
									{
										if(namep.length()<=15)
										{
																					if(point)
										{
											namep.pop_back();
											namep+=event.text.text;
											namep+='|';
										}
										else namep+=event.text.text;
										}
									}
								else if (event.type == SDL_KEYDOWN) 
									{
										if(event.key.keysym.sym==SDLK_BACKSPACE)
										{
											if(point)
											{
												if(namep.length()>1)
												{
													namep.pop_back();
												namep.pop_back();
												namep+='|';
												}
											}
											else 
											{
												if(!namep.empty()) namep.pop_back();
											}
										}
									 else if(event.key.keysym.sym==SDLK_ESCAPE) return;
									}
								else if(event.type==SDL_MOUSEBUTTONDOWN) 
								{
									if(point) namep.pop_back();
									return;
								}
							}
							if(start-end>=delaypoint)
							{
								end=start;
								if(point)
								{
									point=0;
									namep.pop_back();
								}
								else{
									point=1;
									namep+='|';
								}
							}
						}

						SDL_StopTextInput(); // Kết thúc chế độ nhập văn bản
}
int Tetris::renderinfortext()
{
            clean1();
            SDL_Event e;
			infortext = Util.loadTexture("res/demo image/INFOR-MINECRAFT.png",Util.renderer); 
				SDL_RenderCopy(Util.renderer, infortext, NULL, NULL); 
                SDL_DestroyTexture(infortext);
				SDL_RenderPresent(Util.renderer); 
				while (SDL_WaitEvent(&e)) {
					switch(e.type) {
						case SDL_QUIT: 
							return 0; 
						case SDL_KEYDOWN: 
							switch(e.key.keysym.sym) {
								case SDLK_ESCAPE: return 0; 
								case SDLK_h: 

                                    return 1;
							}
					}
				}
		
}
int Tetris::renderrecord()
{
            clean1();
            SDL_Event e;
			int *add=new int [3];
                recordboard = Util.loadTexture("res/demo image/bgrecord.png",Util.renderer); 
				SDL_RenderCopy(Util.renderer, recordboard, NULL, NULL); 
                SDL_DestroyTexture(recordboard);
                recordboard = Util.Text("Level 1",80,410,Util.renderer,"res/font/EvilEmpire-4BBVK.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
                recordboard = Util.Text("Level 2",80,490,Util.renderer,"res/font/EvilEmpire-4BBVK.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
                recordboard = Util.Text("Level 3",80,570,Util.renderer,"res/font/EvilEmpire-4BBVK.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
				for(int i=0;i<3;i++)
				{
					if(a[i]==0) add[i]=25;
				if(a[i]>100) add[i]=10;
				if(a[i]>1000) add[i]=0;
				if(a[i]>10000) add[i]=-10;
				}
                recordboard = Util.Text(to_string(a[0]),270+add[0],410,Util.renderer,"res/font/font.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
                recordboard = Util.Text(to_string(a[1]),270+add[1],490,Util.renderer,"res/font/font.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
                recordboard = Util.Text(to_string(a[2]),270+add[2],570,Util.renderer,"res/font/font.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
                recordboard = Util.Text(recordname[0],405,420,Util.renderer,"res/font/Pixellettersfull-BnJ5.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
                recordboard = Util.Text(recordname[1],405,500,Util.renderer,"res/font/Pixellettersfull-BnJ5.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
                recordboard = Util.Text(recordname[2],405,580,Util.renderer,"res/font/Pixellettersfull-BnJ5.ttf",{255,255,255},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
				recordboard = Util.Text("Press H to go back",30,90,Util.renderer,"res/font/font.ttf",{0,0,0},30,dRects);
                SDL_RenderCopy(Util.renderer, recordboard, NULL, &dRects); 
                SDL_DestroyTexture(recordboard);
				SDL_RenderPresent(Util.renderer); 
                delete [] add;
				while (SDL_WaitEvent(&e)) {
					switch(e.type) {
						case SDL_QUIT: 
							return 0; 
						case SDL_KEYDOWN: 
							switch(e.key.keysym.sym) {
								case SDLK_ESCAPE: return 0; 
								case SDLK_h: 
                                    return 1;
							}
					}
				}
		
}