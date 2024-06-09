#include "Tetris.h"
#include "Tetris.cpp"
#include "Util.h"
#include "Util.cpp"
#include "Menu.cpp"
#undef main

using namespace std;

const int M = 23;
const int N = 10;
// int ThreadFunction(void* data) {

//     tetris->MouseGame(); // Gọi phương thức từ luồng
// 	return 0;
// }

int main(int argc, char* argv[])
{
//  util Util;
 Tetris *tetris = new Tetris();
 srand((int)time(0));
 if(tetris -> init())
 {
    Home:
        tetris -> menu();
        int i=tetris->showmenu();
        if (i == 0) {
			//exit
            tetris->clean1();
		game:
            tetris->SetupGame();
			tetris->renderstartgame();
			// SDL_Thread* thread;
			while(tetris -> isRunning())
         {
            tetris->updateRenderer();
             tetris->setCurrentTime(SDL_GetTicks());
			// int a=4;
			// thread = SDL_CreateThread(ThreadFunction, "MyThread", (void*)a);
             tetris->Event();
             tetris->game();
            tetris->checkline();
            tetris->gameOver();
         }
		tetris->reset();
		int check=tetris->endgame();
		if(check) goto game;
		else{
				tetris->clean();
         		goto Home;
		}

        }
		else if (i == 1) {
			//game instruction
            tetris->clean1();
            SDL_Event e;
			SDL_Texture* infor_text; 
			infor_text = tetris->Util.loadTexture("res/demo image/INFOR-MINECRAFT.png",tetris->Util.renderer); 
			while (true) {
				SDL_RenderCopy(tetris->Util.renderer, infor_text, NULL, NULL); 
				SDL_RenderPresent(tetris->Util.renderer); 
                
				while (SDL_PollEvent(&e)) {
					switch(e.type) {
						case SDL_QUIT: 
							exit(0);  
						case SDL_KEYDOWN: 
							switch(e.key.keysym.sym) {
								case SDLK_ESCAPE: break; 
								case SDLK_h: 
									SDL_DestroyTexture(infor_text);
                                    goto Home;
							}
					}
				}
			} 
     }
 }
 tetris->clean1();
 tetris->~Tetris();
 delete tetris; tetris = NULL;
 Mix_CloseAudio();
 return 0;
}

