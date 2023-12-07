#include"ObjectBase.h"
#include"ObjectServer.h"
#include"appframe.h"
#include"ModeGame.h"
#include<string>
ObjectBase::ObjectBase(ObjectServer* server) {
	//自分を管理するサーバーを記録する
	_server = server;
	//自身をサーバーに追加
	//_server->AddObj(this);
}

ObjectBase::~ObjectBase() {
	Terminate();
}

bool ObjectBase::Initialize() {

	_handle = MV1LoadModel("res/SDChar/SDChar.mv1");
	// 3Dモデルの1番目のアニメーションをアタッチする
	_attach_index = -1;
	
	//MV1SetRotationXYZ(_handle,VGet(0,0,-1));
	MV1SetRotationXYZ(_handle, VGet(0.f, 0.f, 0.f));




	_pos = Vector3D(0, 0, 0);
	_gravity = 0.f;

	return true;
}

bool ObjectBase::Terminate() {
	MV1DeleteModel(_handle);
	return false;
}

bool ObjectBase::Process() {
	//// 再生時間を進める
	//_play_time += 0.5f;
	//// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	//if (_play_time >= _total_time) {
	//	_play_time = 0.0f;
	//}
	return true;
}

bool ObjectBase::Renderer() {

	matrix = MGetIdent();
	matrix = MMult(matrix, MGetRotX(_euler_angle.x));
	matrix = MMult(matrix, MGetRotY(_euler_angle.y));
	matrix = MMult(matrix, MGetRotZ(_euler_angle.z));
	matrix = MMult(matrix, MGetTranslate(DxConverter::VecToDx(_pos)));
	MV1SetMatrix(_handle, matrix);
	// モデルを描画する
	MV1DrawModel(_handle);

	return true;
}



