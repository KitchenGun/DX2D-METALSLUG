#include "stdafx.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReverse)
	: clipName(clipName), 
	frameCount(frameCount), 
	bReverse(bReverse)
{
	//clip이란 애니메이션 동작의 묶음
	//텍스쳐 가져옴
	srv = srcTex->GetSRV();

	float imageWidth = (float)srcTex->GetWidth();
	float imageHeight = (float)srcTex->GetHeight();
	
	//이미지 갯수
	Vector2 clipSize = Math::absVec2(endPos - startPos);
	Vector2 frameSize;
	//애니메이션으로 사용할 이미지를 어느정도 크기로 자를것인가?
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;
	//이미지의 화소를 텍셀이라고 함
	Vector2 texelSize = Vector2(1.0f / imageWidth, 1.0f / imageHeight);
							//화면기준의 포지션을 텍셀기준으로 비율 변경
	Vector2 texelStartPos = Vector2(startPos.x * texelSize.x, startPos.y * texelSize.y);
	texelFrameSize = Vector2(frameSize.x * texelSize.x, frameSize.y * texelSize.y);
	//이미지 갯수만큼 돌림
	for (UINT i = 0; i < frameCount; i++)
	{
		Vector2 keyframe;
		keyframe.x = texelStartPos.x + texelFrameSize.x * i;//이미지의 시작 좌표
		keyframe.y = texelStartPos.y;
		keyframes.push_back(keyframe);
	}
}

AnimationClip::~AnimationClip()
{
}

Animator::Animator(AnimationClip* animClip)
	: currentAnimClip(animClip)
{
	//자료구조에 집어넣을때 키(이름)와 넣을 데이터(클립)를 추가함
	animClips.insert(make_pair(animClip->GetClipName(), animClip));
}

Animator::Animator(vector<AnimationClip*> animClips)
	:currentAnimClip(animClips[0])
{
	for (AnimationClip* animClip : animClips)
	{
		this->animClips.insert(make_pair(animClip->GetClipName(), animClip));
	}
}

Animator::~Animator()
{

}

void Animator::Update()
{
	if (bStop) return;
	
	//cout << deltaTime << " " << playRate << endl;
	//프레임에서 프레임으로 넘어가는 시간
	//cout << String::ToString(currentAnimClip->GetClipName()) <<" "<<currentFrameIndex << endl;
	if (deltaTime > playRate)//일정 시간 마다 실행하여 그림 변경 함 
	{
		if (currentAnimClip->GetIsReverse() == false)//반전 여부 
		{
			currentFrameIndex++;
			
			if (currentFrameIndex >= currentAnimClip->GetLastFrameIndex() && bLoop)//반복을 시킬 때 이미지를 반복한다
			{
				if (changeBlock == true)
				{
					isFirstPlay = false;
				}
				currentFrameIndex = 0;
			}
			else if (currentFrameIndex >= currentAnimClip->GetLastFrameIndex() && !bLoop)
			{
				currentFrameIndex = currentAnimClip->GetLastFrameIndex();
			}

			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);//가져온 좌표를 현재 프래임으로 만들겠다.
		}
		else
		{
			currentFrameIndex--;
			//거꾸로 돌리는것
			if (currentFrameIndex <= 0 && bLoop)
			{
				if (changeBlock == true)
				{
					isFirstPlay = false;
				}
				currentFrameIndex = currentAnimClip->GetLastFrameIndex();
			}
			else if (currentFrameIndex <= 0 && !bLoop)
			{
				currentFrameIndex = 0;
			}
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);
		}
		//델타타임을 초기화 update돌때마다 교체 되기 때문에 초기화 해야한다
		deltaTime = 0.0f;
	}
	else//작동환경과 상관없이 일정하게 맞춰준다
		deltaTime += Time::Delta();
}

void Animator::Render(UINT slotIndex)
{
}

void Animator::AddAnimClip(AnimationClip* animClip)
{//애니메이션 클립추가
	animClips.insert(make_pair(animClip->GetClipName(), animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName,bool Changeblock,bool GetCurIndex)// 클립 이름에 맞게 세팅
{
	if (Changeblock)
	{
		if (animClips.find(clipName) != animClips.end())
		{
			isFirstPlay = true;
			//클립에는 객체가 있음
			currentAnimClip = animClips.find(clipName)->second;
			//동작을 처음부터 시작해야하기 때문에
			deltaTime = 0.0f;
			if (!GetCurIndex)
			{
				if (currentAnimClip->GetIsReverse())
					currentFrameIndex = currentAnimClip->GetLastFrameIndex();
				else
					currentFrameIndex = 0;
			}
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);
		}
	}
	else if(isFirstPlay==false)
	{
		//같은 클립일 경우
		if (clipName == currentAnimClip->GetClipName()) return;
		//아닐경우 탐색   //end는 끝나는 지점을 이야기함 마지막 바이트
		//같은 이름이 있을 경우만  바꿔준다
		if (animClips.find(clipName) != animClips.end())
		{
			//클립에는 객체가 있음
			currentAnimClip = animClips.find(clipName)->second;
			//동작을 처음부터 시작해야하기 때문에
			deltaTime = 0.0f;
			if (!GetCurIndex)
			{
				if (currentAnimClip->GetIsReverse())
					currentFrameIndex = currentAnimClip->GetLastFrameIndex();
				else
					currentFrameIndex = 0;
			}
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);
		}
	}
}
