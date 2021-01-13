#include "TileMap.h"

CTileMap::CTileMap(int ID, LPCWSTR FilePath_tex, LPCWSTR FilePath_data, int Map_rows, int  Map_cols, int Num_row_read, int Num_col_read, int Tile_width, int Tile_height, float main_start, float main_end, float hidden_start, float hidden_end)
{
	this->Id = ID;

	this->MapPNG = FilePath_tex;
	this->MapFilePath = FilePath_data;

	this->Num_Rows = Map_rows;
	this->Num_Cols = Map_cols;

	this->num_row_read = Num_row_read;
	this->num_col_read = Num_col_read;
	
	this->Tile_Width = Tile_width;
	this->Tile_Height = Tile_height;

	this->mainStart_x = main_start;
	this->mainEnd_x = main_end;

	this->hiddenStart_x = hidden_start;
	this->hiddenEnd_x = hidden_end;

	LoadMap();
	Load();
}
void CTileMap::Load()
{
	DebugOut(L"[INFO] Start loading map resources from : %s \n", MapFilePath);
	ifstream f;
	f.open(MapFilePath);
	if (f.fail())
	{
		DebugOut(L"[ERROR] TileMap::Load_MapData failed: ID=%d", Id);
		f.close();
		return;
	}
	for (int i = 0; i < Num_Rows; i++)
	{
		for (int j = 0; j < Num_Cols; j++)
			f >> tilemap[i][j];
	}

	f.close();

	DebugOut(L"[INFO] Done loading map resources %s\n", MapFilePath);
}

void CTileMap::LoadMap()
{
	CTextures* texture = CTextures::GetInstance();
	texture->Add(Id, MapPNG, D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texTileMap = texture->Get(Id);	

	int id_sprite = 1;
	for (UINT i = 0; i < num_row_read; i++)
	{
		for (UINT j = 0; j < num_col_read; j++)
		{
			int id_Sprite = Id + id_sprite;
			sprites->Add(id_Sprite, Tile_Width * j, Tile_Height * i, Tile_Width * (j + 1), Tile_Height * (i + 1), texTileMap);
			id_sprite = id_sprite + 1;
		}
	}

}

void CTileMap::Draw()
{
	int firstcol = (int)CGame::GetInstance()->GetCamPosX() / 16;
	int lastcol = firstcol + (SCREEN_WIDTH / 16);

	for (UINT i = 0; i < Num_Rows; i++)
	{
		for (UINT j = firstcol; j <= lastcol; j++)
		{
			float x = Tile_Width * (j - firstcol) + CGame::GetInstance()->GetCamPosX() - (int)CGame::GetInstance()->GetCamPosX() % Tile_Width;
			float y = Tile_Height * i /*+ CGame::GetInstance()->GetCamPosY() - (int)CGame::GetInstance()->GetCamPosY() % Tile_Height*/;

			sprites->Get(tilemap[i][j] + Id)->Draw( x, y);
		}
	}
}

CTileMap::~CTileMap()
{
}