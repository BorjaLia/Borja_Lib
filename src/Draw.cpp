#include "BorjaLib.h"

namespace drw {

	SpriteData defaultSprite;
	SpriteData spriteDataList[spriteDataMaxAmount] = {};

	FontData defaultFont;
	FontData fontDataList[fontDataMaxAmount] = {};

	vec::Vector2 PercentToScreen(vec::Vector2 vec)
	{
		return vec::Vector2(vec.x * rend::windowRatio, vec.y);
	}


	void Clear(bColor color)
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

	int InitSpriteData(SpriteData& spriteData)
	{
		int availableID = 0;
		int currentID = -1;

		bool isAvailable = false;
		while (!isAvailable) {
			currentID++;

			isAvailable = !spriteDataList[currentID].active;

			if (isAvailable) {
				availableID = currentID;
			}
			if (currentID == spriteDataMaxAmount - 1) {
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

		spriteDataList[availableID] = spriteData;
		return availableID;
	}

	bool DeInitSpriteData(SpriteData& spriteData)
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

	int InitAnimData(AnimationData& animData, SpriteData spriteData[], int frames)
	{
		animData.frames = frames;

		animData.timeOffset = rend::secondCounter;

		int firstSpot = 0;
		int currentSpot = 0;

		for (int i = 0; i < frames; i++)
		{
			currentSpot = InitSpriteData(spriteData[i]);

			if (currentSpot == spriteDataMaxAmount - 1) {
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

	int InitFontData(FontData& fontData)
	{
		int availableID = 0;
		int currentID = -1;

		bool isAvailable = false;
		while (!isAvailable) {
			currentID++;

			isAvailable = !fontDataList[currentID].active;

			if (isAvailable) {
				availableID = currentID;
			}
			if (currentID == fontDataMaxAmount - 1) {
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

		fontDataList[availableID] = fontData;
		return availableID;
	}

	void Begin()
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

	void End()
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
				Text(mousePosX.c_str(), { 0.015f,0.95f }, 20, { 0.0f,0 }, GREEN_B);
				Text(mousePosY.c_str(), { 0.09f,0.95f }, 20, { 0.0f,0.0f }, GREEN_B);

				mouseDeltaX = std::to_string((rend::mouseDelta.x * 100));
				mouseDeltaY = std::to_string((rend::mouseDelta.y * 100));
				Text(mouseDeltaX.c_str(), { 0.015f,0.92f }, 20, { 0.0f,0.0f }, GREEN_B);
				Text(mouseDeltaY.c_str(), { 0.09f,0.92f }, 20, { 0.0f,0.0f }, GREEN_B);
			case rend::InfoMode::BASIC: {
				std::string framerate = std::to_string(static_cast<int>(rend::framerate));
				std::string seconds = std::to_string(static_cast<int>(rend::secondCounter));
				Text(framerate.c_str(), { 0.015f,0.98f }, 20, { 0.0f,0.0f }, GREEN_B);
				Text(seconds.c_str(), { 0.09f,0.98f }, 20, { 0.0f,0.0f }, GREEN_B);
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
			Text(devInfoText.c_str(), { 0.95f ,0.98f }, 20, { 0.0f,0.0f }, BLUE_B);

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

			Text(devModeText.c_str(), { 0.95f - devModeTextOffset.x ,0.98f - devModeTextOffset.y }, 20, { 0.0f,0.0f }, RED_B);

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

	bool Animation(AnimationData& animation, vec::Vector2 pos, vec::Vector2 size, vec::Vector2 offset, bColor color)
	{
		if (!animation.active) {
			return false;
		}

		if (rend::secondCounter - animation.timeOffset > animation.duration) {
			animation.timeOffset = rend::secondCounter;
		}

		//std::cout << "Frame: " << animation.id + ((int)(((rend::secondCounter - animation.timeOffset) / animation.duration) * animation.frames)) << '\n';

		Sprite(spriteDataList[animation.id + ((int)(((rend::secondCounter - animation.timeOffset) / animation.duration) * animation.frames))], pos, size, offset, color);

		return true;
	}

	bool Sprite(SpriteData sprite, vec::Vector2 pos, vec::Vector2 size, vec::Vector2 offset, bColor color)
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

	void Text(const char* text, TextData& textData, vec::Vector2 pos, int fontSize, vec::Vector2 offset, bColor color)
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
			DrawTextPro(fontDataList[textData.fontID].font, text, { pos.x * rend::windowSize.x + offset.x * rend::windowSize.x - rend::windowSize.x * textSize.x / 3, rend::windowSize.y * (1.0f - pos.y) + (1.0f - offset.y * rend::windowSize.y) - rend::windowSize.y * textSize.y / 2 }, { textData.origin.x,textData.origin.y }, textData.rotation, tempFontSize, fontDataList[textData.fontID].spacing, { color.r,color.g,color.b,color.a });
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

	void Text(const char* text, vec::Vector2 pos, int fontSize, vec::Vector2 offset, bColor color)
	{
		TextData textData;
		Text(text, textData, pos, fontSize, offset, color);
	}

	void Text(TextData& textData, vec::Vector2 pos, int fontSize, vec::Vector2 offset, bColor color)
	{
		Text(textData.text.c_str(), textData, pos, fontSize, offset, color);
	}

	void Triangle(vec::Vector2 p1, vec::Vector2 p2, vec::Vector2 p3, bColor color)
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

	void Rectangle(vec::Vector2 pos, vec::Vector2 size, bColor color, vec::Vector2 offset)
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

	void Circle(vec::Vector2 pos, vec::Vector2 size, bColor color)
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

	void Line(vec::Vector2 start, vec::Vector2 end, bColor color)
	{
		Line(start, end, 0.0f, color);
	}

	void Line(vec::Vector2 start, vec::Vector2 end, float size, bColor color)
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

	//void ButtonClick(btn::ButtonClick button)
	//{
	//
	//	switch (button.type)
	//	{
	//	case btn::Type::Normal: {
	//		if (button.beingHeld) {
	//			button.offset += button.clickedOffset * button.size.y;
	//		}
	//		if (button.useSprite) {
	//			Sprite(button.activeSprite, button.pos, button.size, button.offset);
	//		}
	//		else {
	//			Rectangle(button.pos, button.size, button.activeColor, button.offset);
	//			Text(button.text.c_str(), button.pos, button.fontSize, button.offset, button.textColor);
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
	//			Sprite(button.activeSprite, button.pos, button.size, button.offset);
	//		}
	//		else {
	//			Rectangle(button.pos, button.size, button.activeColor, button.offset);
	//			Text(button.text.c_str(), button.pos, button.fontSize, button.offset, button.textColor);
	//		}
	//		break;
	//	}
	//	case btn::Type::Slider: {
	//		if (button.useSprite) {
	//			Sprite(button.activeSprite, button.pos, button.size, button.offset);
	//		}
	//		else {
	//			Rectangle(button.pos, button.size, button.activeColor, button.offset);
	//			Rectangle(button.pos, { button.size.x * 8 / 10,button.size.y / 3 }, button.textColor, button.offset);
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

	//void Container(btn::Container container, btn::ButtonClick buttons[], int buttonsSize)
	//{
	//	for (int i = 0; i < buttonsSize; i++)
	//	{
	//		ButtonClick(buttons[i]);
	//	}
	//}


}