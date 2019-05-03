#include "init.h"
#include "object.h"

using namespace std;

car::car()
    {
        xPos = 25;
        yPos = 480;
    }

void car::appear(SDL_Rect &carRect, SDL_Texture* &carTexture, SDL_Renderer* &carRenderer)
    {
        carTexture = loadTexture("car1.png", carRenderer);
        carRect.x = xPos;
        carRect.y = yPos;
        carRect.h = 70;
        carRect.w = 80;
        SDL_RenderCopy(carRenderer, carTexture, NULL, &carRect);
    }
void car::appearReverse(SDL_Rect &carRect, SDL_Texture* &carTexture, SDL_Renderer* &carRenderer)
    {
        carTexture = loadTexture("reversecar1.png", carRenderer);
        carRect.x = xPos;
        carRect.y = yPos;
        carRect.h = 70;
        carRect.w = 80;
        SDL_RenderCopy(carRenderer, carTexture, NULL, &carRect);
    }
void car::appearInvisible(SDL_Rect &carRect, SDL_Texture* &carTexture, SDL_Renderer* &carRenderer)
    {
        carTexture = loadTexture("invisiblecar1.png", carRenderer);
        carRect.x = xPos;
        carRect.y = yPos;
        carRect.h = 70;
        carRect.w = 80;
        SDL_RenderCopy(carRenderer, carTexture, NULL, &carRect);
    }
void car::control(SDL_Event& e, bool& quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_LEFT:
                                moveLeft();
                                break;
							case SDLK_RIGHT:
                                moveRight();
                                break;
                        }
                    }
				}
    }
void car::controlReverse(SDL_Event& e, bool& quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_LEFT:
                                moveRight();
                                break;
							case SDLK_RIGHT:
                                moveLeft();
                                break;
                        }
                    }
				}
    }
void car::controlCloser(SDL_Event& e, bool& quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_LEFT:
                                xPos = ( (xPos-130) < 25 )? 25: (xPos-130);
                                yPos = 340;
                                break;
							case SDLK_RIGHT:
                                xPos = ( (xPos+130) > 285 )? 285: (xPos+130);
                                yPos = 340;
                                break;
                        }
                    }
				}
    }
void car::moveLeft()
    {
        xPos = ( (xPos-130) < 25 )? 25: (xPos-130);
        yPos = 480;
    }
void car::moveRight()
    {
        xPos = ((xPos+130) > 285)? 285: (xPos+130);
        yPos = 480;
    }

enemycar::enemycar(int _xPos, int _yPos)
    {
        xPos = _xPos;
        yPos = _yPos;
    }
void enemycar::appear(SDL_Rect &ecarRect, SDL_Texture* &ecarTexture, SDL_Renderer* &ecarRenderer, int &score, int &loop, int &speed, Mix_Chunk* &challengeS)
    {
        if(yPos >= 580){
            int randomPos = rand()%3;
            if(randomPos==0){
                xPos = 25;
            }
            else if(randomPos==1)
            {
                xPos = 25+130;
            }
            else{
                xPos = 25+130+130;
            }
            score++;
            if(score % 5 == 0){
                speed++;
            }
            if(score==(10*loop) || score == 10*(loop+2) || score == 10*(loop+4)){
                Mix_PlayChannel(-1, challengeS, 0);
            }
            if(score & 60 == 0){
                loop = loop+6;
            }
            yPos = -80;
        }
        ecarRect.x = xPos;
        ecarRect.y = yPos;
        ecarRect.h = 70;
        ecarRect.w = 80;
        SDL_RenderCopy(ecarRenderer, ecarTexture, NULL, &ecarRect);
    }
void enemycar::move(int &speed)
    {
        yPos=yPos+speed;
    }

