#pragma once
#include "Sprites.h"
#include "define.h"
#include "string"
#include "Textures.h"
#include "Game.h"
#include "Utils.h"
#include "map"

# define No_0 1110
# define No_1 1111
# define No_2 1112
# define No_3 1113
# define No_4 1114
# define No_5 1115
# define No_6 1116
# define No_7 1117
# define No_8 1118
# define No_9 1119

class CText
{
	unordered_map<char, int> spriteID{ { '0', No_0 }, { '1', No_1 }, { '2', No_2 }, { '3', No_3 }, { '4', No_4 }, { '5', No_5 }, { '6', No_6 }, { '7', No_7 }, { '8', No_8 }, { '9', No_9 } };

	LPSPRITE character;
	int charWidth = 8;
	int charHeight = 8;

public:
	~CText();
	CText()=default;

	void RenderCharacter(char c, D3DXVECTOR2 position);
	void Render(char* s, D3DXVECTOR2 position);
};

typedef CText* LPTEXT;
