#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Snake {
public:
	Snake(int size, int bx) : size(size) {
		startP = Vector2f(bx / 2, bx / 2);
	};
	struct segment {
		segment() {
			shape.setFillColor(Color(0, 128, 0));
			shape.setSize(Vector2f(size - 2, size - 2));
			shape.setOutlineThickness(2.f);
			shape.setOutlineColor(Color::White);
		}
		RectangleShape shape;
		Vector2f pos, lastPos;
		int speedx = 1, speedy = 0;
		int size = 20;
	};
	bool update(Vector2f appPos, std::vector<std::vector<int>> board, int bx);
	void draw(RenderWindow &window);
	int size;
	std::vector<segment> body{ 1 };
	int length = 0, curr, prev;
	Vector2f startP;
};
