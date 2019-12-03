#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Board {
public:
	Board() = default;
	void init(int bx) {
		size = bx;
		for (int i = 0; i < board.size(); i++) {
			board[i].resize(bx);
			for (int j = 0; j < bx; j++) board[i][j] = -1;

		}
	}
	std::vector<std::vector<int>> board{ 4 };
	int size;
	bool hamCycle(Vector2f pos, Vector2f endPos, int &path);
};