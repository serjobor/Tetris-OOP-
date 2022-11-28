#pragma once
#include<memory>

class Coords {  // Координаты фигуры

	std::uint32_t x, y;

public:
	std::uint32_t getX();
	std::uint32_t getY();

	void setX(std::uint32_t);
	void setY(std::uint32_t);

	Coords& operator = (const Coords&);
	Coords& operator ++ ();
};
