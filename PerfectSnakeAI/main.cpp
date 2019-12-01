#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"

using namespace sf;

//global variables
int boardX = 30;
int boardY = 30;
int size = 20;

int main() {
	//setup 
	RenderWindow window;
	window.create(VideoMode(boardX * size, boardY * size), "Perfect snake AI");

	Event e;
	Clock c;
	Snake s(size);
	Apple a(size);
	int dir = 0, upd = 0;
	//game loop
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Left)) {  s.body[0].speedx = -1; s.body[0].speedy = 0; }
			if (Keyboard::isKeyPressed(Keyboard::Right)) { s.body[0].speedx = 1;  s.body[0].speedy = 0; }
			if (Keyboard::isKeyPressed(Keyboard::Up)) {  s.body[0].speedy = -1; s.body[0].speedx = 0; }
			if (Keyboard::isKeyPressed(Keyboard::Down)) {  s.body[0].speedy = 1; s.body[0].speedx = 0; }
		}

		bool eaten = false;
		if (upd == 60) {
			eaten = s.update(a.pos); upd = 0;
		}
		else upd += 1;
		
		a.update(eaten);

		window.clear(Color::White);
		s.draw(window);
		a.draw(window);
		window.display();

		c.restart();
	}
	return 0;
}