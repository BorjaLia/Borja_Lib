#include "BorjaLib.h"

namespace btn {

	int ToInt(ButtonType type)
	{
		return static_cast<int>(type);
	}

	ButtonType ToButtonType(int num)
	{
		return static_cast<ButtonType>(num);
	}

	void Init(Button& button)
	{
		button.isActive = true;
		button.isRendered = true;
	}

	void Init(Button buttons[], int buttonsSize)
	{
		for (int b = 0; b < buttonsSize; b++)
		{
			Init(buttons[b]);
		}
	}

	void Init(Button& button, Container& container, bool firstInit)
	{
		Init(button);

		if (firstInit) {

			button.pos.x *= container.size.x;
			button.pos.y *= container.size.y;
			button.pos.x += container.pos.x - container.size.x / 2;
			button.pos.y += container.pos.y - container.size.y / 2;
		}
	}

	void Init(Container& container, Button buttons[], int buttonsSize)
	{
		for (int b = 0; b < buttonsSize; b++)
		{
			Init(buttons[b], container);
		}
	}

	void Init(Container& container)
	{
		container.size = drw::PercentToScreen(container.size);
	}

	bool isHovered(Button button)
	{
		if (!button.isActive) {
			return false;
		}
		return upd::isMouseOver(button.pos, button.size);
	}

	bool isClicked(Button button)
	{
		if (!button.isActive) {
			return false;
		}
		return upd::isMouseClicking(button.pos, button.size);
	}

	void UpdateInput(Button& button) {

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

	void UpdateInput(Button buttons[], int buttonsSize)
	{
		for (int b = 0; b < buttonsSize; b++)
		{
			UpdateInput(buttons[b]);
		}
	}

	void Sound(Button button) {

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

	void Sound(Button buttons[], int buttonsSize)
	{
		for (int b = 0; b < buttonsSize; b++)
		{
			Sound(buttons[b]);
		}
	}

	void Draw(Button& button) {

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

	void Draw(Container container)
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

	void Draw(Button buttons[], int buttonsSize)
	{
		for (int i = 0; i < buttonsSize; i++)
		{
			Draw(buttons[i]);
		}
	}

	void Draw(Container container, Button buttons[], int buttonsSize)
	{
		Draw(container);
		Draw(buttons, buttonsSize);
	}
}