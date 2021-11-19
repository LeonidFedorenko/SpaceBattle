#ifndef OPPONENT_H
#define OPPONENT_H

#include <SFML/Graphics.hpp>
#include <vector>

// класс противников
class Opponent
{
private:
	unsigned pointEnemyCount;
	sf::CircleShape shapeEnemy; // фигура врага
	int typeEnemy; // тип фигуры врага
	float speedEnemy; // скорость движения врага
	int healthEnemy; // здоровье
	int healthEnemyMAX; // максимальное
	int damageEnemy; // повреждение
	int pointsEnemy; // очки

	// функция для пременных
	void initAnyVar();
	// функция для фигур врагов
	void initShapeEnemy();

public:
	Opponent(float d_X, float d_Y);
	virtual ~Opponent();
	// свойства-аксессоры врагов
	const sf::FloatRect getBounds() const;
	// здоровье врагов
	const int &getPointsEnemy() const;
	// повреждение игрока
	const int &getDamageEnemy() const;
	// функции обновления и перерисовки
	void Update();
	void Render(sf::RenderTarget* target);
};

#endif // !OPPONENT_H
