
#ifndef FIRE_BULLET_H // начало
#define FIRE_BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>
// класс снарядов-патронов
class FireBullet
{
private:
	// форма снаряда
	sf::Sprite shape;

	// направление и скорость снаряда
	sf::Vector2f bulletDirection;
	float moveBulletSpeed;

public:
	FireBullet();
	// передаю позиции каждого выпущенного снаряда
	FireBullet(sf::Texture *texture, float pos_x, float pos_y, float d_X, float d_Y, float move_Bullet_Speed);
	virtual ~FireBullet();

	// для снарядов (позиции)
	const sf::FloatRect getBounds() const;

	void Update();
	void Render(sf::RenderTarget *target);
};

#endif // конец
