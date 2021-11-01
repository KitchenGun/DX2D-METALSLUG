#pragma once

class Intro :public Scene
{
public:
	Intro();
	~Intro();

	void Init() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

	int index=0;

private:
	TextureRect* Main = nullptr;
	SoundSystem* BGM = nullptr;
	SoundSystem* OK = nullptr;
	bool IsStart = false;
};