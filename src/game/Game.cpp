#include <iostream>
#include "Game.hpp"

void display_ball_dir(Ball *ball) {
    std::cout << "ball-dir-x: " << ball->dir.x << std::endl;
    // std::cout << "ball-dir-y: " << ball->dir.y << std::endl;
}

template <typename T>
void display_object_pos(T *object, bool x, bool y) {
    if(x) std::cout << "object-pos-X: " << object->pos.x << std::endl;
    if(y) std::cout << "object-pos-Y: " << object->pos.y << std::endl;
}


Game::Game(){
    m_game_over = false;
    m_ticks_count = 0;

    m_pad.pos.y = WINDOW_CENTER_Y - PADD_CENTER;
    m_pad2.pos.y = WINDOW_CENTER_Y - PADD_CENTER;

    m_ball.pos.x = WINDOW_CENTER_X - BALL_CENTER;
    m_ball.pos.y = WINDOW_CENTER_Y - BALL_CENTER;
    m_ball.dir.x = 1; m_ball.dir.y = 0.5f;

    std::cout << "ball x: " << m_ball.dir.x << std::endl;
    std::cout << "ball y: " << m_ball.dir.y << std::endl;
}

void Game::ProcessInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        switch(event.type){
            // handle events

            case SDL_QUIT:
                m_isRunning = false;
                break;
        }
    }

    const Uint8 *kb_state = SDL_GetKeyboardState(NULL);
    if(kb_state[SDL_SCANCODE_ESCAPE]) m_isRunning = false;

    m_pad.dir = 0;
    if(kb_state[SDL_SCANCODE_W]) m_pad.dir -= 1;
    if(kb_state[SDL_SCANCODE_S]) m_pad.dir += 1;

    m_pad2.dir = 0;
    if(kb_state[SDL_SCANCODE_K]) m_pad2.dir -= 1;
    if(kb_state[SDL_SCANCODE_J]) m_pad2.dir += 1;


    if(kb_state[SDL_SCANCODE_Q]) {m_game_over = true; Game::Game_Restart();}
    if(kb_state[SDL_SCANCODE_SPACE]) m_game_over = false; 

};

void Game::UpdateGame() {
    
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks_count + 16)); // wait 16ms

    float deltaTime = (SDL_GetTicks() - m_ticks_count) / 1000.0f;
    m_ticks_count = SDL_GetTicks();

    if(deltaTime > 0.05f) deltaTime = 0.05f;

    // Update Game objects
    // m_ball_pos.x += 1;

    if(m_pad.dir != 0) {
        float y = m_pad.pos.y + m_pad.dir * PADD_SPEED * deltaTime;
        if(y <= 0 || y >= WINDOW_H - PADD_H) {
            std::cout << "reached limit -> y: " << (int)m_pad.pos.y << std::endl;
            m_pad.dir = 0;
        }
        m_pad.pos.y += m_pad.dir * PADD_SPEED * deltaTime;
        
    }

    if(m_pad2.dir != 0) {
        float y = m_pad2.pos.y + m_pad2.dir * PADD_SPEED * deltaTime;
        if(y <= 0 || y >= WINDOW_H - PADD_H) {
            std::cout << "reached limit -> y: " << (int)m_pad2.pos.y << std::endl;
            m_pad2.dir = 0;
        }
        m_pad2.pos.y += m_pad2.dir * PADD_SPEED * deltaTime;
        
    }
    
    if (m_ball.dir.x != 0 && m_ball.dir.y != 0) {
        float x = m_ball.pos.x + m_ball.dir.x * BALL_SPEED * deltaTime;
        float y = m_ball.pos.y + m_ball.dir.y * BALL_SPEED * deltaTime;

        int diff = m_ball.pos.y - m_pad.pos.y;
        int diff2 = m_ball.pos.y - m_pad2.pos.y;

        if (y <= 0) {
            std::cout << "[BALL]: reached top wall" << std::endl;
            m_ball.dir.y = 1;
            // display_ball_dir(&m_ball);
        }

        if ( y >= WINDOW_H - BALL_H) {
            std::cout << "[BALL]: reached bottom wall" << std::endl;
            m_ball.dir.y = -1;
            // display_ball_dir(&m_ball);
        }

        if (x <= 0) { 
            std::cout << "[BALL]: reached left wall" << std::endl;
            // m_ball.dir.x = 1;
            // display_ball_dir(&m_ball);
            std::cout << "[LEFT PLAYER] >> game over bro" << std::endl;
            m_game_over = true;
        }

        if (x >= WINDOW_W - BALL_W) {
            std::cout << "[BALL] reached right wall" << std::endl;
            // m_ball.dir.x = -1;

            std::cout << "[RIGHT PLAYER] >> game over bro" << std::endl;
            m_game_over = true;
            // display_ball_dir(&m_ball);
        }


        // BALL HIT THE LEFT PADD
        if (m_ball.pos.x >= 20.0f && m_ball.pos.x <= 25.0f &&
            m_ball.pos.y >= m_pad.pos.y && m_ball.pos.y <= m_pad.pos.y + PADD_H
        ) {   // range between 20 and25 bc the frames

            m_ball.dir.x = 1;

            if (m_ball.pos.y == PADD_CENTER) m_ball.dir.y -= 0.2f;
            if ((m_ball.pos.y >= m_pad.pos.y && 
                    m_ball.pos.y <= PADD_CENTER / 2) ||
                (m_ball.pos.y >= PADD_CENTER / 2 &&
                 m_ball.pos.y <= m_pad.pos.y + PADD_H)) {
                
                m_ball.dir.y == 1 ? -1 : 1;
                std::cout << "[BALL] touched a corner" << std::endl;
            }


            display_object_pos(&m_ball, true, false);

        } 


        // BALL HIT RIGHT PADD
        if (m_ball.pos.x <= WINDOW_W - 20.0f && m_ball.pos.x >= WINDOW_W - 25.0f &&
            m_ball.pos.y >= m_pad2.pos.y && m_ball.pos.y <= m_pad2.pos.y + PADD_H
        ) {  

            m_ball.dir.x = -1;

            if (m_ball.pos.y == PADD_CENTER) m_ball.dir.y -= 0.2f;
            if ((m_ball.pos.y >= m_pad2.pos.y && 
                    m_ball.pos.y <= PADD_CENTER / 2) ||
                (m_ball.pos.y >= PADD_CENTER / 2 &&
                 m_ball.pos.y <= m_pad2.pos.y + PADD_H)) {
                
                m_ball.dir.y == 1 ? -1 : 1;
            }

            if (m_ball.pos.y == PADD_CENTER) m_ball.dir.y -= 0.5f;

            display_object_pos(&m_ball, true, false);

        }   
        
    }

    

    m_ball.pos.x += m_ball.dir.x * BALL_SPEED * deltaTime;
    m_ball.pos.y += m_ball.dir.y * BALL_SPEED * deltaTime;
};

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(
        m_renderer,
        50,      // R
        10,      // G 
        255,     // B
        255      // A
    );
    SDL_RenderClear(m_renderer);

    SDL_Rect padd1 = {
        PADD_PADING,
        static_cast<int>(m_pad.pos.y),
        PADD_W,
        PADD_H
    };

    SDL_Rect padd2 = {
        WINDOW_W - PADD_PADING - PADD_W,
        static_cast<int>(m_pad2.pos.y),
        PADD_W,
        PADD_H
    };

    SDL_Rect ball {
        static_cast<int>(m_ball.pos.x),
        static_cast<int>(m_ball.pos.y),
        BALL_W,
        BALL_H
    };


    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &padd1);
    SDL_RenderFillRect(m_renderer, &padd2);
    SDL_RenderFillRect(m_renderer, &ball);

    SDL_RenderPresent(m_renderer); // swap buffers
}

bool Game::Game_Init() {
    if(SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow(
        "Hello, Matrix",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_W,
        WINDOW_H,
        SDL_WINDOW_RESIZABLE
    );

    if(!m_window) {
        SDL_Log("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if(!m_renderer) {
        SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

}

void Game::Game_RunLoop() {
    while(m_isRunning) {
        ProcessInput();
        if(!m_game_over) UpdateGame();
        GenerateOutput();
    }
}

void Game::Game_Shutdown() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

void Game::Game_Restart() {
    m_pad.pos.y = WINDOW_CENTER_Y - PADD_CENTER;
    m_pad2.pos.y = WINDOW_CENTER_Y - PADD_CENTER;

    m_ball.pos.x = WINDOW_CENTER_X - BALL_CENTER;
    m_ball.pos.y = WINDOW_CENTER_Y - BALL_CENTER;
    m_ball.dir.x = 1; m_ball.dir.y = 0.5f;
}
