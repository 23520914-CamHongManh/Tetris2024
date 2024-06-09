#ifndef _TETRIS_H
#define _TETRIS_H
#define playgame 0
#define changelevel 1
#define inforcheck 2
#define switchmusic 3
#include "Util.h"
#include "Tetrimino.cpp"
    typedef struct 
    {
        int x, y;
    }point;
class Tetris
{
private:
    enum{blockW = 30, blockH = 30};
    enum{line = 20, col = 10};
    SDL_Texture *background = NULL, *block = NULL;
    SDL_Texture* backgroundMenu = NULL;
    SDL_Texture* play = NULL;
    SDL_Texture* play_light = NULL;
    SDL_Texture* lv1 = NULL;
    SDL_Texture* lv2 = NULL;
    SDL_Texture* lv3 = NULL;
    // SDL_Texture* lv1_light = NULL;
    // SDL_Texture* lv2_light = NULL;
    // SDL_Texture* lv3_light = NULL;
    // SDL_Texture* gameover_background= NULL;
    SDL_Texture* gamebg= NULL;
    SDL_Texture* next=NULL;
    SDL_Texture* score1= NULL;
    SDL_Texture* high=NULL;
    SDL_Texture* border= NULL;
    SDL_Texture* border1= NULL;
    SDL_Texture* dispender=NULL;
    SDL_Texture* music=NULL;
    SDL_Texture* infor=NULL;
    SDL_Texture* scoretex=NULL;
    SDL_Texture* scorenum=NULL;
    SDL_Texture* hightex=NULL;
    SDL_Texture* highnum=NULL;
    SDL_Texture* pauseb=NULL;
    SDL_Texture* playa=NULL;
    SDL_Texture* pausebg=NULL;
    SDL_Texture* replay=NULL;
    SDL_Texture* remenu=NULL;
    SDL_Texture* explode=NULL;
    SDL_Texture* nameframe=NULL;
    SDL_Texture* cup=NULL;
    SDL_Texture* name=NULL;
    SDL_Rect sRect = {0, 0, 10, 10}, dRect = {0, 0, blockW, blockH};
    // SDL_Rect dRect_score_frame = {5, 5, blockW*4, blockH*4};
    SDL_Rect sRectbg={0,0,320,640};
    SDL_Rect dRectbg={blockW,SCREEN_HEIGHT - (line + 1)*blockH,blockW*10,blockH*20};
    SDL_Rect sRectbd={0,0,200,20};
    // SDL_Rect dRectbd={blockW,SCREEN_HEIGHT - (line + 2)*blockH+10,blockW*10,20};
    SDL_Rect dRectbdf={blockW,SCREEN_HEIGHT - (line - 19)*blockH,blockW*10,20};
    SDL_Rect sRectbd1={0,0,20,440};
    SDL_Rect dRectbd1={10,SCREEN_HEIGHT - (line + 1)*blockH,20,blockH*21-10};
    SDL_Rect dRectbd1f={blockW*11,SCREEN_HEIGHT - (line + 1)*blockH,20,blockH*21-10};
    SDL_Rect playRect = {250, 263, 94, 53};
    SDL_Rect levelRect = {300, 351, 174, 53};
    SDL_Rect sRectmu = {0, 0, 32, 32};
    // 	TextureManager::SetPos(pos_menu[MUSIC], Vector2D(42, 15), Vector2D(32, 32)); 
    SDL_Rect dRectmu = {20, 20, 40, 40};
    SDL_Rect sRectin = {64, 0, 64, 64};
        // TextureManager::SetPos(pos_menu[INFOR], Vector2D(570, 190), Vector2D(64, 64)); 
    SDL_Rect dRectin = {230, 600, 50, 50};
    SDL_Rect sRectnext = {8, 365, 403, 347};
    SDL_Rect dRectnext = {blockW*12, blockH*16+30, 230, 178};
    SDL_Rect dRectscore = {blockW*12, blockH*3, 230, 160};
    SDL_Rect sRecthigh = {50, 0, 48, 32};
    SDL_Rect dRecthigh = {blockW*12, blockH*9+25, 230, 180};
    SDL_Rect dRects = {0, 0, 0, 0};
    SDL_Rect dRects1 = {0, 0, 0, 0};
    SDL_Rect dRecths = {0, 0, 0, 0};
    SDL_Rect dRecths1 = {0, 0, 0, 0};
    SDL_Rect dpause={blockW*13, 20 , 55, 55};
    SDL_Rect dplay={200,250,200,200};
    SDL_Rect dreplay={100,500,150,150};
    SDL_Rect dremenu={350,500,150,150};
    SDL_Rect dexplode={0,0,0,0};
    SDL_Rect dnamef={320, 170, 196, 56};
    SDL_Rect dname={0,0,0,0};
    SDL_Rect dcup={520, 590, 70, 70};
    bool Checkmouse[4]={0,0,0,0};
    bool running = false;
    int level = 1;
    int score = 0;
    int highestscore=0;
    int highestscore1=0;
    int a[3];
    int field[line+1][col] = {{0}};
    point backup[4];
    point temp[2][4];
    Tetrimino **ter;
    unsigned int delay = 0;
    bool rotatel = false;
    bool rotater = false;
    int move = 0;
    Uint32 currentTime = 0, lastTime = 0;
    int color[2] = {1,1};
    string namep="Your name...";
    //  theme_music; 
public:
    Tetris() {ter=new Tetrimino*[2];}
    ~Tetris();
    util Util;
    bool init();
    void menu();
    int showmenu();
    bool isRunning()
    {
        return running;
    }
    void Event();
    void tetromino(SDL_Rect &rect, int x = 0, int y = 0, int w = blockW, int h = blockH);
    bool selectRect(SDL_Rect &rect, const int x, const int y);
    void game();
    void clean();
    void clean1();
    void SetupGame();
    void setCurrentTime(Uint32 t);
    void fixcollision();
    bool collision();
    bool collision1();
    bool collision2();
    void nextTetromino();
    void updateRenderer();
    void updateField(SDL_Rect &rect, const int x, const int y);
    void checkline();
    void gameOver();
    void reset();
    void updatetemp();
    void renderexplode(int n);
    void renderstartgame();
    int endgame();
    void rendername();
};
// int a=1;
// #define SDL_CreateThread(Tetris::MouseGame(), "EventThread", (void*)a)  threadID
#endif //TETRIS_H
