#include "stdafx.h"
#include "Blade.h"
#include "Utilities/Animator.h"

Blade::Blade(Vector3 position, Vector3 size, float rotation, Helicopter* heli)
	:AnimationRect(position, size, rotation),
	Heli(heli)
{
}

Blade::~Blade()
{
}

void Blade::Update()
{
}

void Blade::Render()
{
}

void Blade::SetAnimation()
{
}

void Blade::SetSize(Vector3 tempSize)
{
}

void Blade::SetPos(Vector3 tempPos)
{
}
