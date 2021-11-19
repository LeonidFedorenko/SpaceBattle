#include "FireBullet.hpp"

FireBullet::FireBullet() { }

FireBullet::FireBullet(sf::Texture *texture, float pos_x, float pos_y, float d_X, float d_Y, float move_Bullet_Speed)
{	// параметры для каждого снаряда (передаю)
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_x, pos_y);
	this->bulletDirection.x = d_X;
	this->bulletDirection.y = d_Y;
	this->moveBulletSpeed = move_Bullet_Speed;
}

FireBullet::~FireBullet() { }

const sf::FloatRect FireBullet::getBounds() const
{	// возвращаю позицию в окне
	return this->shape.getGlobalBounds();
}

void FireBullet::Update()
{	// движение снаряда
	this->shape.move(this->moveBulletSpeed * this->bulletDirection);
}

void FireBullet::Render(sf::RenderTarget* target)
{	// для прорисовки снарядов
	target->draw(this->shape);
}
