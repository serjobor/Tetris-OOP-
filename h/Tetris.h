#pragma once

#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <memory>
#include "Shape.h"
#include "Coords.h"
#include "BulderText.h"

class Tetris 
{
	static const std::uint32_t lines   {20}; // Кол-во линий
	static const std::uint32_t cols    {10}; // Кол-во столбцов
	static const std::uint32_t squares {4};  // Кол-во квадратов
	static const std::uint32_t shapes  {7};  // Кол-во форм фигур

	const std::uint32_t w = 34;

	std::vector<std::vector<std::uint32_t>> area;  // Игровая область
	std::vector<Shapes*> figures; // Массив фигур

	Coords z[squares], k[squares];

	enum records
	{
		NewGame = 0,
		Info = 1,
		Exit = 2,
		SCORE = 3,
		Lines = 4,
		GAMEOVER = 5
	};


	std::shared_ptr<sf::RenderWindow> window;	
	std::shared_ptr<sf::Sprite> sprite, background, backgroundTwo, background1, background2, Tex1, Tex2;

	sf::Clock clock;

	sf::Image ico;
	sf::Texture tiles, bg, bg2, Texture1, Texture2;

	std::vector<std::pair<sf::Text*, sf::Font*>> all_records;
	
	sf::Font  font, font2;
	sf::Text txtScore, txtLines, txtGameOver;

	sf::SoundBuffer sb_rotateFigure, sb_lineBoost, sb_gameOver, sb_mainTheme, sb_LP;
	sf::Sound sound_rotateFigure, sound_lineBoost, sound_gameOver, sound_mainTheme, sound_LP;

	int dirx, color, score, Line;
	bool rotate, gameover;
	float timercount, delay, speed;

	void loadResources();   // Подгрузка файлов для игры

protected:
	void events();          // Обработка событий
	void draw();            // Прорисовка
	void moveToDown();      // Создание и движеине фигуры
	void setRotate();       // Поворот фигуры
	void resetValues();     // Восстановление прежних значений
	void changePosition();  // 
	bool maxLimit();        // Ограничения игрового поля
	void setScore();        // Удаление заполненной линии и присвоение очков
	void menu();            // Начальное меню

public:
	Tetris();               
	~Tetris();             
	void run();             // Запуск игры
};