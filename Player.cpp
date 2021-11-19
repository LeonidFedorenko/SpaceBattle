#include "Player.hpp"

namespace alfSpaceBattle { }

void Player::initAnyVar()
{	// ставлю скорость передвижения корабля (игрока)
	this->moveShipSpeed = 2.3f;
	// переменные для стрельбы
	this->terminationAttackMAX = 10.f;
	this->terminationAttack = this->terminationAttackMAX;
	// здоровье корабля (игрока)
	this->HealthPlayerMAX = 100; // максимальное здоровье
	this->HealthPlayer = this->HealthPlayerMAX;
}

void Player::initTextureGame()
{	// здесь загружаю текстуру из файла (с проверкой загрузки)
	if (!this->textureGame.loadFromFile("Resources/alfShip.png"))
	{ // при неудачной загрузке
		std::cout << "Ошибка при загрузке текстуры корабля!"<< "n" << std::endl;
	}
}

void Player::initSpriteGame()
{	// загружаю текстуру из спрайта
	this->spriteGame.setTexture(this->textureGame);
	// изменяю размер текстуры корабля
	this->spriteGame.scale(0.17f, 0.17f);
	this->spriteGame.setPosition(this->spriteGame.getGlobalBounds().width / 0.115,
		this->spriteGame.getGlobalBounds().height / 0.09);
}

Player::Player()
{	// переменные для стрельбы
	this->initAnyVar();
	// загрузка текстуры и спрайта
	this->initTextureGame();
	this->initSpriteGame();
}

Player::~Player() {  }

void Player::UpdateAttack()
{	// обновление атаки при стрельбе
	if (this->terminationAttack < this->terminationAttackMAX)
	{	// чтобы снаряды не сливались в одну линию
		this->terminationAttack += 0.5f;
	}
}

void Player::Update()
{	// для обновления атаки при стрельбе
	this->UpdateAttack();
}

const sf::Vector2f& Player::getPositionBullet() const
{	// снаряды
	return this->spriteGame.getPosition();
}

const sf::FloatRect Player::enemyBoundaries() const
{	// противник
	return this->spriteGame.getGlobalBounds();
}

const int& Player::getHealthPlayer() const
{	// возвращаю величину здоровья
	return this->HealthPlayer;
}

const int& Player::getHealthPlayerMAX() const
{	// возвращаю макимальную величину здоровья
	return this->HealthPlayerMAX;
}

void Player::setPosition(const sf::Vector2f posPlayer)
{	// изменяю позицию
	this->spriteGame.setPosition(posPlayer);
}

void Player::setPosition(const float xPos, const float yPos)
{	// изменяю позицию
	this->spriteGame.setPosition(xPos, yPos);
}

void Player::setHEALTH(const int HPlayer)
{	// здоровье равно
	this->HealthPlayer = HPlayer;
}

void Player::lossHEALTHplayer(const int HPvalue)
{	// потеря части здоровья
	this->HealthPlayer -= HPvalue;
	// проверка количества здоровья
	if (this->HealthPlayer < 0)
		this->HealthPlayer = 0;
}

const bool Player::canFire()
{	// возможна ли атака?
	if (this->terminationAttack >= this->terminationAttackMAX)
	{
		this->terminationAttack = 0.f;
		return true;
	}
	return false;
}

void Player::move(const float dX, const float dY)
{	// движение игрока
	this->spriteGame.move(this->moveShipSpeed *dX, this->moveShipSpeed *dY);
}

void Player::Render(sf::RenderTarget &target)
{	// перерисовка спрайта
	target.draw(this->spriteGame);
}
