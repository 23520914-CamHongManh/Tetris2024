#include "Tetris.h"
#include <thread>
/*
 0 1 2 3
 4 5 6 7 */

// const int Tetris::figure[7][4] =
// {
//     0, 1, 2, 3, // I
//     0, 1, 5, 6, // Z
//     0, 4, 5, 6, // J
//     2, 6, 5, 4, // L
//     1, 2, 5, 6, // O
//     2, 1, 5, 4, // S
//     1, 4, 5, 6  // T
// };

bool Tetris::init()
{
    Util.initSDL(Util.window, Util.renderer);
    SDL_SetRenderDrawColor(Util.renderer, 255, 255, 255, 255);
    //Util.backgroundAudio("Background.wav");
    nextTetromino();
    return true;
}

bool Tetris::selectRect(SDL_Rect &rect, const int x, const int y)
{
    if(x >= rect.x && x <= rect.x + rect.w
       && y >= rect.y && y <= rect.y + rect.h)
        return true;
    return false;
}


void Tetris::updateField(SDL_Rect &rect, const int x, const int y)
{
    rect.x += x;
    rect.y += y;
}

void Tetris::Event()
{
    SDL_Event e;
    int xm ; int ym ;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            running = false;
            break;
        }
        else if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
            case SDLK_RIGHT :
                {
                     move = 1;
                     Util.effectAudio("res/audio/music/Move.wav");
                     break;
                }
            case SDLK_LEFT :
                {
                     move = -1;
                     Util.effectAudio("res/audio/music/Move.wav");
                     break;
                }
            case SDLK_UP :
                {
                    rotate = true;
                    Util.effectAudio("res/audio/music/rotate.wav");
                    break;
                }
            case SDLK_DOWN :
                {
                    delay = 0;
                    break;
                }
                case  SDLK_ESCAPE: {
                    running=false;
					return;
					}
            }
        }

				else if(e.type== SDL_MOUSEBUTTONDOWN){
					xm = e.button.x; 
					ym = e.button.y;
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
                    if(selectRect(dpause,xm,ym))
                    {
                        SDL_RenderCopy(Util.renderer,pausebg,NULL,NULL);
                        SDL_RenderCopy(Util.renderer,playa,NULL,&dplay);
                        SDL_RenderPresent(Util.renderer);
                        SDL_Event m;
                        now:
                            SDL_WaitEvent(&m);
                            int xz,yz;
                            switch(m.type)
                            {
                                case SDL_QUIT: 
                                    running=false;
                                    return;
                                case SDL_MOUSEBUTTONDOWN:
                                    xz = m.button.x; 
                                    yz = m.button.y;
                                    if (!selectRect(dplay,xz,yz)) {
                                        goto now;
                                default: goto now;
                            }
                        }
                    }
                   }
            // if(!SDL_PollEvent(&e)) break;
        }
    }


void Tetris::setCurrentTime(Uint32 t)
{
    currentTime = t;
}

bool Tetris::collision()
{
    for(int i = 0; i < 4; i++)
    {
        if(temp[0][i].x < 0 || temp[0][i].x >= col || temp[0][i].y >= line)   //va cham vs field
            return false;
        else if(field[temp[0][i].y][temp[0][i].x])  //va cham vs block
            return false;
    }
    return true;
}

void Tetris::tetromino(SDL_Rect &rect, int x, int y, int w, int h)
{
    rect = {x, y, w, h};
}

void Tetris::nextTetromino()
{
    color[0]=color[1];
    color[1] = 1 + rand()%12;
    int a = rand()%7+1;
    switch(a)
    {
        case 1:ter[1]=new TerI();break;
        case 2:ter[1]=new TerZ();break;
        case 3:ter[1]=new TerS();break;
        case 4:ter[1]=new TerJ();break;
        case 5:ter[1]=new TerL();break;
        case 6:ter[1]=new TerT();break;
        case 7:ter[1]=new TerO();break;
        default: break;
    }
    // int b = rand()%7;
}
void Tetris::updatetemp()
{
        int *c=ter[0]->getback();
    int *b=ter[1]->getback();
    for(int i = 0; i < 4; i++)
    {
        switch(ter[0]->getloai())
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        temp[0][i].x = c[i] % 4+3; break;
        case 6:
        temp[0][i].x = c[i] % 4+rand()%2+3; break;
        case 7:
        temp[0][i].x = c[i] % 4+rand()%3+3; break;
        default: break;
    }
        temp[0][i].y = c[i] / 4;
        temp[1][i].x = b[i] % 4;
        temp[1][i].y = b[i] / 4;
    }
    delete c;
    delete b;
}
void Tetris::game()
{
    //backup
    for(int i = 0; i < 4; i++)
        backup[i] = temp[0][i];   // save block khi va cham
    // move
    for(int i = 0; i < 4; i++)
    {
        temp[0][i].x += move;
    }
    if(!collision())   // xu li va cham khi move
        {
            for(int i = 0; i < 4; i++)
                temp[0][i] = backup[i];
        }
    //rotate
    if(rotate)
    {
        point p = temp[0][1];
        for(int i = 0; i < 4; i++)
        {
            int x = temp[0][i].y - p.y;
            int y = temp[0][i].x - p.x;
            temp[0][i].x = p.x - x;
            temp[0][i].y = p.y + y;
        }
        if(!collision())  // xu ly va cham khi rotate
        {
            for(int i = 0; i < 4; i++)
                temp[0][i] = backup[i];
        }
    }

    if(currentTime - lastTime > delay)
    {
        for(int i = 0; i < 4; i++)
        {
            temp[0][i].y += 1;
        }
        lastTime = currentTime;
        if(!collision())
        {
            for(int i = 0; i < 4; i++)
                field[backup[i].y][backup[i].x] = color[0];// save mau o cuoi line
                Tetrimino *p=ter[0];
                ter[0]=ter[1];
                delete p;
            nextTetromino();
        }
    }

    move = 0;
    rotate = false;
    if(level == 1)
        delay = 400;
    else if(level == 2)
        delay = 250;
    else if(level == 3)
        delay = 150;
}

void Tetris::checkline()
{
    int n = line - 1;
    for(int i = n; i > 0; i--)
    {
        int count = 0;
        for(int j = 0; j < col; j++)
        {
            if(field[i][j])
                count++;
            field[n][j] = field[i][j];
        }
        if(count < col)
            n--;
        if(count == col)
        {
            Util.effectAudio("res/audio/music/metal hit.wav");
            score += 100;
            if(highestscore<score) highestscore=score;
            string text = to_string(score);
            string text1= to_string(highestscore);
            if(score < 1000){
                scorenum=Util.Text(text, blockW*12+83, blockH*3+80, Util.renderer, { 255, 255, 255 },50,dRects);
                highnum=Util.Text(text1, blockW*12+83, blockH*9+115, Util.renderer, { 255, 255, 255 },50,dRecths);
            }
            else if(score < 10000){
                scorenum=Util.Text(text, blockW*12+70, blockH*3+80, Util.renderer, { 255, 255, 255 },50,dRects);
                highnum=Util.Text(text1, blockW*12+70, blockH*9+115, Util.renderer, { 255, 255, 255 },50,dRecths);
        }
        else
        {
            scorenum=Util.Text(text, blockW*12+57, blockH*3+80, Util.renderer, { 255, 255, 255 },50,dRects);
                highnum=Util.Text(text1, blockW*12+57, blockH*9+115, Util.renderer, { 255, 255, 255 },50,dRecths);
        }
        }
    }
}

void Tetris::gameOver()
{
    int game_over_count = 0;
    for(int i = 0; i < line; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(field[i][j] != 0)
            {
                game_over_count ++;
                break;
            }
        }
    }
    if(game_over_count == line)
    {
        Util.effectAudio("res/audio/sound/lose.wav");
        running = false;
        if(highestscore>highestscore1)
        {
            ofstream p("Highestscore.txt");

            switch(level)
            {
                case 1:
                case 2:
                case 3:
                a[level-1]=highestscore;
                break;
            }
            for(int i=0;i<3;i++)
            {
                p<<a[i]<<" ";
            }
        p.close();
    //         FILE *p=fopen("Highest Score.txt","w");
    // int *a=new int[3];
    // switch(level)
    // {
    //     case 1:
    //     case 2:
    //     case 3:
    //     a[level-1]=highestscore;
    //     break;
    // }
    // for(int i=0;i<3;i++)
    // {
    //     fwrite(&a[i],sizeof(int),1,p);
    // }
    // delete a;a=NULL;
    // fclose(p);
        }
        // return true;
        // Util.quitSDL(Util.window, Util.renderer,Util.Tex);
        //clean();
        //gameover_background = Util.loadTexture("menu_background.png", Util.renderer);
       // SDL_Rect game_over_rect = {0, 0, 300, 300};
        //SDL_RenderCopy(Util.renderer, gameover_background, NULL, &game_over_rect);
        //SDL_RenderPresent(Util.renderer);
    }
    // return false;
}
void Tetris::SetupGame()
{
    gamebg=Util.loadTexture("res/demo image/bg.png",Util.renderer);
    // Util.backgroundAudio("res/audio/music/HQ _ Fish-Man Island Stage Theme (SoundTrack) - One Piece Bounty Rush.mp3",30);
    background = Util.loadTexture("res/demo image/stone-wall1.png", Util.renderer);
    block = Util.loadTexture("res/demo image/minecraft.png", Util.renderer);
    next = Util.loadTexture("res/demo image/minecraft-inventory.webp", Util.renderer);
    score1 = Util.loadTexture("res/demo image/levelText_bg.png", Util.renderer);
    high=Util.loadTexture("res/demo image/UI_bg.png",Util.renderer);
    border = Util.loadTexture("res/gfx/Background/border.png", Util.renderer);
    border1 = Util.loadTexture("res/gfx/Background/border1.png", Util.renderer);
    dispender = Util.loadTexture("res/demo image/dispender.png", Util.renderer);
    pauseb=Util.loadTexture("res/demo image/pause1.png",Util.renderer);
    playa=Util.loadTexture("res/demo image/play1.png",Util.renderer);
    pausebg=Util.loadTexture("res/demo image/UI_bg.png",Util.renderer);
    dRectmu = {blockW*17,20,50,50};
    nextTetromino();
    ter[0]=ter[1];
    nextTetromino();
    if(score == 0)
    {
        scorenum=Util.Text("0", blockW*12+105, blockH*3+80, Util.renderer, { 255, 255, 255 },50,dRects);
        // SDL_RenderCopy(Util.renderer, Util.Tex, &Util.srcRest, &Util.desRect);
    }
    scoretex=Util.Text("Your score", blockW*12+35, blockH*3+20, Util.renderer, { 255, 255, 255 },40,dRects1);
    ifstream p("Highestscore.txt");
    if(!p) cerr<<"Can't open file"<<endl;
    for(int i=0;i<3;i++)
    {
        p>>a[i];
    }
    switch(level)
    {
        case 1:
        case 2:
        case 3:
        highestscore=a[level-1];
        break;
    }
    p.close();
    //     FILE *p=fopen("Highest Score.txt","r");
    // int *a=new int[3];
    // for(int i=0;i<3;i++)
    // {
    //     fread(&a[i],sizeof(int),1,p);
    // }
    // switch(level)
    // {
    //     case 1:
    //     case 2:
    //     case 3:
    //     highestscore=a[level-1];
    //     break;
    // }
    // delete a;a=NULL;
    // fclose(p);
    hightex=Util.Text("Highest Score", blockW*12+15, blockH*9+45, Util.renderer, { 255, 255, 255 },40,dRecths1);
    string text = to_string(highestscore);
    if(highestscore < 1000){
        if(highestscore == 0)
    {
        highnum=Util.Text(text, blockW*12+105, blockH*9+115, Util.renderer, { 255, 255, 255 },50,dRecths);
        // SDL_RenderCopy(Util.renderer, Util.Tex, &Util.srcRest, &Util.desRect);
    }
               else highnum=Util.Text(text, blockW*12+83, blockH*9+115, Util.renderer, { 255, 255, 255 },50,dRecths);
    }
            else if(highestscore < 10000)
                highnum=Util.Text(text, blockW*12+70, blockH*9+115, Util.renderer, { 255, 255, 255 },50,dRecths);
                else
        {
                highnum=Util.Text(text, blockW*12+57, blockH*9+115, Util.renderer, { 255, 255, 255 },50,dRecths);
        }

}
void Tetris::updateRenderer()
{
    SDL_RenderClear(Util.renderer);
    SDL_RenderCopy(Util.renderer, background, NULL, NULL);
    // SDL_RenderCopy(Util.renderer, score_frame, NULL, &dRect_score_frame);
    SDL_RenderCopy(Util.renderer, gamebg, &sRectbg, &dRectbg);
    SDL_RenderCopy(Util.renderer, border1, &sRectbd1, &dRectbd1);
    SDL_RenderCopy(Util.renderer, border1, &sRectbd1, &dRectbd1f);
    // SDL_RenderCopy(Util.renderer, border, &sRectbd, &dRectbd);
    for(int i=0;i<10;i++)
    {
        SDL_Rect dRectdis={blockW*(1+i),SCREEN_HEIGHT - (line + 2)*blockH,blockW,blockH};
        SDL_RenderCopy(Util.renderer, dispender, NULL, &dRectdis);
    }
    SDL_RenderCopy(Util.renderer, border, &sRectbd, &dRectbdf);
    SDL_RenderCopy(Util.renderer, next, &sRectnext, &dRectnext);
    SDL_RenderCopy(Util.renderer, score1, NULL, &dRectscore);
    SDL_RenderCopy(Util.renderer, high, &sRecthigh, &dRecthigh);
    SDL_RenderCopy(Util.renderer, scorenum, NULL, &dRects);
    SDL_RenderCopy(Util.renderer, scoretex, NULL, &dRects1);
    SDL_RenderCopy(Util.renderer, highnum, NULL, &dRecths);
    SDL_RenderCopy(Util.renderer, hightex, NULL, &dRecths1);
    SDL_RenderCopy(Util.renderer,music,&sRectmu,&dRectmu);
    SDL_RenderCopy(Util.renderer,pauseb,NULL,&dpause);
    // string text = to_string(highestscore);
    // Util.Text(text, blockW*12+100, blockH*9+40, Util.renderer, { 255, 255, 255 },50);
    // va cham vs day ( luu hinh anh cuoi cung khi o day - bao gom ca mau sac)
    for(int i = 0; i < line; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(field[i][j]!=0)
            {
                int nx,ny;
        switch(field[i][j])
        {
         case 1:nx= 8; ny= 3;
            break;
            case 2:nx= 36; ny= 3;
            break;
            case 3:nx= 62; ny= 3;
            break;
            case 4:nx= 8; ny= 31;
            break;
            case 5:nx= 36; ny= 31;
            break;
            case 6:nx= 62; ny= 31;
            break;
            case 7:nx= 9; ny= 60;
            break;
            case 8:nx= 36; ny= 60;
            break;
            case 9:nx= 62; ny= 60;
            break;
            case 10:nx= 8; ny= 87;
            break;
            case 11:nx= 36; ny= 87;
            break;
            case 12:nx= 62; ny= 87;
            break;

        }
                tetromino(sRect, nx,ny,28,28);  // Giu nguyen mau cua block khi dang o day
                tetromino(dRect, j*blockW, i*blockH);
                updateField(dRect, blockW, SCREEN_HEIGHT - (line + 1)*blockH);
                SDL_RenderCopy(Util.renderer, block, &sRect, &dRect);
            }
        }
    }
    //Tao block
    for(int i = 0; i < 4; i++)
    {
        int nx,ny;
        switch(color[0])
        {
            case 1:nx= 8; ny= 3;
            break;
            case 2:nx= 36; ny= 3;
            break;
            case 3:nx= 62; ny= 3;
            break;
            case 4:nx= 8; ny= 31;
            break;
            case 5:nx= 36; ny= 31;
            break;
            case 6:nx= 62; ny= 31;
            break;
            case 7:nx= 9; ny= 60;
            break;
            case 8:nx= 36; ny= 60;
            break;
            case 9:nx= 62; ny= 60;
            break;
            case 10:nx= 8; ny= 87;
            break;
            case 11:nx= 36; ny= 87;
            break;
            case 12:nx= 62; ny= 87;
            break;
        }
        tetromino(sRect, nx,ny,28,28);
        tetromino(dRect, temp[0][i].x *blockW, temp[0][i].y*blockH);
        updateField(dRect, blockW, SCREEN_HEIGHT - (line + 1)*blockH);
        SDL_RenderCopy(Util.renderer, block, &sRect, &dRect);
    };
    SDL_RenderPresent(Util.renderer);
}

void Tetris::reset()
{
    for(int i = 0; i < line; i++)
    {
        for(int j = 0; j < col; j++)
        {
            field[i][j] = 0;
        }
    }
    score=0;
    dRectmu = {20, 20, 40, 40};
    //SDL_RenderCopy(Util.renderer, background, NULL, NULL);
}

void Tetris::clean() // chong tran bo nho
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(gamebg);
    SDL_DestroyTexture(block);
    // SDL_DestroyTexture(backgroundMenu);
    // SDL_DestroyTexture(play);
    // SDL_DestroyTexture(play_light);
    // SDL_DestroyTexture(lv1);
    // SDL_DestroyTexture(lv2);
    // SDL_DestroyTexture(lv3);
    SDL_DestroyTexture(border);
    SDL_DestroyTexture(border1);
    SDL_DestroyTexture(dispender);
     SDL_DestroyTexture(next);
    SDL_DestroyTexture(score1);
    SDL_DestroyTexture(high);
     SDL_DestroyTexture(scoretex);
    SDL_DestroyTexture(scorenum);
    SDL_DestroyTexture(hightex);
     SDL_DestroyTexture(highnum);
     SDL_DestroyTexture(music);
     SDL_DestroyTexture(pauseb);
     SDL_DestroyTexture(playa);
     SDL_DestroyTexture(pausebg);
    // SDL_DestroyTexture(infor);
    // SDL_DestroyTexture(lv1_light);
    // SDL_DestroyTexture(lv2_light);
    // SDL_DestroyTexture(lv3_light);
}
void Tetris::clean1() // chong tran bo nho
{
    // SDL_DestroyTexture(background);
    // SDL_DestroyTexture(gamebg);
    // SDL_DestroyTexture(block);
    SDL_DestroyTexture(backgroundMenu);
    SDL_DestroyTexture(play);
    SDL_DestroyTexture(play_light);
    SDL_DestroyTexture(lv1);
    SDL_DestroyTexture(lv2);
    SDL_DestroyTexture(lv3);
    // SDL_DestroyTexture(border);
    // SDL_DestroyTexture(border1);
    // SDL_DestroyTexture(dispender);
    SDL_DestroyTexture(infor);
    // SDL_DestroyTexture(lv1_light);
    // SDL_DestroyTexture(lv2_light);
    // SDL_DestroyTexture(lv3_light);
}
Tetris::~Tetris()
{
    delete ter[0];
        delete ter[1];
        delete [] ter;
    Util.quitSDL();
}
