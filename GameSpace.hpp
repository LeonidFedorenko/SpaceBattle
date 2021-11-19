#pragma once
#include <map> // карта окна игры
#include "Player.hpp" //игрок
#include "FireBullet.hpp" //патроны
#include "Opponent.hpp" //враги
#include <string> // очки
#include <sstream> // очки

// класс дл¤ игры
class GameSpace
{
private: 
	// окно игры
	sf::RenderWindow *window;
	// ресурсы дл¤ снар¤дов
	std::map<std::string, sf::Texture*> textures;
	std::vector<FireBullet*> fireBullets;
	// интерфейс игрока (шрифт и очки)
	sf::Font gameFont;
	sf::Text scoreText;
	// гейм-овер
	sf::Text gameOverTXT;
	// фон дл¤ игры
	sf::Texture spaceTexture;
	sf::Sprite spaceBackGround;
	// дл¤ набора очков
	unsigned scorePlayer;
	// игрок
	Player *player;
	// повреждени¤ корабл¤ - подсчЄт повреждений
	sf::RectangleShape healthPlayerAll;
	sf::RectangleShape healthPlayerBack;
	// враги
	float spawnTimeEnemy;
	float spawnTimeEnemyMAX;
	std::vector<Opponent*> opponents;

	// инициализаци¤
	void initWindow();
	void initTextures();
	void initInterfaceGame();
	void initSpaceFon();
	void initScorePlayer();
	void initPlayer();
	void initSpaceEnemy();
public:
	GameSpace();
	virtual ~GameSpace();

	void Run();
	// обновл¤ю событи¤
	void UpdateEvents();
	// обновл¤ю ввод
	void UpdateInput();
	// обновл¤ю интерфейс игрока
	void UpdateInterface();
	// обновл¤ю подложку игры
	void UpdateSpaceSky();
	// обновл¤ю столкновени¤
	void UpdateCollisionEnemy();
	// обновл¤ю снар¤ды
	void UpdateFireBullets();
	// обновл¤ю врагов
	void UpdateSpaceEnemy();
	// обновл¤ю попадани¤ во врагов
	void UpdateFireEnemy();
	// рендер фонового изображени¤
	void RenderSpaceFon();
	void Update();
	// рендер интерфейса игрока
	void RenderInterface();
	void Render();
};
