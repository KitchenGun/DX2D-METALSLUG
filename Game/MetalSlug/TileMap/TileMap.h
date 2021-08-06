#pragma once
class TileSet;

struct Tile//타일 구조체
{
	Vector3 pos;
	Vector2 uvStart;
	Vector2 uvEnd;
	Color color;
};

class TileMap
{
public:
	friend class TileSet;//타일 셋에서 좌표를 가져오기 위해서
public:
	TileMap(Vector2 position, Vector3 size, float rotation);
	~TileMap();

private:
	UINT width, height;
	UINT vertexCount;
	UINT indexCount;

	vector<VertexTextureColor> vertices;
	vector<UINT> indices;
	Tile** tiles;						//???왜 더블포인터 인지 아직 모르겠음
	UINT spacing;
	InputLayout* IL = nullptr;
};