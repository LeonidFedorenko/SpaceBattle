#include "GameSpace.hpp"
// переменные для окна
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 760
// конструктор
GameSpace::GameSpace()
{	// запускаю окно
	this->initWindow();
	// игрок
	this->initPlayer();
	// интерфейс (очки)
	this->initInterfaceGame();
	this->initScorePlayer();
	// снаряды
	this->initTextures();
	// враги
	this->initSpaceEnemy();
	// фон игры
	this->initSpaceFon();
}

void GameSpace::Run()
{	// пока окно открыто
	while(this->window->isOpen())
	{	// обновляю
		this->UpdateEvents();
		// проверка здоровья игрока (не геймовер)
		if(this->player->getHealthPlayer() > 0)
			this->Update();	// обновление
		this->Render(); // перерисовка
	}	
}

void GameSpace::UpdateEvents()
{	// обновляю события
	sf::Event eventGame;
	// пока окно открыто (ловлю события)
	while (this->window->pollEvent(eventGame))
	{
		if (eventGame.Event::type == sf::Event::Closed)
		{	// закрываю окно мышкой
			this->window->close();
		}
		if (eventGame.Event::KeyPressed && eventGame.Event::key.code == sf::Keyboard::Escape)
		{	// закрываю окно клавиатурой
			this->window->close();
		}
	}
}

void GameSpace::UpdateInput()
{	// обновляю движение корабля (буквами клавиатуры и крестиком клавиатуры)
	if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) || 
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
	{	// влево клавиши: "Left" || "A"
		this->player->move(-1.f, 0.f);
	}
	if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) || 
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
	{	// вправо клавиши: "Right" || "D"
		this->player->move(1.f, 0.f);
	}
	if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) || 
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)))
	{	// вверх клавиши: "Up" || "W"
		this->player->move(0.f, -1.f);
	}
	if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) || 
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)))
	{	// вниз клавиши: "Down" || "S"
		this->player->move(0.f, 1.f);
	}

	// по нажатию пробела или мыши (левая кнопка) - стрельба
	// и есть ли разрешение на стрельбу - canFire()
	if ( ( (sf::Mouse::isButtonPressed(sf::Mouse::Left)) || (sf::Keyboard::isKeyPressed
		   (sf::Keyboard::Key::Space)) ) && this->player->canFire())
	{	// с перемещением снарядов (из центра корабля)
		this->fireBullets.push_back(new FireBullet(
			this->textures["FIREBULLET"],
			this->player->getPositionBullet().x + this->player->enemyBoundaries().width/2.5f, 
			this->player->getPositionBullet().y, 
			0.f, 			-1.f, 			5.f));
	}
}

void GameSpace::UpdateInterface()
{	// обновляю интерфейс игрока (набор очков)
	std::stringstream ScoreGamePlayer; // переменная для очков
	ScoreGamePlayer << "                                                      SCORE: " << 
		this->scorePlayer; // очки в переменную
	this->scoreText.setString(ScoreGamePlayer.str()); // переменную в строку
	// для полоски здоровья (потеря здоровья)
	// this->player->setHEALTH(100); // начало: 100% здоровья (красная полоска)
	float healthPercent = static_cast<float>(this->player->
		getHealthPlayer()) / this->player->getHealthPlayerMAX(); // процент для здоровья
	this->healthPlayerAll.setSize(sf::Vector2f(300.f * healthPercent, this->healthPlayerAll.getSize().y));
}

void GameSpace::UpdateSpaceSky()
{ } 	// обновления фона  

void GameSpace::UpdateCollisionEnemy()
{	// обновление столкновений слева
	if(this->player->enemyBoundaries().left < 0.f)
	{	// при столкновении меняю позицию
		this->player->setPosition(0.f, this->player->enemyBoundaries().top);
	}
	// границы справа (размер окна по Х)
	else if (this->player->enemyBoundaries().left + this->player->enemyBoundaries().width >= this->window->getSize().x)
	{	// при столкновении справа
		this->player->setPosition(this->window->getSize().x - this->player->enemyBoundaries().width, 
			this->player->enemyBoundaries().top);
	}
	// граница сверху
	if (this->player->enemyBoundaries().top < 0.f)
	{	// вверх нельзя (за окно)
		this->player->setPosition(this->player->enemyBoundaries().left, 0.f);
	}
	// границы снизу (по высоте корабля)
	else if (this->player->enemyBoundaries().top + this->player->enemyBoundaries().height >= this->window->getSize().y)
	{	// при столкновении справа
		this->player->setPosition(this->player->enemyBoundaries().left,
			this->window->getSize().y - this->player->enemyBoundaries().height);
	}
}

void GameSpace::UpdateFireBullets()
{	// для подсчёта
	unsigned bullet_counter = 0;
	// обновление для снарядов 
	for (auto *iBullet : this->fireBullets)
	{
		iBullet->Update();
		// обновление (уничтожение на верху) при стрельбе (позиция)
		if(iBullet->getBounds().top + iBullet->getBounds().height < 0.f)
		{	// отчистка (уничтожение снаряда)
			delete iBullet;
			this->fireBullets.erase(this->fireBullets.begin() + bullet_counter);
			// проверка - std::cout << this->fireBullets.size() << std::endl;
		}
		// увеличиваю счётчик снарядов
		++bullet_counter;
	}
}

void GameSpace::UpdateSpaceEnemy()
{	// скорость движения врагов (вниз)
	this->spawnTimeEnemy += 0.3f;
	// обновление появляющихся врагов
	if (this->spawnTimeEnemy >= this->spawnTimeEnemyMAX)
	{	// чтобы враги появлялись в окне (сверху)
		this->opponents.push_back(new Opponent(rand() % this->window->getSize().x - 20.f, -77.f));
		this->spawnTimeEnemy = 0.f;
	}
	// враги для подсчёта
	unsigned enemy_counter = 0;
	// обновление для врагов 
	for (auto *iEnemy : this->opponents)
	{
		iEnemy->Update();
		// обновление (уничтожение врага) при стрельбе (позиция) 
		if (iEnemy->getBounds().top > this->window->getSize().y)
		{	// отчистка при попадании (уничтожение врага)
			delete this->opponents.at(enemy_counter);
			this->opponents.erase(this->opponents.begin() + enemy_counter);
		}
		else if (iEnemy->getBounds().intersects(this->player->enemyBoundaries()))
		{	// при столкновении уменьшаю здоровье игрока (на величину повреждения от врага - damageEnemy)
			this->player->lossHEALTHplayer(this->opponents.at(enemy_counter)->getDamageEnemy());
			// отчистка при столкновении (уничтожение врага)
			delete this->opponents.at(enemy_counter);
			this->opponents.erase(this->opponents.begin() + enemy_counter);
		}
		// увеличиваю счётчик врагов
		++enemy_counter;
	}
}

void GameSpace::UpdateFireEnemy()
{	// обновление для врагов - и попадание снарядов при стрельбе
	for (int iEnemy = 0; iEnemy < this->opponents.size(); ++iEnemy)
	{
		bool killEnemy = false; // убит ли враг?
		// беру размер снаряда, проверяю попадание и жив ли враг
		for (size_t jBullet = 0; jBullet < this->fireBullets.size() && killEnemy == false; jBullet++)
		{	// и проверяю попадание (столкновение с врагом)
			if (this->opponents[iEnemy]->getBounds().intersects(this->fireBullets[jBullet]->getBounds()))
			{	// добавляю очки при попадании (случайное количество)
				this->scorePlayer += this->opponents[iEnemy]->getPointsEnemy();
				// удаляю врага (в которого попало)
				delete this->opponents[iEnemy];
				this->opponents.erase(this->opponents.begin() + iEnemy);
				// удаляю снаряд (которым попало во врага)
				delete this->fireBullets[jBullet];
				this->fireBullets.erase(this->fireBullets.begin() + jBullet);
				// значит враг был убит
				killEnemy = true;
			}
		}
	}
}

void GameSpace::RenderSpaceFon()
{	// рендер фонового изображения из ресурсов
	this->window->draw(this->spaceBackGround);
}

void GameSpace::Update()
{	// события в игре 	
	this->UpdateInput();
	this->player->Update();
	this->UpdateCollisionEnemy(); // столкновения
	this->UpdateFireBullets(); // снаряды
	this->UpdateSpaceEnemy(); // враги
	this->UpdateFireEnemy(); // попадания
	this->UpdateInterface(); // интерфейс
	this->UpdateSpaceSky(); // фон
}

void GameSpace::RenderInterface()
{	// рендер интерфейса игрока в течении игры
	this->window->draw(this->scoreText);
	// рендер для здоровья
	this->window->draw(this->healthPlayerBack);
	this->window->draw(this->healthPlayerAll);
}

void GameSpace::Render()
{
	this->window->clear();
	// загружаю фон игры
	this->RenderSpaceFon();
	// здесь рисую объекты (корабль)
	this->player->Render(*this->window);
	// рендер снарядов
	for (auto *iBullet : this->fireBullets)
	{
		iBullet->Render(this->window);
	}
	// рендер врагов
	for (auto* opponent : this->opponents)
	{
		opponent->Render(this->window);
	}
	// вывод интерфейса (набрано очков)
	this->RenderInterface();
	// окно при геймовере (надпись поверх окна)
	if (this->player->getHealthPlayer() <= 0)
		this->window->draw(this->gameOverTXT);
	// вывожу на окно (на форму)
	this->window->display();
}

void GameSpace::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), 
		L"Игра ''Космическая битва'' / Управление: мышь (левая клавиша - выстрел), клавиатура (клавиши: ↑, ↓, ←, →, W, S, A, D, пробел - выстрел).",
		sf::Style::Close | sf::Style::Titlebar); // заголовок окна и кнопка закрытия 
	this->window->setFramerateLimit(144);
	// запрещаю контроль частоты кадров по вертикали
	this->window->setVerticalSyncEnabled(false);
}

void GameSpace::initTextures()
{	// снаряды
	this->textures["FIREBULLET"] = new sf::Texture();
	// загружаю рисунок пули-снаряда 
	this->textures["FIREBULLET"]->loadFromFile("Resources/fireBullet.png");
}

void GameSpace::initInterfaceGame()
{	// взаимодействие с пользователем, проверка и загрузка шрифта
	if (!this->gameFont.loadFromFile("Resources/ScoreFont.ttf"))
	{
		std::cout << "Ошибка при загрузке шрифта!" << "\n";
	};
	// вывод набранных очков
	this->scoreText.setFont(this->gameFont);
	this->scoreText.setCharacterSize(36);
	this->scoreText.setFillColor(sf::Color::Yellow);
	this->scoreText.setString(L"                                                      ОЧКИ: ");
	// конец игры
	this->gameOverTXT.setFont(this->gameFont);
	this->gameOverTXT.setCharacterSize(60);
	this->gameOverTXT.setFillColor(sf::Color::Red);
	this->gameOverTXT.setString("                         -= GAME OVER =-                        ");
	// надпись по центру экрана
	this->gameOverTXT.setPosition(this->window->getSize().x / 2.f - 
		this->gameOverTXT.getGlobalBounds().width / 2.f, this->window->getSize().y / 2.f -
		this->gameOverTXT.getGlobalBounds().height);
	// здоровье игрока (корабля)
	this->healthPlayerAll.setSize(sf::Vector2f(300.f, 25.f));
	this->healthPlayerAll.setFillColor(sf::Color::Red); // цвет полоски здоровья
	this->healthPlayerAll.setPosition(sf::Vector2f(20.f, 20.f));
	this->healthPlayerBack = this->healthPlayerAll;
	this->healthPlayerBack.setFillColor(sf::Color(45, 45, 45, 123));
}

void GameSpace::initSpaceFon()
{	// проверка возможно ли загрузить рисунок
	if (!this->spaceTexture.loadFromFile("Resources/spaceBackground.png"))
	{
		std::cout << "Ошибка при загрузке фонового изображения!" << "\n";
	}
	// загрузка фона из ресурсов
	this->spaceBackGround.setTexture(this->spaceTexture);
}

void GameSpace::initScorePlayer()
{	// для набора очков (начало игры)
	this->scorePlayer = 0;
}

void GameSpace::initPlayer()
{	// инициализация игрока
	this->player = new Player();
}

void GameSpace::initSpaceEnemy()
{	// инициализация появляющихся врагов
	this->spawnTimeEnemyMAX = 45.0f;
	this->spawnTimeEnemy = this->spawnTimeEnemyMAX;
}

// деструктор
GameSpace::~GameSpace()
{	// уничтожаю окно
	delete this->window;
	// уничтожаю игрока
	delete this->player;
	// уничтожаю текстуры снарядов
	for (auto &iBullet : this->textures)
	{	// все существующие контейнеры снарядов
		delete iBullet.second;
	}
	for (auto *iBullet : this->fireBullets)
	{	// все пули
		delete iBullet;
	}
	// для удаления врагов
	for (auto *iEnemys : this->opponents)
	{	// все пули
		delete iEnemys;
	}
}
