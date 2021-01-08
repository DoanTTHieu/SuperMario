#include "P_Switch.h"
#include "Utils.h"
#include "Coin.h"

CP_Switch::CP_Switch(float x, float y)
{
	this->type = Type::P_SWITCH;
	this->x = x;
	this->y = y;
	this->start_y = y;
	state = STATE_ON;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(15));
}
CP_Switch::~CP_Switch()
{

}

void CP_Switch::Render()
{
	if (GetState() == STATE_ON)
		ani = P_SWITCH_ANI_ON;
	else
		ani = P_SWITCH_ANI_OFF;
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();

}

void CP_Switch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == STATE_DESTROYED||state == STATE_OFF)
		l = t = b = r = 0;
	else
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
}

void CP_Switch::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	vector<LPGAMEOBJECT> bronzeBricks;

	if (checkTurn)
	{
		checkTurn = false;

		for (int i = 0; i < objects->size(); i++)
		{
			if (objects->at(i)->GetType() == Type::BRICK)
			{
				CBrick* brick = dynamic_cast<CBrick*>(objects->at(i));
				if (brick->GetBrickType() == BrickType::bronze && brick->GetState() != BRICK_STATE_HIDDEN)
				{
					brick->SetState(BRICK_STATE_HIDDEN);
				}
			}
		}
	}

	if (changeTimer && changeTimer->IsTimeUp())
	{
		//tien bien lai thanh gach
		for (int i = 0; i < objects->size(); i++)
		{
			if (dynamic_cast<CBrick*>(objects->at(i)))
			{
				CBrick* brick = dynamic_cast<CBrick*>(objects->at(i));
				if (brick->GetBrickType() == BrickType::bronze)
				{
					if (brick->GetState() == BRICK_STATE_HIDDEN)
					{
						brick->SetState(STATE_NORMAL);
						//brick->Set
					}

				}
			}
		}

		changeTimer->Stop();
	}


	
}

void CP_Switch::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STATE_OFF:
		changeTimer->Start();
		//gach bien thanh tien
		checkTurn = true;
		break;
	case STATE_ON:
		break;
	default:
		break;
	}
}
