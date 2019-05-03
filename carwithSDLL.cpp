#include "init.h"
#include "object.h"
#include "variable.h"


using namespace std;

void loadMedia();

void playGame();
void showHome();
void showGameover();
void showRule();
void showDonate();

void chooseFromGameover();
void chooseFromRule();
void chooseFromDonate();
void chooseFromHome();
void close();

int main(int argc, char* args[])
{
    ifstream high_score_in;
    high_score_in.open("highscore.txt");
    while(high_score_in >> highscore) {}
    high_score_in.close();
    ofstream high_score_out;
    high_score_out.open("highscore.txt");

    if(!init(Window, Renderer, SCREEN_WIDTH, SCREEN_HEIGHT)){
        cout << "Fail to init" << endl;
    }
    else{
        srand(time(0));

        loadMedia();

        while( gameRunning ){
            showHome();
            chooseFromHome();
                if( rule == true ){
                    showRule();
                    chooseFromRule();
                        if( home == true ){
                            rule = false;
                            continue;
                        }
                }
                if( donate == true ){
                    showDonate();
                    chooseFromDonate();
                        if( home == true ){
                            donate = false;
                            continue;
                        }
                }
            while( playingGame ){
                playGame();
                showGameover();
                chooseFromGameover();
            }
        }
    }
    high_score_out << highscore << endl;
    high_score_out.close();

    close();

    return 0;
}

void loadMedia()
{
    soundEffect = Mix_LoadWAV("door_lock.wav");
    scoreSound = Mix_LoadWAV("sfx_point.wav");
    accidentSound = Mix_LoadWAV("soundAccident.wav");
    playgameMusic = Mix_LoadMUS("playgameMusic.wav");
    challengeSound = Mix_LoadWAV("challenge.wav");
    backgroundMusic = Mix_LoadMUS("backgroundMusic.wav");
    Font = TTF_OpenFont("design.graffiti.snap____.ttf", 100);
    homeTexture = loadTexture("home.png", Renderer);
    gameoverTexture = loadTexture("gameover.png", Renderer);
    ruleTexture = loadTexture("rules.png", Renderer);
    donateTexture = loadTexture("donate.png", Renderer );
    road = loadTexture("road2.png", Renderer);
    blues = loadTexture("material.png", Renderer);
}

void showHome()
{
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, homeTexture, NULL, NULL);
    SDL_RenderPresent(Renderer);
    Mix_PlayMusic(backgroundMusic, -1);
}
void showGameover()
{
    SDL_Color textColor = {237, 28, 36};
    SDL_Rect* yourscoreRect = new SDL_Rect;
    yourscoreRect->x = 260;
    yourscoreRect->y = 180;
    yourscoreRect->h = 60;
    yourscoreRect->w = 40;

    string stryourScore = to_string(currentScore);
    SDL_Surface* yourscoreSurface = TTF_RenderText_Solid(Font, stryourScore.c_str(), textColor);
    SDL_Texture* yourscoreTexture = SDL_CreateTextureFromSurface(Renderer, yourscoreSurface);
    SDL_FreeSurface(yourscoreSurface);

    SDL_RenderCopy(Renderer, yourscoreTexture, NULL, yourscoreRect);

    textColor = {255, 242, 0};
    SDL_Rect* highscoreRect = new SDL_Rect;
    highscoreRect->x = 260;
    highscoreRect->y = 260;
    highscoreRect->h = 60;
    highscoreRect->w = 40;

    string strhighscore = to_string(highscore);
    SDL_Surface* highscoreSurface = TTF_RenderText_Solid(Font, strhighscore.c_str(), textColor);
    SDL_Texture* highscoreTexture= SDL_CreateTextureFromSurface(Renderer, highscoreSurface);
    SDL_FreeSurface(highscoreSurface);

    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, gameoverTexture, NULL, NULL);
    SDL_RenderCopy(Renderer, yourscoreTexture, NULL, yourscoreRect);
    SDL_RenderCopy(Renderer, highscoreTexture, NULL, highscoreRect);
    SDL_RenderPresent(Renderer);

    delete(yourscoreRect);
    delete(highscoreRect);
}
void showRule()
{
    SDL_RenderClear(Renderer);
    SDL_RenderCopy(Renderer, ruleTexture, NULL, NULL);
    SDL_RenderPresent(Renderer);
}
void showDonate()
{
    SDL_RenderClear( Renderer );
    SDL_RenderCopy(Renderer, donateTexture, NULL, NULL);
    SDL_RenderPresent(Renderer);
}

void checkCollusion(car& x, enemycar& y, enemycar& z, bool& check)
{
    if((x.xPos == y.xPos && abs(x.yPos - y.yPos) <= 40) || (x.xPos == z.xPos && abs(x.yPos - z.yPos) <= 40) )
    {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, accidentSound, 0);
        SDL_Delay(10);
        check = true;
        currentScore = score;
        highscore = (highscore > currentScore)? highscore : currentScore;
        score = 0;
        speed = 10;
    }
    else
    {
        check = false;
    }
}

void playGame()
{
        Mix_PlayMusic(playgameMusic, -1);

        SDL_RenderClear( Renderer );
        SDL_RenderCopy( Renderer, road, NULL, NULL );

        car mycar = car();
        //mycarTexture = loadTexture("car1.png", Renderer);
        enemycar ecar1 = enemycar(25, -80);
        ecar1Texture = loadTexture("car2rotate.png", Renderer);
        enemycar ecar2 = enemycar(155, -370);
        ecar2Texture = loadTexture("car2rotate.png", Renderer);

        SDL_Color textColor = {255, 255, 255};
        FontRect.x = 170;
        FontRect.y = 10;
        FontRect.h = 100;
        FontRect.w = 50;

        bool quit = false;
        SDL_Event e;
        string strScore;

        while(!quit){

        int start = SDL_GetTicks();

        SDL_RenderCopy(Renderer, blues, NULL, &FontRect);
        SDL_RenderCopy(Renderer, blues, NULL, &mycarRect);
        SDL_RenderCopy(Renderer, blues, NULL, &ecar1Rect);
        SDL_RenderCopy(Renderer, blues, NULL, &ecar2Rect);

        strScore = to_string(score);
        FontSurface = TTF_RenderText_Solid(Font, strScore.c_str(), textColor);
        FontTexture = SDL_CreateTextureFromSurface(Renderer, FontSurface);
        SDL_FreeSurface(FontSurface);
        SDL_RenderCopy(Renderer, FontTexture, NULL, &FontRect);

        if(score>=(10*loop) && score<=(10*loop+9))
            {
                mycar.controlReverse(e, quit);
                mycar.appearReverse(mycarRect, mycarTexture, Renderer);
            }
        else if(score>=10*(loop+2) && score<=(10*(loop+2)+9))
            {
                mycar.control(e, quit);
                mycar.appearInvisible(mycarRect, mycarTexture, Renderer);
            }
        else if(score>=10*(loop+4) && score<=(10*(loop+4)+9))
            {
                mycar.controlCloser(e, quit);
                mycar.appear(mycarRect, mycarTexture, Renderer);
            }
        else{
                mycar.control(e, quit);
                mycar.appear(mycarRect, mycarTexture, Renderer);
            }

            ecar1.appear(ecar1Rect, ecar1Texture, Renderer, score, loop, speed, challengeSound);
            ecar1.move(speed);

            ecar2.appear(ecar2Rect, ecar2Texture, Renderer, score, loop, speed, challengeSound);
            ecar2.move(speed);

            checkCollusion(mycar, ecar1, ecar2, quit);

            SDL_RenderPresent(Renderer);

            int theend = SDL_GetTicks();
            int delay = 1000 / 60 - (theend - start);
            SDL_Delay(delay > 0 ? delay : 0);
    }
}
void chooseFromHome()
{
    SDL_Event eHome;
    bool quitHome = false;
    while(!quitHome){
        if(SDL_WaitEvent(&eHome) == 0){
            continue;
        }
        if(eHome.type == SDL_QUIT){
            gameRunning = false;
            playingGame = false;
            quitHome = true;
        }
        if(eHome.type == SDL_MOUSEBUTTONDOWN){
            if(eHome.button.button == SDL_BUTTON_LEFT){
                if(eHome.button.x >=160 && eHome.button.x<=280 && eHome.button.y >= 320 && eHome.button.y <=345)
                {
                    Mix_HaltMusic();
                    Mix_PlayChannel(-1, soundEffect, 0);
                    playingGame = true;
                    quitHome = true;
                }
                else if(eHome.button.x >= 160 && eHome.button.x <= 280 && eHome.button.y >= 370 && eHome.button.y <= 395)
                {
                    Mix_PlayChannel(-1, soundEffect, 0);
                    rule = true;
                    quitHome = true;
                }
                else if(eHome.button.x >= 160 && eHome.button.x <= 300 && eHome.button.y >= 420 && eHome.button.y <= 445)
                {
                    Mix_PlayChannel(-1, soundEffect, 0);
                    donate = true;
                    quitHome = true;
                }
            }
        }
    }
}
void chooseFromGameover()
{
    SDL_Event eOver;
    bool quitOver = false;
    while(!quitOver){
        SDL_Delay(10);
        if(SDL_WaitEvent(&eOver) == 0){
            continue;
        }
        if(eOver.type == SDL_QUIT){
            gameRunning = false;
            playingGame = false;
            quitOver = true;
        }
        if(eOver.type == SDL_MOUSEBUTTONDOWN){
            if (eOver.button.button == SDL_BUTTON_LEFT){
                if(eOver.button.x >= 140 && eOver.button.y >= 400 && eOver.button.x <= 310 && eOver.button.y <=430 ){
                    Mix_HaltMusic();
                    Mix_PlayChannel(-1, soundEffect, 0);
                    playingGame = true;
                    quitOver = true;
                }
                if(eOver.button.x >= 140 && eOver.button.y >= 444 && eOver.button.x <= 270 && eOver.button.y <=470){
                    Mix_HaltMusic();
                    playingGame = false;
                    gameRunning = false;
                    quitOver = true;
                }
                if(eOver.button.x >= 140 && eOver.button.y >= 480 && eOver.button.x <= 250 && eOver.button.y <=510){
                    Mix_HaltMusic();
                    Mix_PlayChannel(-1, soundEffect, 0);
                    playingGame = false;
                    gameRunning = true;
                    home = true;
                    quitOver = true;
                }
            }
        }
    }
}

void chooseFromRule()
{
    SDL_Event eRule;
    bool quitRule= false;
    while(!quitRule){
        SDL_Delay(10);
        if(SDL_WaitEvent(&eRule) == 0){
            continue;
        }
        if(eRule.type == SDL_QUIT){
            gameRunning = false;
            playingGame = false;
            quitRule = true;
        }
        if(eRule.type == SDL_MOUSEBUTTONDOWN){
            if (eRule.button.button == SDL_BUTTON_LEFT){
                if(eRule.button.x >= 140 && eRule.button.y >= 460 && eRule.button.x <= 260 && eRule.button.y <=490 ){
                    Mix_HaltMusic();
                    Mix_PlayChannel(-1, soundEffect, 0);
                    home = false;
                    playingGame = true;
                    quitRule = true;
                }
                if(eRule.button.x >= 140 && eRule.button.y >= 500 && eRule.button.x <= 260 && eRule.button.y <=530 ){
                    Mix_PlayChannel(-1, soundEffect, 0);
                    quitRule = true;
                }
            }
        }
    }
}

void chooseFromDonate()
{
    SDL_Event eDonate;
    bool quitDonate= false;
    while(!quitDonate){
        SDL_Delay(10);
        if(SDL_WaitEvent(&eDonate) == 0){
            continue;
        }
        if(eDonate.type == SDL_QUIT){
            gameRunning = false;
            playingGame = false;
            quitDonate = true;
        }
        if(eDonate.type == SDL_MOUSEBUTTONDOWN){
            if (eDonate.button.button == SDL_BUTTON_LEFT){
                if(eDonate.button.x >= 150 && eDonate.button.y >= 460 && eDonate.button.x <= 280 && eDonate.button.y <=495 ){
                    Mix_HaltMusic();
                    Mix_PlayChannel(-1, soundEffect, 0);
                    playingGame = true;
                    home = false;
                    quitDonate = true;
                }
                if(eDonate.button.x >= 150 && eDonate.button.y >= 480 && eDonate.button.x <= 280 && eDonate.button.y <=540){
                    Mix_PlayChannel(-1, soundEffect, 0);
                    quitDonate = true;
                }
            }
        }
    }
}

void close()
{
    SDL_DestroyTexture(homeTexture);
	SDL_DestroyTexture(gameoverTexture);
	SDL_DestroyTexture(ruleTexture);
	SDL_DestroyTexture(donateTexture);
	SDL_DestroyTexture(road);
	SDL_DestroyTexture(mycarTexture);
	SDL_DestroyTexture(ecar1Texture);
	SDL_DestroyTexture(ecar2Texture);
	SDL_DestroyTexture(blues);
	SDL_DestroyTexture(FontTexture);

	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow( Window );

	Mix_FreeChunk(soundEffect);
	Mix_FreeChunk(scoreSound);
	Mix_FreeChunk(accidentSound);
	Mix_FreeChunk(challengeSound);

	Mix_FreeMusic(backgroundMusic);
	Mix_FreeMusic(playgameMusic);

	IMG_Quit();
	SDL_Quit();
}


