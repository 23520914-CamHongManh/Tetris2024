#include "Tetris.h"

bool Tetris::init()
{
    Util.initSDL(Util.window, Util.renderer);
    SDL_SetRenderDrawColor(Util.renderer, 255, 255, 255, 255);
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
                     Util.effectAudio("res/audio/music/Move.wav",50);
                     break;
                }
            case SDLK_LEFT :
                {
                     move = -1;
                     Util.effectAudio("res/audio/music/Move.wav",50);
                     break;
                }
            case SDLK_e :
                {
                    rotater = true;
                    Util.effectAudio("res/audio/music/rotate.wav",40);
                    break;
                }
                case SDLK_q :
                {
                    rotatel = true;
                    Util.effectAudio("res/audio/music/rotate.wav",40);
                    break;
                }
            case SDLK_DOWN :
                {
                    delay = 0;
                    space=0;
                    break;
                }
                case SDLK_SPACE :
                {
                    delay=0;
                    space=1;
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
        if(temp[0][i].x < 0|| temp[0][i].x >=col||temp[0][i].y >= line+1)   //va cham vs field
            return false;
        else if(field[temp[0][i].y][temp[0][i].x])  //va cham vs block
            return false;
    }
    return true;
}
bool Tetris::collision1()
{
    for(int i = 0; i < 4; i++)
    {
        if(temp[0][i].y >= line+1)   //va cham vs field
            return false;
        else if(field[temp[0][i].y][temp[0][i].x])  //va cham vs block
            return false;
    }
    return true;
}
void Tetris::fixcollision()
{
    for(int i = 0; i < 4; i++)
    {
        while(temp[0][i].x < 0)
        {
            temp[0][0].x++;
            temp[0][1].x++;
            temp[0][2].x++;
            temp[0][3].x++;
        }
        while(temp[0][i].x >=col) 
        {
            temp[0][0].x--;
            temp[0][1].x--;
            temp[0][2].x--;
            temp[0][3].x--;
        }
    }

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
}
void Tetris::updatetemp()
{
        int *c=ter[0]->getback();
    int *b=ter[1]->getback();
    int m=0,n=0;
    if(ter[0]->getloai()==6) m=rand()%2;
    if(ter[1]->getloai()==6) n=rand()%2;
    // else if(ter[0]->getloai()==7) m=rand()%3;
    for(int i = 0; i < 4; i++)
    {
        temp[0][i].x = c[i] % 4+3+m;
        temp[0][i].y = c[i] / 4;
        temp[1][i].x = b[i] % 4+n;
        temp[1][i].y = b[i] / 4;
    }
    delete c;
    delete b;
}
void Tetris::game()
{
    //backup
    for(int i = 0; i < 4; i++)
        backup[i] = temp[0][i];   
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
    //rotate right
    if(rotater)
    {
        int z=ter[0]->getloai();
        if(z>=2&&z<=6) {
            point p=temp[0][1];
        for(int i = 0; i < 4; i++)
        {
            int x = temp[0][i].y - p.y;
            int y = temp[0][i].x - p.x;
            temp[0][i].x = p.x - x;
            temp[0][i].y = p.y + y;
        }
        }
        else if(z==1)
        {
            point p=temp[0][1];
            int x1 = temp[0][2].x - p.x;
            int y1 = temp[0][2].y - p.y;
        for(int i = 0; i < 4; i++)
        {
            int x = temp[0][i].y - p.y;
            int y = temp[0][i].x - p.x;
            temp[0][i].x = p.x - x + x1;
            temp[0][i].y = p.y + y + y1;
        }
        }
        fixcollision();
        if(!collision1())  // xu ly va cham khi rotate
        {
            for(int i = 0; i < 4; i++)
                temp[0][i] = backup[i];
        }
    }
    //rotate left
    if(rotatel)
    {
        int z=ter[0]->getloai();
        if(z>=2&&z<=6) {
            point p=temp[0][1];
        for(int i = 0; i < 4; i++)
        {
            int x = temp[0][i].y - p.y;
            int y = temp[0][i].x - p.x;
            temp[0][i].x = p.x + x;
            temp[0][i].y = p.y - y;
        }
        }
        else if(z==1)
        {
            point p=temp[0][1];
            int x1 = temp[0][2].x - p.x;
            int y1 = temp[0][2].y - p.y;
        for(int i = 0; i < 4; i++)
        {
            int x = temp[0][i].y - p.y;
            int y = temp[0][i].x - p.x;
            // cout<<x1<<" "<<y1<<endl;
            temp[0][i].x = p.x + x + y1;
            temp[0][i].y = p.y - y + x1;
        }
        }
        fixcollision();
        if(!collision1())  // xu ly va cham khi rotate
        {
            for(int i = 0; i < 4; i++)
                temp[0][i] = backup[i];
        }
        // else if(ter[0]->getloai()==1) swaptemp();
    }
    if(currentTime - lastTime > delay)
    {
        for(int i = 0; i < 4; i++)
        {
            temp[0][i].y += 1;
        }
        lastTime = currentTime;
        if(!collision1())
        {
            for(int i = 0; i < 4; i++)
                field[backup[i].y][backup[i].x] = color[0];// save mau o cuoi line
                // thoi gian delay giua cac lan blocks roi
                if(level == 1)
                    delay = ((400-score/10)>300)? (400-score/10):300;
                else if(level == 2)
                    delay = ((300-score/10)>150)? (300-score/10):140;
                else if(level == 3)
                    delay = 70+rand()%180;
                delay1=delay;
                for(int i = 0; i < 4; i++)
                    backup[i] = temp[1][i];   
                Tetrimino *p=ter[0];
                ter[0]=ter[1];
                delete p;
            nextTetromino();
            updatetemp();
        }
    }

    move = 0;
    rotater = false;
    rotatel=false;
    if(!space) 
    {
        delay=delay1;
    }
}

void Tetris::checkline() // kiem tra xem dong co day khong
{
    int n = line;
    int bonus=0;
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
            bonus++;
            renderexplode(i);
    }
    }
    if(bonus){
        int tempscore=score+(bonus-1)*50;
        for(;score<tempscore;)
        {
            score+=10;
            string text = to_string(score);
            SDL_DestroyTexture(scorenum);
            if(score < 1000){
                if(score==0) scorenum=Util.Text(text, blockW*12+105, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
                else scorenum=Util.Text(text, blockW*12+83, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
            }
            else if(score < 10000){
                scorenum=Util.Text(text, blockW*12+70, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
        }
        else
        {
            scorenum=Util.Text(text, blockW*12+57, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
        }
        updateexplode();
        SDL_Delay(10);
        }
    }
    if(highestscore<score){ 
            highestscore=score;
            SDL_DestroyTexture(highnum);
            string text1= to_string(highestscore);
                    if(highestscore < 1000){
                        highnum=Util.Text(text1, blockW*12+83, blockH*9+115, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRecths);
                    }
                    else if(highestscore < 10000){
                        highnum=Util.Text(text1, blockW*12+70, blockH*9+115, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRecths);
                }
                else
                {
                    highnum=Util.Text(text1, blockW*12+57, blockH*9+115, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRecths);
                }
            }
}

void Tetris::gameOver()
{
    int game_over_count = 0;
    for(int i = line; i > 0; i--)
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
        Util.effectAudio("res/audio/sound/lose.wav",90);
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
                recordname[level-1]=namep;
                break;
            }
            for(int i=0;i<3;i++)
            {
                p<<a[i]<<endl;
                p<<recordname[i]<<endl;
            }
            p.close();
        }
    }
}
void Tetris::SetupGame()
{
    gamebg=Util.loadTexture("res/demo image/bg.png",Util.renderer);
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
    replay=Util.loadTexture("res/demo image/replay.png",Util.renderer);
    remenu=Util.loadTexture("res/demo image/menuback.png",Util.renderer);
    explode=Util.loadTexture("res/demo image/explode.png",Util.renderer);
    music =Util.loadTexture("res/gfx/Button/music.png",Util.renderer);
    dRectmu = {blockW*17,20,50,50};
    nextTetromino();
    ter[0]=ter[1];
    nextTetromino();
    updatetemp();
        // thoi gian delay giua cac lan blocks roi
    if(level == 1)
        delay = 400;
    else if(level == 2)
        delay = 300;
    else if(level == 3)
        delay = 200;
    delay1=delay;
    scorenum=Util.Text(to_string(score), blockW*12+105, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
    scoretex=Util.Text("Your score", blockW*12+35, blockH*3+20, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },40,dRects1);
    ifstream p("Highestscore.txt");
    string c;
    if(!p) cerr<<"Can't open file"<<endl;
    for(int i=0;i<3;i++)
    {
                p>>a[i];
				getline(p,c);
				getline(p,recordname[i]);
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
    highestscore1=highestscore;
    hightex=Util.Text("Highest Score", blockW*12+15, blockH*9+45, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },40,dRecths1);
    string text = to_string(highestscore);
    if(highestscore < 1000){
        if(highestscore == 0)
    {
        highnum=Util.Text(text, blockW*12+105, blockH*9+115, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRecths);
        // SDL_RenderCopy(Util.renderer, Util.Tex, &Util.srcRest, &Util.desRect);
    }
               else highnum=Util.Text(text, blockW*12+83, blockH*9+115, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRecths);
    }
            else if(highestscore < 10000)
                highnum=Util.Text(text, blockW*12+70, blockH*9+115, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRecths);
                else
        {
                highnum=Util.Text(text, blockW*12+57, blockH*9+115, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRecths);
        }

}
void Tetris::updateRenderer()
{
    SDL_RenderClear(Util.renderer);
    SDL_RenderCopy(Util.renderer, background, NULL, NULL);
    SDL_RenderCopy(Util.renderer, gamebg, &sRectbg, &dRectbg);
    SDL_RenderCopy(Util.renderer, border1, &sRectbd1, &dRectbd1);
    SDL_RenderCopy(Util.renderer, border1, &sRectbd1, &dRectbd1f);
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
    // va cham vs day ( luu hinh anh cuoi cung khi o day - bao gom ca mau sac)
    for(int i = 0; i < line+1; i++)
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
                updateField(dRect, blockW, SCREEN_HEIGHT - (line + 2)*blockH);
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
        updateField(dRect, blockW, SCREEN_HEIGHT - (line + 2)*blockH);
        SDL_RenderCopy(Util.renderer, block, &sRect, &dRect);
    }
    //dispender
    for(int i=0;i<10;i++)
    {
        SDL_Rect dRectdis={blockW*(1+i),SCREEN_HEIGHT - (line +2)*blockH,blockW,blockH};
        SDL_RenderCopy(Util.renderer, dispender, NULL, &dRectdis);
    }
    //Tao block xem truoc
    for(int i = 0; i < 4; i++)
    {
        int nx,ny;
        switch(color[1])
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
        tetromino(dRect, temp[1][i].x *53, temp[1][i].y*55,blockW+15,blockH+15);
        updateField(dRect, blockW*12+11, blockH*19+4);
        SDL_RenderCopy(Util.renderer, block, &sRect, &dRect);
    }
    SDL_RenderPresent(Util.renderer);
}

void Tetris::reset()
{
    for(int i = 0; i < line+1; i++)
    {
        for(int j = 0; j < col; j++)
        {
            field[i][j] = 0;
        }
    }
    SDL_DestroyTexture(scoretex);
    if(score<=highestscore1) scoretex=Util.Text("Awesome!", 160, 100, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },80,dRects1);
    else scoretex=Util.Text("New Record!!!", 110, 100, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },80,dRects1);
    SDL_DestroyTexture(scorenum);
    string text = to_string(score);
        if(score < 1000){
                if(score==0)  scorenum=Util.Text(text, 280, 250, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },70,dRects);
                else scorenum=Util.Text(text, 250, 250, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },70,dRects);          }
            else if(score < 10000){
                scorenum=Util.Text(text, 235, 250, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },70,dRects);        }
        else
        {
            scorenum=Util.Text(text, 220, 250, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },70,dRects);        }
    score=0;
    dRectmu = {20, 20, 40, 40};
}
int Tetris::endgame()
{
    Util.pause();
    SDL_Delay(500);
    if(highestscore==highestscore1) Util.effectAudio("res/audio/music/awesome.wav",128);
    else Util.effectAudio("res/audio/music/newrecord.wav",128);
    SDL_RenderCopy(Util.renderer,pausebg,NULL,NULL);
    SDL_RenderCopy(Util.renderer,pausebg,NULL,NULL);
    SDL_RenderCopy(Util.renderer,pausebg,NULL,NULL);
    SDL_RenderCopy(Util.renderer,pausebg,NULL,NULL);
    SDL_RenderCopy(Util.renderer,replay,NULL,&dreplay);
    SDL_RenderCopy(Util.renderer,remenu,NULL,&dremenu);
    SDL_RenderCopy(Util.renderer,scorenum,NULL,&dRects);
    SDL_RenderCopy(Util.renderer,scoretex,NULL,&dRects1);
    SDL_RenderPresent(Util.renderer);
    SDL_Event e;
     while(SDL_WaitEvent(&e))
     {
        switch(e.type)
        {
            case SDL_QUIT: if(Checkmouse[switchmusic]==0) Util.resume(); return 0; break;
            case SDL_KEYDOWN:
            if(e.key.keysym.sym==SDLK_ESCAPE) 
            {
                if(Checkmouse[switchmusic]==0) Util.resume();
                return 0; break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {int x=e.button.x;
            int y=e.button.y;
            if(selectRect(dreplay,x,y))
            { 
                if(Checkmouse[switchmusic]==0) Util.resume();
                running=true;
                return 1;
            }
            else if(selectRect(dremenu,x,y)){ 
                if(Checkmouse[switchmusic]==0) Util.resume();
                return 0;
            }
            }
            default: break;
        }
     }

}
void Tetris::clean() // chong tran bo nho cho che do choi
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(gamebg);
    SDL_DestroyTexture(block);
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
     SDL_DestroyTexture(replay);
     SDL_DestroyTexture(remenu);
     SDL_DestroyTexture(explode);
}
void Tetris::clean1() // chong tran bo nho cho menu
{
    SDL_DestroyTexture(backgroundMenu);
    SDL_DestroyTexture(play);
    SDL_DestroyTexture(play_light);
    SDL_DestroyTexture(lv1);
    SDL_DestroyTexture(lv2);
    SDL_DestroyTexture(lv3);
    SDL_DestroyTexture(infor);
    SDL_DestroyTexture(nameframe);
    SDL_DestroyTexture(name);
    SDL_DestroyTexture(cupdark);
    SDL_DestroyTexture(cup);
    SDL_DestroyTexture(music);
}
Tetris::~Tetris()
{
    delete ter[0];
        delete ter[1];
        delete [] ter;
    Util.quitSDL();
}
void Tetris::renderexplode(int n)
{
    Util.effectAudio("res/audio/music/explode.wav",90);
        for(int j = 0; j < col; j++)
        {
                tetromino(dexplode, j*blockW, n*blockH,blockW-10,blockH-10);
                updateField(dexplode, blockW+5, SCREEN_HEIGHT - (line + 2)*blockH+5);
                SDL_RenderCopy(Util.renderer, explode, NULL, &dexplode);
        }
        SDL_RenderPresent(Util.renderer);
        for(int i=0;i<10;i++)
        {
            score += 10;
            string text = to_string(score);
            SDL_DestroyTexture(scorenum);
            if(score < 1000){
                if(score==0) scorenum=Util.Text(text, blockW*12+105, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
                else scorenum=Util.Text(text, blockW*12+83, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
            }
            else if(score < 10000){
                scorenum=Util.Text(text, blockW*12+70, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
        }
        else
        {
            scorenum=Util.Text(text, blockW*12+57, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
        }
            updateexplode();
            SDL_Delay(10);
        }
        for(int j = 0; j < col; j++)
        {
                tetromino(dexplode, j*blockW, n*blockH,blockW,blockH);
                updateField(dexplode, blockW, SCREEN_HEIGHT - (line + 2)*blockH);
                SDL_RenderCopy(Util.renderer, explode, NULL, &dexplode);
        }
        SDL_RenderPresent(Util.renderer);
        SDL_Delay(80);
        for(int j = 0; j < col; j++)
        {
                tetromino(dexplode, j*blockW, n*blockH,blockW+10,blockH+10);
                updateField(dexplode, blockW-5, SCREEN_HEIGHT - (line + 2)*blockH-5);
                SDL_RenderCopy(Util.renderer, explode, NULL, &dexplode);
        }
        SDL_RenderPresent(Util.renderer);
        SDL_Delay(80);
}
void Tetris::renderstartgame()
{
    Util.pause();
    SDL_RenderClear(Util.renderer);
        SDL_RenderCopy(Util.renderer, background, NULL, NULL);
        SDL_RenderCopy(Util.renderer, gamebg, &sRectbg, &dRectbg);
        SDL_RenderCopy(Util.renderer, border1, &sRectbd1, &dRectbd1);
        SDL_RenderCopy(Util.renderer, border1, &sRectbd1, &dRectbd1f);
        SDL_RenderCopy(Util.renderer, border, &sRectbd, &dRectbdf);
        SDL_RenderCopy(Util.renderer, score1, NULL, &dRectscore);
        SDL_RenderCopy(Util.renderer, high, &sRecthigh, &dRecthigh);
        SDL_RenderCopy(Util.renderer, scoretex, NULL, &dRects1);
        SDL_RenderCopy(Util.renderer, hightex, NULL, &dRecths1);
        SDL_RenderCopy(Util.renderer,music,&sRectmu,&dRectmu);
        SDL_RenderCopy(Util.renderer,pauseb,NULL,&dpause);
        //dispender
    for(int i=0;i<10;i++)
    {
        SDL_Rect dRectdis={blockW*(1+i),SCREEN_HEIGHT - (line + 2)*blockH,blockW,blockH};
        SDL_RenderCopy(Util.renderer, dispender, NULL, &dRectdis);
    }
        SDL_RenderCopy(Util.renderer,pausebg,NULL,NULL);
        SDL_RenderCopy(Util.renderer,pausebg,NULL,NULL);
        SDL_RenderCopy(Util.renderer,pausebg,NULL,NULL);
        SDL_RenderCopy(Util.renderer, next, &sRectnext, &dRectnext);
            //Tao block xem truoc
    for(int i = 0; i < 4; i++)
    {
        int nx,ny;
        switch(color[1])
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
        tetromino(dRect, temp[1][i].x *53, temp[1][i].y*55,blockW+15,blockH+15);
        updateField(dRect, blockW*12+11, blockH*19+4);
        SDL_RenderCopy(Util.renderer, block, &sRect, &dRect);
    }
        SDL_DestroyTexture(scorenum);
        scorenum=Util.Text("Go!!!",230,290,Util.renderer,"res/font/font.ttf",{255,255,255},130,dRects);
        SDL_RenderPresent(Util.renderer);
        SDL_Delay(600);
        Util.effectAudio("res/audio/music/go.wav",100);
        SDL_Delay(100);
        SDL_RenderCopy(Util.renderer,scorenum,NULL,&dRects);
        SDL_RenderPresent(Util.renderer);
        SDL_Delay(700);
    if(Checkmouse[switchmusic]==0) Util.resume();
    SDL_DestroyTexture(scorenum);
    scorenum=Util.Text(to_string(score), blockW*12+105, blockH*3+80, Util.renderer, "res/font/font.ttf",{ 255, 255, 255 },50,dRects);
    Tetrimino *p=ter[0];
                ter[0]=ter[1];
                delete p;
            nextTetromino();
            updatetemp();
}
void Tetris::updateexplode()
{
    SDL_RenderClear(Util.renderer);
    SDL_RenderCopy(Util.renderer, background, NULL, NULL);
    SDL_RenderCopy(Util.renderer, gamebg, &sRectbg, &dRectbg);
    SDL_RenderCopy(Util.renderer, border1, &sRectbd1, &dRectbd1);
    SDL_RenderCopy(Util.renderer, border1, &sRectbd1, &dRectbd1f);
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
    // va cham vs day ( luu hinh anh cuoi cung khi o day - bao gom ca mau sac)
    for(int i = 0; i < line+1; i++)
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
                updateField(dRect, blockW, SCREEN_HEIGHT - (line + 2)*blockH);
                SDL_RenderCopy(Util.renderer, block, &sRect, &dRect);
            }
        }
    }
    //dispender
    for(int i=0;i<10;i++)
    {
        SDL_Rect dRectdis={blockW*(1+i),SCREEN_HEIGHT - (line +2)*blockH,blockW,blockH};
        SDL_RenderCopy(Util.renderer, dispender, NULL, &dRectdis);
    }
    //Tao block xem truoc
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
        tetromino(dRect, backup[i].x *53, backup[i].y*55,blockW+15,blockH+15);
        updateField(dRect, blockW*12+11, blockH*19+4);
        SDL_RenderCopy(Util.renderer, block, &sRect, &dRect);
    }
    SDL_RenderPresent(Util.renderer);
}