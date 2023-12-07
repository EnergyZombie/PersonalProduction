#pragma once
#include"ObjectBase.h"
#include"appframe.h"

class Cube :public ObjectBase {
public:
	Cube(class ObjectServer* server);
	virtual ~Cube();

	bool Initialize()override;
	//bool Terminate()override;
	bool Process()override;
	bool Renderer()override;
protected:
	double _move_con;
	double _move_alpha;
	bool _is_fall;
	int _count;
};