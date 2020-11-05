#include "Enemy.h"

void CEnemy::DieByCrush()
{
	SetState(EState::DIE_BY_CRUSH);
	dieByCrushTimer->Start();
}

void CEnemy::DieByAttack()
{
	SetState(EState::DIE_BY_ATTACK);
	//dieTimer->Start();
}