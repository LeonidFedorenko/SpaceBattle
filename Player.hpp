#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
// класс игрока
class Player
{
private:
	sf::Sprite spriteGame;
	sf::Texture textureGame;
	// переменная для движения корабля
	float moveShipSpeed;
	// для прекращения атаки
	float terminationAttack;
	float terminationAttackMAX;
	// здоровье корабля (игрока)
	int HealthPlayer;
	int HealthPlayerMAX;
	// функция для пременной
	void initAnyVar();
	// функции загрузки
	void initTextureGame();
	void initSpriteGame();
public:
	Player();
	virtual ~Player();
	// обновление атаки
	void UpdateAttack();
	// обновление игры
	void Update();
	// позизция в окне для каждого снаряда
	const sf::Vector2f& getPositionBullet() const;
	// границы врагов
	const sf::FloatRect enemyBoundaries() const;
	// контроль за здоровьем игрока
	const int &getHealthPlayer() const;
	const int &getHealthPlayerMAX() const;
	// изменение положения
	void setPosition(const sf::Vector2f posPlayer);
	void setPosition(const float xPos, const float yPos);
	// здоровье
	void setHEALTH(const int HPlayer);
	// потеря здоровья
	void lossHEALTHplayer(const int HPvalue);
	// переменная для атаки
	const bool canFire();
	void move(const float dX, const float dY); // движение
	void Render(sf::RenderTarget &target); // перерисовка
};
