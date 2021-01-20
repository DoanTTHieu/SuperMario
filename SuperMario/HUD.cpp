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
	background->Draw(position.x, position.y + board_margin_y);

	board->at(0)->Render(position.x + MARGINLEFT, position.y + board_margin_y);

	// scores
	text.Render(IntToChar(player->GetScore(), 7), { position.x + score_margin_x, position.y + score_margin_y });

	// money
	int coin = player->GetCoin();
	string strCoin = to_string(coin);
	int length = strCoin.length();
	text.Render(IntToChar(player->GetCoin(), length), { position.x+ time_margin_x, position.y + money_margin_y });

	// player's life
	text.Render(IntToChar(player->GetLife(), 1), { position.x+ left_margin_x, position.y + score_margin_y });

	// time
	text.Render(IntToChar(remainingTime, 3), { position.x + time_margin_x, position.y + score_margin_y });

	// item
	for (size_t i = 0; i < player->cards.size(); i++)
	{
		switch (i)
		{
		case 0:
			card->at(player->cards.at(i))->Render(position.x + card_1_margin_x, position.y + card_margin_y);
			break;
		case 1:
			card->at(player->cards.at(i))->Render(position.x + card_2_margin_x, position.y + card_margin_y);
			break;
		case 2:
			card->at(player->cards.at(i))->Render(position.x + card_3_margin_x, position.y + card_margin_y);
			break;
		}
	}
	//world map
	text.Render(IntToChar(1, 1), { position.x + left_margin_x, position.y + money_margin_y });

	//speedbar
	speedBar->Render(position.x+ speedbar_margin_x, position.y + money_margin_y, player->vx);
}

