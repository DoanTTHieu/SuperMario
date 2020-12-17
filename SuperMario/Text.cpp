#include "Text.h"

void CText::RenderCharacter(char c, D3DXVECTOR2 position)
{
	character = CSprites::GetInstance()->Get(spriteID.at(c));
	character->Draw(position.x , position.y);
}

void CText::Render(char* s, D3DXVECTOR2 position)
{
	for (int i = 0; i < strlen(s); i++)
	{
		RenderCharacter(s[i], { position.x + i * charWidth, position.y });
	}
}

CText::~CText()
{
}