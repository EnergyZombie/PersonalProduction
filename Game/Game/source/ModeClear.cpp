#include"ModeClear.h"
#include"ModeTitle.h"
#include "ApplicationMain.h"

bool ModeClear::Initialize() {
	return true;
}

bool ModeClear::Terminate() {

	return true;
}

bool ModeClear::Process() {
	base::Process();

	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	if (trg & INPUT_A) { 
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Clear();
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeClear::Render() {
	base::Render();
	SetFontSize(64);
	DrawFormatString(500, 500, GetColor(255, 0, 0), "clear");
	return true;
}