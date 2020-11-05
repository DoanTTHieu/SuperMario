#pragma once

#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"


class CTileMap
{
	CSprites* sprites = CSprites::GetInstance();
	LPCWSTR MapFilePath;
	LPCWSTR MapPNG;
	int Num_Rows, Num_Cols;
	int num_row_read, num_col_read;
	int Tile_Width, Tile_Height;
	int Id;

	int tilemap[300][300];

public:
	CTileMap(int ID, LPCWSTR FilePath_tex, LPCWSTR FilePath_data, int Num_Rows, int  Num_Cols, int Num_row_read, int Num_col_read, int Tile_width = 16, int Tile_height = 16);
	~CTileMap();

	void Load();
	void LoadMap();
	void Draw();
	int GetMapWidth() { return Num_Cols * Tile_Width; }
	int GetMapHeight() { return Num_Rows * Tile_Height+62; }
};

typedef CTileMap* LPTILEMAP;