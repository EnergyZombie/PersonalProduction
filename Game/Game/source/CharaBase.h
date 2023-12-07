#pragma once
#include"ObjectBase.h"

class CharaBase :public ObjectBase{
public :
	CharaBase(class ObjectServer* server);
	bool IsHitMap();
	double GetRadian()const { return radian; }
	float GetCollSubY()const { return _colSubY; }
	void AddMove(Vector3D add) { _move += add; }

protected:
	double radian;
	bool	_is_stand;		//�I�u�W�F�N�g�̏�ɗ����Ă��邩
	Vector3D _move;
	float _play_time;
	float _total_time;

public:
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j
};