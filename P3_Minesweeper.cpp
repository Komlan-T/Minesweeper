#include <SFML/Graphics.hpp>
#include "Random.h"
#include "TextureManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "Board.h"
using namespace std;
using namespace sf;

void TestBoards(string fileName, int width, int height, vector<vector<Board::Tile>>& digits) {
	
	ifstream file(fileName);
	char digit = ' ';
	int i = 0;
	int j = 0;

	for (int i = 0; i < width; i++) {

		for (int j = 0; j < height; j++) {

			digits[i][j].hasMine = false;
		}
	}

	if (file.is_open()) {

		while (file.get(digit)) {

			if (digit == '1') {

				digits[i][j].hasMine = true;
			}
			if (i < width) {
				i++;
			}
			else {
				i = 0;
				
				if (j < height) {
					j++;
				}
				else {
					j = 0;
				}
			}
		}
	}
}

int main() {
	
	ifstream file("boards/config.cfg");

	if (file.is_open()) {

		int width = 0;
		int height = 0;
		int bombNum = 0;

		// READ BOARD
		while (!file.eof()) {

			file >> width;
			file >> height;
			file >> bombNum;
		}

		int widthPix = width * 32;
		int heightPix = height * 32 + 100;

		RenderWindow window(VideoMode(widthPix, heightPix), "Minesweeper");

		TextureManager textures;

		Texture tile = textures.GetTexture("tile_hidden");

		Texture happyFace = textures.GetTexture("face_happy");
		Sprite smile;
		smile.setTexture(happyFace);
		if (width % 2 == 0) {
			smile.setPosition(Vector2f((widthPix / 2), heightPix - 100));
		}
		else {
			smile.setPosition(Vector2f((widthPix / 2) - 32, heightPix - 100));
		}

		Texture sadFace = textures.GetTexture("face_lose");
		Sprite frown;
		frown.setTexture(sadFace);
		if (width % 2 == 0) {
			frown.setPosition(Vector2f((widthPix / 2), heightPix - 100));
		}
		else {
			frown.setPosition(Vector2f((widthPix / 2) - 32, heightPix - 100));
		}

		Texture sunglasses = textures.GetTexture("face_win");
		Sprite _sunglasses;
		_sunglasses.setTexture(sunglasses);
		if (width % 2 == 0) {
			_sunglasses.setPosition(Vector2f((widthPix / 2), heightPix - 100));
		}
		else {
			_sunglasses.setPosition(Vector2f((widthPix / 2) - 32, heightPix - 100));
		}

		Texture test3 = textures.GetTexture("test_3");
		Sprite test_3;
		test_3.setTexture(test3);
		if (width % 2 == 0) {
			test_3.setPosition(Vector2f((widthPix / 2) + 320, heightPix - 100));
		}
		else {
			test_3.setPosition(Vector2f((widthPix / 2) - 32 + 320, heightPix - 100));
		}

		Texture test2 = textures.GetTexture("test_2");
		Sprite test_2;
		test_2.setTexture(test2);
		if (width % 2 == 0) {
			test_2.setPosition(Vector2f((widthPix / 2) + 256, heightPix - 100));
		}
		else {
			test_2.setPosition(Vector2f((widthPix / 2) - 32 + 256, heightPix - 100));
		}

		Texture test1 = textures.GetTexture("test_1");
		Sprite test_1;
		test_1.setTexture(test1);
		if (width % 2 == 0) {
			test_1.setPosition(Vector2f((widthPix / 2) + 192, heightPix - 100));
		}
		else {
			test_1.setPosition(Vector2f((widthPix / 2) - 32 + 192, heightPix - 100));
		}

		Texture debug = textures.GetTexture("debug");
		Sprite _debug;
		_debug.setTexture(debug);
		if (width % 2 == 0) {
			_debug.setPosition(Vector2f((widthPix / 2) + 128, heightPix - 100));
		}
		else {
			_debug.setPosition(Vector2f((widthPix / 2) - 32 + 128, heightPix - 100));
		}

		Texture hiddenTile = textures.GetTexture("tile_hidden");

		Texture revealedTile = textures.GetTexture("tile_revealed");
		Sprite _revealedTile;
		_revealedTile.setTexture(revealedTile);

		Texture flag = textures.GetTexture("flag");
		Sprite _flag;
		_flag.setTexture(flag);

		Texture mine = textures.GetTexture("mine");
		Sprite _mine;
		_mine.setTexture(mine);

		Texture digits = textures.GetTexture("digits");
		Sprite _digits;
		_digits.setTexture(digits);
		_digits.setPosition(Vector2f(0.0f, heightPix - 100));

		Texture num1 = textures.GetTexture("number_1");
		Texture num2 = textures.GetTexture("number_2");
		Texture num3 = textures.GetTexture("number_3");
		Texture num4 = textures.GetTexture("number_4");
		Texture num5 = textures.GetTexture("number_5");
		Texture num6 = textures.GetTexture("number_6");
		Texture num7 = textures.GetTexture("number_7");
		Texture num8 = textures.GetTexture("number_8");


		int debug_Pressed_Num = 0;
		int test1_Pressed = 0;
		int test2_Pressed = 0;
		int test3_Pressed = 0;

		// CREATE TILES
		vector<vector<Board::Tile>> tiles;

		for (int i = 0; i < width; i++) {

			vector<Board::Tile> temp;

			for (int j = 0; j < (float)height + 3.125; j++) {

				Sprite first;
				Sprite second;

				Board::Tile _tile(i, j, 0, false, false, false, first, second);

				temp.push_back(_tile);
			}

			tiles.push_back(temp);
		}

		// SETUP MINES
		vector<Sprite> mines;

		for (int i = 0; i < bombNum; i++) {

			int x = Random::Int(0, widthPix);
			int y = Random::Int(0, height * 32);

			if (tiles[floor(x / 32)][floor(y / 32)].hasMine == false) {

				tiles[floor(x / 32)][floor(y / 32)].hasMine = true;

				_mine.setPosition(floor(x / static_cast<float>(32)) * 32, floor(y / static_cast<float>(32)) * 32);

				mines.push_back(_mine);
			}
			else {

				int _x = Random::Int(0, widthPix);
				int _y = Random::Int(0, height * 32);

				tiles[floor(_x / 32)][floor(_y / 32)].hasMine = true;

				_mine.setPosition(floor(_x / static_cast<float>(32)) * 32, floor(_y / static_cast<float>(32)) * 32);

				mines.push_back(_mine);
			}
		}

		Board board(0, bombNum, 0, tiles, false);

		// NEIGHBORING TILES

		// TOP LEFT

		tiles[0][0].adjacentTile.push_back(&tiles[1][0]);
		tiles[0][0].adjacentTile.push_back(&tiles[0][1]);
		tiles[0][0].adjacentTile.push_back(&tiles[1][1]);

		// TOP RIGHT

		tiles[width - 1][0].adjacentTile.push_back(&tiles[width - 2][0]);
		tiles[width - 1][0].adjacentTile.push_back(&tiles[width - 1][1]);
		tiles[width - 1][0].adjacentTile.push_back(&tiles[width - 2][1]);

		//// BOTTOM LEFT

		tiles[0][height - 1].adjacentTile.push_back(&tiles[0][height - 2]);
		tiles[0][height - 1].adjacentTile.push_back(&tiles[1][height - 1]);
		tiles[0][height - 1].adjacentTile.push_back(&tiles[1][height - 2]);

		//// BOTTOM RIGHT

		tiles[width - 1][height - 1].adjacentTile.push_back(&tiles[width - 1][height - 2]);
		tiles[width - 1][height - 1].adjacentTile.push_back(&tiles[width - 2][height - 1]);
		tiles[width - 1][height - 1].adjacentTile.push_back(&tiles[width - 2][height - 2]);

		// TOP ROW

		for (int i = 1; i <= width - 2; i++) {

			tiles[i][0].adjacentTile.push_back(&tiles[i - 1][0]);
			tiles[i][0].adjacentTile.push_back(&tiles[i - 1][1]);
			tiles[i][0].adjacentTile.push_back(&tiles[i][1]);
			tiles[i][0].adjacentTile.push_back(&tiles[i + 1][1]);
			tiles[i][0].adjacentTile.push_back(&tiles[i + 1][0]);
		}

		// BOTTOM ROW

		for (int i = 1; i <= width - 2; i++) {

			tiles[i][height - 1].adjacentTile.push_back(&tiles[i - 1][height - 1]);
			tiles[i][height - 1].adjacentTile.push_back(&tiles[i - 1][height - 2]);
			tiles[i][height - 1].adjacentTile.push_back(&tiles[i][height - 2]);
			tiles[i][height - 1].adjacentTile.push_back(&tiles[i + 1][height - 2]);
			tiles[i][height - 1].adjacentTile.push_back(&tiles[i + 1][height - 1]);
		}

		// LEFT COLUMN

		for (int i = 1; i <= height - 2; i++) {

			tiles[0][i].adjacentTile.push_back(&tiles[0][i - 1]);
			tiles[0][i].adjacentTile.push_back(&tiles[1][i - 1]);
			tiles[0][i].adjacentTile.push_back(&tiles[0][i]);
			tiles[0][i].adjacentTile.push_back(&tiles[1][i + 1]);
			tiles[0][i].adjacentTile.push_back(&tiles[0][i + 1]);
		}

		// RIGHT COLUMN

		for (int i = 1; i <= height - 2; i++) {

			tiles[width - 1][i].adjacentTile.push_back(&tiles[width - 1][i - 1]);
			tiles[width - 1][i].adjacentTile.push_back(&tiles[width - 1][i + 1]);
			tiles[width - 1][i].adjacentTile.push_back(&tiles[width - 2][i]);
			tiles[width - 1][i].adjacentTile.push_back(&tiles[width - 2][i - 1]);
			tiles[width - 1][i].adjacentTile.push_back(&tiles[width - 2][i + 1]);
		}

		// EVERY OTHER TILE	

		for (int i = 1; i <= width - 2; i++) {

			for (int j = 1; j <= height - 2; j++) {

				tiles[i][j].adjacentTile.push_back(&tiles[i][j - 1]);
				tiles[i][j].adjacentTile.push_back(&tiles[i + 1][j]);
				tiles[i][j].adjacentTile.push_back(&tiles[i][j + 1]);
				tiles[i][j].adjacentTile.push_back(&tiles[i - 1][j]);
				tiles[i][j].adjacentTile.push_back(&tiles[i - 1][j - 1]);
				tiles[i][j].adjacentTile.push_back(&tiles[i + 1][j - 1]);
				tiles[i][j].adjacentTile.push_back(&tiles[i - 1][j + 1]);
				tiles[i][j].adjacentTile.push_back(&tiles[i + 1][j + 1]);
			
			}
		}

		// ASSIGNING SURROUNDING MINES

		for (int i = 0; i < width; i++) {

			for (int j = 0; j < height; j++) {

				for (int k = 0; k < tiles[i][j].adjacentTile.size(); k++) {

					if (tiles[i][j].adjacentTile[k]->hasMine == true) {

						tiles[i][j].surroundingMines++;
					}
				}
			}
		}

		while (window.isOpen()) {

			Event event;

			while (window.pollEvent(event)) {

				if (event.type == Event::Closed) {
					window.close();
				}

				window.clear();

				for (int i = 0; i < width; i++) {

					for (int j = 0; j < height; j++) {

						Sprite x;

						x.setTexture(hiddenTile);

						x.setPosition(i * 32, j * 32);

						window.draw(x);
					}
				}

				window.draw(smile);
				window.draw(test_3);
				window.draw(test_2);
				window.draw(test_1);
				window.draw(_debug);
				window.draw(_digits);

				// COORDINATES
				Vector2i cursor = Mouse::getPosition(window);
				Vector2f convert = window.mapPixelToCoords(cursor);

				int X = floor(cursor.x / 32);
				int Y = floor(cursor.y / 32);


				// REVEALING TILES
				if (Mouse::isButtonPressed(Mouse::Left) && !tiles[X][Y].isFlaged && !tiles[X][Y].revealedTile && !tiles[X][Y].hasMine) {

					if (tiles[X][Y].surroundingMines == 0) {

						tiles[X][Y].tile.setTexture(revealedTile);

						tiles[X][Y].tile.setPosition(X * 32, Y * 32);

						tiles[X][Y].revealedTile = true;

						board.revealedTiles++;

						for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

							if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

								if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
							}
						}
					}
				else if (tiles[X][Y].surroundingMines == 1) {

						tiles[X][Y].tile.setTexture(revealedTile);

						tiles[X][Y].tile.setPosition(X * 32, Y * 32);

						tiles[X][Y].revealedTile = true;

						board.revealedTiles++;

						for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

							if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

								if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
								else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

									tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

									tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

									tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

									tiles[X][Y].revealedTile = true;

									board.revealedTiles++;
								}
							}
						}
				}
				else if (tiles[X][Y].surroundingMines == 2) {

				tiles[X][Y].tile.setTexture(revealedTile);

				tiles[X][Y].tile.setPosition(X * 32, Y * 32);

				tiles[X][Y].revealedTile = true;

				board.revealedTiles++;

				for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

					if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

						if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
					}
				}
				}
				else if (tiles[X][Y].surroundingMines == 3) {

				tiles[X][Y].tile.setTexture(revealedTile);

				tiles[X][Y].tile.setPosition(X * 32, Y * 32);

				tiles[X][Y].revealedTile = true;

				board.revealedTiles++;

				for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

					if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

						if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
					}
				}
				}
				else if (tiles[X][Y].surroundingMines == 4) {

				tiles[X][Y].tile.setTexture(revealedTile);

				tiles[X][Y].tile.setPosition(X * 32, Y * 32);

				tiles[X][Y].revealedTile = true;

				board.revealedTiles++;

				for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

					if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

						if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
					}
				}
				}
				else if (tiles[X][Y].surroundingMines == 5) {

				tiles[X][Y].tile.setTexture(revealedTile);

				tiles[X][Y].tile.setPosition(X * 32, Y * 32);

				tiles[X][Y].revealedTile = true;

				board.revealedTiles++;

				for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

					if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

						if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
					}
				}
				}
				else if (tiles[X][Y].surroundingMines == 6) {

				tiles[X][Y].tile.setTexture(revealedTile);

				tiles[X][Y].tile.setPosition(X * 32, Y * 32);

				tiles[X][Y].revealedTile = true;

				board.revealedTiles++;

				for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

					if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

						if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
					}
				}
				}
				else if (tiles[X][Y].surroundingMines == 7) {

				tiles[X][Y].tile.setTexture(revealedTile);

				tiles[X][Y].tile.setPosition(X * 32, Y * 32);

				tiles[X][Y].revealedTile = true;

				board.revealedTiles++;

				for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

					if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

						if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
					}
				}
				}
				else if (tiles[X][Y].surroundingMines == 8) {

				tiles[X][Y].tile.setTexture(revealedTile);

				tiles[X][Y].tile.setPosition(X * 32, Y * 32);

				tiles[X][Y].revealedTile = true;

				board.revealedTiles++;

				for (int i = 0; i < tiles[X][Y].adjacentTile.size(); i++) {

					if (tiles[X][Y].adjacentTile[i]->hasMine == false) {

						if (tiles[X][Y].adjacentTile[i]->surroundingMines == 0) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 1) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num1);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 2) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num2);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 3) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num3);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 4) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num4);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 5) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num5);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 6) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num6);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 7) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num7);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
						else if (tiles[X][Y].adjacentTile[i]->surroundingMines == 8) {

							tiles[X][Y].adjacentTile[i]->tile.setTexture(revealedTile);

							tiles[X][Y].adjacentTile[i]->tile2.setTexture(num8);

							tiles[X][Y].adjacentTile[i]->tile.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].adjacentTile[i]->tile2.setPosition(tiles[X][Y].adjacentTile[i]->x * 32, tiles[X][Y].adjacentTile[i]->y * 32);

							tiles[X][Y].revealedTile = true;

							board.revealedTiles++;
						}
					}
				}
				}
				}
				// CLEAR BOARD
				else if (Mouse::isButtonPressed(Mouse::Left) && smile.getGlobalBounds().contains(convert)) {

					board.flagedTiles = 0;

					board.revealedTiles = 0;

					for (int i = 0; i < tiles.size(); i++) {

						for (int j = 0; j < tiles[i].size(); j++) {

							tiles[i][j].tile.setTexture(hiddenTile);

							tiles[i][j].tile2.setTexture(hiddenTile);

							tiles[i][j].isFlaged = false;

							tiles[i][j].revealedTile = false;
						}
					}

					mines.clear();

					debug_Pressed_Num *= 2;

					for (int i = 0; i < bombNum; i++) {

						int x = Random::Int(0, widthPix);
						int y = Random::Int(0, height * 32);

						if (tiles[floor(x / 32)][floor(y / 32)].hasMine == false) {

							tiles[floor(x / 32)][floor(y / 32)].hasMine = true;

							_mine.setPosition(floor(x / static_cast<float>(32)) * 32, floor(y / static_cast<float>(32)) * 32);

							mines.push_back(_mine);
						}
						else {

							int _x = Random::Int(0, widthPix);
							int _y = Random::Int(0, height * 32);

							tiles[floor(_x / 32)][floor(_y / 32)].hasMine = true;

							_mine.setPosition(floor(_x / static_cast<float>(32)) * 32, floor(_y / static_cast<float>(32)) * 32);

							mines.push_back(_mine);
						}
					}
				}
				// PRESS ON A MINE
				else if (Mouse::isButtonPressed(Mouse::Left) && !tiles[X][Y].isFlaged && !tiles[X][Y].revealedTile && tiles[X][Y].hasMine) {

					board.gameOver = true;
				}
				// REVEAL MINES
				else if (Mouse::isButtonPressed(Mouse::Left) && _debug.getGlobalBounds().contains(convert)) {
					
					board.revealedTiles--;
					
					debug_Pressed_Num++;
				}
				// PLACING FLAGS
				else if (Mouse::isButtonPressed(Mouse::Right) && tiles[X][Y].isFlaged == false && tiles[X][Y].revealedTile == false) {

					tiles[X][Y].tile.setTexture(flag);

					tiles[X][Y].tile.setPosition(X * 32, Y * 32);

					tiles[X][Y].isFlaged = true;

					board.flagedTiles++;
				}
				// REMOVING FLAGS
				else if (Mouse::isButtonPressed(Mouse::Right) && tiles[X][Y].isFlaged && !tiles[X][Y].revealedTile) {

					tiles[X][Y].tile.setTexture(hiddenTile);

					tiles[X][Y].tile.setPosition(X * 32, Y * 32);

					tiles[X][Y].isFlaged = false;

					board.flagedTiles--;
				}
				// GAME OVER
				if (board.gameOver) {

					for (int i = 0; i < width; i++) {

						for (int j = 0; j < height; j++) {

							if (tiles[i][j].hasMine) {

								tiles[i][j].tile.setTexture(revealedTile);

								tiles[i][j].tile2.setTexture(mine);

								tiles[i][j].tile.setPosition(i * 32, j * 32);

								tiles[i][j].tile2.setPosition(i * 32, j * 32);
							}
						}
					}

					window.draw(frown);

					if (Mouse::isButtonPressed(Mouse::Left) && frown.getGlobalBounds().contains(convert)) {

						board.flagedTiles = 0;

						board.revealedTiles = 0;

						debug_Pressed_Num *= 2;

						window.draw(smile);

						board.gameOver = false;
					}
				}
				// DEBUG BUTTON
				if (debug_Pressed_Num % 2 != 0) {

					for (int i = 0; i < mines.size(); i++) {

						if (mines[i].getGlobalBounds().contains(convert)) {

							Vector2f find = mines[i].getPosition();

							_revealedTile.setPosition(Vector2f(find.x, find.y));
						}
					}
					for (int i = 0; i < mines.size(); i++) {

						window.draw(mines[i]);
					}
				}
				// TEST CASE 1
				if (Mouse::isButtonPressed(Mouse::Left) && test_1.getGlobalBounds().contains(convert)) {

					TestBoards("boards/testBoard1.brd", width, height, tiles);
		
					test1_Pressed++;

					if (test1_Pressed % 2 != 0) {

						for (int i = 0; i < tiles.size(); i++) {

							for (int j = 0; j < tiles[i].size(); j++) {

								tiles[i][j].tile.setTexture(hiddenTile);

								tiles[i][j].tile2.setTexture(hiddenTile);

								tiles[i][j].isFlaged = false;

								tiles[i][j].revealedTile = false;
							}
						}
					}
				}
				// TEST CASE 2
				else if (Mouse::isButtonPressed(Mouse::Left) && test_2.getGlobalBounds().contains(convert)) {

					TestBoards("boards/testBoard1.brd", width, height, tiles);

					test2_Pressed++;

					if (test2_Pressed % 2 != 0) {

						for (int i = 0; i < tiles.size(); i++) {

							for (int j = 0; j < tiles[i].size(); j++) {

								tiles[i][j].tile.setTexture(hiddenTile);

								tiles[i][j].tile2.setTexture(hiddenTile);

								tiles[i][j].isFlaged = false;

								tiles[i][j].revealedTile = false;
							}
						}
					}
					
				}
				// TEST CASE 3
				else if (Mouse::isButtonPressed(Mouse::Left) && test_3.getGlobalBounds().contains(convert)) {

					TestBoards("boards/testBoard3.brd", width, height, tiles);

					//test3_Pressed++;

					//if (test3_Pressed % 2 != 0) {

						for (int i = 0; i < tiles.size(); i++) {

							for (int j = 0; j < tiles[i].size(); j++) {

								tiles[i][j].tile.setTexture(hiddenTile);

								tiles[i][j].tile2.setTexture(hiddenTile);

								tiles[i][j].isFlaged = false;

								tiles[i][j].revealedTile = false;
							}
						}
					//}
				}
				
				for (int i = 0; i < width; i++) {

					for (int j = 0; j < height; j++) {

						window.draw(tiles[i][j].tile);

						window.draw(tiles[i][j].tile2);

					}
				}

				// FLAG COUNTER
				vector<int> digit$;
				vector<int> digit$2;
				int temp = 0;
				int offset = 0;
				int diff = board.mineCount - board.flagedTiles;
				int numDigits = log10(diff) + 1;

				if (diff > 0) {

					if (numDigits == 1) {

						digit$.push_back(0);
						digit$.push_back(0);

						while (diff > 0) {

							int digit = diff % 10;
							diff /= 10;
							digit$.push_back(digit);
						}
						for (int i = 0; i < digit$.size(); i++) {
							offset += 21;
							_digits.setTextureRect(IntRect(digit$[i] * 21, 0, 21, 32));
							_digits.setPosition(offset, heightPix - 100);
							window.draw(_digits);
						}
					}
					else if (numDigits == 2) {

						digit$.push_back(0);

						while (diff > 0) {

							int digit = diff % 10;
							diff /= 10;
							digit$.push_back(digit);
						}

						_digits.setTextureRect(IntRect(digit$[0] * 21, 0, 21, 32));
						_digits.setPosition(21, heightPix - 100);
						window.draw(_digits);

						_digits.setTextureRect(IntRect(digit$[2] * 21, 0, 21, 32));
						_digits.setPosition(42, heightPix - 100);
						window.draw(_digits);

						_digits.setTextureRect(IntRect(digit$[1] * 21, 0, 21, 32));
						_digits.setPosition(63, heightPix - 100);
						window.draw(_digits);
					}
					else if (numDigits == 3) {

						while (diff > 0) {

							int digit = diff % 10;
							diff /= 10;
							digit$.push_back(digit);
						}
						for (int i = digit$.size() - 1; i >= 0; i--) {
							offset += 21;
							_digits.setTextureRect(IntRect(digit$[i] * 21, 0, 21, 32));
							_digits.setPosition(offset, heightPix - 100);
							window.draw(_digits);
						}
					}
				}

				else if (diff == 0) {

					_digits.setTextureRect(IntRect(0 * 21, 0, 21, 32));
					_digits.setPosition(21, heightPix - 100);
					window.draw(_digits);

					_digits.setTextureRect(IntRect(0 * 21, 0, 21, 32));
					_digits.setPosition(42, heightPix - 100);
					window.draw(_digits);

					_digits.setTextureRect(IntRect(0 * 21, 0, 21, 32));
					_digits.setPosition(63, heightPix - 100);
					window.draw(_digits);
				}

				else if (diff < 0) {

					temp = abs(diff);
					int numOfDigits = log10(temp) + 1;
					
					_digits.setTextureRect(IntRect(10 * 21, 0, 21, 32));
					_digits.setPosition(21, heightPix - 100);
					window.draw(_digits);
					
					if (numOfDigits == 1) {

						_digits.setTextureRect(IntRect(0 * 21, 0, 21, 32));
						_digits.setPosition(42, heightPix - 100);
						window.draw(_digits);

						_digits.setTextureRect(IntRect(temp * 21, 0, 21, 32));
						_digits.setPosition(63, heightPix - 100);
						window.draw(_digits);
					}
					else if (numOfDigits == 2) {

						for (int i = 0; i < 2; i++) {
							
							int digit = temp % 10;
							temp /= 10;
							digit$2.push_back(digit);
						}

						_digits.setTextureRect(IntRect(digit$2[1] * 21, 0, 21, 32));
						_digits.setPosition(42, heightPix - 100);
						window.draw(_digits);

						_digits.setTextureRect(IntRect(digit$2[0] * 21, 0, 21, 32));
						_digits.setPosition(63, heightPix - 100);
						window.draw(_digits);
					}

				}

				// WIN CONDITION
				if (board.revealedTiles == board.tile$.size() - board.mineCount) {

					for (int i = 0; i < width; i++) {

						for (int j = 0; j < height; j++) {

							if (tiles[i][j].hasMine) {

								tiles[i][j].tile.setTexture(flag);
							}
						}
					}

					window.draw(_sunglasses);
				}
			}
			window.display();
		}
	}
}