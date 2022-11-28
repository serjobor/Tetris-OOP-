#pragma once
#include "Coords.h"
#include <vector>

class Shapes 
{
protected:
	std::vector<std::uint32_t>active_square; // ������ �������� ���������

public:
	Coords* changeZarray(Coords*);           // ���������� ��������� ��������
};

class I : public Shapes
{
public:
	I();
};

class Z : public Shapes
{
public:
	Z();
};

class S : public Shapes
{
public:
	S();
};

class T : public Shapes
{
public:
	T();
};

class L : public Shapes
{
public:
	L();
};

class J : public Shapes
{
public:
	J();
};

class O : public Shapes
{
public:
	O();
};

