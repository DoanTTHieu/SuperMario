#include "HUD.h"
#include "Utils.h"

CHUD::CHUD()
{
	this->board = CAnimationSets::GetInstance()->Get(1101);
	this->background = CSprites::GetInstance()->Get(1102);
	this->card = CAnimationSets::GetInstance()->Get(1130);
	speedBar = new CSpeedBar();
}

CHUD::~CHUD()
{
}

char* IntToChar(int value, int len = 10)
{
	char* c = new char[len + 1];
	c[len] = '\0';
	for (int i = len - 1; i >= 0; i--)
	{
		c[i] = value % 10 + 48;
		value = value / 10;
	}
	return c;
}

void CHUD::Render(D3DXVECTOR2 position, CMario * player, int remainingTime, int stage)
{
	background->Draw(position.x, position.y+192);

	board->at(0)->Render(position.x + MARGINLEFT, position.y + 192/*218*//*+ 432*/);

	// scores
	text.Render(IntToChar(player->GetScore(), 7), { position.x+100 + MARGINLEFT, /*448*/ position.y+207 });

	// money
	int coin = player->GetCoin();
	string strCoin = to_string(coin);
	int length = strCoin.length();
	text.Render(IntToChar(player->GetCoin(), length), { position.x+140 + MARGINLEFT, position.y + 199 /*439*/ });

	// player's life
	text.Render(IntToChar(player->GetLife(), 1), { position.x+ 38 + MARGINLEFT, position.y + 207/*448*/});

	// time
	text.Render(IntToChar(remainingTime, 3), { position.x + 141 + MARGINLEFT, position.y + 207 });

	// item
	for (size_t i = 0; i < player->cards.size(); i++)
	{
		switch (i)
		{
		case 0:
			card->at(player->cards.at(i))->Render(position.x + 141 + MARGINLEFT + 23, position.y + 198);
			break;
		case 1:
			card->at(player->cards.at(i))->Render(position.x + 141 + MARGINLEFT + 47, position.y + 198);
			break;
		case 2:
			card->at(player->cards.at(i))->Render(position.x + 141 + MARGINLEFT + 71, position.y + 198);
			break;
		}
	}
	//world map
	text.Render(IntToChar(stage, 1), { position.x + 38 + MARGINLEFT, position.y + 199 });

	//speedbar
	speedBar->Render(position.x+51 + MARGINLEFT, position.y + 199, player->vx);
}

