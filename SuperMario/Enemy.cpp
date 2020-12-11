#include "Enemy.h"

void CEnemy::DieByCrush()
{
	SetState(EState::DIE_BY_CRUSH);
	dieByCrushTimer->Start();
}

void CEnemy::DieByAttack()
{
	if (this->GetType() != Type::PIRANHA_PLANT && this->GetType() != Type::VENUS_FIRE_TRAP)
		SetState(EState::DIE_BY_ATTACK);
	else
		SetState(STATE_DESTROYED);
	//dieTimer->Start();
}