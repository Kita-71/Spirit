#include "define.h"
#include "acllib.h"
#include <math.h> 
#include<vector>
object::object()
{
	speed = 0;
	icon = new ACL_Image;
	x = 0;
	y = 0;
}

double object::getx()
{
	return x;
}
double object::gety()
{
	return y;
}
