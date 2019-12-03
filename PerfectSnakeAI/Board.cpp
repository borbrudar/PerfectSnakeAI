#include "Board.h"

bool Board::hamCycle( Vector2f pos, Vector2f endPos, int &path) {

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
		if (pos == endPos) { 
			path = 0;
			return true; }
		else {
			path--;
			board[pos.x][pos.y] = -1;
			return false;
		};
	}
	//draw random (to make it more interesting), but it's unnecessary
	int ran = rand() % 4;
	//recursion time -> recursion time -> recursion time -> recursion time ...
	if (ran == 0) {
		if (hamCycle(Vector2f(pos.x + 1, pos.y), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x - 1, pos.y), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x, pos.y + 1), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x, pos.y - 1), endPos, path)) return true;
	}
	if (ran == 1) {
		if (hamCycle(Vector2f(pos.x, pos.y + 1), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x, pos.y - 1), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x + 1, pos.y), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x - 1, pos.y), endPos, path)) return true;
	}
	if (ran == 2) {
		if (hamCycle(Vector2f(pos.x, pos.y - 1), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x - 1, pos.y), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x, pos.y + 1), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x + 1, pos.y), endPos, path)) return true;
	}
	if (ran == 3) {
		if (hamCycle(Vector2f(pos.x + 1, pos.y), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x, pos.y - 1), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x, pos.y + 1), endPos, path)) return true;
		if (hamCycle(Vector2f(pos.x - 1, pos.y), endPos, path)) return true;
	}

	path--;
	board[pos.x][pos.y] = -1;
	return false;
}