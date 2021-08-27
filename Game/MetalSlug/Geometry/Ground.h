#pragma once

class Animator;
class AnimationClip;

class Ground : public PlayerAnimationRect
{
public:

	Ground(Vector3 position, Vector3 size, float rotation,bool isObb);
	~Ground();

	void Update() override;
	void Render() override;

	bool GetisObb() { return isObb; }
private:
	bool isObb = true;
};