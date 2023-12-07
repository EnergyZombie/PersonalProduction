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

	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	auto trg = ApplicationMain::GetInstance()->GetPad()->GetTrgButton();

	if (trg & INPUT_A) { 
		// このモードを削除予約
		ModeServer::GetInstance()->Clear();
		// 次のモードを登録
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