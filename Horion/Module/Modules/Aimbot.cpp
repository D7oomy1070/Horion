#include "Aimbot.h"



Aimbot::Aimbot() : IModule('M') // <-- keybind
{
}


Aimbot::~Aimbot()
{
}

std::string Aimbot::getModuleName()
{
	return std::string("Aimbot");
}
struct CompareTargetEnArray
{
	bool operator() (C_Entity *lhs, C_Entity *rhs)
	{
		C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();
		return lhs->eyePos0.dist(localPlayer->eyePos0) < rhs->eyePos0.dist(localPlayer->eyePos0); 
	}
};
void Aimbot::onAimbot()
{
	C_LocalPlayer* localPlayer = g_Data.getLocalPlayer();

	C_EntityList* entList = localPlayer->getEntityList();
	size_t listSize = entList->getListSize();

	if (listSize > 1000) {
		logF("Big ent list wtf men %i", listSize);
		return;
	}

	//Loop through all our players and retrieve their information
	float maxDist = 6;
	static std::vector <C_Entity*> targetList;
	targetList.clear();
	for (size_t i = 0; i < listSize; i++)
	{
		C_Entity* currentEntity = entList->get(i);

		if (currentEntity == 0)
			break;

		if (currentEntity == localPlayer) // Skip Local player
			continue;

		if (localPlayer->getEntityTypeId() != currentEntity->getEntityTypeId()) // Skip Invalid Entity
			continue;
		// i want to hit villagers ok
//		if (localPlayer->entityType2 != currentEntity->entityType2)
//			continue;

		float dist = currentEntity->eyePos0.dist(localPlayer->eyePos0);

		if (dist < maxDist) 
		{
			targetList.push_back(currentEntity);
		}
	}

	if (targetList.size() > 0)
	{
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		vec3_t ghetto;
		vec3_t yeet = localPlayer->eyePos0.CalcAngle(targetList[0]->eyePos0);
		ghetto.x = localPlayer->yaw;
		ghetto.y = localPlayer->pitch;
		yeet = ghetto.DifferenceAngle(yeet);
		//Premium code :)
		yeet.x /= 4;
		yeet.y /= 4;
		localPlayer->yaw += yeet.x;
		localPlayer->pitch += yeet.y;
	}
	
}

