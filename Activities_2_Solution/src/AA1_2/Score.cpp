#include "Score.h"

Score::Score(int textWidth, int textHeight, int posx, int posy)
{
	frame.h = textHeight;
	frame.w = textWidth/10;
	position.w = frame.w /2;
	position.h = frame.h /2;
	frame.x = 0;
	frame.y = 0;
	position.x = posx;
	position.y = posy;
}

void Score::PlusScore()
{
		frame.x += frame.w;

}
