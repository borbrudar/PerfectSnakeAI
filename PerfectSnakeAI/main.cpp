#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Apple.h"
#include "Board.h"
#include <math.h>

using namespace sf;

//global variables
int board = 24;
int size = 20;

int main() {
	//setup 
	RenderWindow window;
	window.create(VideoMode(board * size, board * size), "Perfect snake AI");

	Event e;
	Clock c;
	Snake s(size, board);
	Apple a(size, board);
	int dir = 0, upd = 0, speed = 10;

	//calculate the hamiltonian cycle
	// setup
	int path = 0;
	int bx = 4;
	std::vector<std::vector<int>> ultimateBoard; ultimateBoard.resize(24);
	std::vector<Vector2f> boardp; boardp.resize(36);
	for (int i = 0; i < ultimateBoard.size(); i++) {
		ultimateBoard[i].resize(24);
	}
	std::vector<Board> boards; boards.resize(36);
	for (int i = 0; i < boards.size(); i++) boards[i].init(bx);
	//algorithm for all 36 boards  (row/column) actually it's a hamiltonian path 
	{
		boards[0].hamCycle(Vector2f(3, 1), Vector2f(0, 3), path); boardp[0] =   { 0,0 };
		boards[1].hamCycle(Vector2f(0, 0), Vector2f(3, 0), path); boardp[1] =   { 0,1 };
		boards[2].hamCycle(Vector2f(0, 0), Vector2f(3, 0), path); boardp[2] =   { 1,1 };
		boards[3].hamCycle(Vector2f(0, 0), Vector2f(2, 3), path); boardp[3] =   { 2,1 };
		boards[4].hamCycle(Vector2f(2, 0), Vector2f(0, 3), path); boardp[4] =   { 2,2 };
		boards[5].hamCycle(Vector2f(3, 3), Vector2f(0, 3), path); boardp[5] =   { 1,2 };
		boards[6].hamCycle(Vector2f(3, 3), Vector2f(0, 3), path); boardp[6] =   { 0,2 };
		boards[7].hamCycle(Vector2f(0, 0), Vector2f(3, 0), path); boardp[7] =   { 0,3 };
		boards[8].hamCycle(Vector2f(0, 0), Vector2f(3, 0), path); boardp[8] =   { 1,3 };
		boards[9].hamCycle(Vector2f(0, 0), Vector2f(2, 3), path); boardp[9] =   { 2,3 };
		boards[10].hamCycle(Vector2f(2, 0), Vector2f(0, 3), path); boardp[10] = { 2,4 };
		boards[11].hamCycle(Vector2f(3, 3), Vector2f(0, 3), path); boardp[11] = { 1,4 };
		boards[12].hamCycle(Vector2f(3, 3), Vector2f(0, 3), path); boardp[12] = { 0,4 };
		boards[13].hamCycle(Vector2f(0, 0), Vector2f(3, 2), path); boardp[13] = { 0,5 };
		boards[14].hamCycle(Vector2f(0, 2), Vector2f(3, 2), path); boardp[14] = { 1,5 };
		boards[15].hamCycle(Vector2f(0, 2), Vector2f(3, 2), path); boardp[15] = { 2,5 };
		boards[16].hamCycle(Vector2f(0, 2), Vector2f(3, 2), path); boardp[16] = { 3,5 };
		boards[17].hamCycle(Vector2f(0, 2), Vector2f(3, 2), path); boardp[17] = { 4,5 };
		boards[18].hamCycle(Vector2f(0, 2), Vector2f(3, 0), path); boardp[18] = { 5,5 };
		boards[19].hamCycle(Vector2f(3, 3), Vector2f(0, 3), path); boardp[19] = { 5,4 };
		boards[20].hamCycle(Vector2f(3, 3), Vector2f(0, 3), path); boardp[20] = { 4,4 };
		boards[21].hamCycle(Vector2f(3, 3), Vector2f(1, 0), path); boardp[21] = { 3,4 };
		boards[22].hamCycle(Vector2f(1, 3), Vector2f(3, 0), path); boardp[22] = { 3,3 };
		boards[23].hamCycle(Vector2f(0, 0), Vector2f(3, 0), path); boardp[23] = { 4,3 };
		boards[24].hamCycle(Vector2f(0, 0), Vector2f(3, 0), path); boardp[24] = { 5,3 };
		boards[25].hamCycle(Vector2f(3, 3), Vector2f(0, 3), path); boardp[25] = { 5,2 };
		boards[26].hamCycle(Vector2f(3, 3), Vector2f(0, 3), path); boardp[26] = { 4,2 };
		boards[27].hamCycle(Vector2f(3, 3), Vector2f(1, 0), path); boardp[27] = { 3,2 };
		boards[28].hamCycle(Vector2f(1, 3), Vector2f(3, 0), path); boardp[28] = { 3,1 };
		boards[29].hamCycle(Vector2f(0, 0), Vector2f(3, 0), path); boardp[29] = { 4,1 };
		boards[30].hamCycle(Vector2f(0, 0), Vector2f(3, 0), path); boardp[30] = { 5,1 };
		boards[31].hamCycle(Vector2f(3, 3), Vector2f(0, 1), path); boardp[31] = { 5,0 };
		boards[32].hamCycle(Vector2f(3, 1), Vector2f(0, 1), path); boardp[32] = { 4,0 };
		boards[33].hamCycle(Vector2f(3, 1), Vector2f(0, 1), path); boardp[33] = { 3,0 };
		boards[34].hamCycle(Vector2f(3, 1), Vector2f(0, 1), path); boardp[34] = { 2,0 };
		boards[35].hamCycle(Vector2f(3, 1), Vector2f(0, 1), path); boardp[35] = { 1,0 };
	}
	//combine them all into the ultimate board
	for (int k = 0; k < boards.size(); k++) {
		for (int i = 0; i < bx; i++) {
			for (int j = 0; j < bx; j++) {
				// 4 is just bx, and 16 is bx^2
				ultimateBoard[boardp[k].y * 4 + j][boardp[k].x * 4 + i] = boards[k].board[i][j] + 16 * k;
			}
		}
	}

	//print out the ultimate board
	/*for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 24; j++) {
			std::cout << ultimateBoard[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	
	//game loop
	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Up)) { speed += 10; std::cout << "Speed: " << speed << std::endl; }
			if (Keyboard::isKeyPressed(Keyboard::Down)) { speed -= 10; std::cout << "Speed: " << speed << std::endl; }
		}
		//clamp speed
		if (speed < 0) speed = 0;
		if (speed > 200) speed = 200;
		//update
		bool eaten = false;
		if (upd >= speed) {
			eaten = s.update(a.pos, ultimateBoard, board); 
			upd = 0;
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


