#include "Tetris.h"
#include "Tetris.cpp"
#include "Util.h"
#include "Util.cpp"
#include "Menu.cpp"
#undef main

using namespace std;

const int M = 23;
const int N = 10;

int main(int argc, char* argv[])
{
 Tetris *tetris = new Tetris();
 srand((int)time(0));
 if(tetris -> init())
 {
    Home:
        tetris -> menu();
        int i=tetris->showmenu();
        if (i == 0) {
            tetris->clean1();
		game:
            tetris->SetupGame();
			tetris->renderstartgame();
			while(tetris -> isRunning())
         {
            tetris->updateRenderer();
             tetris->setCurrentTime(SDL_GetTicks());
             tetris->Event();
             tetris->game();
            tetris->checkline();
            tetris->gameOver();
         }
		tetris->reset();
		int check=tetris->endgame();
		if(check) 
		{
			tetris->clean();
			goto game;
		}
		else{
				tetris->clean();
         		goto Home;
		}

        }
		else if (i == 1) {
			//game instruction
           int a=tetris->renderinfortext();
		   if(a==1) goto Home;
     }
	 else if(i==2)
	 {
		//recordboard
		int a=tetris->renderrecord();
		if(a==1) goto Home;
	 }
 }
 tetris->clean1();
 tetris->~Tetris();
 delete tetris; tetris = NULL;
 Mix_CloseAudio();
 return 0;
}

