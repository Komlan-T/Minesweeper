#include "Board.h"
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace sf;

Board::Board(){
	flagedTiles = 0;
	mineCount = 0;
	revealedTiles = 0;
	gameOver = false;
}

Board::Board(int flagedTiles, int mineCount, int revealedTiles, vector<vector<Tile>> tile$, bool gameOver) {
	this->flagedTiles = flagedTiles;
	this->mineCount = mineCount;
	this->revealedTiles = revealedTiles;
	this->tile$ = tile$;
	this->gameOver = gameOver;
}

Board::Tile::Tile() {
	x = 0;
	y = 0;
	surroundingMines = 0;
	isFlaged = false;
	hasMine = false;
	revealedTile = false;
}

Board::Tile::Tile(unsigned x, unsigned int y, unsigned int surroundingMines, bool isFlaged, bool hasMine, bool revealedTile, Sprite tile, Sprite tile2) {
	this->x = x;
	this->y = y;
	this->surroundingMines = surroundingMines;
	this->isFlaged = isFlaged;
	this->hasMine = hasMine;
	this->revealedTile = revealedTile;
	this->tile = tile;
	this->tile2 = tile2;
}