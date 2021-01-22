#include "Grid.h"

CGrid::CGrid(int map_width, int map_height, int cell_width, int cell_height)
{
	this->cell_width = cell_width;
	this->cell_height = cell_height;

	this->map_width = map_width;
	this->map_height = map_height;

	this->nums_col = this->map_width / this->cell_width + 1;//210 and 161 
	this->nums_row = this->map_height / this->cell_height + 1;//27:6=4 + 1

	cells.resize(nums_row);
	for (int i = 0; i < nums_row; i++)
		cells[i].resize(nums_col);

	Clear(nums_row, nums_col);
}

void CGrid::Clear(int nums_row, int nums_col)
{
	for (int i = 0; i < nums_row; i++)
		for (int j = 0; j < nums_col; j++)
			cells[i][j].clear();
}

//update lai gridMoving: do quai duy chuyen
void CGrid::UpdateGrid(vector<LPGAMEOBJECT> list)
{
	Clear(nums_row, nums_col);

	for (int i = 0; i < list.size(); i++)
	{
		float l, t, r, b;
		list[i]->GetBoundingBox(l, t, r, b);
		if (b > (map_height * 16) || l<0 || r>(map_width * 16))
			list[i]->SetState(STATE_DESTROYED);

		int top = int(t / (cell_height * 16));
		int bot = ceil(b / (cell_height * 16));
		int left = int(l / (cell_width * 16));
		int right = ceil(r / (cell_width * 16));

		if (list[i]->GetState() != STATE_DESTROYED)
			for (int row = top; row < bot; row++)
				for (int col = left; col < right; col++)
					cells[row][col].push_back(list[i]);
	}
}

void CGrid::pushNewObjIntoGrid(LPGAMEOBJECT obj)
{
	float t,l,r,b;
	obj->GetBoundingBox(l, t, r, b);
	int top = int(t / (cell_height * 16));
	int bot = ceil(b / (cell_height * 16));
	int left = int(l / (cell_width * 16));
	int right = ceil(r / (cell_width * 16));

	if (obj->GetState() != STATE_DESTROYED)
		for (int row = top; row < bot; row++)
			for (int col = left; col < right; col++)
				cells[row][col].push_back(obj);
}

void CGrid::pushObjIntoGrid(LPGAMEOBJECT obj, int row, int col)
{
	cells[row][col].push_back(obj);
}

void CGrid::ResetCamGrid(vector<LPGAMEOBJECT>& list)
{
	for (int i = 0; i < list.size(); i++)
		list[i]->isInCam = false;
}

void CGrid::GetObjFromGrid(vector<LPGAMEOBJECT>& list)
{
	int firstCol = (int)(CGame::GetInstance()->GetCamPosX() / (cell_width * 16));
	int lastCol = ceil((CGame::GetInstance()->GetCamPosX() + SCREEN_WIDTH) / (cell_width * 16));

	for (int i = 0; i < nums_row; i++)
	{
		for (int j = firstCol; j < lastCol; j++)
		{
			for (int k = 0; k < cells[i][j].size(); k++)
			{
				if (!cells[i][j][k]->isInCam && cells[i][j][k]->GetState()!=STATE_DESTROYED)
				{
					cells[i][j][k]->isInCam = true;
					list.push_back(cells[i][j][k]);
				}
			}
		}
	}
}

CGrid::~CGrid()
{
}
