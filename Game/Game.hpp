#ifndef GAME_H
#define GAME_H 

#include <SDL2/SDL.h>

#define BALL_H 12
#define BALL_W 12
#define BALL_CENTER (BALL_H / 2)
#define BALL_SPEED 300.0f

#define PADD_H 80
#define PADD_W 12
#define PADD_CENTER (PADD_H / 2)
#define PADD_PADING 10
#define PADD_SPEED 500.0f

#define WINDOW_W 800
#define WINDOW_H 768
#define WINDOW_CENTER_X (WINDOW_W / 2)
#define WINDOW_CENTER_Y (WINDOW_H / 2)

template <typename T>
struct Vector2 {
    T x;
    T y;
};

struct Pad {
    int dir;
    Vector2<float> pos;
};

struct Ball {
Vector2<float> dir;
    Vector2<float> pos;
};


class Game {

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    bool m_game_over;
    bool m_isRunning;

    Uint32 m_ticks_count;

    Pad m_pad;
    Pad m_pad2;
    Ball m_ball;

    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

public:
    Game();

    bool Game_Init();
    void Game_RunLoop();
    void Game_Shutdown();

    void Game_Restart();
};

#endif // GAME_H
