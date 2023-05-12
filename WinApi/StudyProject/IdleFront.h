#pragma once
#include "PlayerState.h"
class IdleFront :
    public PlayerState
{
public:
	void HandleInput(CAnimator* _animator, const wstring& _strState) override;
	void update(CPlayer* _player) override;
};

