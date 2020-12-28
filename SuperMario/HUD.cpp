#include "HUD.h"
#include "Utils.h"

CHUD::CHUD()
{
	this->board = CAnimationSets::GetInstance()->Get(1101);
	this->background = CSprites::GetInstance()->Get(1102);
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

	board->at(0)->Render(position.x, position.y + 192/*218*//*+ 432*/);

	// scores
	text.Render(IntToChar(player->GetScore(), 7), { position.x+100, /*448*/ position.y+207 });

	// money
	int coin = player->GetCoin();
	string strCoin = to_string(coin);
	int length = strCoin.length();
	text.Render(IntToChar(player->GetCoin(), length), { position.x+140, position.y + 199 /*439*/ });

	// player's life
	text.Render(IntToChar(player->GetLife(), 1), { position.x+ 38, position.y + 207/*448*/});

	// time
	//text.Render(IntToChar(remainingTime, 3), { 141, 3 });
	text.Render(IntToChar(remainingTime, 3), { position.x + 141, position.y + 207 });

	//// item
	//GetItemSprite()->Draw(165, 31);

	//world map
	text.Render(IntToChar(stage, 1), { position.x + 38, position.y + 199 });

	//speedbar

}
