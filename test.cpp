bool Tetris::menu()
{
    SDL_RenderClear(Util.renderer);
    SDL_Event e;
    backgroundMenu = Util.loadTexture("res/demo image/bgf.jpg", Util.renderer);
    play = Util.loadTexture("res/demo image/play.png", Util.renderer);
    // play_light = Util.loadTexture("res/demo image/play_light.png", Util.renderer);
    lv1 = Util.loadTexture("res/demo image/level_1.png", Util.renderer);
    lv2 = Util.loadTexture("res/demo image/level_2.png", Util.renderer);
    lv3 = Util.loadTexture("res/demo image/level_3.png", Util.renderer);
    // lv1_light = Util.loadTexture("res/demo image/level_1_light.png", Util.renderer);
    // lv2_light = Util.loadTexture("res/demo image/level_2_light.png", Util.renderer);
    // lv3_light = Util.loadTexture("res/demo image/level_3_light.png", Util.renderer);
    const int playRect_x = 250;
    const int playRect_y = 260;
    const int levelRect_x = 300;
    const int levelRect_y = 350;
    SDL_Rect playRect = {playRect_x, playRect_y, 94, 53};
    SDL_Rect levelRect = {levelRect_x, levelRect_y, 174, 53};
    SDL_RenderCopy(Util.renderer, backgroundMenu, NULL, NULL);
    SDL_RenderCopy(Util.renderer, play, NULL, &playRect);
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
    int x = 0;
    int y = 0;
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            return false;
        }
        else if(e.type == SDL_MOUSEMOTION)
        {
            x = e.motion.x;
            y = e.motion.y;
            if(selectRect(playRect, x, y))
            {
                SDL_RenderCopy(Util.renderer, play_light, NULL, &playRect);
                // Util.effectAudio("res/audio/music/hardDrop.wav");
            }
        }
        //     else if(selectRect(levelRect, x, y))
        //     {
        //         if(level == 1)
        //         {
        //             SDL_RenderCopy(Util.renderer, lv1_light, NULL, &levelRect);
        //             Util.effectAudio("res/audio/music/hardDrop.wav");
        //         }
        //         else if(level == 2)
        //         {
        //             SDL_RenderCopy(Util.renderer, lv2_light, NULL, &levelRect);
        //             Util.effectAudio("res/audio/music/hardDrop.wav");
        //         }
        //         else if(level == 3)
        //         {
        //             SDL_RenderCopy(Util.renderer, lv3_light, NULL, &levelRect);
        //             Util.effectAudio("res/audio/music/hardDrop.wav");
        //         }

        //     }
        // }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            x = e.button.x;
            y = e.button.y;
            if(selectRect(playRect, x, y))
            {
                Util.effectAudio("res/audio/music/hardDrop.wav");
                running = true;
            }
            else if(selectRect(levelRect, x, y))
            {
                Util.effectAudio("res/audio/music/hardDrop.wav");
                if(level == 1)
                    level++;
                else if(level == 2)
                    level++;
                else if(level == 3)
                    level -= 2;
            }
        }
        }

    }
    SDL_RenderPresent(Util.renderer);
    return true;
}
