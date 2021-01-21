#include <iostream>
#include <fstream>
#include <vector>

#define map_width	210
#define map_height	27

#define cell_width	8
#define cell_height	6

#define mario_width		15
#define mario_height	27

#define goomba_width	16
#define goomba_height	15

#define para_goomba_width	20
#define para_goomba_height	24

#define koopa_width		15
#define koopa_height	26

#define piranha_width	16
#define piranha_height	24

#define trap_width		16
#define trap_height		32

#define green_trap_width		16
#define green_trap_height		24


#define brother_width	16
#define brother_height	24

#define brick_width		16
#define brick_height	16

#define pipe_width		32
#define pipe_height		48
#define short_pipe_height		32

#define lift_width		48
#define lift_height		16

#define SCENE_SECTION_UNKNOWN				-1
#define SCENE_SECTION_MARIO					1
#define SCENE_SECTION_GOOMBA				2
#define SCENE_SECTION_KOOPA					3
#define SCENE_SECTION_PIRANHA_PLANT			4
#define SCENE_SECTION_VENUS_FIRE_TRAP		5
#define SCENE_SECTION_BOOMERANG_BROTHER		6
#define SCENE_SECTION_COIN					7
#define SCENE_SECTION_GROUND				8
#define SCENE_SECTION_PIPE					9
#define SCENE_SECTION_BRICK					10
#define SCENE_SECTION_LAST_ITEM				11
#define SCENE_SECTION_LIFT					12

#define MAX_SCENE_LINE 1024

using namespace std;

vector<string> split(string line, string delimeter = "\t");
vector<string> split(string line, string delimeter);


void _ParseSection_MARIO(string line, ofstream& ofs);
void _ParseSection_GOOMBA(string line, ofstream& ofs);
void _ParseSection_KOOPA(string line, ofstream& ofs);
void _ParseSection_PIRANHA_PLANT(string line, ofstream& ofs);
void _ParseSection_VENUS_FIRE_TRAP(string line, ofstream& ofs);
void _ParseSection_BOOMERANG_BROTHER(string line, ofstream& ofs);
void _ParseSection_COIN(string line, ofstream& ofs);
void _ParseSection_GROUND(string line, ofstream& ofs);
void _ParseSection_PIPE(string line, ofstream& ofs);
void _ParseSection_BRICK(string line, ofstream& ofs);
void _ParseSection_LAST_ITEM(string line, ofstream& ofs);
void _ParseSection_LIFT(string line, ofstream& ofs);


wstring ToWSTR(string st);
void CalculateBBox(float x, float y, float w, float h, int& t, int& b, int& l, int& r)
{
	t = int(y / (cell_height * 16));
	b = ceil((y + h) / (cell_height * 16));
	l = int(x / (cell_width * 16));
	r = ceil((x + w) / (cell_width * 16));

}
//ground
void Calculate(float x, float y, float w, float h, int& t, int& b, int& l, int& r)
{
	t = int(y / (cell_height * 16));
	b = ceil((y + h * 16) / (cell_height * 16));
	l = int(x / (cell_width * 16));
	r = ceil((x + w * 16) / (cell_width * 16));
}

int main()
{
	ifstream f;
	f.open("in.txt");
	ofstream ofs;
	ofs.open("out.txt");
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[MARIO]") { section = SCENE_SECTION_MARIO;					continue; }
		if (line == "[GOOMBA]") { section = SCENE_SECTION_GOOMBA;				continue; }
		if (line == "[KOOPA]") { section = SCENE_SECTION_KOOPA;					continue; }
		if (line == "[PIRANHA_PLANT]") { section = SCENE_SECTION_PIRANHA_PLANT;		continue; }
		if (line == "[VENUS_FIRE_TRAP]") { section = SCENE_SECTION_VENUS_FIRE_TRAP;			continue; }
		if (line == "[BOOMERANG_BROTHER]") { section = SCENE_SECTION_BOOMERANG_BROTHER;		continue; }
		if (line == "[COIN]") { section = SCENE_SECTION_COIN;					continue; }
		if (line == "[GROUND]") { section = SCENE_SECTION_GROUND;				continue; }
		if (line == "[PIPE]") { section = SCENE_SECTION_PIPE;					continue; }
		if (line == "[BRICK]") { section = SCENE_SECTION_BRICK;					continue; }
		if (line == "[LAST_ITEM]") { section = SCENE_SECTION_LAST_ITEM;				continue; }
		if (line == "[LIFT]") { section = SCENE_SECTION_LIFT;					continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN;					continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_MARIO:				 _ParseSection_MARIO(line, ofs); break;
		case SCENE_SECTION_GOOMBA:				 _ParseSection_GOOMBA(line, ofs); break;
		case SCENE_SECTION_KOOPA:				 _ParseSection_KOOPA(line, ofs); break;
		case SCENE_SECTION_PIRANHA_PLANT:		 _ParseSection_PIRANHA_PLANT(line, ofs); break;
		case SCENE_SECTION_VENUS_FIRE_TRAP:		 _ParseSection_VENUS_FIRE_TRAP(line, ofs); break;
		case SCENE_SECTION_BOOMERANG_BROTHER:	 _ParseSection_BOOMERANG_BROTHER(line, ofs); break;
		case SCENE_SECTION_COIN:				 _ParseSection_COIN(line, ofs); break;
		case SCENE_SECTION_GROUND:				 _ParseSection_GROUND(line, ofs); break;
		case SCENE_SECTION_PIPE:				 _ParseSection_PIPE(line, ofs); break;
		case SCENE_SECTION_BRICK:				 _ParseSection_BRICK(line, ofs); break;
		case SCENE_SECTION_LAST_ITEM:			 _ParseSection_LAST_ITEM(line, ofs); break;
		case SCENE_SECTION_LIFT:				 _ParseSection_LIFT(line, ofs); break;
		}
	}

	f.close();
	ofs.close();
	system("pause");
}

vector<string> split(string line, string delimeter)
{
	vector<string> tokens;
	size_t last = 0; size_t next = 0;
	while ((next = line.find(delimeter, last)) != string::npos)
	{
		tokens.push_back(line.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(line.substr(last));

	return tokens;
}

/*
char * string to wchar_t* string.
*/
wstring ToWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring wstr(wcstring);

	// delete wcstring   // << can I ? 
	return wstr;
}

void _ParseSection_MARIO(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int t, b, l, r;
	CalculateBBox(x, y, mario_width, mario_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_GOOMBA(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int gtype = atoi(tokens[4].c_str());
	int t, b, l, r;
	if (gtype == 1)
		CalculateBBox(x, y, goomba_width, goomba_height, t, b, l, r);
	else
		CalculateBBox(x, y, para_goomba_width, para_goomba_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << gtype << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_KOOPA(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int type = atoi(tokens[4].c_str());
	int t, b, l, r;
	CalculateBBox(x, y, koopa_width, koopa_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << type << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_PIRANHA_PLANT(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int t, b, l, r;
	CalculateBBox(x, y, piranha_width, piranha_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_VENUS_FIRE_TRAP(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int type = atoi(tokens[4].c_str());
	int t, b, l, r;
	if (type == 1)
		CalculateBBox(x, y, green_trap_width, green_trap_height, t, b, l, r);
	else
		CalculateBBox(x, y, trap_width, trap_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << type << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_BOOMERANG_BROTHER(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int t, b, l, r;
	CalculateBBox(x, y, brother_width, brother_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_COIN(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int t, b, l, r;
	CalculateBBox(x, y, brick_width, brick_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_GROUND(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int w = atoi(tokens[4].c_str());
	int h = atoi(tokens[5].c_str());
	int i = atoi(tokens[6].c_str());
	int t, b, l, r;
	Calculate(x, y, w, h, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << w << "\t" << h << "\t" << i << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;

}
void _ParseSection_PIPE(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int type = atoi(tokens[4].c_str());
	int hasPortal = atoi(tokens[5].c_str());
	float des_x = strtof(tokens[6].c_str(), NULL);
	float des_y = strtof(tokens[7].c_str(), NULL);
	int dir = atoi(tokens[8].c_str());
	int t, b, l, r;
	if (type == 1)
		CalculateBBox(x, y, pipe_width, pipe_height, t, b, l, r);
	else
		CalculateBBox(x, y, pipe_width, short_pipe_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << type << "\t" << hasPortal << "\t" << des_x << "\t" << des_y << "\t" << dir << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_BRICK(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int btype = atoi(tokens[4].c_str());
	int contain = atoi(tokens[5].c_str());
	int sl = atoi(tokens[6].c_str());
	int t, b, l, r;
	CalculateBBox(x, y, brick_width, brick_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << btype << "\t" << contain << "\t" << sl << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_LAST_ITEM(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int t, b, l, r;
	CalculateBBox(x, y, brick_width, brick_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
void _ParseSection_LIFT(string line, ofstream& ofs)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);
	int ani_set_id = atoi(tokens[3].c_str());
	int t, b, l, r;
	CalculateBBox(x, y, lift_width, lift_height, t, b, l, r);
	ofs << object_type << "\t" << x << "\t" << y << "\t" << ani_set_id << "\t" << t << "\t" << b << "\t" << l << "\t" << r << endl;
}
