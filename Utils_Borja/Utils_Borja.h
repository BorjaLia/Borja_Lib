#pragma once
#include <iostream>
#include "conio.h"

//#include "windows.h"

#include <fstream>
#include <string>

#define HAS_SIGIL
#define HAS_RAYLIB

#ifdef HAS_RAYLIB
#include "raylib.h" 
#endif

#ifdef HAS_SIGIL
#include "sl.h"
#endif

//constexpr float PI = 3.14159265359;

//struct Color {
//	unsigned char r;
//	unsigned char g;
//	unsigned char b;
//	unsigned char a;
//
//	Color();
//	Color(unsigned char r, unsigned char g, unsigned char b);
//	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
//};

namespace ctrl {

	enum class ButtonMouse {
		LMB = 0,
		RMB,
		MMB,
		BWB,
		FWB
	};

	enum class Key {

		NULL_KEY = 0,
		APOSTROPHE = 39,
		COMMA = 44,
		MINUS = 45,
		PERIOD = 46,
		SLASH = 47,
		ZERO = 48,
		ONE = 49,
		TWO = 50,
		THREE = 51,
		FOUR = 52,
		FIVE = 53,
		SIX = 54,
		SEVEN = 55,
		EIGHT = 56,
		NINE = 57,
		SEMICOLON = 59,
		EQUAL = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LEFT_BRACKET = 91,
		BACKSLASH = 92,
		RIGHT_BRACKET = 93,
		GRAVE = 96,
		SPACE = 32,
		ESCAPE = 256,
		ENTER = 257,
		TAB = 258,
		BACKSPACE = 259,
		INSERT = 260,
		DELETE = 261,
		RIGHT = 262,
		LEFT = 263,
		DOWN = 264,
		UP = 265,
		PAGE_UP = 266,
		PAGE_DOWN = 267,
		HOME = 268,
		END = 269,
		CAPS_LOCK = 280,
		SCROLL_LOCK = 281,
		NUM_LOCK = 282,
		PRINT_SCREEN = 283,
		PAUSE = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		KB_MENU = 348,
		KP_0 = 320,
		KP_1 = 321,
		KP_2 = 322,
		KP_3 = 323,
		KP_4 = 324,
		KP_5 = 325,
		KP_6 = 326,
		KP_7 = 327,
		KP_8 = 328,
		KP_9 = 329,
		KP_DECIMAL = 330,
		KP_DIVIDE = 331,
		KP_MULTIPLY = 332,
		KP_SUBTRACT = 333,
		KP_ADD = 334,
		KP_ENTER = 335,
		KP_EQUAL = 336,
		SIZE = 349
	};

	bool IsMouseDown(ButtonMouse mouseButton);

	bool IsKeyHeldDown(Key key);
	Key GetKeyDown();

}

extern ctrl::ButtonMouse menuSelectionMouseButton;

namespace utl {

	void Clamp(float& num, float min = 0, float max = 1.0f);		// clamp number between min and max
	float Clamped(float num, float min = 0, float max = 1.0f);		// clamp number between min and max
	float Abs(float& num);										// makes the number positive

	char LastKeyPressed();										// returns last key press. false if none

	float RadianToDegree(float angle);							// radians to degrees
	float DegreeToRadian(float angle);							// degrees to radians

	float MapToRange(float& num, float min = 0, float max = 1.0f);

	std::string SearchInFile(const char* filename, const char* search);
	bool SaveToFile(const char* filename, const char* filter, std::string info);
	bool SaveToFile(const char* filename, const char* filter, int info);
}

namespace rng {

	void SetRandomSeed(time_t seed = 0);													// set random seed
	int GetRandom(int min = 0, int max = 100);												// get random int
	float GetRandomf(float min = 0.0f, float max = 1.0f, unsigned int accuracy = 100);		// get random float
}

namespace vec {

	struct Vector3 {
	private:

		bool isCartesianBool = true;
		bool isSphericalBool = false;

	public:

		float x;
		float y;
		float z;

		Vector3(bool cartesian = true);
		Vector3(float x, float y, float z, bool cartesian = true);
	};

	struct Vector2 {

	private:

		bool isCartesianBool = true;
		bool isCircularBool = false;

	public:

		float x;
		float y;

		Vector2(bool cartesian = true);
		Vector2(float x, float y, bool cartesian = true);

		void normalize();											// normalize the vector
		vec::Vector2 normalized();									// returns the normalized vector without modyfing the original
		float magnitude();											// returns the magnitude
		float magnitude(float magnitude);							// scale the vector and returns the new magnitude
		float determinant(Vector2 v);								// determinant between 2 vectors
		void clamp(float max);										// clamp the magnitude to a max value
		void clamp(float min, float max);							// clamp the magnitude between values
		float angle(Vector2 v = { 1,0 });							// angle between 2 vectors. default is {1,0}
		void rotate(float angle);									// rotate the vector by the given angle in radians
		vec::Vector2 rotated(float angle);							// return the rotated vector by the given angle in radians without modyfing the original
		void rotateDegree(float angle);								// rotate the vector by the given angle in degrees
		vec::Vector2 rotatedDegree(float angle);					// return the rotated vector by the given angle in degrees without modyfing the original
		void randomize();											// randomize the direction of the vector. keep magnitude
		void randomize(float maxMagnitude);							// randomize the direction of the vector. randomize magnitude between 1 and max
		void randomize(float minMagnitude, float maxMagnitude);		// randomize the direction of the vector. randomize magnitude between min and max

		bool isCartesian();
		bool setAsCartesian();
		bool isCircular();
		bool setAsCircular();

		vec::Vector2 asCircular();									// from cartesian (in radians)
		vec::Vector2 asCircularDegree();							// from cartesian (in degrees)
		vec::Vector2 toCircular();									// transform to circular from cartesian (in radians)
		vec::Vector2 toCircularDegree();							// transform to circular from cartesian (in degrees)

		vec::Vector2 asCartesian();									// from circular (in radians)
		vec::Vector2 asCartesianDegree();							// from circular (in degrees)
		vec::Vector2 toCartesian();									// to cartesian from circular (in radians)
		vec::Vector2 toCartesianDegree();							// to cartesian from circular (in degrees)

		vec::Vector2 operator + (const vec::Vector2 vector) {
			return vec::Vector2(x + vector.x, y + vector.y);
		}
		vec::Vector2 operator +=  (const vec::Vector2 vector) {
			this->x += vector.x;
			this->y += vector.y;
			return *this;
		}
		vec::Vector2 operator - (const vec::Vector2 vector) {
			return vec::Vector2(x - vector.x, y - vector.y);
		}
		vec::Vector2 operator -= (const vec::Vector2 vector) {
			this->x -= vector.x;
			this->y -= vector.y;
			return *this;
		}
		float operator * (const vec::Vector2 vector) {
			return (float)((x * vector.x) + (y * vector.y));
		}
		vec::Vector2 operator * (const float scalar) {
			vec::Vector2 result = *this;
			result.x *= scalar;
			result.y *= scalar;
			return result;
		}
		vec::Vector2 operator * (const int scalar) {
			vec::Vector2 result = *this;
			result.x *= scalar;
			result.y *= scalar;
			return result;
		}
		vec::Vector2 operator *= (const float scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}
		vec::Vector2 operator *= (const int scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}
		vec::Vector2 operator = (const vec::Vector2 vector) {
			this->x = vector.x;
			this->y = vector.y;
			return *this;
		}
		vec::Vector2 operator = (const float value) {
			this->x = value;
			this->y = value;
			return *this;
		}
		vec::Vector2 operator = (const int value) {
			this->x = value;
			this->y = value;
			return *this;
		}
		bool operator == (const vec::Vector2 vector) {
			if (x == vector.x && y == vector.y) {
				return true;
			}
			else {
				return false;
			}
		}
		bool operator == (const float value) {
			if (x == value && y == value) {
				return true;
			}
			else {
				return false;
			}
		}
		bool operator == (const int value) {
			if (x == value && y == value) {
				return true;
			}
			else {
				return false;
			}
		}
		bool operator != (const vec::Vector2 vector) {
			if (x == vector.x && y == vector.y) {
				return false;
			}
			else {
				return true;
			}
		}
		bool operator != (const float value) {
			if (x == value && y == value) {
				return false;
			}
			else {
				return true;
			}
		}
		bool operator != (const int value) {
			if (x == value && y == value) {
				return false;
			}
			else {
				return true;
			}
		}
	};
	std::ostream& operator <<(std::ostream& os, const vec::Vector2& v);
}

namespace con {

	void UpdateConInfo();

	void SetColor(int foreground, int background);
	bool GoToxy(int x = 0, int y = 0);
	bool GoToxy(vec::Vector2 v);
	int GetCursorLine();
	void Clear();

	void DrawVector(vec::Vector2 v, vec::Vector2 pos, int borderSize);
	void ClearVector(vec::Vector2 v, vec::Vector2 pos, int borderSize);
	void DrawBorder(vec::Vector2 pos, int borderSize);
}

namespace rend {

//colors

#define TRANSPARENT	{ 0, 0, 0, 0 }
#define SEMITRANSPARENT	{ 0, 0, 0, 128 }

#define WHITE	{ 255, 255, 255, 255 }
#define LIGHTGREY	{ 192, 192, 192, 255 }
#define GREY	{ 128, 128, 128, 255 }
#define DARKGREY	{ 64, 64, 64, 255 }
#define BLACK	{ 0, 0, 0, 255 }

#define RED		{ 255, 0, 0, 255 }
#define GREEN	{ 0, 255, 0, 255 }
#define BLUE	{ 0, 0, 255, 255 }

#define YELLOW		{ 255, 255, 0, 255 }
#define LIGHTBLUE		{ 0, 255, 255, 255 }
#define MAGENTA		{ 255, 0, 255, 255 }

#define ORANGE		{ 255, 128, 0, 255 }
#define LIME		{ 128, 255, 0, 255 }
#define FUSCHIA		{ 255, 0, 128, 255 }
#define PURPLE		{ 128, 0, 255, 255 }
#define MINT		{ 0, 255, 128, 255 }
#define BLUEBERRY		{ 0, 128, 255, 255 }

//resolutions

#define HD_RES {1280,720}
#define FHD_RES {1920,1080}
#define QHD_RES {2560,1440}
#define UHD_RES {3480,2160}

	enum class Resolution {
		MANUAL,
		HD,
		FHD,
		QHD,
		UHD
	};

	enum class WindowType {
		WINDOWED,
		FULLSCREEN
	};

	enum class GraphicsLib {
		NONE,
		RAYLIB,
		SIGIL
	};

	bool ChangeRenderer();

	void OpenWindow(vec::Vector2 size, const char* title, bool fullscreen = false);
	bool ShouldExit();
	void Close();

	vec::Vector2 GetWindowSize();
	vec::Vector2 GetMousePos();
	float GetDeltaTime();

	struct SpriteData {

		std::string name = "Sprite";
		std::string file = "NoTexture.png";
		int id = 0;
		vec::Vector2 offset = { 0,0 };
	};

	struct AudioData {

		bool slInitialized = false;
		bool raylibInitialized = false;

		std::string name = "No Audio";
		std::string file = "ButtonClick.wav";
		int soundFileID = -1;

		int id = -1;

		Sound sound;
	};

	struct TextData {

		bool slInitialized = false;
		bool raylibInitialized = false;

		vec::Vector2 origin = {0,0};
		float rotation = 0;

		float spacing = 1.0f;

		std::string name = "No Font";
		std::string file = "font.ttf";
		int fontFileID = -1;

		int id = -1;

		Font font;
	};

	extern rend::GraphicsLib activeGraphics;
	extern rend::GraphicsLib nextGraphics;

	extern rend::Resolution activeResolution;
	
	extern float deltaTime;

	extern vec::Vector2 windowSize;
	extern float windowRatio;

	extern std::string mouseSprite;
	extern vec::Vector2 mousePos;

	extern rend::SpriteData defaultContainerTexture;

	extern rend::SpriteData defaultButtonMainTexture;
	extern rend::SpriteData defaultButtonHoveredTexture;

	extern rend::AudioData defaultButtonClickDownSound;
	extern rend::AudioData defaultButtonClickUpSound;
	extern rend::AudioData defaultButtonHoverSound;

	extern rend::TextData defaultFont;
}

namespace btn {

	struct Container {

		vec::Vector2 pos;
		vec::Vector2 offset;

		vec::Vector2 size;

		bool isRendered = false;
		bool useTexture = false;

		Color color = WHITE;

		rend::SpriteData texture;
	};

	struct Button {

		// active
		bool isActive = false;
		bool isRendered = true;

		//signal

		bool signal = false;

		bool startSignalTimer = false;
		float signalTimer = 0.0f;
		float signalTimerLimit = 0.2f;

		// interface
		bool isClicked = false;
		bool isHovered = false;

		bool isClickedDownChange = false;
		bool isClickedUpChange = false;
		bool isHoveredChange = false;


		//positions
		vec::Vector2 pos = { 0,0 };
		vec::Vector2 offset = { 0,0 };

		vec::Vector2 clickedOffset = { 0,-0.25f };

		vec::Vector2 size = { 0,0 };

		//Text
		bool useText = true;

		std::string text = "Text";
		float fontSize = 50;

		rend::TextData textData;

		//colors
		Color activeColor = LIGHTGREY;

		Color mainColor = LIGHTGREY;
		Color hoveredColor = DARKGREY;

		Color textColor = GREEN;

		//textures
		bool useSprite = false;

		rend::SpriteData activeTexture;

		rend::SpriteData mainTexture;
		rend::SpriteData hoveredTexture;

		//sounds

		bool slAudioInit = false;
		bool raylibAudioInit = false;

		rend::AudioData clickedDownSound;
		rend::AudioData clickedUpSound;
		rend::AudioData hoveredSound;
	};

	void InitButtonDefaults();
	void DeInitButtonDefaults();

	void Init(Button& button, bool firstInit = false);
	void Init(Button buttons[], int buttonsSize);
	void Init(Button& button, Container& container, bool firstInit = false);
	void Init(Container& container, Button buttons[], int buttonsSize);
	void Init(Container& container);

	bool isHovered(Button button);
	bool isClicked(Button button);

	void UpdateInput(Button& button);
	void UpdateInput(Button buttons[], int buttonsSize);

	void Sound(Button button);
	void Sound(Button buttons[], int buttonsSize);
	void Draw(Button& button);
	void Draw(Container container);
	void Draw(Button buttons[], int buttonsSize);
	void Draw(Container container, Button buttons[], int buttonsSize);

}

namespace drw {

	vec::Vector2 PercentToScreen(vec::Vector2 vec);

	void Clear(Color color = BLACK);

	bool InitSpriteData(rend::SpriteData& spriteData);
	bool DeInitSpriteData(rend::SpriteData& spriteData);

	void Begin();
	void End();

	bool Sprite(rend::SpriteData sprite, vec::Vector2 pos = { 0,0 }, vec::Vector2 size = { 0,0 }, vec::Vector2 offset = { 0,0 }, Color color = WHITE);
	void Text(const char* text, rend::TextData& textData, vec::Vector2 pos = { 0,0 }, int fontSize = 10, vec::Vector2 offset = { 0,0 }, Color color = WHITE);
	void Triangle(vec::Vector2 p1, vec::Vector2 p2, vec::Vector2 p3, Color color = WHITE);
	void Rectangle(vec::Vector2 pos, vec::Vector2 size, Color color = WHITE, vec::Vector2 offset = { 0,0 });
	void Circle(vec::Vector2 pos, vec::Vector2 size, Color color = WHITE);

}

namespace snd {

	void StartAudioDevice();
	void EndAudioDevice();

	void Init(rend::AudioData& audioData);
	void DeInit(rend::AudioData& audioData);
	void Play(rend::AudioData& audioData, bool loop = false);
	void Pause(rend::AudioData& audioData, bool pause = true);
	void Stop(rend::AudioData& audioData);

	bool IsPlaying(rend::AudioData& audioData);

}

namespace fnt {

	void Init(rend::TextData& textData);
	void DeInit(rend::TextData& textData);

}

namespace upd {

	bool isMouseOver(vec::Vector2 pos, vec::Vector2 size);
	bool isMouseClicking(vec::Vector2 pos, vec::Vector2 size);
}