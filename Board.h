#pragma once
#include <vector>
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

struct Board{
	struct Tile {
		unsigned int x;
		unsigned int y;
		unsigned int surroundingMines;
		bool isFlaged;
		bool hasMine;
		bool revealedTile;
		Sprite tile;
		Sprite tile2;
		vector<Tile*> adjacentTile;

		Tile();
		Tile(unsigned x, unsigned int y, unsigned int surroundingMines, bool isFlaged, bool hasMine, bool revealedTile, Sprite tile, Sprite tile2);
	};
	int flagedTiles;
	int mineCount;
	int revealedTiles;
	bool gameOver;
	vector<vector<Tile>> tile$;

	Board();
	Board(int flagedTiles, int mineCount, int revealedTiles, vector<vector<Tile>> tile$, bool gameOver);
};