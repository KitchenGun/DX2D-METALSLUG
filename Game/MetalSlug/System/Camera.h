#pragma once

class Camera : public Singleton<Camera>
{
public:
	friend class Singleton<Camera>;

	void Update();
	void Render();

	void Move(Vector3 position);
	void SetCamPos(Vector3 position);
	void UpdateView();

	void UnProjection(Vector3* out, Vector3 source, Matrix world);
	void SetCamPosLimit(float MaxX, float MinX, float fYValue) { fMaxXValue = MaxX; fMinXValue = MinX; fYValue = fYValue; }
	Vector3 GetCamPos() { return position; }
private:
	Camera();
	~Camera();

	ViewProjectionBuffer* VPBuffer = nullptr;
	Matrix view, proj;
	float fMinXValue = 0;
	float fMaxXValue = 0;
	float fYValue = 0;
	Vector3 position = Vector3(0, 0, 0);
};