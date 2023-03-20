#define  _CRT_SECURE_NO_WARNINGS
#include "acllib.h"
#include "define.h"
#include <iostream>
#include <time.h>
#include<windows.h>
#include<vector>
using namespace std;

int start = 0;
player*player1=NULL;
vector<collected*>collectors;
vector<property*> properties;
enermy* boss = NULL;
void time_event(int TimeID)
{
	if (TimeID == 0)
	{
		beginPaint();
		clearDevice();
		//打印字符串
		char* t = new char[100];
		char* s = new char[100];
		_itoa(player1->get_scores(), s, 10);
		_itoa(player1->get_blood(), t, 10);
		setTextColor(BLACK);
		setTextBkColor(WHITE);
		setTextSize(20);
		paintText(720, 40, "Scores");
		paintText(720, 60, "HP");
		paintText(800, 40, s);
		paintText(800, 60, t);
		setTextSize(60);
		paintText(300, 30, "努力收集吧！");
		//
		player1->draw();
		boss->draw();
		boss->location_change();

		for (int i = 0; i < collectors.size(); i++)
		{
			if (collectors.at(i)->crash(player1) == true)
			{
				collectors.at(i)->effect(player1);
				collectors.erase(collectors.begin() + i);
				if (i == collectors.size())
					break;
			}
			collectors.at(i)->location_change();
			collectors.at(i)->draw();
		}
		for (int i = 0; i < properties.size(); i++)
		{
			if (properties.at(i)->crash(player1) == true)
			{
				properties.at(i)->effect(player1);
				properties.erase(properties.begin() + i);
				if (i == properties.size())
					break;
			}
			properties.at(i)->location_change();
			properties.at(i)->draw();
		}

		endPaint();

		boss->levelup(player1);
		boss->follow(player1);

		if (player1->get_blood() <= 0)
		{
			cancelTimer(0);
			MessageBoxA(NULL, "你的血量已空", "可惜！", MB_OK);
			exit(0);
		}
		if (player1->get_scores() >= 100)
		{
			cancelTimer(0);
			MessageBoxA(NULL,"你的分数达到100分啦！恭喜", "胜利！", MB_OK);
			exit(0);
		}
		delete[] s;
		delete[] t;
	}
	if (TimeID == 1)
	{
		if (boss->crash(player1) == true)
		{
			boss->effect(player1);
			cancelTimer(1);
			startTimer(6, 2000);
		}
	}
	if (TimeID == 2)
	{
		if (collectors.size() != 7)
		{
			collectors.push_back(new colleted1);
		}

	}
	if (TimeID == 3)
	{
		if (collectors.size() != 7)
		{
			collectors.push_back(new colleted2);
		}
	}
	if (TimeID == 4)
	{
		if (collectors.size() != 7)
		{
			collectors.push_back(new colleted3);
		}
		if (properties.size() != 2)
		{
			properties.push_back(new speedup);
		}
	}
	if (TimeID == 5)
	{
		if (properties.size() != 2)
		{
			properties.push_back(new clr);
		}
	}
	if (TimeID == 6)
	{
		startTimer(1, 300);
		cancelTimer(6);
	}
	if (TimeID == 7)
	{
		ACL_Image* background = new ACL_Image;
		loadImage("开始游戏.jpg", background);
		beginPaint();
		putImageTransparent(background, -1, -1, 960, 640, WHITE);
		endPaint();
		if (start)
		{
			startTimer(0, 100);
			startTimer(1, 300);
			startTimer(2, 1500);
			startTimer(3, 5000);
			startTimer(4, 20000);
			startTimer(5, 30000);
			cancelTimer(7);
		}

	}

}
void keyControl(int key, int event)
{
	if (key)
	{
		start = 1;
	}
	if (key == 0x26)
	{
		player1->control(1);
	} //↑
	if (key == 0x28)
	{
		player1->control(2);
	} //↓
	if (key == 0x25)
	{
		player1->control(3);
	} //←
	if (key == 0x27)
	{
		player1->control(4);
	} // →
}

int Setup()
{
	initWindow("Spirit Game", DEFAULT, DEFAULT, 960, 640);

	srand(time(NULL)); //用于rand

	player1=new player;
	boss = new enermy;

	startTimer(7, 100);

	registerKeyboardEvent(keyControl);
	registerTimerEvent(time_event);


	return 0;
}