#pragma once

class Monster;

class CMonsterCreator
{
private:



public:
	Monster* CreateMonster(MONSTER_NAME _eType);

public:
	CMonsterCreator();
	~CMonsterCreator();
};

