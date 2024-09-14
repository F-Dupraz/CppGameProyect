#include "Enemy.h"

Enemy::Enemy() : SDLGameObject()
{
    //
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::load(const LoaderParams* pParams)
{
    SDLGameObject::load(pParams);
    this->m_velocity.setX(4);
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
