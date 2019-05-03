#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

bool init(SDL_Window* &Window, SDL_Renderer* &Renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

SDL_Texture* loadTexture( std::string path , SDL_Renderer* &renderer);
