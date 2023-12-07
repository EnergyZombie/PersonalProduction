#include"Cube.h"
#include"ModeGame.h"
#include"ObjectServer.h"
#include"Map.h"
#include"Player.h"

Cube::Cube(ObjectServer* server) :ObjectBase(server) {

}

Cube::~Cube(){}

bool Cube::Initialize() {
	//_handle = MV1LoadModel("res/SDChar/SDChar.mv1");
	// 3Dモデルの1番目のアニメーションをアタッチする
	//SetUseTransColor(1); 
	//SetUsePremulAlphaConvertLoad(1);
	_handle = MV1LoadModel("res/Object/wall.mv1");
	_attach_index =  MV1SearchFrame(_handle, "cube");
	//MV1SetRotationXYZ(_handle,VGet(0,0,-1));
	MV1SetupCollInfo(_handle, _attach_index, 8, 8, 8);

	_is_fall = false;

	//GetServer()->AddObj(this);

	_move_con = 1;
	_move_alpha = 0;
	_count = 120;

	return true;
}


bool Cube::Process(){
	_old_pos = _pos;

	//_euler_angle.z += 1 * 3.14 / 180;

	//Segment3D s(Vector3D(0, 000, 200), Vector3D(300, 000, 200));

	//_move_alpha += 0.01 * _move_con;

	//_pos = s.start_point + s.Vector() * _move_alpha;

	MV1SetPosition(_handle, DxConverter::VecToDx(_pos));
	MV1RefreshCollInfo(_handle, _attach_index);

	if (_move_alpha > 1.0 || _move_alpha < 0.0) {
		_move_con *= -1;
	}


	if (GetServer()->GetPlayer()->GetOnObject() == this) {
		GetServer()->GetPlayer()->AddPos(_pos - _old_pos);
		_is_fall = true;
	}

	if (_is_fall) {
		_count--;
		if (_count < 0) {
			_pos.y--;
		}
	}
	
	double rad = GetServer()->GetPlayer()->GetRadian();
	double colsub = GetServer()->GetPlayer()->_colSubY;
	auto pos = GetServer()->GetPlayer()->GetPos();

	MV1_COLL_RESULT_POLY_DIM hitXZ = MV1CollCheck_Capsule(
		_handle,
		_attach_index,
		DxConverter::VecToDx(pos + Vector3D(0, rad, 0)),
		DxConverter::VecToDx(pos + Vector3D(0, rad + colsub, 0)),
		rad
	);
	if (hitXZ.Dim) {

		double dist = 9999999999;

		Vector3D under_pos(pos);
		under_pos.y += rad;
		Vector3D up_pos(pos);
		up_pos.y += (colsub + rad);

		Segment3D coll_seg(under_pos, up_pos);
		Vector3D pol_latest_point(0, 0, 0);
		Vector3D add_base_point(0, 0, 0);

		for (int a = 0; a < hitXZ.HitNum; a++) {
			Polygon3D detection = Polygon3D(
				DxConverter::DxToVec(hitXZ.Dim[a].Position[0]),
				DxConverter::DxToVec(hitXZ.Dim[a].Position[1]),
				DxConverter::DxToVec(hitXZ.Dim[a].Position[2])
			);

			SEGMENT_TRIANGLE_RESULT result = Collision::SegmentPolygonAnalyze(detection, coll_seg);

			double dist_com = result.Seg_Tri_MinDist_Square;

			if (dist_com < dist) {
				dist = dist_com;
				pol_latest_point = DxConverter::DxToVec(result.Tri_MinDist_Pos);
				add_base_point = DxConverter::DxToVec(result.Seg_MinDist_Pos);
			}
		}

		if (dist < rad * rad) {
			Vector3D latest_v(pol_latest_point - add_base_point);
			latest_v.Normalized();
			latest_v *= (rad);
			Vector3D add((pol_latest_point - latest_v));
			GetServer()->GetPlayer()->AddPos(add - add_base_point);
		}

	}
	MV1CollResultPolyDimTerminate(hitXZ);
	return true;
}

bool Cube::Renderer() {
	ObjectBase::Renderer();

	return true;
}