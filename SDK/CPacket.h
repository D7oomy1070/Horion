#pragma once
#include "../Utils/HMath.h"
class MovePlayerPacket
{
public:
	uintptr_t** Vtable;
	int a, b, c, d, e, f, entityRuntimeID, h;
	vec3_t Position;
	vec3_t ViewAngles;

	// x, y, z, pitch, yaw, yaw2
};