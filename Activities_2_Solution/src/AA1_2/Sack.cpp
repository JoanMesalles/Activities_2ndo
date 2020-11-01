#include "Sack.h"

Sack::Sack()
{
}

Sack::Sack(int textWidth, int textHeight, int posx, int posy)
{


	frame.h = textHeight;
	frame.w = textWidth;
	position.w = frame.w;
	position.h = frame.h;
	frame.x = 0;
	frame.y = 0;
	position.x = posx;
	position.y = posy;

}
