#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_pWindow != 0) // window init success
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if (m_pRenderer != 0) // renderer init success
            {
                m_player = new Player();
                m_enemy1 = new Enemy();
                m_enemy2 = new Enemy();
                m_enemy3 = new Enemy();

                if (!TheTextureManager::Instance()->load("./Images/background.bmp", "background", m_pRenderer))
                    return false;

                if (!TheTextureManager::Instance()->load("./Images/pixil-frame-0.png", "hinchaT", m_pRenderer))
                    return false;

                if (!TheTextureManager::Instance()->load("./Images/pixil-frame-1.png", "hinchaPirata", m_pRenderer))
                    return false;

                m_player->load(((width / 2) - 50), 50, 100, 100, "hinchaT");
                m_enemy1->load(50, 600, 100, 100, "hinchaPirata");
                m_enemy2->load(125, 480, 100, 100, "hinchaPirata");
                m_enemy3->load(200, 360, 100, 100, "hinchaPirata");

                m_gameObjects.push_back(m_player);
                m_gameObjects.push_back(m_enemy1);
                m_gameObjects.push_back(m_enemy2);
                m_gameObjects.push_back(m_enemy3);
            }
            else
            {
                std::cout << "renderer init fail\n";
                return false; // renderer init fail
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false; // window init fail
        }
    }
    else
    {
        std::cout << "SDL init fail\n";
        return false; // SDL init fail
    }
    std::cout << "init success\n";
    m_bRunning = true; // everything inited successfully, start the main loop
    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    TextureManager::Instance()->draw("background", 0, 0, 720, 720, m_pRenderer);

    for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
        m_gameObjects[i]->draw(m_pRenderer);

    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) 
        m_gameObjects[i]->update();
}

void Game::draw()
{
    for (std::vector<GameObject*>::size_type i = 0; i !=
        m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw(m_pRenderer);
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            m_bRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
