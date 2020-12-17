#include "HUD.h"
#include "Utils.h"

CHUD::CHUD()
{
	this->background = CAnimationSets::GetInstance()->Get(1101);
	
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

void CHUD::Render(D3DXVECTOR2 position, CMario * player)
{
	background->at(0)->Render(0, 432);

	// scores
	text.Render(IntToChar(player->GetScore(), 7), { 51, 448 });

	// money
	int coin = player->GetCoin();
	string strCoin = to_string(coin);
	int length = strCoin.length();
	text.Render(IntToChar(player->GetCoin(), length), { 132, 439 });

	// player's life
	text.Render(IntToChar(player->GetLife(), 1), { 20, 448});

	// time
	//text.Render(IntToChar(player->GetTime(), 3), { 141, 3 });

	//// item
	//GetItemSprite()->Draw(165, 31);

	//world map

	//speedbar

}
