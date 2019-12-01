#include "Snake.h"

bool Snake::update(Vector2f appPos)
{
	bool eaten = false, overlapping = false;
	body[0].lastPos = body[0].pos;
	body[0].pos.x += body[0].speedx;
	body[0].pos.y += body[0].speedy;
	body[0].shape.setPosition(Vector2f(body[0].pos.x *size + 2, body[0].pos.y * size + 2));

	if (body[0].pos == appPos) {
		body.resize(body.size() + 1);
		body[body.size() - 1].pos = body[body.size() - 2].lastPos;
		eaten = true;
		
		length++;
		std::cout << length << std::endl;
	}
	
	for (int i = 1; i < body.size(); i++) {
		body[i].lastPos = body[i].pos;
		body[i].pos = body[i - 1].lastPos;
		body[i].shape.setPosition(Vector2f(body[i].pos.x *size + 2, body[i].pos.y * size + 2));
	}
	
	for (int i = 1; i < body.size(); i++) {
		if (body[i].pos == body[0].pos) overlapping = true;
	}

	if (body[0].pos.y > 30 || body[0].pos.y < 0 || body[0].pos.x < 0 || body[0].pos.x > 30 || overlapping) {
		body.resize(1);
		body[0].pos = { 15,15 };

		std::cout << "--------------Game Over-----------" << std::endl;
		length = 0;
	}

	return eaten;
}

void Snake::draw(RenderWindow & window)
{
	for (int i = 0; i < body.size(); i++) {
		window.draw(body[i].shape);
	}
}
