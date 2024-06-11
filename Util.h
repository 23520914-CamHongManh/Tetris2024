#ifndef _UTIL_H
#define _UTIL_H


#include"SDL2/include/SDL.h"
#include"SDL2/include/SDL_image.h"
#include"SDL2/include/SDL_mixer.h"
#include"SDL2/include/SDL_ttf.h"
#include<bits/stdc++.h>
#include <thread>

using namespace std;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 700;



const string WINDOW_TITLE = "TETRIS !!!!";

class util
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect srcRest;
    Mix_Chunk* chunk = NULL;
	Mix_Music* music = NULL;
    friend class Tetris;
public:
    void logSDLError(std::ostream& os, const string &msg, bool fatal = false);
    void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
    void quitSDL();
    void waitUntilKeyPressed();
    SDL_Texture *loadTexture(string path, SDL_Renderer *renderer);
    void backgroundAudio(const char* nameSong, const int vol);
    void effectAudio(const char* nameSong,int vol);
    SDL_Texture* Text(string text, int x, int y, SDL_Renderer* renderer,const char* fonttype, SDL_Color color,int size,SDL_Rect &dRect);
	bool isPlaying();
	void pause();
	void resume();
    void clearmusic();
};


#endif
