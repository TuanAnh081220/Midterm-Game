int score = 0;
int loop = 1;
int speed = 10;
int currentScore;
int highscore;

bool gameRunning = true;
bool playingGame = false;
bool home = false;
bool donate = false;
bool rule = false;

const int SCREEN_WIDTH = 390;
const int SCREEN_HEIGHT = 580;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;
SDL_Texture* Texture = NULL;
SDL_Texture* Surface = NULL;
SDL_Texture* homeTexture = NULL;
SDL_Texture* gameoverTexture = NULL;
SDL_Texture* ruleTexture = NULL;
SDL_Texture* donateTexture = NULL;

SDL_Texture* road = NULL;
SDL_Texture* mycarTexture = NULL;
SDL_Texture* ecar1Texture = NULL;
SDL_Texture* ecar2Texture = NULL;
SDL_Texture* blues = NULL;

SDL_Rect roadRect;
SDL_Rect mycarRect;
SDL_Rect ecar1Rect;
SDL_Rect ecar2Rect;

TTF_Font* Font = NULL;
SDL_Surface* FontSurface = NULL;
SDL_Texture* FontTexture = NULL;
SDL_Rect FontRect;

Mix_Music* backgroundMusic = NULL;
Mix_Music* playgameMusic = NULL;
Mix_Chunk* soundEffect = NULL;
Mix_Chunk* scoreSound = NULL;
Mix_Chunk* accidentSound = NULL;
Mix_Chunk* challengeSound = NULL;

