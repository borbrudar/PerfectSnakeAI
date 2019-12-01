#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Apple {
public:
	Apple(int size) : size(size) {
		apple.setSize(Vector2f(size - 2, size - 2));
		apple.setFillColor(Color::Red);
		apple.setOutlineThickness(2.f);
		apple.setOutlineColor(Color::White);
		pos.x = rand() % 21;
		pos.y = rand() % 21;
	}
	void update(bool eaten);
	void draw(RenderWindow &window);
	RectangleShape apple;
	int size;
	Vector2f pos;
};