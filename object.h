#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

class car
{
public:
    int xPos;
    int yPos;

    car();
    void appear(SDL_Rect &carRect, SDL_Texture* &carTexture, SDL_Renderer* &carRenderer);
    void appearReverse(SDL_Rect &carRect, SDL_Texture* &carTexture, SDL_Renderer* &carRenderer);
    void appearInvisible(SDL_Rect &carRect, SDL_Texture* &carTexture, SDL_Renderer* &carRenderer);
    void control(SDL_Event& e, bool& quit);
    void controlReverse(SDL_Event& e, bool& quit);
    void controlCloser(SDL_Event& e, bool& quit);
    void moveLeft();
    void moveRight();
};

class enemycar
{
public:
    int xPos;
    int yPos;

    enemycar(int _xPos, int _yPos);
    void appear(SDL_Rect &ecarRect, SDL_Texture* &ecarTexture, SDL_Renderer* &ecarRenderer, int &score, int &loop, int &speed, Mix_Chunk* &challengeS );
    void move(int &speed);
};


