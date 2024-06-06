#include "Tetris.h"
#include "Tetris.cpp"
#include "Util.h"
#include "Util.cpp"
#undef main

using namespace std;

const int M = 23;
const int N = 10;

int main(int argc, char* argv[])
{
 util *Util = new util;
 Tetris *tetris = new Tetris;
 srand((int)time(0));
 if(tetris -> init())
 {
     while(tetris -> menu())
     {
         while(tetris -> isRunning())
         {
            tetris -> setCurrentTime(SDL_GetTicks());
            tetris -> Event();
            tetris -> game();
            tetris -> checkline();
            tetris -> gameOver();
            tetris -> updateRenderer();
         }
         tetris->reset();
     }
 }
 tetris->clean();
 Util -> quitSDL(Util -> window, Util -> renderer,Util->Tex);
 Mix_CloseAudio();
 SDL_Quit();
 TTF_Quit();
 delete Util; Util = NULL;
 delete tetris; tetris = NULL;
 return 0;
}