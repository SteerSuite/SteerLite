//
// Copyright (c) 2015 Mahyar Khayatkhoei
// Copyright (c) 2009-2014 Shawn Singh, Glen Berseth, Mubbasir Kapadia, Petros Faloutsos, Glenn Reinman
// See license.txt for complete license.
//

#include <iostream>
#include <vector>
#include <util/Geometry.h>
#include <util/
#include "Globals.h"

using namespace Util;

void Curve::drawCurve();
bool Curve::getPoint(Point& outputPoint, float time);
bool CurveAgent::hermiteCurve(const std::vector<SteerLib::AgentGoalInfo>& controlPoints, Util::Point& curvePosition, float time)
{
	const SteerLib::AgentGoalInfo *p0, *p1;
	SteerLib::AgentGoalInfo startPoint;
	Util::Point newPosition;
	float normalTime, intervalTime;

	//Check for the current interval, supposing that controlPoints is sorted
	if (time > controlPoints.back().targetTime)
	{
		return false;
	}
	else if (time < controlPoints.front().targetTime)
	{
		Util::Point startTangent(0, 0, 0);
		startPoint.targetLocation = __startPosition;
		startPoint.targetTangent = startTangent;
		startPoint.targetTime = 0;
		p0 = &startPoint;
		p1 = &controlPoints.front();
	}
	else
	{
		for (int i = 1; i < controlPoints.size(); i++)
		{
			if (time <= controlPoints[i].targetTime)
			{
				p1 = &controlPoints[i];
				p0 = &controlPoints[i - 1];
				break;
			}
		}
	}

	intervalTime = (p1->targetTime - p0->targetTime);
	normalTime = (time - p0->targetTime) / intervalTime;

	newPosition = p0->targetLocation * (2 * pow(normalTime, 3) - 3 * pow(normalTime, 2) + 1)
		+ p1->targetLocation * (-2 * pow(normalTime, 3) + 3 * pow(normalTime, 2))
		+ p0->targetTangent * (intervalTime*pow(normalTime, 3) + -2 * intervalTime*pow(normalTime, 2) + intervalTime*normalTime)
		+ p1->targetTangent * (intervalTime*pow(normalTime, 3) - intervalTime*pow(normalTime, 2));

	curvePosition = newPosition;
	return true;
}