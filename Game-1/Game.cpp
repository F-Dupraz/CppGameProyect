#include "Game.h"

Game* Game::s_pInstance = nullptr;

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
                if (!TheTextureManager::Instance()->load("./Images/background.bmp", "background", m_pRenderer))
                    return false;

                if (!TheTextureManager::Instance()->load("./Images/pixil-frame-0.png", "hinchaT", m_pRenderer))
                    return false;

                if (!TheTextureManager::Instance()->load("./Images/pixil-frame-1.png", "hinchaPirata", m_pRenderer))
                    return false;

                m_gameObjects.push_back(new Player(new LoaderParams(((720 / 2) - 50), 70, 100, 100, "hinchaT")));
                m_gameObjects.push_back(new Enemy(new LoaderParams(470, 240, 100, 100, "hinchaPirata")));
                m_gameObjects.push_back(new Enemy(new LoaderParams(520, 360, 100, 100, "hinchaPirata")));
                m_gameObjects.push_back(new Enemy(new LoaderParams(570, 480, 100, 100, "hinchaPirata")));
                m_gameObjects.push_back(new Enemy(new LoaderParams(620, 600, 100, 100, "hinchaPirata")));
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
        m_gameObjects[i]->draw();

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
        m_gameObjects[i]->draw();
    }
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheInputHandler::Instance()->clean();
    SDL_Quit();
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}
