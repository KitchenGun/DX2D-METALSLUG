#pragma once

#define VK_00 48//정의되지 않은 가상키 정의
#define VK_01 49
#define VK_02 50
#define VK_03 51
#define VK_04 52
#define VK_05 53
#define VK_06 54
#define VK_07 55
#define VK_08 56
#define VK_09 57

class Square;

class Math
{
	//static 함수를 사용하여서 객체없이 사용할수있도록 제작
public:
	//충돌
	static bool Intersect(Square *r1, Square *r2); 
	static bool Intersect(PlayerAnimationRect* r2, PlayerAnimationRect* r1);
	static bool Intersect(PlayerAnimationRect* r1, AnimationRect* r2);
	static bool Intersect(AnimationRect* r1, AnimationRect* r2);
	static bool Intersect(Square *rect, Vector3 position);
	//OBB 충돌
	static bool OBBIntersect(PlayerAnimationRect* r1, AnimationRect* r2);
	//바닥 충돌
	static bool GroundIntersect(Player* p1, vector<Ground*> GL);//캐릭터 바닥 충돌
	static bool GroundIntersect(Enemy* e1, vector<Ground*> GL);//캐릭터 바닥 충돌
	static bool GroundIntersect(Player* p1, PlayerAnimationRect* o1);//캐릭터 바닥 충돌
	static bool GroundIntersect(Enemy* e1, PlayerAnimationRect* o1);//캐릭터 바닥 충돌
	static bool GroundIntersect(AnimationRect* r1, vector<Ground*> GL);//투사체 및 사물 바닥 충돌
	//바닥 OBB 충돌
	static bool GroundObbIntersect(Player* p1, Ground* g1);//캐릭터 바닥 충돌
	static bool GroundObbIntersect(Enemy* e1, Ground* g1);//캐릭터 바닥 충돌
	static bool GroundObbIntersect(PlayerAnimationRect* p1, Ground* g1);//캐릭터 바닥 충돌
	static bool GroundObbIntersect(AnimationRect* r1, Ground* g1);//투사체 및 사물 바닥 충돌
	//절댓값 반환
	static Vector2 absVec2(Vector2 val);
	static Vector3 absVec3(Vector3 val);
	//lerp
	static float Lerpf(float min, float max, float target);
	//dist
	static float Distance(Vector3 v1, Vector3 v2);
	//내적
	static float Dot(Vector3 v1, Vector3 v2);
};