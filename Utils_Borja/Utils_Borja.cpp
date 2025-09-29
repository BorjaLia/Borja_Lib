#include "Utils_Borja.h"

// has the random seed been set?
bool randomSeedSet = false;

// has the console info been found?
bool isConInfoSet = false;
//console info
//HANDLE hCon;

bool ctrl::IsMouseDown(ButtonMouse mouseButton)
{
	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		return IsMouseButtonDown((int)mouseButton);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		return slGetMouseButton((int)mouseButton);
#endif
		break;
	}
	default:
		break;
	}
}

bool ctrl::IsKeyHeldDown(Key key)
{
	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		return IsKeyDown((int)key);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		return slGetKey((int)key);
#endif
		break;
	}
	default:
		break;
	}

	return false;
}

ctrl::Key ctrl::GetKeyDown()
{

	ctrl::Key key = ctrl::Key::NULL_KEY;

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		for (int i = 0; i < (int)ctrl::Key::SIZE; i++)
		{
			if (IsKeyDown(i)) {
				key = (ctrl::Key)i;
			}
		}
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		for (int i = 0; i < (int)ctrl::Key::SIZE; i++)
		{
			;
			if (slGetKey(i)) {
				key = (ctrl::Key)i;
			}
		}
#endif
		break;
	}
	default:
		break;
	}

	return key;
}

ctrl::ButtonMouse menuSelectionMouseButton = ctrl::ButtonMouse::LMB;

void utl::Clamp(float& num, float min, float max)
{
	if (num < min) {
		num = min;
	}
	if (num > max) {
		num = max;
	}
}

float utl::Clamped(float num, float min, float max)
{
	float n = num;
	if (num < min) {
		n = min;
	}
	if (num > max) {
		n = max;
	}
	return n;
}

float utl::Abs(float& num)
{
	if (num < 0) {
		num *= -1.0f;
	}
	return num;
}

char utl::LastKeyPressed()
{
	if (_kbhit()) {
		return _getch();
	}
	return false;
}

float utl::RadianToDegree(float angle)
{
	return (angle * 180 / PI);
}

float utl::DegreeToRadian(float angle)
{
	return (angle * PI / 180);
}

float utl::MapToRange(float& num, float min, float max)
{
	min *= 100;
	max *= 100;

	num = ((int)(num - min) % (int)(2 * (max - min + 1))) % (int)(max - min + 1) + min;
	num /= 100;
	return num;
}

std::string utl::SearchInFile(const char* filename, const char* search)
{
	std::ifstream file(filename);
	std::string line;
	std::string filter = "";
	std::string result = "";

	bool onInfo = true;
	bool shouldSkip = false;

	while (std::getline(file, line)) {
		onInfo = true;
		filter = "";
		result = "";
		int i = 0;
		int size = line.size();
		while (i < size)
		{
			char c = line[i];
			char nc = line[i + 1];
			if (line[0] == '#') {
				//i = size;
				shouldSkip = true;
			}
			if (onInfo && !shouldSkip) {
				filter.push_back(c);
			}
			else if (!shouldSkip) {
				result.push_back(c);
			}
			shouldSkip = false;
			if (nc == '=') {
				onInfo = false;
				shouldSkip = true;
			}
			else if (nc == ' ') {
				shouldSkip = true;
			}
			if (nc == '|') {
				i = size;
			}
			i++;
		}
		if (filter == search) {
			return result;
		}
	}
	return "NONE";
}

bool utl::SaveToFile(const char* filename, const char* filter, std::string info)
{
	std::ifstream file(filename);
	std::string line;
	std::string settings = "";

	bool saved = false;

	while (std::getline(file, line)) {
		std::string newLine = line;

		if (!line.empty() && line[0] != '#') {
			size_t eqPos = line.find('=');
			if (eqPos != std::string::npos) {
				std::string key = line.substr(0, eqPos);
				while (!key.empty() && key.back() == ' ')
					key.pop_back();

				if (key == filter) {
					size_t commentPos = line.find('|', eqPos);
					if (commentPos != std::string::npos) {
						newLine = key + " = " + info + " " + line.substr(commentPos);
					}
					else {
						newLine = key + " = " + info;
					}
					saved = true;
				}
			}
		}
		settings.append(newLine + "\n");
	}
	file.close();

	std::ofstream outFile(filename, std::ios::trunc);

	outFile << settings;
	outFile.close();

	return saved;
}

bool utl::SaveToFile(const char* filename, const char* filter, int info)
{
	return SaveToFile(filename, filter, std::to_string(info));
}

//bool utl::SaveToFile(const char* filename, const char* filter, std::string info)
//{
//	std::ifstream file(filename);
//	std::string line;
//	std::string settings = "";
//
//	bool saved = false;
//
//	while (std::getline(file, line,'~')) {
//		
//		settings.append(line);
//	}
//	file.close();
//
//	std::remove(filename);
//
//	std::ofstream objetiveFile(filename);
//
//	objetiveFile << "HAII" << settings;
//
//	objetiveFile.close();
//
//	return saved;
//}


void rng::SetRandomSeed(time_t seed)
{
	if (seed == 0) {
		srand(time(nullptr));
	}
	else {
		srand(time(&seed));
	}
	randomSeedSet = true;
}

int rng::GetRandom(int min, int max)
{
	if (!randomSeedSet) {
		SetRandomSeed();
	}
	return (int)(rand() % (max - min + 1) + min);
}

float rng::GetRandomf(float min, float max, unsigned int accuracy)
{
	if (!randomSeedSet) {
		SetRandomSeed();
	}
	return (float)((rand() % ((int)(accuracy * max) - (int)(accuracy * min) + 1) + (int)(accuracy * min)) / accuracy);
}


vec::Vector3::Vector3(bool cartesian)
{
	isCartesianBool = cartesian;
	isSphericalBool = !isCartesianBool;

	x = 0;
	y = 0;
	z = 0;
}

vec::Vector3::Vector3(float x, float y, float z, bool cartesian)
{
	isCartesianBool = cartesian;
	isSphericalBool = !isCartesianBool;

	this->x = x;
	this->y = y;
	this->z = z;
}


vec::Vector2::Vector2(bool cartesian)
{
	isCartesianBool = cartesian;
	isCircularBool = !isCartesianBool;

	x = 0;
	y = 0;
}

vec::Vector2::Vector2(float x, float y, bool cartesian)
{
	isCartesianBool = cartesian;
	isCircularBool = !isCartesianBool;

	this->x = x;
	this->y = y;
}

void vec::Vector2::normalize()
{
	float magnitude = this->magnitude();

	if (magnitude == 0) {
		return;
	}

	x /= magnitude;
	y /= magnitude;
}

vec::Vector2 vec::Vector2::normalized()
{
	float magnitude = this->magnitude();

	if (magnitude == 0) {
		return { 0,0 };
	}

	vec::Vector2 v = *this;

	v.x /= magnitude;
	v.y /= magnitude;

	return v;
}

float vec::Vector2::magnitude()
{
	return sqrt(x * x + y * y);
}

float vec::Vector2::magnitude(float magnitude)
{
	this->normalize();
	*this *= magnitude;
	return this->magnitude();
}

float vec::Vector2::determinant(Vector2 v)
{
	return ((x * v.y) - (y * v.x));
}

void vec::Vector2::clamp(float max)
{
	if (this->magnitude() > max) {
		this->magnitude(max);
	}
}

void vec::Vector2::clamp(float min, float max)
{
	float magnitude = this->magnitude();

	if (magnitude < min) {
		this->magnitude(min);
	}
	if (magnitude > max) {
		this->magnitude(max);
	}
}

float vec::Vector2::angle(Vector2 v)
{
	Vector2 v1 = *this;
	float angle = 0;

	v1.normalize();
	v.normalize();

	angle = atan2f(v.determinant(v1), v * v1);

	if (angle < 0) {
		angle += 2.0f * PI;
	}

	return angle;
}

void vec::Vector2::rotate(float angle)
{
	vec::Vector2 v = *this;

	float cos = cosf(angle);
	float sin = sinf(angle);

	x = v.x * cos - v.y * sin;
	y = v.x * sin + v.y * cos;
}

vec::Vector2 vec::Vector2::rotated(float angle)
{
	vec::Vector2 v = *this;

	float cos = cosf(angle);
	float sin = sinf(angle);

	v.x = x * cos - y * sin;
	v.y = x * sin + y * cos;

	return v;
}

void vec::Vector2::rotateDegree(float angle)
{
	this->rotate(utl::DegreeToRadian(angle));
}

vec::Vector2 vec::Vector2::rotatedDegree(float angle)
{
	return this->rotated(utl::DegreeToRadian(angle));
}

void vec::Vector2::randomize()
{
	this->rotateDegree(rng::GetRandom(0, 360));
}

void vec::Vector2::randomize(float maxMagnitude)
{
	utl::Clamp(maxMagnitude, 1, maxMagnitude);
	*this = 1;
	this->magnitude(rng::GetRandomf(0, maxMagnitude));
	this->randomize();
}

void vec::Vector2::randomize(float minMagnitude, float maxMagnitude)
{
	utl::Abs(minMagnitude);
	utl::Clamp(minMagnitude, 1, maxMagnitude);
	utl::Clamp(maxMagnitude, minMagnitude, maxMagnitude);
	*this = 1;
	this->magnitude(rng::GetRandomf(minMagnitude, maxMagnitude));
	this->randomize();
}

bool vec::Vector2::isCartesian()
{
	return isCartesianBool;
}

bool vec::Vector2::setAsCartesian()
{
	if (isCartesianBool) {
		return false;
	}
	isCartesianBool = true;
	isCircularBool = !isCartesianBool;
	return true;
}

bool vec::Vector2::isCircular()
{
	return isCircularBool;
}

bool vec::Vector2::setAsCircular()
{
	if (isCircularBool) {
		return false;
	}
	isCircularBool = true;
	isCartesianBool = !isCircularBool;
	return true;
}

vec::Vector2 vec::Vector2::asCircular()
{
	return vec::Vector2(this->magnitude(), this->angle());
}

vec::Vector2 vec::Vector2::asCircularDegree()
{
	return vec::Vector2(this->magnitude(), utl::RadianToDegree(this->angle()));
}

vec::Vector2 vec::Vector2::toCircular()
{
	if (isCircularBool) {
		return *this;
	}
	isCircularBool = true;
	isCartesianBool = !isCircularBool;
	return *this = vec::Vector2(this->magnitude(), this->angle());
}

vec::Vector2 vec::Vector2::toCircularDegree()
{
	if (isCircularBool) {
		return *this;
	}
	isCircularBool = true;
	isCartesianBool = !isCircularBool;
	return *this = vec::Vector2(this->magnitude(), utl::RadianToDegree(this->angle()));
}

vec::Vector2 vec::Vector2::asCartesian()
{
	return vec::Vector2(x * cosf(y), x * sinf(y));
}

vec::Vector2 vec::Vector2::asCartesianDegree()
{
	return vec::Vector2(x * cosf(utl::DegreeToRadian(y)), x * sinf(utl::DegreeToRadian(y)));
}

vec::Vector2 vec::Vector2::toCartesian()
{
	if (isCartesianBool) {
		return *this;
	}
	isCartesianBool = true;
	isCircularBool = !isCartesianBool;
	return *this = vec::Vector2(x * cosf(y), x * sinf(y));
}

vec::Vector2 vec::Vector2::toCartesianDegree()
{
	if (isCartesianBool) {
		return *this;
	}
	isCartesianBool = true;
	isCircularBool = !isCartesianBool;
	return *this = vec::Vector2(x * cosf(utl::DegreeToRadian(y)), x * sinf(utl::DegreeToRadian(y)));
}

std::ostream& vec::operator<<(std::ostream& os, const vec::Vector2& v)
{
	return os << v.x << " , " << v.y;
}


void con::UpdateConInfo()
{
	//hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	isConInfoSet = true;
}

void con::SetColor(int foreground, int background)
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

bool con::GoToxy(int x, int y)
{
	//COORD dwPos;
	//dwPos.X = x;
	//dwPos.Y = y;

	if (!isConInfoSet) {
		UpdateConInfo();
	}

	//if (SetConsoleCursorPosition(hCon, dwPos)) {
	return true;
	//}
	//else {
	return false;
	//}
}

bool con::GoToxy(vec::Vector2 v)
{
	return GoToxy(v.x, v.y);
}

int con::GetCursorLine()
{
	if (!isConInfoSet) {
		con::UpdateConInfo();
	}
	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	//GetConsoleScreenBufferInfo(hCon, &csbi);

	//return csbi.dwCursorPosition.Y;
	return 0;
}

void con::Clear()
{
	system("CLS");
}

void con::DrawVector(vec::Vector2 v, vec::Vector2 pos, int borderSize)

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

void con::ClearVector(vec::Vector2 v, vec::Vector2 pos, int borderSize)
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

void con::DrawBorder(vec::Vector2 pos, int borderSize)
{
	vec::Vector2 border = { 0,0 };
	border.y = borderSize + 3;

	for (float i = 0; i < 360; i += 0.5f)
	{
		border.rotateDegree(i);
		GoToxy(pos.x - border.x, pos.y - border.y / 2);
		std::cout << "+";
	}
}

bool rend::ChangeRenderer()
{
	switch (activeGraphics)
	{
	case rend::GraphicsLib::NONE:
		nextGraphics = rend::GraphicsLib::RAYLIB;
		break;
	case rend::GraphicsLib::RAYLIB:
		nextGraphics = rend::GraphicsLib::SIGIL;
		break;
	case rend::GraphicsLib::SIGIL:
		nextGraphics = rend::GraphicsLib::RAYLIB;
		break;
	default:
		return false;
		break;
	}

	utl::SaveToFile("Settings.txt", "graphics", (int)nextGraphics);

	return true;
}


void rend::OpenWindow(vec::Vector2 size, const char* title, bool fullScreen)
{
	std::string graphics = "NONE";
	switch ((rend::GraphicsLib)activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		std::cout << "NONE";
		break;
	}
	case rend::GraphicsLib::RAYLIB: {

		std::cout << "RAYLIB";
#ifdef HAS_RAYLIB
		graphics = title;
		graphics.append(" - RAYLIB");
		SetWindowState(FLAG_WINDOW_RESIZABLE);
		InitWindow(size.x, size.y, graphics.c_str());
		int monitor = GetCurrentMonitor();
		SetWindowPosition((GetMonitorWidth(monitor) / 2) - windowSize.x / 2, (GetMonitorHeight(monitor) / 2) - windowSize.y / 2);
		if (fullScreen) {
			ToggleFullscreen();
		}

#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

		std::cout << "SIGIL";
#ifdef HAS_SIGIL
		graphics = title;
		graphics.append(" - SIGIL");
		slWindow(size.x, size.y, graphics.c_str(), fullScreen);
#endif
		break;
	}
	default:
		break;
	}
}

bool rend::ShouldExit()
{
	switch ((rend::GraphicsLib)activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		return WindowShouldClose();
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		return slShouldClose();
#endif
		break;
	}
	default:
		break;
	}
}

void rend::Close()
{
	switch ((rend::GraphicsLib)activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		CloseWindow();
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		slClose();
#endif
		break;
	}
	default:
		break;
	}
}

vec::Vector2 rend::GetWindowSize()
{
	vec::Vector2 size = { 1,1 };
	switch (activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB

		size = { (float)GetScreenWidth(),(float)GetScreenHeight() };
		//utl::Clamp(size.x, 1, (16.0f / 9.0f) * size.y);
		//utl::Clamp(size.y, 1, (9.0f / 16.0f) * size.x);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		size = windowSize;
#endif
		break;
	}
	default:
		break;
	}

	windowRatio = size.y / size.x;

	return size;
}

vec::Vector2 rend::GetMousePos()
{
	vec::Vector2 pos = { 0,0 };

	switch (activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		pos = { (float)GetMousePosition().x / windowSize.x,(windowSize.y - (float)GetMousePosition().y) / windowSize.y };
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		pos = { (float)slGetMouseX() / windowSize.x,(float)slGetMouseY() / windowSize.y };
		//return { (float)slGetMouseX() / windowSize.x,(float)slGetMouseY() / windowSize.y };
#endif
		break;
	}
	default:
		break;
	}
	return pos;
}

float rend::GetDeltaTime()
{
	switch (activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		return GetFrameTime();
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		return slGetDeltaTime();
#endif
		break;
	}
	default:
		break;
	}
}

rend::GraphicsLib rend::activeGraphics = rend::GraphicsLib::NONE;
rend::GraphicsLib rend::nextGraphics = rend::GraphicsLib::NONE;

float rend::deltaTime = 0;

vec::Vector2 rend::windowSize = { 1600,900 };
float rend::windowRatio = (9.0f / 16.0f);

std::string rend::mouseSprite = "";
vec::Vector2 rend::mousePos = { 0,0 };

vec::Vector2 drw::PercentToScreen(vec::Vector2 vec)
{
	return vec::Vector2(vec.x * rend::windowRatio, vec.y);
}


void drw::Clear(Color color)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		ClearBackground(color);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		slSetBackColor(color.r, color.g, color.b);
#endif
		break;
	}
	default:
		break;
	}
}

bool drw::InitSpriteData(rend::SpriteData& spriteData)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		spriteData.id = LoadTexture(spriteData.file.c_str()).id;
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		spriteData.id = slLoadTexture(spriteData.file.c_str());
#endif
		break;
	}
	default:
		break;
	}

	return spriteData.id;
}

bool drw::DeInitSpriteData(rend::SpriteData& spriteData)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		Texture2D texture;
		texture.id = spriteData.id;
		UnloadTexture(texture);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL

#endif
		break;
	}
	default:
		break;
	}
	spriteData.id = 0;
	return !spriteData.id;
}

void drw::Begin()
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		BeginDrawing();
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL

#endif
		break;
	}
	default:
		break;
	}
}

void drw::End()
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		EndDrawing();
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		slRender();
#endif
		break;
	}
	default:
		break;
	}
}

bool drw::Sprite(rend::SpriteData sprite, vec::Vector2 pos, vec::Vector2 size, vec::Vector2 offset, Color color)
{
	if (sprite.id == 0) {
		return false;
	}

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		Texture2D texture;
		texture.id = sprite.id;
		texture.width = size.x * rend::windowSize.x;
		texture.height = size.y * rend::windowSize.y;
		DrawTexture(texture, pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * size.x / 2, rend::windowSize.y * (1.0f - pos.y) + (1.0f - offset.y * rend::windowSize.y) - rend::windowSize.y * size.y / 2, color);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		slSetForeColor(1, 1, 1, 1);
		slSprite(sprite.id, pos.x * rend::windowSize.x + offset.x * rend::windowSize.x, pos.y * rend::windowSize.y + offset.y * rend::windowSize.y, size.x * rend::windowSize.x, size.y * rend::windowSize.y);
#endif
		break;
	}
	default:
		break;
	}
}

void drw::Text(const char* text, rend::TextData& textData, vec::Vector2 pos, int fontSize, vec::Vector2 offset, Color color)
{
	vec::Vector2 textSize = fontSize;

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {
		if (!textData.raylibInitialized) {
			fnt::Init(textData);
		}
		textSize.x = MeasureText(text, fontSize) / rend::windowSize.x;
		float tempFontSize = fontSize * 1.5f;
		textSize.y = tempFontSize / rend::windowSize.y;
		DrawTextPro(textData.font, text, { pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * textSize.x / 3, rend::windowSize.y * (1.0f - pos.y) + (1.0f - offset.y * rend::windowSize.y) - rend::windowSize.y * textSize.y / 2 }, { textData.origin.x,textData.origin.y }, textData.rotation, tempFontSize, textData.spacing, color);
		break;
	}
	case rend::GraphicsLib::SIGIL: {

		if (!textData.slInitialized) {
			fnt::Init(textData);
		}
		slSetFont(textData.id, fontSize);
		slSetFontSize(fontSize);
		slSetForeColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255);
		textSize.x = slGetTextWidth(text) / rend::windowSize.x;
		textSize.y = slGetTextHeight(text) / rend::windowSize.y;
		//slSetTextAlign(SL_ALIGN_CENTER);
		//slText(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x, rend::windowSize.y * (1.0f - pos.y) + offset.y * rend::windowSize.y, text);
		slText(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * textSize.x / 2, rend::windowSize.y * pos.y + offset.y * rend::windowSize.y - rend::windowSize.y * textSize.y / 2, text);
		break;
	}
	default:
		break;
	}
}

void drw::Triangle(vec::Vector2 p1, vec::Vector2 p2, vec::Vector2 p3, Color color)
{

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

		break;
	}
	case rend::GraphicsLib::SIGIL: {

		break;
	}
	default:
		break;
	}
}

void drw::Rectangle(vec::Vector2 pos, vec::Vector2 size, Color color, vec::Vector2 offset)
{
	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		DrawRectangle(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * size.x / 2, rend::windowSize.y * (1.0f - pos.y) + (1.0f - offset.y * rend::windowSize.y) - rend::windowSize.y * size.y / 2, size.x * rend::windowSize.x, size.y * rend::windowSize.y, color);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		slSetForeColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255);
		slRectangleFill(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x, pos.y * rend::windowSize.y + offset.y * rend::windowSize.y, size.x * rend::windowSize.x, size.y * rend::windowSize.y);
#endif
		break;
	}
	default:
		break;
	}
}

void drw::Circle(vec::Vector2 pos, vec::Vector2 size, Color color)
{

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

		DrawEllipse(pos.x * rend::windowSize.x, (1.0f - pos.y) * rend::windowSize.y, size.x * rend::windowSize.x, size.y * rend::windowSize.y, color);
		break;
	}
	case rend::GraphicsLib::SIGIL: {
		slSetForeColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255);
		slCircleFill(pos.x * rend::windowSize.x, pos.y * rend::windowSize.y, size.x * rend::windowSize.x, 100);
		break;
	}
	default:
		break;
	}
}

//void drw::ButtonClick(btn::ButtonClick button)
//{
//
//	switch (button.type)
//	{
//	case btn::Type::Normal: {
//		if (button.beingHeld) {
//			button.offset += button.clickedOffset * button.size.y;
//		}
//		if (button.useSprite) {
//			drw::Sprite(button.activeSprite, button.pos, button.size, button.offset);
//		}
//		else {
//			drw::Rectangle(button.pos, button.size, button.activeColor, button.offset);
//			drw::Text(button.text.c_str(), button.pos, button.fontSize, button.offset, button.textColor);
//		}
//		break;
//	}
//	case btn::Type::Checkbox: {
//
//		if (button.beingHeld) {
//			button.offset += button.clickedOffset * button.size.y;
//		}
//		if (button.value) {
//			button.text = "X";
//		}
//		else {
//			button.text = "";
//		}
//
//		if (button.useSprite) {
//			drw::Sprite(button.activeSprite, button.pos, button.size, button.offset);
//		}
//		else {
//			drw::Rectangle(button.pos, button.size, button.activeColor, button.offset);
//			drw::Text(button.text.c_str(), button.pos, button.fontSize, button.offset, button.textColor);
//		}
//		break;
//	}
//	case btn::Type::Slider: {
//		if (button.useSprite) {
//			drw::Sprite(button.activeSprite, button.pos, button.size, button.offset);
//		}
//		else {
//			drw::Rectangle(button.pos, button.size, button.activeColor, button.offset);
//			drw::Rectangle(button.pos, { button.size.x * 8 / 10,button.size.y / 3 }, button.textColor, button.offset);
//		}
//		break;
//	}
//	case btn::Type::DropDown: {
//
//		break;
//	}
//	case btn::Type::Selector: {
//
//		break;
//	}
//	default:
//		break;
//	}
//}

//void drw::Container(btn::Container container, btn::ButtonClick buttons[], int buttonsSize)
//{
//	for (int i = 0; i < buttonsSize; i++)
//	{
//		drw::ButtonClick(buttons[i]);
//	}
//}

void snd::StartAudioDevice()
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		InitAudioDevice();
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL

#endif
		break;
	}
	default:
		break;
	}
}

void snd::EndAudioDevice()
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		CloseAudioDevice();
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL

#endif
		break;
	}
	default:
		break;
	}
}

void snd::Init(rend::AudioData& audioData)
{

	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (audioData.raylibInitialized) {
			return;
		}
		audioData.sound = LoadSound(audioData.file.c_str());
		audioData.raylibInitialized = true;
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (audioData.slInitialized) {
			return;
		}
		audioData.soundFileID = slLoadWAV(audioData.file.c_str());
		audioData.slInitialized = true;
#endif
		break;
	}
	default:
		break;
	}
}

void snd::DeInit(rend::AudioData& audioData)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (!audioData.raylibInitialized) {
			return;
		}
		UnloadSound(audioData.sound);
		audioData.raylibInitialized = false;
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (!audioData.slInitialized) {
			return;
		}
		//audioData.soundFileID = -1;
		//audioData.slInitialized = false;
#endif
		break;
	}
	default:
		break;
	}
}

void snd::Play(rend::AudioData& audioData, bool loop)
{

	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (!audioData.raylibInitialized) {
			snd::Init(audioData);
		}
		PlaySound(audioData.sound);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (!audioData.slInitialized) {
			snd::Init(audioData);
		}
		if (loop) {
			audioData.id = slSoundLoop(audioData.soundFileID);
		}
		else {
			audioData.id = slSoundPlay(audioData.soundFileID);
		}
#endif
		break;
	}
	default:
		break;
	}
}

void snd::Pause(rend::AudioData& audioData, bool pause)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (!audioData.raylibInitialized) {
			snd::Init(audioData);
		}
		if (pause) {
			PauseSound(audioData.sound);
		}
		else {
			ResumeSound(audioData.sound);
		}
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (!audioData.slInitialized) {
			snd::Init(audioData);
		}
		if (pause) {
			slSoundPause(audioData.id);
		}
		else {
			slSoundPlay(audioData.id);
		}
#endif
		break;
	}
	default:
		break;
	}
}

void snd::Stop(rend::AudioData& audioData)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (!audioData.raylibInitialized) {
			snd::Init(audioData);
		}
		StopSound(audioData.sound);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (!audioData.slInitialized) {
			snd::Init(audioData);
		}
#endif
		break;
	}
	default:
		break;
	}
}

bool snd::IsPlaying(rend::AudioData& audioData)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (!audioData.raylibInitialized) {
			snd::Init(audioData);
		}
		IsSoundPlaying(audioData.sound);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (!audioData.slInitialized) {
			snd::Init(audioData);
		}
		//return slSoundPlaying(audioData.id);
#endif
		break;
	}
	default:
		break;
	}
	return false;
}

rend::AudioData buttonClickSound;
rend::AudioData buttonHoverSound;

bool upd::isMouseOver(vec::Vector2 pos, vec::Vector2 size)
{
	bool horizontalCollision = rend::mousePos.x > pos.x - size.x / 2 && rend::mousePos.x < pos.x + size.x / 2;
	bool verticalCollision = rend::mousePos.y > pos.y - size.y / 2 && rend::mousePos.y < pos.y + size.y / 2;

	return horizontalCollision && verticalCollision;
}

bool upd::isMouseClicking(vec::Vector2 pos, vec::Vector2 size)
{
	if (!isMouseOver(pos, size)) {
		return false;
	}

	return ctrl::IsMouseDown(ctrl::ButtonMouse::LMB);
}

//Color::Color()
//{
//	r = 255;
//	g = 255;
//	b = 255;
//	a = 255;
//}
//
//Color::Color(unsigned char r, unsigned char g, unsigned char b)
//{
//	this->r = r;
//	this->g = g;
//	this->b = b;
//}
//
//Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
//{
//	this->r = r;
//	this->g = g;
//	this->b = b;
//	this->a = a;
//}

rend::SpriteData rend::defaultContainerTexture = rend::SpriteData();

rend::SpriteData rend::defaultButtonMainTexture = rend::SpriteData();
rend::SpriteData rend::defaultButtonHoveredTexture = rend::SpriteData();

rend::AudioData rend::defaultButtonClickDownSound = rend::AudioData();
rend::AudioData rend::defaultButtonClickUpSound = rend::AudioData();
rend::AudioData rend::defaultButtonHoverSound = rend::AudioData();

rend::TextData rend::defaultFont = rend::TextData();

void btn::InitButtonDefaults()
{
	drw::InitSpriteData(rend::defaultContainerTexture);

	drw::InitSpriteData(rend::defaultButtonMainTexture);
	drw::InitSpriteData(rend::defaultButtonHoveredTexture);

	snd::Init(rend::defaultButtonClickDownSound);
	snd::Init(rend::defaultButtonClickUpSound);
	snd::Init(rend::defaultButtonHoverSound);

	fnt::Init(rend::defaultFont);
}

void btn::DeInitButtonDefaults()
{
	drw::DeInitSpriteData(rend::defaultContainerTexture);

	drw::DeInitSpriteData(rend::defaultButtonMainTexture);
	drw::DeInitSpriteData(rend::defaultButtonHoveredTexture);

	snd::DeInit(rend::defaultButtonClickDownSound);
	snd::DeInit(rend::defaultButtonClickUpSound);
	snd::DeInit(rend::defaultButtonHoverSound);

	fnt::DeInit(rend::defaultFont);
}

void btn::Init(Button& button, bool firstInit)
{
	if (firstInit) {
		button.isActive = true;
		button.isRendered = true;
		button.size = drw::PercentToScreen(button.size);
	}

	button.activeTexture = rend::defaultButtonMainTexture;

	button.mainTexture = rend::defaultButtonMainTexture;
	button.hoveredTexture = rend::defaultButtonHoveredTexture;

	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (button.raylibAudioInit) {
			return;
		}
		button.raylibAudioInit = true;
		snd::Init(button.clickedDownSound);
		snd::Init(button.clickedUpSound);
		snd::Init(button.hoveredSound);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (button.slAudioInit) {
			return;
		}
		button.slAudioInit = true;
		snd::Init(button.clickedDownSound);
		snd::Init(button.clickedUpSound);
		snd::Init(button.hoveredSound);
#endif
		break;
	}
	default:
		break;
	}
}

void btn::Init(Button buttons[], int buttonsSize)
{
	for (int b = 0; b < buttonsSize; b++)
	{
		Init(buttons[b]);
	}
}

void btn::Init(Button& button, Container& container, bool firstInit)
{
	Init(button);

	if (firstInit) {

		button.pos.x *= container.size.x;
		button.pos.y *= container.size.y;
		button.pos.x += container.pos.x - container.size.x / 2;
		button.pos.y += container.pos.y - container.size.y / 2;
	}
}

void btn::Init(Container& container, Button buttons[], int buttonsSize)
{
	for (int b = 0; b < buttonsSize; b++)
	{
		Init(buttons[b], container);
	}
}

void btn::Init(Container& container)
{
	container.size = drw::PercentToScreen(container.size);

	container.texture = rend::defaultContainerTexture;
}

bool btn::isHovered(btn::Button button)
{
	return upd::isMouseOver(button.pos, button.size);
}

bool btn::isClicked(btn::Button button)
{
	return upd::isMouseClicking(button.pos, button.size);
}

void btn::UpdateInput(Button& button) {

	button.isHoveredChange = false;

	if (isHovered(button)) {
		if (!button.isHovered) {
			button.isHoveredChange = true;
		}
		button.isHovered = true;
	}
	else {
		button.isHovered = false;
	}

	button.isClickedDownChange = false;
	button.isClickedUpChange = false;

	if (isClicked(button) && !button.startSignalTimer) {
		if (!button.isClicked) {
			button.isClickedDownChange = true;
		}
		button.isClicked = true;
	}
	else {
		if (button.isClicked) {
			button.isClickedUpChange = true;
		}
		button.isClicked = false;
	}

	if (button.isHovered) {
		button.activeTexture = button.hoveredTexture;
	}
	else {
		button.activeTexture = button.mainTexture;
	}

	button.signal = false;

	if (button.isClickedUpChange && button.isActive) {
		button.startSignalTimer = true;
	}
	if (button.startSignalTimer) {
		button.signalTimer += rend::deltaTime;
	}
	if (button.signalTimer > button.signalTimerLimit) {
		button.signal = true;
		button.startSignalTimer = false;
		button.signalTimer = 0;
	}
}

void btn::UpdateInput(Button buttons[], int buttonsSize)
{
	for (int b = 0; b < buttonsSize; b++)
	{
		UpdateInput(buttons[b]);
	}
}

void btn::Sound(Button button) {

	if (!button.isActive) {
		return;
	}
	if (button.isHoveredChange) {
		snd::Play(button.hoveredSound);
	}
	if (button.isClickedDownChange) {
		snd::Play(button.clickedDownSound);
	}
	if (button.isClickedUpChange) {
		snd::Play(button.clickedUpSound);
	}
}

void btn::Sound(Button buttons[], int buttonsSize)
{
	for (int b = 0; b < buttonsSize; b++)
	{
		Sound(buttons[b]);
	}
}

void btn::Draw(Button& button) {

	if (!button.isRendered) {
		return;
	}
	vec::Vector2 tempOffset = button.offset;
	if (button.isClicked) {
		button.offset += button.clickedOffset * button.size.y;
	}
	if (button.useSprite) {
		drw::Sprite(button.activeTexture, button.pos, button.size, button.offset);
	}
	else {
		drw::Rectangle(button.pos, button.size, button.activeColor, button.offset);
	}
	if (button.useText) {
		drw::Text(button.text.c_str(), button.textData, button.pos, button.fontSize, button.offset, button.textColor);
	}
	button.offset = tempOffset;
}

void btn::Draw(Container container)
{
	if (!container.isRendered) {
		return;
	}
	if (container.useTexture) {
		drw::Sprite(container.texture, container.pos, container.size, container.offset);
	}
	else {
		drw::Rectangle(container.pos, container.size, container.color, container.offset);
	}
}

void btn::Draw(Button buttons[], int buttonsSize)
{
	for (int i = 0; i < buttonsSize; i++)
	{
		Draw(buttons[i]);
	}
}

void btn::Draw(Container container, Button buttons[], int buttonsSize)
{
	Draw(container);
	Draw(buttons, buttonsSize);
}

void fnt::Init(rend::TextData& textData)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (textData.raylibInitialized) {
			return;
		}
		textData.font = LoadFont(textData.file.c_str());
		textData.raylibInitialized = true;
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (textData.slInitialized) {
			return;
		}
		textData.id = slLoadFont(textData.file.c_str());
		textData.slInitialized = true;
#endif
		break;
	}
	default:
		break;
	}
}

void fnt::DeInit(rend::TextData& textData)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		UnloadFont(textData.font);
		textData.raylibInitialized = false;
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (!textData.slInitialized) {
			return;
		}
		//audioData.soundFileID = -1;
		//audioData.slInitialized = false;
#endif
		break;
	}
	default:
		break;
	}
}