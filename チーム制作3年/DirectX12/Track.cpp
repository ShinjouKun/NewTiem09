#include "Track.h"

Track::Track()
{
}

void Track::Init()
{
	_trackNum = 0;
	time = 0;
	_speed = 0.5f;
	p1 = _addTrack[_trackNum];
	dist = p1-_pos ;
}

void Track::Update()
{
	MovingObj();

}

void Track::AddTrackPoint(int trackPointNum, Vector3 pointPos)
{
	_addTrack[trackPointNum] = pointPos;


}

void Track::MovingObj()
{
	p1 = _addTrack[_trackNum];

	//dist.normal();

	_pos -= dist * _speed;

	if (_pos == p1) {
		_trackNum + 1;
	}


}
