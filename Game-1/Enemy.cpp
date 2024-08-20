#include "Enemy.h"

void Enemy::load(int x, int y, int width, int height, std::string textureID)
{
	GameObject::load(x, y, width, height, textureID);
}

void Enemy::draw(SDL_Renderer* pRenderer)
{
	GameObject::draw(pRenderer);
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

    if (this->isVisibleX() == 1)
    {
        this->isAddingX = true;
        m_x += 2;
    }
    else if (this->isVisibleX() == 2) {
        this->isAddingX = false;
        m_x -= 2;
    }
    else if (this->isVisibleX() == 0) {
        if (this->isAddingX)
            m_x += 2;
        else
            m_x -= 2;
    }

}

int Enemy::isVisibleX()
{
    if (this->m_x <= 0)
        return 1;
    else if ((this->m_x + this->m_width) > 720)
        return 2;
    else
        return 0;
}
