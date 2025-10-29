#include "BorjaLib.h"

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
	return false;
}

bool ctrl::IsMousePressed(ButtonMouse mouseButton)
{
	ctrl::ButtonMouse heldButton = GetMouseButtonDown();

	if (heldButton == ctrl::lastMouseButton) {
		return false;
	}
	else {
		if (mouseButton == heldButton && heldButton != ctrl::ButtonMouse::NULL_BUTTON) {
			ctrl::lastMouseButton = heldButton;
			return true;
		}
		return false;
	}
}

ctrl::ButtonMouse ctrl::GetMouseButtonDown()
{
	ctrl::ButtonMouse button = ctrl::ButtonMouse::NULL_BUTTON;

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		for (int i = 0; i < (int)ctrl::ButtonMouse::SIZE; i++)
		{
			if (IsMouseButtonDown(i)) {
				button = (ctrl::ButtonMouse)i;
			}
		}
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		for (int i = 0; i < (int)ctrl::ButtonMouse::SIZE; i++)
		{
			if (slGetMouseButton(i)) {
				button = (ctrl::ButtonMouse)i;
			}
		}
#endif
		break;
	}
	default:
		break;
	}

	return button;
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

bool ctrl::IsKeyPressed(Key key)
{
	ctrl::Key heldKey = GetKeyDown();

	if (heldKey == ctrl::lastKeyPress) {
		return false;
	}
	else {
		if (key == heldKey && heldKey != ctrl::Key::NULL_KEY) {
			ctrl::lastKeyPress = heldKey;
			return true;
		}
		return false;
	}
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

ctrl::Key ctrl::lastKeyPress = ctrl::Key::NULL_KEY;
ctrl::ButtonMouse ctrl::lastMouseButton = ctrl::ButtonMouse::NULL_BUTTON;
ctrl::ButtonMouse ctrl::menuSelectionMouseButton = ctrl::ButtonMouse::LMB;

std::string utl::settingsFilePath = "config/Settings.txt";

void mth::Clamp(float& num, float min, float max)
{
	if (num < min) {
		num = min;
	}
	if (num > max) {
		num = max;
	}
}

float mth::Clamped(float num, float min, float max)
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

float mth::Abs(float& num)
{
	if (num < 0) {
		num *= -1.0f;
	}
	return num;
}

float mth::AsAbs(float num)
{
	if (num < 0) {
		num *= -1.0f;
	}
	return num;
}

float mth::Min(float num1, float num2)
{
	if (num1 > num2) {
		return num2;
	}
	else {
		return num1;
	}
}

float mth::Max(float num1, float num2)
{
	if (num1 < num2) {
		return num2;
	}
	else {
		return num1;
	}
}

char ctrl::LastKeyPressed()
{
	if (_kbhit()) {
		return static_cast<char>(_getch());
	}
	return false;
}

float mth::RadianToDegree(float angle)
{
	return (angle * 180 / PI);
}

float mth::DegreeToRadian(float angle)
{
	return (angle * PI / 180);
}

float mth::Normalize(float& num, float min, float max)
{
	if (max == min) {
		return 0.0f;
	}
	num = (num - min) / (max - min);
	return num;
}

float mth::Normalized(float num, float min, float max)
{
	float result = num;
	if (max == min) {
		return 0.0f;
	}
	result = (num - min) / (max - min);
	return num;
}

float mth::Lerp(float min, float max, float percentage)
{
	return min * (1.0f - percentage) + (max * percentage);
}

float mth::WrapToRange(float num, float min, float max)
{
	float range = max - min;
	float result = mth::Clamped(num, min, max);
	if (range == 0) {
		return min;
	}

	if (result < 0) {
		result += range;
	}
	result = fmodf(num - min, range);
	return result + min;
}

float mth::MapToRange(float num, float iMin, float iMax, float oMin, float oMax)
{
	return iMin + (oMax - oMin) * ((num - iMin) / (iMax - iMin));
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
		int size = static_cast<int>(line.size());
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


void mth::SetRandomSeed(time_t seed)
{
	if (seed == 0) {
		srand((unsigned int)time(nullptr));
	}
	else {
		srand((unsigned int)time(&seed));
	}
	randomSeedSet = true;
}

int mth::GetRandom(int min, int max)
{
	if (!randomSeedSet) {
		SetRandomSeed();
	}
	return (int)(rand() % (max - min + 1) + min);
}

float mth::GetRandomf(float min, float max)
{
	if (!randomSeedSet) {
		SetRandomSeed();
	}
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
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
	this->rotate(mth::DegreeToRadian(angle));
}

vec::Vector2 vec::Vector2::rotatedDegree(float angle)
{
	return this->rotated(mth::DegreeToRadian(angle));
}

void vec::Vector2::randomizeAngle()
{
	this->rotateDegree(mth::GetRandomf(0.0f, 360.0f));
}

void vec::Vector2::randomizeAngle(float min, float max)
{
	this->rotateDegree(mth::GetRandomf(min, max));
}

void vec::Vector2::randomize(float maxMagnitude)
{
	mth::Clamp(maxMagnitude, 1, maxMagnitude);
	*this = 1;
	this->magnitude(mth::GetRandomf(0, maxMagnitude));
	this->randomizeAngle();
}

void vec::Vector2::randomize(float minMagnitude, float maxMagnitude)
{
	mth::Abs(minMagnitude);
	mth::Clamp(minMagnitude, 1, maxMagnitude);
	mth::Clamp(maxMagnitude, minMagnitude, maxMagnitude);
	*this = 1;
	this->magnitude(mth::GetRandomf(minMagnitude, maxMagnitude));
	this->randomizeAngle();
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
	vec::Vector2 v = vec::Vector2(this->magnitude(), this->angle());
	v.setAsCircular();
	return v;
}

vec::Vector2 vec::Vector2::asCircularDegree()
{
	vec::Vector2 v = vec::Vector2(this->magnitude(), mth::RadianToDegree(this->angle()));
	v.setAsCircular();
	return v;
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
	return *this = vec::Vector2(this->magnitude(), mth::RadianToDegree(this->angle()));
}

vec::Vector2 vec::Vector2::asCartesian()
{
	vec::Vector2 v = vec::Vector2(x * cosf(y), x * sinf(y));
	v.setAsCartesian();
	return v;
}

vec::Vector2 vec::Vector2::asCartesianDegree()
{
	vec::Vector2 v = vec::Vector2(x * cosf(mth::DegreeToRadian(y)), x * sinf(mth::DegreeToRadian(y)));
	v.setAsCartesian();
	return v;
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
	return *this = vec::Vector2(x * cosf(mth::DegreeToRadian(y)), x * sinf(mth::DegreeToRadian(y)));
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

bool con::GoToxy(float x, float y)
{
	return GoToxy(static_cast<int>(x), static_cast<int>(y));
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

void con::DrawBorder(vec::Vector2 pos, float borderSize)
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
		InitWindow(static_cast<int>(size.x), static_cast<int>(size.y), graphics.c_str());
		int monitor = GetCurrentMonitor();
		SetWindowPosition((GetMonitorWidth(monitor) / 2) - static_cast<int>(windowSize.x) / 2, (GetMonitorHeight(monitor) / 2) - static_cast<int>(windowSize.y) / 2);
		if (fullScreen) {
			ToggleFullscreen();
		}
		SetExitKey(KEY_MENU);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

		std::cout << "SIGIL";
#ifdef HAS_SIGIL
		graphics = title;
		graphics.append(" - SIGIL");
		slWindow(static_cast<int>(size.x), static_cast<int>(size.y), graphics.c_str(), fullScreen);
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
		return false;
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
	return true;
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

	windowRatio = size.x / size.y;

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
		return static_cast<float>(slGetDeltaTime());
#endif
		break;
	}
	default:
		break;
	}
	return 1.0f;
}

void rend::UpdateDeltaTime()
{
	rend::deltaTime = rend::GetDeltaTime();
	rend::secondCounter += rend::deltaTime;
	rend::secondSmallCounter += rend::deltaTime;
}

void rend::UpdateFramerate()
{
	rend::frameCounter++;
	rend::secondFrameCounter++;

	if (secondSmallCounter >= 1.0f) {
		rend::framerate = secondFrameCounter;
		rend::secondSmallCounter = 0;
		rend::secondFrameCounter = 0;
	}
}

rend::GraphicsLib rend::activeGraphics = rend::GraphicsLib::NONE;
rend::GraphicsLib rend::nextGraphics = rend::GraphicsLib::NONE;

ctrl::Key rend::frameInfoKey = ctrl::Key::F1;
rend::InfoMode rend::frameInfo = rend::InfoMode::NONE;
ctrl::Key rend::devInfoKey = ctrl::Key::F2;
rend::InfoMode rend::devInfo = rend::InfoMode::NONE;
ctrl::Key rend::devModeKey = ctrl::Key::F3;
rend::InfoMode rend::devMode = rend::InfoMode::NONE;

int rend::frameCounter = 0;
int rend::framerate = 0;
float rend::secondCounter = 0;
float rend::secondSmallCounter = 0;
int rend::secondFrameCounter = 0;
float rend::deltaTime = 0;

float rend::fullscreen = false;

vec::Vector2 rend::windowSize = { 1600,900 };
float rend::windowRatio = (16.0f / 9.0f);

std::string rend::mouseSprite = "";
vec::Vector2 rend::mousePos = { 0,0 };
vec::Vector2 rend::lastMousePos = { 0,0 };
vec::Vector2 rend::mouseDelta = { 0,0 };

bool rend::pixelMode = false;

bool coll::PointOnRec(vec::Vector2 point, vec::Vector2 pos, vec::Vector2 size)
{
	if (!(point.x > pos.x - size.x / 2.0f && point.x < pos.x + size.x / 2.0f)) {
		return false;
	}
	if (!(point.y > pos.y - size.y / 2.0f && point.y < pos.y + size.y / 2.0f)) {
		return false;
	}
	return true;
}

bool coll::PointOnCircle(vec::Vector2 point, vec::Vector2 pos, float radius)
{
	if ((point - pos).magnitude() < radius) {
		return true;
	}
	return false;
}

bool coll::RecOnRec(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2, vec::Vector2& point)
{
	vec::Vector2 half1 = { size1.x * 0.5f, size1.y * 0.5f };
	vec::Vector2 half2 = { size2.x * 0.5f, size2.y * 0.5f };

	float left1 = pos1.x - half1.x;
	float right1 = pos1.x + half1.x;
	float top1 = pos1.y - half1.y;
	float bottom1 = pos1.y + half1.y;

	float left2 = pos2.x - half2.x;
	float right2 = pos2.x + half2.x;
	float top2 = pos2.y - half2.y;
	float bottom2 = pos2.y + half2.y;

	float overlapLeft = mth::Max(left1, left2);
	float overlapRight = mth::Min(right1, right2);
	float overlapTop = mth::Max(top1, top2);
	float overlapBottom = mth::Min(bottom1, bottom2);

	if (overlapLeft >= overlapRight || overlapTop >= overlapBottom) {
		return false;
	}

	point.x = (overlapLeft + overlapRight) * 0.5f;
	point.y = (overlapTop + overlapBottom) * 0.5f;

	return true;
}

bool coll::CircleOnCircle(vec::Vector2 pos1, vec::Vector2 pos2, float radius1, float radius2, vec::Vector2& point)
{
	vec::Vector2 distance = { pos1.x - pos2.x, pos1.y - pos2.y };
	distance = { distance.x * distance.x, distance.y * distance.y };

	if ((distance.x + distance.y) <= ((radius1 + radius2) * (radius1 + radius2))){
		point = (pos1 + pos2) * 0.5f;
		return true;
	}
	return false;
}

bool coll::CircleOnCircle(vec::Vector2 pos1, vec::Vector2 pos2, float radius1, float radius2)
{
	vec::Vector2 point;
	return CircleOnCircle(pos1, pos2, radius1, radius2, point);
}

//bool coll::RecOnElipse(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2, vec::Vector2& point)
//{
//
//}
//
//bool coll::RecOnElipse(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2, vec::Vector2& point)
//{
//	return false;
//}
//
//bool coll::RecOnCircle(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2, vec::Vector2& point)
//{
//	return false;
//}
//
//bool coll::RecOnCircle(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, float radius, vec::Vector2& point)
//{
//	return false;
//}

drw::SpriteData drw::defaultSprite;
drw::SpriteData drw::spriteDataList[drw::spriteDataMaxAmount] = {};

drw::FontData drw::defaultFont;
drw::FontData drw::fontDataList[drw::fontDataMaxAmount] = {};

snd::AudioData snd::defaultAudio;
snd::AudioData snd::audioDataList[snd::audioDataMaxAmount] = {};

vec::Vector2 drw::PercentToScreen(vec::Vector2 vec)
{
	return vec::Vector2(vec.x * rend::windowRatio, vec.y);
}


void drw::Clear(bColor color)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		ClearBackground({ color.r,color.g,color.b,color.a });
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

int drw::InitSpriteData(SpriteData& spriteData)
{
	int availableID = 0;
	int currentID = -1;

	bool isAvailable = false;
	while (!isAvailable) {
		currentID++;

		isAvailable = !drw::spriteDataList[currentID].active;

		if (isAvailable) {
			availableID = currentID;
		}
		if (currentID == drw::spriteDataMaxAmount - 1) {
			isAvailable = true;
		}
	}
	spriteData.active = true;

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

	drw::spriteDataList[availableID] = spriteData;
	return availableID;
}

bool drw::DeInitSpriteData(drw::SpriteData& spriteData)
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

int drw::InitAnimData(AnimationData& animData, SpriteData spriteData[], int frames)
{
	animData.frames = frames;

	animData.timeOffset = rend::secondCounter;

	int firstSpot = 0;
	int currentSpot = 0;

	for (int i = 0; i < frames; i++)
	{
		currentSpot = drw::InitSpriteData(spriteData[i]);

		if (currentSpot == drw::spriteDataMaxAmount - 1) {
			return 0;
		}

		if (firstSpot == 0) {
			firstSpot = currentSpot;
		}
	}
	animData.active = true;
	animData.id = firstSpot;
	return firstSpot;
}

int drw::InitFontData(FontData& fontData)
{
	int availableID = 0;
	int currentID = -1;

	bool isAvailable = false;
	while (!isAvailable) {
		currentID++;

		isAvailable = !drw::fontDataList[currentID].active;

		if (isAvailable) {
			availableID = currentID;
		}
		if (currentID == drw::fontDataMaxAmount - 1) {
			isAvailable = true;
		}
	}
	fontData.active = true;

	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		fontData.font = LoadFont(fontData.file.c_str());
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		fontData.id = slLoadFont(fontData.file.c_str());
#endif
		break;
	}
	default:
		break;
	}

	drw::fontDataList[availableID] = fontData;
	return availableID;
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

	if (rend::frameInfo != rend::InfoMode::NONE) {
		
		
		std::string mousePosX;
		std::string mousePosY;
		std::string mouseDeltaX;
		std::string mouseDeltaY;

		switch (rend::frameInfo)
		{

		case rend::InfoMode::ADVANCED:
			mousePosX = std::to_string(static_cast<int>(rend::mousePos.x * 100.0f));
			mousePosY = std::to_string(static_cast<int>(rend::mousePos.y * 100.0f));
			drw::Text(mousePosX.c_str(), { 0.015f,0.95f }, 20, { 0.0f,0 }, GREEN_B);
			drw::Text(mousePosY.c_str(), { 0.09f,0.95f }, 20, { 0.0f,0.0f }, GREEN_B);

			mouseDeltaX = std::to_string((rend::mouseDelta.x * 100));
			mouseDeltaY = std::to_string((rend::mouseDelta.y * 100));
			drw::Text(mouseDeltaX.c_str(), { 0.015f,0.92f }, 20, { 0.0f,0.0f }, GREEN_B);
			drw::Text(mouseDeltaY.c_str(), { 0.09f,0.92f }, 20, { 0.0f,0.0f }, GREEN_B);
		case rend::InfoMode::BASIC: {
			std::string framerate = std::to_string(static_cast<int>(rend::framerate));
			std::string seconds = std::to_string(static_cast<int>(rend::secondCounter));
			drw::Text(framerate.c_str(), { 0.015f,0.98f }, 20, { 0.0f,0.0f }, GREEN_B);
			drw::Text(seconds.c_str(), { 0.09f,0.98f }, 20, { 0.0f,0.0f }, GREEN_B);
			break;
		}
		default:
			break;
		}
	}

	vec::Vector2 devModeTextOffset = { 0.0f , 0.0f };
	std::string devModeText = "Dev mode";
	std::string devInfoText = "Dev info";

	switch (rend::devInfo)
	{

	case rend::InfoMode::ADVANCED:
		devInfoText = "Dev info advanced";
	case rend::InfoMode::BASIC: {
		devModeTextOffset.y = 0.03f;
		drw::Text(devInfoText.c_str(), { 0.95f ,0.98f }, 20, { 0.0f,0.0f }, BLUE_B);

		break;
	}
	default:
		break;
	}

	switch (rend::devMode)
	{

	case rend::InfoMode::ADVANCED:
		devModeText = "Dev mode advanced";
	case rend::InfoMode::BASIC: {

		drw::Text(devModeText.c_str(), { 0.95f - devModeTextOffset.x ,0.98f - devModeTextOffset.y }, 20, { 0.0f,0.0f }, RED_B);

		break;
	}
	default:
		break;
	}

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

bool drw::Animation(AnimationData& animation, vec::Vector2 pos, vec::Vector2 size, vec::Vector2 offset, bColor color)
{
	if (!animation.active) {
		return false;
	}

	if (rend::secondCounter - animation.timeOffset > animation.duration) {
		animation.timeOffset = rend::secondCounter;
	}

	//std::cout << "Frame: " << animation.id + ((int)(((rend::secondCounter - animation.timeOffset) / animation.duration) * animation.frames)) << '\n';

	drw::Sprite(drw::spriteDataList[animation.id + ((int)(((rend::secondCounter - animation.timeOffset) / animation.duration) * animation.frames))], pos, size, offset, color);

	return true;
}

bool drw::Sprite(drw::SpriteData sprite, vec::Vector2 pos, vec::Vector2 size, vec::Vector2 offset, bColor color)
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
		texture.width = static_cast<int>(size.x * rend::windowSize.x);
		texture.height = static_cast<int>(size.y * rend::windowSize.y);

		if (rend::pixelMode) {
			SetTextureFilter(texture, TEXTURE_FILTER_POINT);
		}

		DrawTexture(texture, static_cast<int>(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * size.x / 2.0f), static_cast<int>(rend::windowSize.y * (1.0f - pos.y) + (1.0f - offset.y * rend::windowSize.y) - rend::windowSize.y * size.y / 2.0f), { color.r,color.g,color.b,color.a });
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		slSetForeColor(static_cast<double>(color.r / 255.0f), static_cast<double>(color.g / 255.0f), static_cast<double>(color.b / 255.0f), static_cast<double>(color.a / 255.0f));
		slSprite(sprite.id, pos.x * rend::windowSize.x + offset.x * rend::windowSize.x, pos.y * rend::windowSize.y + offset.y * rend::windowSize.y, size.x * rend::windowSize.x, size.y * rend::windowSize.y);
#endif
		break;
	}
	default:
		break;
	}
	return true;
}

void drw::Text(const char* text, drw::TextData& textData, vec::Vector2 pos, int fontSize, vec::Vector2 offset, bColor color)
{
	vec::Vector2 textSize = fontSize;

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {
		textSize.x = MeasureText(text, fontSize) / rend::windowSize.x;
		float tempFontSize = fontSize * 1.5f;
		textSize.y = tempFontSize / rend::windowSize.y;
		DrawTextPro(drw::fontDataList[textData.fontID].font, text, { pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * textSize.x / 3, rend::windowSize.y * (1.0f - pos.y) + (1.0f - offset.y * rend::windowSize.y) - rend::windowSize.y * textSize.y / 2 }, { textData.origin.x,textData.origin.y }, textData.rotation, tempFontSize, drw::fontDataList[textData.fontID].spacing, { color.r,color.g,color.b,color.a });
		break;
	}
	case rend::GraphicsLib::SIGIL: {

		slSetFont(textData.fontID, fontSize);
		slSetFontSize(fontSize);
		slSetForeColor(static_cast<double>(color.r / 255.0f), static_cast<double>(color.g / 255.0f), static_cast<double>(color.b / 255.0f), static_cast<double>(color.a / 255.0f));
		textSize.x = static_cast<float>(slGetTextWidth(text)) / rend::windowSize.x;
		textSize.y = static_cast<float>(slGetTextHeight(text)) / rend::windowSize.y;
		//slSetTextAlign(SL_ALIGN_CENTER);
		//slText(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x, rend::windowSize.y * (1.0f - pos.y) + offset.y * rend::windowSize.y, text);
		slText(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * textSize.x / 2, rend::windowSize.y * pos.y + offset.y * rend::windowSize.y - rend::windowSize.y * textSize.y / 2, text);
		break;
	}
	default:
		break;
	}
}

void drw::Text(const char* text, vec::Vector2 pos, int fontSize, vec::Vector2 offset, bColor color)
{
	TextData textData;
	drw::Text(text, textData, pos, fontSize, offset, color);
}

void drw::Text(TextData& textData, vec::Vector2 pos, int fontSize, vec::Vector2 offset, bColor color)
{
	drw::Text(textData.text.c_str(), textData, pos, fontSize, offset, color);
}

void drw::Triangle(vec::Vector2 p1, vec::Vector2 p2, vec::Vector2 p3, bColor color)
{

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

		DrawTriangle({ p1.x,p1.y }, { p2.x,p2.y }, { p3.x,p3.y }, { color.r,color.g,color.b,color.a });

		break;
	}
	case rend::GraphicsLib::SIGIL: {

		break;
	}
	default:
		break;
	}
}

void drw::Rectangle(vec::Vector2 pos, vec::Vector2 size, bColor color, vec::Vector2 offset)
{
	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		DrawRectangle(static_cast<int>(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * size.x / 2.0f), static_cast<int>(rend::windowSize.y * (1.0f - pos.y) + (1.0f - offset.y * rend::windowSize.y) - rend::windowSize.y * size.y / 2.0f), static_cast<int>(size.x * rend::windowSize.x), static_cast<int>(size.y * rend::windowSize.y), { color.r,color.g,color.b,color.a });
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		slSetForeColor(static_cast<double>(color.r / 255.0f), static_cast<double>(color.g / 255.0f), static_cast<double>(color.b / 255.0f), static_cast<double>(color.a / 255.0f));
		slRectangleFill(pos.x * rend::windowSize.x + offset.x * rend::windowSize.x, pos.y * rend::windowSize.y + offset.y * rend::windowSize.y, size.x * rend::windowSize.x, size.y * rend::windowSize.y);
#endif
		break;
	}
	default:
		break;
	}
}

void drw::Circle(vec::Vector2 pos, vec::Vector2 size, bColor color)
{

	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

		DrawEllipse(static_cast<int>(pos.x * rend::windowSize.x), static_cast<int>((1.0f - pos.y) * rend::windowSize.y), size.x * rend::windowSize.x, size.y * rend::windowSize.y, { color.r,color.g,color.b,color.a });
		break;
	}
	case rend::GraphicsLib::SIGIL: {
		slSetForeColor(static_cast<double>(color.r / 255.0f), static_cast<double>(color.g / 255.0f), static_cast<double>(color.b / 255.0f), static_cast<double>(color.a / 255.0f));
		slCircleFill(pos.x * rend::windowSize.x, pos.y * rend::windowSize.y, size.x * rend::windowSize.x, 100);
		break;
	}
	default:
		break;
	}
}

void drw::Line(vec::Vector2 start, vec::Vector2 end, bColor color)
{
	Line(start,end, 0.0f,color);
}

void drw::Line(vec::Vector2 start, vec::Vector2 end,float size, bColor color)
{
	vec::Vector2 newEnd = end;

	if (newEnd.isCartesian()) {
		newEnd.toCircular();
	}

	if (size > 0.0f) {
		newEnd.x = size;
	}

	newEnd = start + newEnd.asCartesian();
	
	switch (rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {
		DrawLine(static_cast<int>(start.x * rend::windowSize.x), static_cast<int>((1.0f - start.y) * rend::windowSize.y), static_cast<int>(newEnd.x * rend::windowSize.x), static_cast<int>((1.0f - newEnd.y) * rend::windowSize.y), { color.r,color.g,color.b,color.a });
		break;
	}
	case rend::GraphicsLib::SIGIL: {
		slSetForeColor(static_cast<double>(color.r / 255.0f), static_cast<double>(color.g / 255.0f), static_cast<double>(color.b / 255.0f), static_cast<double>(color.a / 255.0f));
		slLine(start.x * rend::windowSize.x, start.y * rend::windowSize.y, newEnd.x * rend::windowSize.x, newEnd.y * rend::windowSize.y);
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

int snd::InitAudioData(snd::AudioData& audioData)
{
	int availableID = 0;
	int currentID = -1;

	bool isAvailable = false;
	while (!isAvailable) {
		currentID++;

		isAvailable = !snd::audioDataList[currentID].active;

		if (isAvailable) {
			availableID = currentID;
		}
		if (currentID == snd::audioDataMaxAmount - 1) {
			isAvailable = true;
		}
	}
	audioData.active = true;

	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		audioData.sound = LoadSound(audioData.file.c_str());
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		audioData.id = slLoadWAV(audioData.file.c_str());
#endif
		break;
	}
	default:
		break;
	}

	snd::audioDataList[availableID] = audioData;
	return availableID;
}

void snd::DeInit(snd::AudioData& audioData)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		UnloadSound(audioData.sound);
		audioData.id = 0;
		audioData.active = false;
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		audioData.id = 0;
		audioData.active = false;
#endif
		break;
	}
	default:
		break;
	}
}

void snd::Play(int id)
{

	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		PlaySound(snd::audioDataList[id].sound);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		slSoundPlay(snd::audioDataList[id].id);
#endif
		break;
	}
	default:
		break;
	}
}

void snd::Pause(int id, bool pause)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		if (pause) {
			PauseSound(snd::audioDataList[id].sound);
		}
		else {
			ResumeSound(snd::audioDataList[id].sound);
		}
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		if (pause) {
			slSoundPause(snd::audioDataList[id].id);
		}
		else {
			slSoundPlay(snd::audioDataList[id].id);
		}
#endif
		break;
	}
	default:
		break;
	}
}

void snd::Stop(int id)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		StopSound(snd::audioDataList[id].sound);
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

bool snd::IsPlaying(int id)
{
	switch ((rend::GraphicsLib)rend::activeGraphics)
	{
	case rend::GraphicsLib::NONE: {

		break;
	}
	case rend::GraphicsLib::RAYLIB: {

#ifdef HAS_RAYLIB
		IsSoundPlaying(snd::audioDataList[id].sound);
#endif
		break;
	}
	case rend::GraphicsLib::SIGIL: {

#ifdef HAS_SIGIL
		return slSoundPlaying(snd::audioDataList[id].id);
#endif
		break;
	}
	default:
		break;
	}
	return false;
}

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

void btn::InitButtonDefaults()
{

}

void btn::DeInitButtonDefaults()
{

}

void btn::Init(Button& button)
{
	button.isActive = true;
	button.isRendered = true;
	//button.size = drw::PercentToScreen(button.size);
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
}

bool btn::isHovered(btn::Button button)
{
	if (!button.isActive) {
		return false;
	}
	return upd::isMouseOver(button.pos, button.size);
}

bool btn::isClicked(btn::Button button)
{
	if (!button.isActive) {
		return false;
	}
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
		button.activeTextureID = button.hoveredTextureID;
	}
	else {
		button.activeTextureID = button.mainTextureID;
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
		snd::Play(button.hoveredSoundID);
	}
	if (button.isClickedDownChange) {
		snd::Play(button.clickedDownSoundID);
	}
	if (button.isClickedUpChange) {
		snd::Play(button.clickedUpSoundID);
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
	if (button.isClicked && button.isActive) {
		button.offset += button.clickedOffset * button.size.y;
	}
	if (button.useSprite) {
		drw::Sprite(drw::spriteDataList[button.activeTextureID], button.pos, button.size, button.offset);
	}
	else {
		drw::Rectangle(button.pos, button.size, button.activeColor, button.offset);
	}
	if (button.useText) {
		drw::Text(button.textData.text.c_str(), button.textData, button.pos, button.textData.fontSize, button.offset, button.textColor);
	}
	button.offset = tempOffset;
}

void btn::Draw(Container container)
{
	if (!container.isRendered) {
		return;
	}
	if (container.useTexture) {
		drw::Sprite(drw::spriteDataList[container.textureID], container.pos, container.size, container.offset);
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

//void fnt::Init(rend::TextData& textData)
//{
//	switch ((rend::GraphicsLib)rend::activeGraphics)
//	{
//	case rend::GraphicsLib::NONE: {
//
//		break;
//	}
//	case rend::GraphicsLib::RAYLIB: {
//
//#ifdef HAS_RAYLIB
//		if (textData.raylibInitialized) {
//			return;
//		}
//		textData.font.baseSize = 100;
//		textData.font = LoadFont(textData.file.c_str());
//		textData.raylibInitialized = true;
//#endif
//		break;
//	}
//	case rend::GraphicsLib::SIGIL: {
//
//#ifdef HAS_SIGIL
//		if (textData.slInitialized) {
//			return;
//		}
//		textData.id = slLoadFont(textData.file.c_str());
//		textData.slInitialized = true;
//#endif
//		break;
//	}
//	default:
//		break;
//	}
//}

//void fnt::DeInit(rend::TextData& textData)
//{
//	switch ((rend::GraphicsLib)rend::activeGraphics)
//	{
//	case rend::GraphicsLib::NONE: {
//
//		break;
//	}
//	case rend::GraphicsLib::RAYLIB: {
//
//#ifdef HAS_RAYLIB
//		UnloadFont(textData.font);
//		textData.raylibInitialized = false;
//#endif
//		break;
//	}
//	case rend::GraphicsLib::SIGIL: {
//
//#ifdef HAS_SIGIL
//		if (!textData.slInitialized) {
//			return;
//		}
//		//audioData.soundFileID = -1;
//		//audioData.slInitialized = false;
//#endif
//		break;
//	}
//	default:
//		break;
//	}
//}

void bLib::Init(std::string windowName)
{
	rend::activeGraphics = (rend::GraphicsLib)stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "graphics"));
	//rend::activeGraphics = (rend::GraphicsLib)1;

	rend::windowSize.x = (float)stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "resolution_width"));
	rend::windowSize.y = (float)stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "resolution_height"));

	rend::fullscreen = (bool)stoi(utl::SearchInFile(utl::settingsFilePath.c_str(), "fullscreen"));

	rend::OpenWindow(rend::windowSize, windowName.c_str(), rend::fullscreen);
	snd::StartAudioDevice();

	drw::InitSpriteData(drw::defaultSprite);
	drw::InitFontData(drw::defaultFont);
	snd::InitAudioData(snd::defaultAudio);
}

void bLib::UpdateStart()
{
	rend::windowSize = rend::GetWindowSize();
	rend::mousePos = rend::GetMousePos();
	rend::UpdateDeltaTime();
	rend::UpdateFramerate();
}

void bLib::UpdateEnd()
{

	if (rend::lastMousePos != rend::mousePos) {
		rend::mouseDelta = rend::lastMousePos - rend::mousePos;
	}
	rend::lastMousePos = rend::GetMousePos();

	if (IsKeyPressed(rend::frameInfoKey)) {

		switch (rend::frameInfo)
		{
		case rend::InfoMode::NONE: {
			rend::frameInfo = rend::InfoMode::BASIC;
			break;
		}
		case rend::InfoMode::BASIC: {
			rend::frameInfo = rend::InfoMode::ADVANCED;
			break;
		}
		case rend::InfoMode::ADVANCED: {
			rend::frameInfo = rend::InfoMode::NONE;
			break;
		}
		default:
			break;
		}
	}

	if (IsKeyPressed(rend::devInfoKey)) {

		switch (rend::devInfo)
		{
		case rend::InfoMode::NONE: {
			rend::devInfo = rend::InfoMode::BASIC;
			break;
		}
		case rend::InfoMode::BASIC: {
			rend::devInfo = rend::InfoMode::ADVANCED;
			break;
		}
		case rend::InfoMode::ADVANCED: {
			rend::devInfo = rend::InfoMode::NONE;
			break;
		}
		default:
			break;
		}
	}
	if (IsKeyPressed(rend::devModeKey)) {

		switch (rend::devMode)
		{
		case rend::InfoMode::NONE: {
			rend::devMode = rend::InfoMode::BASIC;
			break;
		}
		case rend::InfoMode::BASIC: {
			rend::devMode = rend::InfoMode::ADVANCED;
			break;
		}
		case rend::InfoMode::ADVANCED: {
			rend::devMode = rend::InfoMode::NONE;
			break;
		}
		default:
			break;
		}
	}

	ctrl::lastKeyPress = ctrl::GetKeyDown();
	ctrl::lastMouseButton = ctrl::GetMouseButtonDown();
}

void prtcl::Init(ParticleActivator& activator, ParticleData particles[])
{
	for (int i = 0; i < activator.amount; i++)
	{
		prtcl::Init(activator, particles[i]);
	}
}

void prtcl::Init(ParticleActivator& activator, ParticleData& particle)
{
	if (!activator.active) {
		activator.active = true;
		activator.direction.normalize();
	}

	particle.active = true;
	if (particle.id == 0) {
		particle.id = activator.id;
	}
	if (activator.animated) {
		particle.animated = true;
		particle.animation = activator.animation;
	}
	particle.amount = activator.amount;
	particle.pos = activator.pos;
	particle.pos.x += mth::GetRandomf(0.0f, activator.startingOffset.x) - activator.startingOffset.x / 2.0f;
	particle.pos.y += mth::GetRandomf(0.0f, activator.startingOffset.y) - activator.startingOffset.y / 2.0f;
	particle.size.x = mth::GetRandomf(activator.minSize.x, activator.maxSize.x);
	particle.size.y = mth::GetRandomf(activator.minSize.y, activator.maxSize.y);
	particle.direction = activator.direction;
	particle.direction.randomizeAngle(0, activator.spread);
	particle.direction.rotateDegree(-activator.spread / 2);
	if (activator.startingPosInfluence != 0.0f) {
		mth::Clamp(activator.startingPosInfluence);
		particle.direction = particle.direction * (1.0f - activator.startingPosInfluence) + vec::Vector2{ particle.pos - activator.pos }.normalized() * activator.startingPosInfluence;
		particle.direction.normalize();
	}
	particle.lifetime = mth::GetRandomf(activator.lifetime.x, activator.lifetime.y);
	particle.delay = mth::GetRandomf(activator.delay.x, activator.delay.y);
	particle.rotationChange = mth::GetRandomf(activator.rotation.x, activator.rotation.y);
	particle.speed = mth::GetRandomf(activator.speed.x, activator.speed.y);

	particle.size.x /= rend::windowRatio;
	particle.direction.x /= rend::windowRatio;
}

bool prtcl::Update(ParticleData& particle)
{
	if (particle.active) {

		if (particle.alive) {
			particle.pos += particle.direction * particle.speed * rend::deltaTime;
			particle.lifetime -= rend::deltaTime;
		}
		if (particle.delay > 0.0f) {

			particle.delay -= rend::deltaTime;

			if (particle.delay <= 0.0f) {
				particle.alive = true;
				particle.delay = 0.0f;
			}

		}
		if (particle.lifetime < 0.0f) {
			particle.lifetime = 0.0f;
			particle.active = false;
		}
	}
	return particle.active;
}

void prtcl::Update(ParticleActivator& activator, ParticleData particles[])
{
	bool active = false;

	for (int i = 0; i < particles[0].amount; i++)
	{
		if (prtcl::Update(particles[i])) {
			active = true;
		}
		if (activator.loop) {
			if (particles[i].lifetime <= 0.0f) {
				prtcl::Init(activator, particles[i]);
			}
		}
	}
	if (!activator.loop) {
		activator.active = active;
	}
}

void prtcl::Draw(ParticleData particles[])
{
	for (int i = 0; i < particles[0].amount; i++)
	{
		if (particles[i].alive && particles[i].active) {

			if (particles[i].animated) {
				drw::Animation(particles[i].animation, particles[i].pos, particles[i].size);
			}
			else {
				drw::Sprite(drw::spriteDataList[particles[i].id], particles[i].pos, particles[i].size);
			}
			if (rend::devInfo == rend::InfoMode::ADVANCED) {
				drw::Line(particles[i].pos, particles[i].direction.asCircular(),0.025f, MAGENTA_B);
			}
		}
	}
}

