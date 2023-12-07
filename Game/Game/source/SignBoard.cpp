#include"SignBoard.h"
#include"ObjectServer.h"
#include"Player.h"
#include"ModeGame.h"
#include"ModeScript.h"

bool SignBoard::Initialize() { 
	_handle = MV1LoadModel("res/SignBoard/signboard.mv1");
	_ui_text = LoadGraph("res/ball.png");
	_pos = Vector3D(100, 0, -100);

	/*_attach_index = MV1SearchFrame(_handle, 0);*/
	//MV1SetRotationXYZ(_handle,VGet(0,0,-1));

	MV1SetPosition(_handle, DxConverter::VecToDx(_pos));
	MV1SetupCollInfo(_handle, 0, 8, 8, 8);


	//GetServer()->AddObj(this);
	return true; 
}
bool SignBoard::Process(){ 
	auto pos = GetServer()->GetPlayer()->GetPos();

	if (Vector3D::Length(pos, _pos) < 100) {
		auto pad = GetServer()->GetGame()->GetPad();
		if (pad->GetTrgButton() & INPUT_B) {
			ModeServer::GetInstance()->Add(new ModeScript(), 10, "script");
		}

	}
	
	return true;

}
bool SignBoard::Renderer(){ 
	ObjectBase::Renderer();
	auto pos = GetServer()->GetPlayer()->GetPos();

	if (Vector3D::Length(pos, _pos) < 100) {
		
		DrawBillboard3D(
			DxConverter::VecToDx(Vector3D(pos.x,pos.y+170,pos.z)),
			0.5, 0.5, 100, _euler_angle.y, _ui_text, TRUE
		);
		DrawFormatString(0, 100, GetColor(255, 0, 0), "sign");
	}

	DrawSphere3D(
		DxConverter::VecToDx(_pos),
		100,
		16,
		GetColor(255, 255, 255),
		GetColor(255, 0, 0),
		FALSE
	);

	
	return true;
}