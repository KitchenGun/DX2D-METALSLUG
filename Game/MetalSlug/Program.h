#pragma once

class Program
{
public:
	Program();
	~Program();

	void Init();
	void Update();
	void PreRender();
	void Render();
	void PostRender();

private:
	Scene* currentScene;
	vector<Scene*> sceneList;

};