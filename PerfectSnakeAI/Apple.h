#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Apple {
public:
	Apple(int size, int bx) : size(size), bx(bx) {
		apple.setSize(Vector2f(size - 2, size - 2));
		apple.setFillColor(Color::Red);
		apple.setOutlineThickness(2.f);
		apple.setOutlineColor(Color::White);
		pos.x = rand() % bx;
		pos.y = rand() % bx;
	}
	void update(bool eaten);
	void draw(RenderWindow &window);
	RectangleShape apple;
	int size, bx;
	Vector2f pos;
};