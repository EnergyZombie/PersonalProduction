#include"ModeGameOver.h"
#include "ApplicationMain.h"
#include"ModeGame.h"

bool ModeGameOver::Initialize() {
	return true;
}

bool ModeGameOver::Terminate() {
	return true;
}

bool ModeGameOver::Process() {
	base::Process();

	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	if (trg & INPUT_A) {
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Clear();
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}
	return true;
}

bool ModeGameOver::Render() {
	base::Render();
	SetFontSize(64);
	DrawFormatString(500, 500, GetColor(255, 0, 0), "GameOver");
	return true;
}