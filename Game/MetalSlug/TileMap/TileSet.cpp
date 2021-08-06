#include "stdafx.h"
#include "TileSet.h"

TileSet::TileSet()//애니메이션과 유사한 방식으로 이미지를 자름
{
	tileSprite = new Texture2D(L"./_Textures/TileMap.jpg");
	texId = tileSprite->GetSRV();
	imageSize = Vector2((float)tileSprite->GetWidth(), (float)tileSprite->GetHeight());

	tileXCount = 10;
	tileYCount = 18;
	//uv처럼 정규화 시킴
	UISize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);

	texelTileSize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);
}

TileSet::~TileSet()
{
	SAFE_DELETE(tileSprite);
}

void TileSet::GUI()
{
	static bool bOpen = true;
	ImGui::Begin("TileSprite", &bOpen);
	{
		int index = 0;
		for (UINT y = 0; y < tileYCount; y++)
		{
			for (UINT x = 0; x < tileXCount; x++)
			{
				ImGui::PushID(x + (y*tileYCount));//순서대로 id설정
				if(ImGui::ImageButton(texId,ImVec2(x*texelTileSize.x,y*texelTileSize.y),ImVec2(texelTileSize.x+(x*texelTileSize.x),texelTileSize.y+(y*texelTileSize.y))));
				{
					selectedStartUv = Vector2(x*texelTileSize.x, y*texelTileSize.y);
				}
				index++;
				ImGui::PopID();
				//4개씩 같은 라인으로 함
				if (index % 4 != 0)
					ImGui::SameLine();
			}
		}
	}
	ImGui::End();
}
