#include "define.h"
#include "acllib.h"
#include <math.h> 
#include<vector>
using namespace std;
extern vector<collected*> collectors;



void freemove::location_change()
{
	x += dx/sqrt(dx*dx+dy*dy) * speed;
	y += dy/ sqrt(dx * dx + dy * dy) * speed;
	if (x < 0 || x > getWidth() - small_icon_size)
		dx = 0 - dx;
	if (y < 0 || y > getHeight() - small_icon_size)
		dy = 0 - dy;
};
bool freemove::crash(player* A )
{
	if ((A->getx() - x) * (A->getx() - x) + (A->gety() - y) * (A->gety() - y) <= (big_icon_size *  big_icon_size))
		return true;
	else
		return false;
}
freemove::freemove()
{
	speed = 5;
	sourse = rand() % 4;
	switch (sourse)
	{
	case 0:
		y = getHeight() - small_icon_size;
		x = rand() % (getWidth() - small_icon_size);
		dx = (rand() % 21 - 10) / 10.0;
		dy = 0 - (rand() % 9 + 1) / 10.0;
		break; //ÉÏ²àÇ½
	case 1:
		x = 0;
		y = rand() % (getHeight() - small_icon_size);
		dx = (rand() % 9 + 1) / 10.0;
		dy = (rand() % 21 - 10) / 10.0;
		break; //×ó²àÇ½
	case 2:
		y = 0;
		x = rand() % (getWidth() - small_icon_size);
		dy = (rand() % 9 + 1) / 10.0;
		dx = (rand() % 21 - 10) / 10.0;
		break; //ÏÂ²àÇ½
	case 3:
		x = getWidth() - small_icon_size;
		y = rand() % (getHeight() - small_icon_size);
		dx = 0 - (rand() % 9 + 1) / 10.0;
		dy = (rand() % 21 - 10) / 10.0;
		break; //ÓÒ²àÇ½

	default:
		break;
	}
}

void collected::draw()
{
	putImageTransparent(icon, x, y, small_icon_size, small_icon_size, WHITE);
}
int collected::getscores()
{
	return scores;
}
void collected::effect(player *A)
{
	A->addscores(scores);
}
colleted1::colleted1()
{
	loadImage("collector1.jpg", icon);
	scores = 1;
	speed = 5;
}
colleted2::colleted2()
{
	loadImage("collector2.jpg", icon);
	scores = 5;
	speed = 10;
}
colleted3::colleted3()
{
	loadImage("collector3.jpg", icon);
	scores = 10;
	speed = 20;
}

void property::draw()
{
	putImageTransparent(icon, x, y, small_icon_size, small_icon_size, WHITE);
}
speedup::speedup()
{
	loadImage("speed.jpg", icon);
}
clr::clr()
{
	loadImage("clear.jpg", icon);
}
void speedup::effect(player* A)
{
	A->addspeed(3);
}
void clr::effect(player* A)
{
	for (int i = 0; i < collectors.size();)
	{
		collectors.at(i)->effect(A);
		collectors.erase(collectors.begin() + i);
	}
}

enermy::enermy()
{
	loadImage("1.jpg", icon);
	damage = 1;
	level = 0;
}
void enermy::draw()
{
	putImageTransparent(icon, x, y, big_icon_size, big_icon_size, WHITE);
}
void enermy::effect(player*A)
{
	A->blood_down(damage);
}
void enermy::levelup(player* A )
{
	if (A->get_scores() > 20&&A->get_scores() <= 50)
	{
		loadImage("2.jpg", icon);
		damage = 2;
		speed = 12;
		level = 1;
	}
	else if (A->get_scores() > 50 && A->get_scores() <= 90)
	{
		loadImage("3.jpg", icon);
		damage = 3;
		speed = 18;
		level = 2;
	}
	if (A->get_scores() > 90)
	{
		loadImage("4.jpg", icon);
		damage = 5;
		speed = 25;
		level = 3;
	}
}
void enermy::follow(player* A )
{
	if (level >= 1)
	{
		if (A->getx() != x && A->gety() - y != 0)
		{
			dx = A->getx() - x;
			dy = A->gety() - y;
		}
	}
}