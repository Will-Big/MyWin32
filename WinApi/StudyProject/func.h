#pragma once

// 전역 함수

class CObject;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);


// 굳이 vector<T>& ? 그냥 vector<GROUP_TYPE>& 이랑 다른가 ?
template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); i++)
	{
		if (_vec[i] != nullptr)
			delete _vec[i];
	}

	_vec.clear();
}