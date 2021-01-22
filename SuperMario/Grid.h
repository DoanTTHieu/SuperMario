#pragma once
#include"GameObject.h"
#include"Game.h"
#include"Utils.h"
#include "Define.h"

class CGrid
{
	int map_width;
	int map_height;

	int cell_width;
	int cell_height;

	int nums_col;
	int nums_row;

	vector<vector<vector<LPGAMEOBJECT>>> cells;
public:
	CGrid(int map_width, int map_height, int cell_width = CELL_WIDTH, int cell_height = CELL_HEIGHT);
	~CGrid();

	void Clear(int nums_row, int nums_col);
	void UpdateGrid(vector<LPGAMEOBJECT> list);

	void ResetCamGrid(vector<LPGAMEOBJECT>& list);

	void GetObjFromGrid(vector<LPGAMEOBJECT>& list);
	void pushObjIntoGrid(LPGAMEOBJECT obj, int row, int col);
	void pushNewObjIntoGrid(LPGAMEOBJECT obj);
};
typedef CGrid* LPGRIG;

