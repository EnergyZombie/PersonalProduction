#pragma once
#include"ObjectBase.h"
#include"appframe.h"

class GoalFloor :public ObjectBase {
public:
	GoalFloor(class ObjectServer* server);
	virtual ~GoalFloor();

	bool Initialize()override;
	//bool Terminate()override;
	bool Process()override;

protected:
	double _move_con;
	double _move_alpha;
	float _radian;
};