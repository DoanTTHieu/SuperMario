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
	float mainStart_x;
	float mainEnd_x;
	float hiddenStart_x;
	float hiddenEnd_x;

	CTileMap(int ID, LPCWSTR FilePath_tex, LPCWSTR FilePath_data, int Num_Rows, int  Num_Cols, int Num_row_read, int Num_col_read, int Tile_width , int Tile_height, float main_start, float main_end, float hidden_start, float hidden_end);
	~CTileMap();



	void Load();
	void LoadMap();
	void Draw();
	int GetMapWidth() { return Num_Cols * Tile_Width; }
	int GetMapHeight() { return Num_Rows * Tile_Height; }
};

typedef CTileMap* LPTILEMAP;