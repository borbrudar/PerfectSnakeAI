#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Snake {
public:
	Snake(int size) : size(size) {
		body[0].pos = { 15, 15 };
		body[1].pos = { 16, 15 };
		body[2].pos = { 17, 15 };
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
	bool update(Vector2f appPos);
	void draw(RenderWindow &window);
	int size;
	std::vector<segment> body{ 3 };
	int length = 0;
};