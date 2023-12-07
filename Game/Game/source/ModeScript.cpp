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
	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	if (trg & PAD_INPUT_B) {
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
	
	}

	return true;
}

bool ModeScript::Render() {
	base::Render();

	DrawFormatString(0, 500, GetColor(255, 0, 0), "はしを渡るべからず");

	return true;
}

