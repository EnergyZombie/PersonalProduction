#include"ModeScript.h"
#include "ApplicationMain.h"

bool ModeScript::Initialize() {
	if (!base::Initialize()) { return false; }


	return true;
}

bool ModeScript::Terminate() {

	base::Terminate();
	return true;
}

bool ModeScript::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	if (trg & PAD_INPUT_B) {
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
	
	}

	return true;
}

bool ModeScript::Render() {
	base::Render();

	DrawFormatString(0, 500, GetColor(255, 0, 0), "�͂���n��ׂ��炸");

	return true;
}

