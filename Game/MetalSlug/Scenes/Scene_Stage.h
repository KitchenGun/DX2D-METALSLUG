#pragma once
class Stage :public Scene
{
public:
	Stage();
	~Stage();

	void Init() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	TextureRect* Map = nullptr;
	Player* player = nullptr;
	//지형 테스트
	Ground* ground = nullptr;
};