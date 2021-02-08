#pragma once
#include<vector>
#include<unordered_map>
#include"BaseObject.h"
#include"Vector3.h"
#include"Easing.h"


class Track
{

public:
	
	Track();


	void SetObjPos(Vector3 objpos) { _pos = objpos; };

	void Init();

	void Update();

	
	void AddTrackPoint(int trackPointNum, Vector3 pointPos);

		
private:


	void trackClaer();

	void MovingObj();

	

private:

	BaseObject* _baseobj;

	int _trackNum;

	Vector3 _pos;

	std::unordered_map<int, Vector3>_addTrack; //•Û‘¶—p

	bool branchTrack = false; //•ªŠò‰Â”\“_

	bool finishMove;
	int time;
	float _speed;
	Vector3 p1;
	Vector3 dist;
};

