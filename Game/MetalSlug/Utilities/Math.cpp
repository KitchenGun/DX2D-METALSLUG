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

bool Math::Intersect(PlayerAnimationRect* r2, PlayerAnimationRect* r1)
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

bool Math::Intersect(PlayerAnimationRect* r1, AnimationRect* r2)
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

bool Math::GroundIntersect(PlayerAnimationRect* p1, vector<Ground*> GL)
{
	for (Ground* tempGroundOBj : GL)
	{
		//수정 필요 로컬 좌표가 이상함
		if (p1->GetPosition().x > tempGroundOBj->GetTransformedCoord().LT.x &&p1->GetPosition().x<tempGroundOBj->GetTransformedCoord().RB.x)
		{
			if (tempGroundOBj->GetisObb())
			{
				return GroundObbIntersect(p1, tempGroundOBj);
			}
			else
			{
				return Intersect(p1, tempGroundOBj);
			}
		}
	}
	//플레이어 좌표가 이상한 경우
	return false;
}

bool Math::GroundIntersect(AnimationRect* r1, vector<Ground*> GL)
{
	for (Ground* tempGroundOBj : GL)
	{
		if (r1->GetPosition().x > tempGroundOBj->GetTransformedCoord().LT.x && r1->GetPosition().x < tempGroundOBj->GetTransformedCoord().RB.x)
		{
			if (tempGroundOBj->GetisObb())
			{
				return GroundObbIntersect(r1, tempGroundOBj);
			}
			else
			{
				return Intersect(tempGroundOBj, r1);
			}
		}
	}
	//플레이어 좌표가 이상한 경우
	return false;
}

bool Math::GroundObbIntersect(PlayerAnimationRect* p1, Ground* g1)
{
	Vector3 dist = p1->GetTransformedCoord().Point - g1->GetTransformedCoord().Point;
	cout << String::ToString(p1->GetTransformedCoord().Point) << endl;
	cout << String::ToString(g1->GetTransformedCoord().Point) << endl;
	Vector3 r1Up = p1->Up() * p1->GetScale().y * 0.5f;
	Vector3 r1Right = p1->Right() * p1->GetScale().x * 0.5f;

	Vector3 r2Up = g1->Up() * g1->GetScale().y * 0.5f;
	Vector3 r2Right = g1->Right() * g1->GetScale().x * 0.5f;

	//첫번째 조건 : p1->Right()가 임의의 축
	float c = fabs(Dot(dist, p1->Right()));
	float a = fabs(Dot(r2Up, p1->Right())) + fabs((Dot(r2Right, p1->Right())));
	float b = p1->GetScale().x * 0.5f;
	if (c > a + b)
		return false;
	//두번재 조건 : p1->Up()가 임의의 축
	c = fabs(Dot(dist, p1->Up()));
	a = fabs(Dot(r2Up, p1->Up())) + fabs((Dot(r2Right, p1->Up())));
	b = p1->GetScale().y * 0.5f;
	if (c > a + b)
		return false;
	//세번째 조건 : g1->Right()가 임의의 축
	c = fabs(Dot(dist, g1->Right()));
	a = fabs(Dot(r1Up, g1->Right())) + fabs((Dot(r1Right, g1->Right())));
	b = g1->GetScale().x * 0.5f;
	if (c > a + b)
		return false;
	//네번째 조건 : g1->Up()가 임의의 축
	c = fabs(Dot(dist, g1->Up()));
	a = fabs(Dot(r1Up, g1->Up())) + fabs((Dot(r1Right, g1->Up())));
	b = g1->GetScale().y * 0.5f;
	if (c > a + b)
		return false;

	return true;
}

bool Math::GroundObbIntersect(AnimationRect* r1, Ground* g1)
{
	Vector3 dist = r1->GetPosition() - g1->GetPosition();

	Vector3 r1Up = r1->Up() * r1->GetScale().y * 0.5f;
	Vector3 r1Right = r1->Right() * r1->GetScale().x * 0.5f;

	Vector3 r2Up = g1->Up() * g1->GetScale().y * 0.5f;
	Vector3 r2Right = g1->Right() * g1->GetScale().x * 0.5f;

	//첫번째 조건 : r1->Right()가 임의의 축
	float c = fabs(Dot(dist, r1->Right()));
	float a = fabs(Dot(r2Up, r1->Right())) + fabs((Dot(r2Right, r1->Right())));
	float b = r1->GetScale().x * 0.5f;
	if (c > a + b)
		return false;
	//두번재 조건 : r1->Up()가 임의의 축
	c = fabs(Dot(dist, r1->Up()));
	a = fabs(Dot(r2Up, r1->Up())) + fabs((Dot(r2Right, r1->Up())));
	b = r1->GetScale().y * 0.5f;
	if (c > a + b)
		return false;
	//세번째 조건 : g1->Right()가 임의의 축
	c = fabs(Dot(dist, g1->Right()));
	a = fabs(Dot(r1Up, g1->Right())) + fabs((Dot(r1Right, g1->Right())));
	b = g1->GetScale().x * 0.5f;
	if (c > a + b)
		return false;
	//네번째 조건 : g1->Up()가 임의의 축
	c = fabs(Dot(dist, g1->Up()));
	a = fabs(Dot(r1Up, g1->Up())) + fabs((Dot(r1Right, g1->Up())));
	b = g1->GetScale().y * 0.5f;
	if (c > a + b)
		return false;

	return true;
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

float Math::Dot(Vector3 v1, Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
