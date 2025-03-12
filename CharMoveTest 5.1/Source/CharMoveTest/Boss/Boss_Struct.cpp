// Fill out your copyright notice in the Description page of Project Settings.


#include "CharMoveTest/Boss/Boss_Struct.h"

// Sets default values
ABoss_Struct::ABoss_Struct()
{
	BearDollInfo.Control_DetectRadius = 500.f;
	BearDollInfo.BearDoll_RushSpeed = 1000.f;
	BearDollInfo.RotationSpeed = 2.f;
	BearDollInfo.Rush_Delay = 3.f;
	BearDollInfo.Rotation_Delay = 3.f;
	BearDollInfo.Follow_Speed = 350.f;
	BearDollInfo.Follow_Time = 3.f;
}

float ABoss_Struct::GetDetectRadius()
{
	return BearDollInfo.Control_DetectRadius;
}

FBearDollInfo ABoss_Struct::GetBearDollInfo() const
{
	return BearDollInfo;
}

FBearDollFallObjInfo ABoss_Struct::GetBearDollFallObjInfo() const
{
	return BearDollFallObjInfo;
}

FPlasticDollInfo ABoss_Struct::GetPlasticDollInfo() const
{
	return PlasticDollInfo;
}
