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

	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	if (trg & INPUT_A) {
		// このモードを削除予約
		ModeServer::GetInstance()->Clear();
		// 次のモードを登録
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