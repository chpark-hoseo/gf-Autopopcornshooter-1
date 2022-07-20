#ifndef _GAME_
#define _GAME_

#include "main.h"

class Game {
public:
    Game() {}
    ~Game() {}

    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void render();
    void update();
    bool running();
    void handleEvents();
    void clean();

private:
    SDL_Texture* m_pTexture;
    SDL_Rect m_sourceRectangle;
    SDL_Rect m_destinationRectangle;
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    float m_wWidth;
    float m_wHeight;
    bool m_bRunning;
   
};
#endif // ! _GAME_