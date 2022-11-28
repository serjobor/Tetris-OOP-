#include "Coords.h"

std::uint32_t Coords::getX()
{
	return x;
}

std::uint32_t Coords::getY()
{
	return y;
}

void Coords::setX(std::uint32_t x)
{
	this->x = x;
}

void Coords::setY(std::uint32_t y)
{
	this->y = y;
}

Coords& Coords::operator=(const Coords& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

Coords& Coords::operator++()
{
	y++;
	return *this;
}
