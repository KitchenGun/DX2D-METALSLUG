#pragma once

#define VK_00 48//���ǵ��� ���� ����Ű ����
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
	//static �Լ��� ����Ͽ��� ��ü���� ����Ҽ��ֵ��� ����
public:
	//�浹
	static bool Intersect(Square *r1, Square *r2); 
	static bool Intersect(PlayerAnimationRect* r2, PlayerAnimationRect* r1);
	static bool Intersect(PlayerAnimationRect* r1, AnimationRect* r2);
	static bool Intersect(AnimationRect* r1, AnimationRect* r2);
	static bool Intersect(Square *rect, Vector3 position);
	//OBB �浹
	static bool OBBIntersect(PlayerAnimationRect* r1, AnimationRect* r2);
	//�ٴ� �浹
	static bool GroundIntersect(Player* p1, vector<Ground*> GL);//ĳ���� �ٴ� �浹
	static bool GroundIntersect(Enemy* e1, vector<Ground*> GL);//ĳ���� �ٴ� �浹
	static bool GroundIntersect(Player* p1, PlayerAnimationRect* o1);//ĳ���� �ٴ� �浹
	static bool GroundIntersect(Enemy* e1, PlayerAnimationRect* o1);//ĳ���� �ٴ� �浹
	static bool GroundIntersect(AnimationRect* r1, vector<Ground*> GL);//����ü �� �繰 �ٴ� �浹
	//�ٴ� OBB �浹
	static bool GroundObbIntersect(Player* p1, Ground* g1);//ĳ���� �ٴ� �浹
	static bool GroundObbIntersect(Enemy* e1, Ground* g1);//ĳ���� �ٴ� �浹
	static bool GroundObbIntersect(PlayerAnimationRect* p1, Ground* g1);//ĳ���� �ٴ� �浹
	static bool GroundObbIntersect(AnimationRect* r1, Ground* g1);//����ü �� �繰 �ٴ� �浹
	//���� ��ȯ
	static Vector2 absVec2(Vector2 val);
	static Vector3 absVec3(Vector3 val);
	//lerp
	static float Lerpf(float min, float max, float target);
	//dist
	static float Distance(Vector3 v1, Vector3 v2);
	//����
	static float Dot(Vector3 v1, Vector3 v2);
};