#include "pch.h"
#include "IdleFront.h"

void IdleFront::HandleInput(CAnimator* _animator, const wstring& _strState)
{
	_animator->Play(_strState, true);
}

void IdleFront::update(CPlayer* _player)
{
	
}
