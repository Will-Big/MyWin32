#pragma once

#include "CAnimator.h"
#include "CPlayer.h"

class PlayerState
{
public:
	virtual void HandleInput(CAnimator* _animator, const wstring& _strState) = 0;
	virtual void update(CPlayer* _player) = 0;
};

