#include "Brick.h"
#include "Item.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "Utils.h"
#include "BronzeBrickPiece.h"

CBrick::CBrick(float x, float y, int type, int typeItem, int sl)
{
	Btype = type;
	this->type = Type::BRICK;
	this->x = x;
	this->y = y;
	this->start_x = x;
	this->start_y = y;
	this->containItem = typeItem;
	this->sl = sl;
	isBroken = false;
	GetPosition(this->start_x, this->start_y);
	state = STATE_NORMAL;
}
CBrick::~CBrick()
{

}

void CBrick::Render()
{
	if (listPiece.size() > 0)
	{
		for (auto piece : listPiece)
			piece->Render();
		return;
	}

	if (Btype == BrickType::question_broken)
		ani = BRICK_ANI_BROKEN;
	else
	{
		if (state == BRICK_STATE_HIDDEN)
			ani = BRICK_ANI_HIDDEN;
		else
			ani = BRICK_ANI_NORMAL;
	}
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();

}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == STATE_DESTROYED|| state==STATE_BROKEN)
		l = t = b = r = 0;
	else
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT - 5;
	}
}

void CBrick::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	if (listPiece.size() > 0)
	{
		if (listPiece.size() == 4)
		{
			for (auto piece : listPiece)
				piece->Update(dt, objects);
		}
		else
			this->SetState(STATE_DESTROYED);
	}

	for (size_t i = 0; i < listPiece.size(); i++)
	{
		if (listPiece[i]->GetState() == STATE_DESTROYED)
		{
			listPiece.erase(listPiece.begin() + i);
			i--;
		}
	}

	if (y < (start_y - 5.0f) && vy<0)
	{
		vy = -vy;
	}
	if (y > start_y)
	{
		y = start_y;
		//vy = 0;
		SetState(STATE_NORMAL);
	}
	y += dy;
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STATE_DESTROYED:
		break;
	case STATE_BROKEN:
	{
		isBroken = true;
		CBronzeBrickPiece* piece1 = new CBronzeBrickPiece({ start_x + 8.0f, start_y }, 1, 2.2);
		CBronzeBrickPiece* piece2 = new CBronzeBrickPiece({ start_x + 8.0f, start_y + 8.0f }, 1, 1);
		CBronzeBrickPiece* piece3 = new CBronzeBrickPiece({ start_x, start_y }, -1, 2.2);
		CBronzeBrickPiece* piece4 = new CBronzeBrickPiece({ start_x, start_y + 8.0f }, -1, 1);
		listPiece = { piece1, piece2, piece3, piece4 };
	}
		break;
	case STATE_BEING_TOSSED:
		if(containItem==1 && sl==1)
			diddropItem = true;
		vy = -0.2f;
		DebugOut(L"CONTAIN: %d \n", sl);
		break;
	case STATE_NORMAL:
		vy = 0;
	default:
		break;
	}
}
