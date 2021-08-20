#include "stdafx.h"
#include "Math.h"

#include "Geometry/Line.h"
#include "Geometry/Square.h"
#include "Geometry/Circle.h"
#include "Geometry/FilledCircle.h"
#include "Geometry/TextureRect.h"

bool Math::Intersect(Square *r1, Square *r2)
{
	RectEdges edge1 = r1->GetTransformedCoord();
	RectEdges edge2 = r2->GetTransformedCoord();

	if (edge1.RB.x >= edge2.LT.x && edge1.LT.x <= edge2.RB.x&&edge1.LT.y >= edge2.RB.y && edge1.RB.y <= edge2.LT.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Math::Intersect(Player* p1, PlayerAnimationRect* r1)
{
	Vector3 pPos=p1->GetPosition();
	RectEdges edge = r1->GetTransformedCoord();
	if (pPos.x >= edge.LT.x && pPos.x <= edge.RB.x && pPos.y >= edge.RB.y && pPos.y <= edge.LT.y)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

bool Math::Intersect(AnimationRect* r1, AnimationRect* r2)
{
	RectEdges edge1 = r1->GetTransformedCoord();
	RectEdges edge2 = r2->GetTransformedCoord();

	if (edge1.RB.x >= edge2.LT.x && edge1.LT.x <= edge2.RB.x && edge1.LT.y >= edge2.RB.y && edge1.RB.y <= edge2.LT.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Math::Intersect(Square * rect, Vector3 position)
{
	RectEdges e1 = rect->GetTransformedCoord();
	if (e1.RB.x >= position.x&&e1.LT.x <= position.x&&e1.LT.y >= position.y&&e1.RB.y <= position.y)
		return true;
	else
		return false;
}

Vector2 Math::absVec2(Vector2 val)
{
	float x = abs(val.x);
	float y = abs(val.y);
	return Vector2(x, y);
}

Vector3 Math::absVec3(Vector3 val)
{
	float x = abs(val.x);
	float y = abs(val.y);
	float z = abs(val.z);
	return Vector3(x, y, z);
}

float Math::Lerpf(float min, float max, float target)
{
	return min + target * (max - min);
}

float Math::Distance(Vector3 v1, Vector3 v2)
{
	return sqrtf(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

