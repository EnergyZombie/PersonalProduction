#include"Player.h"
#include"ObjectServer.h"
#include"ModeGame.h"

#include"appframe.h"
#include<vector>
#include<algorithm>
#include"Camera.h"


Player::Player(ObjectServer* server):CharaBase(server) {

}

Player::~Player() {

}

bool Player::Initialize() {
		// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j
	_handle = MV1LoadModel("res/SDChar/SDChar.mv1");
	// 3D���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	_attach_index = 0;
	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	_total_time = 0.f;
	// �Đ����Ԃ̏�����
	_play_time = 0.0f;


	//MV1SetRotationXYZ(_handle,VGet(0,0,-1));
	MV1SetRotationXYZ(_handle, VGet(0.f, 0.f, 0.f));


	//���g���T�[�o�[�ɒǉ�
	//_server->AddObj(this);

	_pos = Vector3D(0,100,0);
	_gravity = 0.f;
	_is_stand = true;
	_colSubY = 40.f;

	radian = 30;

	_euler_angle = Vector3D(0, 0, 0);

	MV1SetAttachAnimTime(_handle, _attach_index, _play_time);

	_action_state = ACTION_STATE::kIdle;

	return true;
}

bool Player::Process() {
	ObjectBase::Process();

	ACTION_STATE old_state = _action_state;

	auto pad = GetServer()->GetGame()->GetPad();
	auto camera = GetServer()->GetGame()->GetCamera();
	auto map = GetServer()->GetGame()->GetMap();

	// �ړ��O�̈ʒu��ۑ�
	_old_pos = _pos;
	float cam_y = 0.f;

	//

	//GravityProcess(this);
		//�d�͏���
	if (_gravity > -40.f) {
		_gravity -= 1.f;
	}
	_pos.y += _gravity;


	MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(
		map->GetHandleMap(),
		map->GetCollisionIndex(),
		DxConverter::VecToDx(_pos + Vector3D(0, _colSubY + radian * 2 , 0)),
		DxConverter::VecToDx(_pos + Vector3D(0, 0, 0))
	);
	if (hit.HitFlag) {
		// ��������
		// ��������Y�ʒu���L�������W�ɂ���
		if (_old_pos.y > _pos.y) {
			_pos.y = hit.HitPosition.y;
			_is_stand = true;
		}
		else {
			_pos.y = VSub(hit.HitPosition, VGet(0, _colSubY + radian * 2 , 0)).y;
		}
		_gravity = 0;
	}
	else { 
		_is_stand = false;
		for (auto& obj : GetServer()->GetObjects()) {
			MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(
				obj->GetHandle(), 
				obj->GetAttachIndex(),
				DxConverter::VecToDx(_pos + Vector3D(0, _colSubY + radian * 2, 0)),
				DxConverter::VecToDx(_pos + Vector3D(0, -1, 0))
			);
			if (hit.HitFlag) {
			
				if (_old_pos.y > _pos.y) {
				
					_is_stand = true;
			
					_pos.y = hit.HitPosition.y + 1;

					_onObj = obj;

				}
				else {
					_pos.y = VSub(hit.HitPosition, VGet(0, _colSubY + radian * 2, 0)).y;
				}
				_gravity = 0;
			}
			else {
				_onObj = nullptr;
			}
		}
	}
	//MV1SetPosition(_handle, DxConverter::VecToDx(_pos));
	
	if (pad->IsInputLeftStick()) {
		_euler_angle.y = atan2((float)pad->GetLeftStick().x,(float)pad->GetLeftStick().y);
		_euler_angle.y -= camera->RotateY;

	
		Vector3D vDir(0, 0, 0);
		vDir.x = sin(_euler_angle.y);
		vDir.z = cos(_euler_angle.y);
		vDir.Normalized();

		_pos += vDir * 5.f;

		_euler_angle = Vector3D(0, _euler_angle.y + (double)PI, 0);

		_action_state = ACTION_STATE::kWalk;

	}
	else{ _action_state = ACTION_STATE::kIdle; }

	//�W�����v����
	if (_is_stand && pad->GetTrgButton() & INPUT_A) {
		_gravity += 30;
		_is_stand = false;
	}


	if (_move.Length() > 0.1) {
		_pos += _move;
		_move *= 0.8;
	}
	else {
		_move *= 0;
	}

	if (_old_pos != _pos) {
		IsHitMap();
	}



	
	// �X�e�[�^�X���ς���Ă��Ȃ����H
	if(old_state == _action_state) {
		// �Đ����Ԃ�i�߂�
		_play_time += 0.5f;
	}
	else {
		// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
		if(_attach_index != -1) {
			MV1DetachAnim(_handle, _attach_index);
			_attach_index = -1;
		}
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
		switch(_action_state) {
		case ACTION_STATE::kIdle:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "idle"), -1, FALSE);
			break;
		case ACTION_STATE::kWalk:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "run"), -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_total_time = MV1GetAttachAnimTotalTime(_handle, _attach_index);
		// �Đ����Ԃ�������
		_play_time = 0.0f;
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if(_play_time >= _total_time) {
		_play_time = 0.0f;
	}

	return true;
}

bool Player::Renderer() {
	ObjectBase::Renderer();
	MV1SetAttachAnimTime(_handle, _attach_index, _play_time);
	DrawCapsule3D(
		VAdd(DxConverter::VecToDx(_pos), VGet(0, _colSubY + radian, 0)),
		VAdd(DxConverter::VecToDx(_pos), VGet(0, radian, 0)),
		radian, 10,
		GetColor(255, 0, 0),
		GetColor(255, 255, 255),
		FALSE
	);

	DrawLine3D(
		DxConverter::VecToDx(_pos + Vector3D(0, _colSubY + radian * 2, 0)),
		DxConverter::VecToDx(_pos + Vector3D(0, -1, 0)),
		GetColor(0, 0, 255)
	);

	DrawFormatString(
		0, 0, GetColor(255, 0, 0),
		"%fl %fl %fl",
		DxConverter::VecToDx(_pos).x,
		DxConverter::VecToDx(_pos).y,
		DxConverter::VecToDx(_pos).z,
		TRUE
		);
	if (_is_stand) {
		DrawFormatString(0, 25, GetColor(255, 0, 0), "stand");
	}

	return true;
}
