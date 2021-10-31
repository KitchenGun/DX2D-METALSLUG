#pragma once
class SFXManager
{
public:
	SFXManager();
	~SFXManager();

	void Update();
	void Render();

	void AddSFX(Vector3 position, DIRECTION dir, PROJECTILETYPE BT,bool loop = false);
	void RemoveSFX(SFX* tempSFX);

	list<SFX*> GetList() { return SFXList; }

private:
	list<SFX*> SFXList;
	list<SFX*>::iterator iter;

	SoundSystem* sound = nullptr;
};