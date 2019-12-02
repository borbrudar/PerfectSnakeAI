#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"

using namespace sf;
//function prototypes
bool hamCycle(std::vector<std::vector<int>> &board, Vector2f pos, int &path, int size);
//global variables
int board = 6;
int size = 20;

int main() {
	//setup 
	RenderWindow window;
	window.create(VideoMode(board * size, board * size), "Perfect snake AI");

	Event e;
	Clock c;
	Snake s(size, board);
	Apple a(size);
	int dir = 0, upd = 0;

	//calculate the hamiltonian cycle
	// setup
	int path = 0;
	int bx = board;
	std::vector<std::vector<int>> board{ 6 };
	Vector2f pos = { 3 , 3 };
	for (int i = 0; i < bx; i++) {
		board[i].resize(bx);
		for (int j = 0; j < bx; j++) board[i][j] = -1;	
	}
	//alg
	hamCycle(board, pos, path, bx);
	//check
	/*for (int i = 0; i < bx; i++) {
		for (int j = 0; j < bx; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	
	
	//game loop
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) window.close();
			//hand controls - unnecessary
			/*if (Keyboard::isKeyPressed(Keyboard::Left)) {  s.body[0].speedx = -1; s.body[0].speedy = 0; }
			if (Keyboard::isKeyPressed(Keyboard::Right)) { s.body[0].speedx = 1;  s.body[0].speedy = 0; }
			if (Keyboard::isKeyPressed(Keyboard::Up)) {  s.body[0].speedy = -1; s.body[0].speedx = 0; }
			if (Keyboard::isKeyPressed(Keyboard::Down)) {  s.body[0].speedy = 1; s.body[0].speedx = 0; }*/
		}

		bool eaten = false;
		if (upd == 50) {
			eaten = s.update(a.pos,board,bx); upd = 0;
		}
		else upd++;
		
		a.update(eaten);

		window.clear(Color::White);
		s.draw(window);
		a.draw(window);
		window.display();

		c.restart();
	}
	return 0;
}


bool hamCycle(std::vector<std::vector<int>> &board,Vector2f pos, int &path, int size) {
	
	//check if it's outside the box
	if (pos.x >= size || pos.x < 0 || pos.y >= size || pos.y < 0) return false;
	if (board[pos.x][pos.y] != -1) return false;

	board[pos.x][pos.y] = path;
	path++;
	//check if the cycle is completed
	bool isDone = true;
	if (path != (size * size)) isDone = false;
	
	//check if this cell is adjacent to the beggining and if so it's done
	if (isDone) {
		if (pos.x != 0 && pos.x != (size - 1) && pos.y != 0 && pos.y != (size - 1)) {
			if ((board[pos.x + 1][pos.y] == 0) || (board[pos.x - 1][pos.y] == 0) || (board[pos.x][pos.y + 1] == 0)
				|| (board[pos.x][pos.y - 1] == 0)) {
				return true;
			}
			path--;
			board[pos.x][pos.y] = -1;
			return false;
		}
		else {
			path--;
			board[pos.x][pos.y] = -1;
			return false;
		};
	}
	//recursion time -> recursion time -> recursion time -> recursion time ...
	if (hamCycle(board, Vector2f(pos.x + 1, pos.y), path, size)) return true;
	if (hamCycle(board, Vector2f(pos.x - 1, pos.y), path, size)) return true;
	if (hamCycle(board, Vector2f(pos.x, pos.y + 1), path, size)) return true;
	if (hamCycle(board, Vector2f(pos.x, pos.y - 1), path, size)) return true;
	
	path--;
	board[pos.x][pos.y] = -1;
	return false;
}