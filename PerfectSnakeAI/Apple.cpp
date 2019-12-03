#include "Apple.h"

void Apple::update(bool eaten)
{
	if (eaten) {
		pos.x = rand() % bx;
		pos.y = rand() % bx;
	}
}

void Apple::draw(RenderWindow & window)
{
	apple.setPosition(pos.x * size + 2, pos.y * size + 2);
	window.draw(apple);
}
