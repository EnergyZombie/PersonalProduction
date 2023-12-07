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
	bool	_is_stand;		//オブジェクトの上に立っているか
	Vector3D _move;
	float _play_time;
	float _total_time;

public:
	float _colSubY;	// コリジョン判定時のY補正(腰位置）
};