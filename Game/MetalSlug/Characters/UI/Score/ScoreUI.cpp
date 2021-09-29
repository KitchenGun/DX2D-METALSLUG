#include "stdafx.h"
#include "ScoreUI.h"

ScoreUI::ScoreUI(GameManager* gm)
	:gm(gm)
{
	bar = new TextureRect(Camera::Get()->GetCamPos(), Vector3(45 * 4, 8 * 4, 1), 0);
	bar->SetSRV(L"./_Textures/UI/Bar.png");
	up = new TextureRect(Camera::Get()->GetCamPos(), Vector3(78 * 2, 18 * 1, 1), 0);
	up->SetSRV(L"./_Textures/UI/1UP=inf.png");
	print0 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 1, 16 * 1, 1), 0);
	print0->SetSRV(L"./_Textures/UI/Score0.png");
	print01 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 1, 16 * 1, 1), 0);
	print01->SetSRV(L"./_Textures/UI/Score0.png");
	//score
	score0 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 1, 16 * 1, 1), 0);
	score0->SetSRV(L"./_Textures/UI/Score0.png");
	score1 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 1, 16 * 1, 1), 0);
	score1->SetSRV(L"./_Textures/UI/Score0.png");
	score2 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 1, 16 * 1, 1), 0);
	score2->SetSRV(L"./_Textures/UI/Score0.png");
	score3 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 1, 16 * 1, 1), 0);
	score3->SetSRV(L"./_Textures/UI/Score0.png");
	score4 = new TextureRect(Camera::Get()->GetCamPos(), Vector3(16 * 1, 16 * 1, 1), 0);
	score4->SetSRV(L"./_Textures/UI/Score0.png");
}
 

ScoreUI::~ScoreUI()
{
	SAFE_DELETE(gm);
	SAFE_DELETE(up);
	SAFE_DELETE(bar);
	SAFE_DELETE(score4);
	SAFE_DELETE(score3);
	SAFE_DELETE(score2);
	SAFE_DELETE(score1);
	SAFE_DELETE(score0);
	SAFE_DELETE(print01);
	SAFE_DELETE(print0);
}

void ScoreUI::Update()
{
	SetPos(Camera::Get()->GetCamPos() + Vector3(400, WinMaxHeight - 50, 0));
	ScoreChange();
}

void ScoreUI::Render()
{
	bar->Render();
	up->Render();
	print0->Render();
	print01->Render();
	score0->Render();
	score1->Render();
	score2->Render();
	score3->Render();
	score4->Render();
}

void ScoreUI::SetPos(Vector3 pos)
{
	bar->Move(pos + Vector3(-250, -5, 0));
	up->Move(pos + Vector3(-250, -30, 0));
	print0->Move(pos + Vector3(-190, 25, 0));
	print01->Move(pos + Vector3(-173, 25, 0));
	score0->Move(pos + Vector3(-207, 25, 0));
	score1->Move(pos + Vector3(-224, 25, 0));
	score2->Move(pos + Vector3(-241, 25, 0));
	score3->Move(pos + Vector3(-258, 25, 0));
	score4->Move(pos + Vector3(-275, 25, 0));
}

void ScoreUI::ScoreChange()
{
	if (gm->GetScore() / 1000000 == 0)
	{
		score4->SetIsRender(false);
		if (gm->GetScore() / 100000 == 0)
		{
			score3->SetIsRender(false);
			if (gm->GetScore() / 10000 == 0)
			{
				score2->SetIsRender(false);
				if (gm->GetScore() / 1000 == 0)
				{
					score1->SetIsRender(false);
					if (gm->GetScore() / 100 == 0)
					{
						score0->SetIsRender(false);
					}
					else
					{
						score0->SetIsRender(true);
					}
				}
				else
				{
					score0->SetIsRender(true);
					score1->SetIsRender(true);
				}
			}
			else
			{
				score0->SetIsRender(true);
				score1->SetIsRender(true);
				score2->SetIsRender(true);
			}
		}
		else
		{
			score0->SetIsRender(true);
			score1->SetIsRender(true);
			score2->SetIsRender(true);
			score3->SetIsRender(true);
		}
	}
	else
	{
		score0->SetIsRender(true);
		score1->SetIsRender(true);
		score2->SetIsRender(true);
		score3->SetIsRender(true);
		score4->SetIsRender(true);
	}
	switch (gm->GetScore() / 100%10)
	{
	case 0:
		score0->SetSRV(L"./_Textures/UI/Score0.png");
		break;
	case 1:
		score0->SetSRV(L"./_Textures/UI/Score1.png");
		break;
	case 2:
		score0->SetSRV(L"./_Textures/UI/Score2.png");
		break;
	case 3:
		score0->SetSRV(L"./_Textures/UI/Score3.png");
		break;
	case 4:
		score0->SetSRV(L"./_Textures/UI/Score4.png");
		break;
	case 5:
		score0->SetSRV(L"./_Textures/UI/Score5.png");
		break;
	case 6:
		score0->SetSRV(L"./_Textures/UI/Score6.png");
		break;
	case 7:
		score0->SetSRV(L"./_Textures/UI/Score7.png");
		break;
	case 8:
		score0->SetSRV(L"./_Textures/UI/Score8.png");
		break;
	case 9:
		score0->SetSRV(L"./_Textures/UI/Score9.png");
		break;
	default:
		break;
	}
	switch (gm->GetScore() / 1000%10)
	{
	case 0:
		score1->SetSRV(L"./_Textures/UI/Score0.png");
		break;
	case 1:
		score1->SetSRV(L"./_Textures/UI/Score1.png");
		break;
	case 2:
		score1->SetSRV(L"./_Textures/UI/Score2.png");
		break;
	case 3:
		score1->SetSRV(L"./_Textures/UI/Score3.png");
		break;
	case 4:
		score1->SetSRV(L"./_Textures/UI/Score4.png");
		break;
	case 5:
		score1->SetSRV(L"./_Textures/UI/Score5.png");
		break;
	case 6:
		score1->SetSRV(L"./_Textures/UI/Score6.png");
		break;
	case 7:
		score1->SetSRV(L"./_Textures/UI/Score7.png");
		break;
	case 8:
		score1->SetSRV(L"./_Textures/UI/Score8.png");
		break;
	case 9:
		score1->SetSRV(L"./_Textures/UI/Score9.png");
		break;
	default:
		break;
	}
	switch (gm->GetScore() / 10000 % 10)
	{
	case 0:
		score2->SetSRV(L"./_Textures/UI/Score0.png");
		break;
	case 1:
		score2->SetSRV(L"./_Textures/UI/Score1.png");
		break;
	case 2:
		score2->SetSRV(L"./_Textures/UI/Score2.png");
		break;
	case 3:
		score2->SetSRV(L"./_Textures/UI/Score3.png");
		break;
	case 4:
		score2->SetSRV(L"./_Textures/UI/Score4.png");
		break;
	case 5:
		score2->SetSRV(L"./_Textures/UI/Score5.png");
		break;
	case 6:
		score2->SetSRV(L"./_Textures/UI/Score6.png");
		break;
	case 7:
		score2->SetSRV(L"./_Textures/UI/Score7.png");
		break;
	case 8:
		score2->SetSRV(L"./_Textures/UI/Score8.png");
		break;
	case 9:
		score2->SetSRV(L"./_Textures/UI/Score9.png");
		break;
	default:
		break;
	}
	switch (gm->GetScore() / 100000 % 10)
	{
	case 0:
		score3->SetSRV(L"./_Textures/UI/Score0.png");
		break;
	case 1:
		score3->SetSRV(L"./_Textures/UI/Score1.png");
		break;
	case 2:
		score3->SetSRV(L"./_Textures/UI/Score2.png");
		break;
	case 3:
		score3->SetSRV(L"./_Textures/UI/Score3.png");
		break;
	case 4:
		score3->SetSRV(L"./_Textures/UI/Score4.png");
		break;
	case 5:
		score3->SetSRV(L"./_Textures/UI/Score5.png");
		break;
	case 6:
		score3->SetSRV(L"./_Textures/UI/Score6.png");
		break;
	case 7:
		score3->SetSRV(L"./_Textures/UI/Score7.png");
		break;
	case 8:
		score3->SetSRV(L"./_Textures/UI/Score8.png");
		break;
	case 9:
		score3->SetSRV(L"./_Textures/UI/Score9.png");
		break;
	default:
		break;
	}
	switch (gm->GetScore() / 100000 % 10)
	{
	case 0:
		score4->SetSRV(L"./_Textures/UI/Score0.png");
		break;
	case 1:
		score4->SetSRV(L"./_Textures/UI/Score1.png");
		break;
	case 2:
		score4->SetSRV(L"./_Textures/UI/Score2.png");
		break;
	case 3:
		score4->SetSRV(L"./_Textures/UI/Score3.png");
		break;
	case 4:
		score4->SetSRV(L"./_Textures/UI/Score4.png");
		break;
	case 5:
		score4->SetSRV(L"./_Textures/UI/Score5.png");
		break;
	case 6:
		score4->SetSRV(L"./_Textures/UI/Score6.png");
		break;
	case 7:
		score4->SetSRV(L"./_Textures/UI/Score7.png");
		break;
	case 8:
		score4->SetSRV(L"./_Textures/UI/Score8.png");
		break;
	case 9:
		score4->SetSRV(L"./_Textures/UI/Score9.png");
		break;
	default:
		break;
	}
}
