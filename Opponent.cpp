#include "Opponent.hpp"

void Opponent::initAnyVar()
{	// переменные
	float sE = rand() % 10 + 1; // переменная для разной скорости
	this->pointEnemyCount = rand() % 21 + 5; // здоровье врага (от 4 до 12)
	this-> typeEnemy = 0; // тип фигуры врага
	this-> speedEnemy = sE / 10; // скорость движения врага 
	this-> healthEnemy = this->healthEnemyMAX; // здоровье
	this-> healthEnemyMAX = static_cast<int>(this->pointEnemyCount); // максимальное
	this-> damageEnemy = this->pointEnemyCount; // повреждение
	this-> pointsEnemy = rand() % 5 + 3; // очки
}

void Opponent::initShapeEnemy()
{	// инициализуция фигур врагов (описываемая окружность и позиция в окне)
	this->shapeEnemy.setRadius(rand() % 30 + 15);
	this->shapeEnemy.setPointCount(this->pointEnemyCount); // случайное здоровье врага
	// цвет противников (случайный)
	int rColor = rand() % 200;
	if (rColor < 100)
	{
		rColor += rColor;
	}
	int bColor = rand() % 200;
	if (bColor < 100)
	{
		bColor += bColor;
	}
	int gColor = rand() % 200;
	if (gColor < 100)
	{
		gColor += gColor;
	}
	this->shapeEnemy.setFillColor(sf::Color(rColor, bColor, gColor, 255));
}

Opponent::Opponent(float d_X, float d_Y)
{	// инициализация переменных
	this->initAnyVar();
	// инициализация врагов
	this->initShapeEnemy();
	// ставлю позицию появления
	this->shapeEnemy.setPosition(d_X, d_Y);
}

Opponent::~Opponent() { }

const sf::FloatRect Opponent::getBounds() const
{	// определение позиций врагов в окне
	return this->shapeEnemy.getGlobalBounds();
}

const int &Opponent::getPointsEnemy() const
{
	return this->pointsEnemy;
}

const int &Opponent::getDamageEnemy() const
{	// возвращаю величину повреждения от врага
	return this->damageEnemy;
}

void Opponent::Update()
{	// при обновлении движение врагов вниз
	this->shapeEnemy.move(0.f, this->speedEnemy);
}

void Opponent::Render(sf::RenderTarget* target)
{	// перерисовка врага
	target->draw(this->shapeEnemy);
}

