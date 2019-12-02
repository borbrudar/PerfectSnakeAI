#include "Apple.h"

void Apple::update(bool eaten)
{
	if (eaten) {
		pos.x = rand() % 6;
		pos.y = rand() % 6;
	}
}

void Apple::draw(RenderWindow & window)
{
	apple.setPosition(pos.x * size + 2, pos.y * size + 2);
	window.draw(apple);
}
