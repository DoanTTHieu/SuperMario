#include "Text.h"

void CText::RenderCharacter(char c, D3DXVECTOR2 position)
{
	character = CSprites::GetInstance()->Get(spriteID.at(c));
	character->Draw(position.x , position.y);
}

//void CText::Render(char* s, D3DXVECTOR2 position)
//{
//	for (int i = 0; i < strlen(s); i++)
//	{
//		RenderCharacter(s[i], { position.x + i * charWidth, position.y });
//	}
//}
void CText::Render(char* s, D3DXVECTOR2 position)
{
	for (int i = 0; i < strlen(s) / 2; i++)
	{
		char temp = s[i];
		s[i] = s[strlen(s) - i - 1];
		s[strlen(s) - i - 1] = temp;
	}

	for (int i = strlen(s)-1; i >= 0; i--)
	{
		RenderCharacter(s[i], { position.x - i * charWidth, position.y });
	}
}

CText::~CText()
{
}