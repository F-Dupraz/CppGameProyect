#include "Enemy.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    this->m_velocity.setX(2);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

    if (this->isVisibleX() == 1)
    {
        this->isAddingX = true;
        this->m_position += this->m_velocity;
    }
    else if (this->isVisibleX() == 2) {
        this->isAddingX = false;
        this->m_position -= this->m_velocity;
    }
    else if (this->isVisibleX() == 0) {
        if (this->isAddingX)
            this->m_position += this->m_velocity;
        else
            this->m_position -= this->m_velocity;
    }
}

int Enemy::isVisibleX()
{
    if (this->m_position.getX() <= 0)
        return 1;
    else if ((this->m_position.getX() + this->m_width) > 720)
        return 2;
    else
        return 0;
}
