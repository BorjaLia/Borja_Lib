#include "BorjaLib.h"

namespace con {

	// has the console info been found?
	bool isConInfoSet = false;

	void UpdateConInfo()
	{
		//hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		isConInfoSet = true;
	}

	void SetColor(int foreground, int background)
	{
		if (!isConInfoSet) {
			UpdateConInfo();
		}

		int color = 0;
		color = foreground + (background * 16);

		if (color == 0) {
			color = 0x007;
		}

		//SetConsoleTextAttribute(hCon, color);
	}

	bool GoToxy(int x, int y)
	{
		//COORD dwPos;
		//dwPos.X = x;
		//dwPos.Y = y;

		int x1 = x;
		int y1 = y;
		return x1 == y1;

		/*if (!isConInfoSet) {
			UpdateConInfo();
		}*/


		//if (SetConsoleCursorPosition(hCon, dwPos)) {
		//return true;
		//}
		//else {
		//return false;
		//}
	}

	bool GoToxy(float x, float y)
	{
		return GoToxy(static_cast<int>(x), static_cast<int>(y));
	}

	bool GoToxy(vec::Vector2 v)
	{
		return GoToxy(v.x, v.y);
	}

	int GetCursorLine()
	{
		if (!isConInfoSet) {
			UpdateConInfo();
		}
		//CONSOLE_SCREEN_BUFFER_INFO csbi;
		//GetConsoleScreenBufferInfo(hCon, &csbi);

		//return csbi.dwCursorPosition.Y;
		return 0;
	}

	void Clear()
	{
		system("CLS");
	}

	void DrawVector(vec::Vector2 v, vec::Vector2 pos, int borderSize)

	{
		std::string type = "NULL";

		if (v.isCartesian()) {
			type = "Cartesian";
		}
		if (v.isCircular()) {
			type = "Circular";
		}

		GoToxy(pos.x - borderSize, pos.y - (borderSize / 2) - 6);
		std::cout << "Vector:" << type << "              \n";
		GoToxy(pos.x - borderSize, pos.y - (borderSize / 2) - 5);
		std::cout << "(x,y): \t" << v << "                             \n";
		GoToxy(pos.x - borderSize, pos.y - (borderSize / 2) - 4);
		if (v.isCartesian()) {
			std::cout << "Circular: \t" << v.asCircularDegree() << "                     \n";
		}
		else if (v.isCircular()) {
			std::cout << "Cartesian: \t" << v.asCartesian() << "                     \n";
		}
		GoToxy(pos.x - borderSize, pos.y - (borderSize / 2) - 3);

		v.toCartesian();

		GoToxy(pos.x, pos.y);
		std::cout << "O";
		for (int i = 0; i < v.magnitude() && i <= borderSize; i++)
		{
			GoToxy(pos.x - (v.normalized().x * -i), pos.y - (v.normalized().y * i / 2));
			std::cout << ".";
		}
		if (v.magnitude() <= borderSize) {
			GoToxy(pos.x - (v.normalized().x * -v.magnitude()), pos.y - (v.normalized().y * v.magnitude() / 2));
			std::cout << "X";
		}
	}

	void ClearVector(vec::Vector2 v, vec::Vector2 pos, int borderSize)
	{
		GoToxy(pos.x, pos.y);
		std::cout << " ";
		for (int i = 0; i < v.magnitude() && i <= borderSize; i++)
		{
			GoToxy(pos.x - (v.normalized().x * -i), pos.y - (v.normalized().y * i / 2));
			std::cout << " ";
		}
		if (v.magnitude() <= borderSize) {
			GoToxy(pos.x - (v.normalized().x * -v.magnitude()), pos.y - (v.normalized().y * v.magnitude() / 2));
			std::cout << " ";
		}
	}

	void DrawBorder(vec::Vector2 pos, float borderSize)
	{
		vec::Vector2 border = { 0,0 };
		border.y = borderSize + 3.0f;

		for (float i = 0; i < 360; i += 0.5f)
		{
			border.rotateDegree(i);
			GoToxy(pos.x - border.x, pos.y - border.y / 2);
			std::cout << "+";
		}
	}
}