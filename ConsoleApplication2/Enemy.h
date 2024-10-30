#pragma once
#include "Person.h"
class Enemy : public Person
{
private:
	std::string name;
public:
	void update(float time);
	//анимация атаки
	//анимация смерти
	//
};

