#pragma once

class SoldierUpper : public PlayerAnimationRect//upper
{
public://생성자 소멸자 update render
	SoldierUpper(Vector3 position, Vector3 size, float rotation);
	~SoldierUpper();
	void Update() override;
	void Render() override;
	void SetClip(string name, bool isRestart = false);//애니메이션 이름에 따른 애니메이션 설정
	void PivotUpdate();//이동에 따른 애니메이션의 지속적인 위치와 크기 변환 처리
public:
	void SetAnimation();
	void SetSize(Vector3 tempSize);
	void SetPos(Vector3 tempPos);
	void SetPlayer(Player* player) { this->player = player; }
	bool GetisPistol() { return isPistol; }
	void SetisPistol(bool val) { isPistol = val; }
	Animator* GetAnimator() { return animator; }
private:
	Player* player;
	bool isPistol;
};