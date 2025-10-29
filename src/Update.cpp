#include "BorjaLib.h"

namespace upd {

	bool isMouseOver(vec::Vector2 pos, vec::Vector2 size)
	{
		bool horizontalCollision = rend::mousePos.x > pos.x - size.x / 2 && rend::mousePos.x < pos.x + size.x / 2;
		bool verticalCollision = rend::mousePos.y > pos.y - size.y / 2 && rend::mousePos.y < pos.y + size.y / 2;

		return horizontalCollision && verticalCollision;
	}

	bool isMouseClicking(vec::Vector2 pos, vec::Vector2 size)
	{
		if (!isMouseOver(pos, size)) {
			return false;
		}

		return ctrl::IsMouseDown(ctrl::ButtonMouse::LMB);
	}
}