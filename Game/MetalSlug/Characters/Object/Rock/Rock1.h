#pragma once
class Rock1 : public Object
{
public:
	Rock1(Vector3 position, Vector3 size, float rotation);
	~Rock1();

	void Update() override;
	void Render() override;

};