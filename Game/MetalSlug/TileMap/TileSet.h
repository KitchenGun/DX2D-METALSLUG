#pragma once

class TileSet
{
public:
	TileSet();
	~TileSet();

	void GUI();

private:
	Texture2D* tileSprite;
	ImTextureID texId;//imgui사용자 자료정의형
	Vector2 imageSize;
	UINT tileXCount;
	UINT tileYCount;

	Vector2 texelTileSize;
	Vector2 UISize;
	Vector2 selectedStartUv;
};