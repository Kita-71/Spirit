#include "acllib.h"
#define small_icon_size 45
#define big_icon_size 100
#define player_speed 5
#define blood_volume 5
class object
{
protected:
	ACL_Image* icon;
	double x, y;
	int speed;
public:
	object();
	virtual void draw()=0;
	double getx();				
	double gety();	
};

class player :public object
{
private:
	int scores;
	int blood;
public:
	player();
	void draw();
	void control(int mode);
	int get_blood();
	int get_scores();
	void blood_down(int damage);
	void addspeed(int s);
	void addscores(int score);
};

class freemove :public object //����ƶ������壨���ࣩ
{
protected:
	int sourse;
	double dx, dy;
public:
	freemove();
	void location_change();
	bool crash(player* A );
	virtual void effect(player* A)=0;
};

class collected : public freemove//�ռ�Ʒ���̳��ࣩ
{
protected:
	int scores;
public:
	void draw();
	int getscores();
	void effect(player* A);
};
class colleted1 :public collected
{
public:
	colleted1();
};
class colleted2 :public collected
{
public:
	colleted2();
};
class colleted3 :public collected
{
public:
	colleted3();
};

class property : public freemove //���ߣ��̳��ࣩ
{
public:
	void draw();
};
class speedup : public property
{
public:
	speedup();
	void effect(player* A);
};
class clr :public property
{
public:
	clr();
	void effect(player* A);
};

class enermy : public freemove //���ˣ��̳��ࣩ
{
private:
	int damage;
	int level;
public:
	enermy();
	void draw();
	void effect(player* A);
	void levelup(player* A );
	void follow(player* A );
};
