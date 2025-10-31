#include "BorjaLib.h"

namespace coll {


	bool PointOnRec(vec::Vector2 point, vec::Vector2 pos, vec::Vector2 size)
	{
		if (!(point.x > pos.x - size.x / 2.0f && point.x < pos.x + size.x / 2.0f)) {
			return false;
		}
		if (!(point.y > pos.y - size.y / 2.0f && point.y < pos.y + size.y / 2.0f)) {
			return false;
		}
		return true;
	}

	bool PointOnCircle(vec::Vector2 point, vec::Vector2 pos, float radius)
	{
		if ((point - pos).magnitude() < radius) {
			return true;
		}
		return false;
	}

	bool RecOnRec(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2, vec::Vector2& point)
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

	bool CircleOnCircle(vec::Vector2 pos1, vec::Vector2 pos2, float radius1, float radius2, vec::Vector2& point)
	{
		vec::Vector2 distance = { pos1.x - pos2.x, pos1.y - pos2.y };
		distance = { distance.x * distance.x, distance.y * distance.y };

		if ((distance.x + distance.y) <= ((radius1 + radius2) * (radius1 + radius2))) {
			point = (pos1 + pos2) * 0.5f;
			return true;
		}
		return false;
	}

	bool CircleOnCircle(vec::Vector2 pos1, vec::Vector2 pos2, float radius1, float radius2)
	{
		vec::Vector2 point;
		return CircleOnCircle(pos1, pos2, radius1, radius2, point);
	}

	//bool RecOnElipse(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2, vec::Vector2& point)
	//{
	//
	//}
	//
	//bool RecOnElipse(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2, vec::Vector2& point)
	//{
	//	return false;
	//}
	//
	bool RecOnCircle(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, vec::Vector2 size2, vec::Vector2& point)
	{
		vec::Vector2 closest = pos2;

		if (pos2.x < pos1.x - size1.x / 2.0f) {
			closest.x = pos1.x - size1.x / 2.0f;
		}
		if (pos2.x > pos1.x + size1.x / 2.0f) {
			closest.x = pos1.x + size1.x / 2.0f;
		}

		if (pos2.y < pos1.y - size1.y / 2.0f) {
			closest.y = pos1.y - size1.y / 2.0f;
		}
		if (pos2.y > pos1.y + size1.y / 2.0f) {
			closest.y = pos1.y + size1.y / 2.0f;
		}

		vec::Vector2 distance = pos2 - distance;

		float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y);

		return distanceSquared <= (size2.x * size2.x);
	}
	//
	//bool RecOnCircle(vec::Vector2 pos1, vec::Vector2 size1, vec::Vector2 pos2, float radius, vec::Vector2& point)
	//{
	//	return false;
	//}

}