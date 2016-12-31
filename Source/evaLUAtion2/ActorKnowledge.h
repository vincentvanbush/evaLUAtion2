#ifndef ACTOR_KNOWLEDGE_H
#define ACTOR_KNOWLEDGE_H
#include <vector>
#include "Navigation.h"
#include <set>
#include "ActorInfo.h"
#include "EvaCharacter.h"
#include "Action.h"

/** Self knowlage of actor
*/
class ActorKnowledge// TODO ? derive form ActorInfo ?
{
public:
	ActorKnowledge(AEvaCharacter * character);
	Vector4d getPosition();
	Vector4d getDirection();
	int getHealth();
	int getArmour();
	uint8 getWeaponType();
	int getAmmo(int32 type);
	bool isLoaded(int32 type);
	unsigned short getTeam();
	const char* getName();
	/** get ActorInfo about oneself*/
	ActorInfo getSelf();
	Vector4d getLongDestination();
	Vector4d getShortDestination();
	ActorInfoVectorWrapper getSeenFriends();
	ActorInfoVectorWrapper getSeenFoes();
	ActorInfoVectorWrapper getSeenActors();
	Navigation * getNavigation();
	bool isMoving();
	float getEstimatedTimeToReach(Vector4d a, Vector4d b);
	uint8 getActionType();
	static int8 moving() { return 0; };
	static int8 shooting() { return 1; };
	static int8 changingweapon() { return 2; };
	static int8 dying() { return 3; };
	static int8 reloading() { return 4; };
	static int8 waiting() { return 5; };

	static int8 chaingun() { return 0; };
	static int8 railgun() { return 1; };
	static int8 rocketlauncher() { return 2; };
	static int8 shotgun() { return 3; };
	static int8 weaponsize() { return 4; };

private:
	AEvaCharacter * character;
	Navigation * navigation;
//	Vector4d getShortDestination();
//	int getId() const;
//	/**
//	*/
//	int getEstimatedTimeToReach(Vector4d self, Vector4d target);
//	Actor * getActor() {
//		return actor;
//	}
//private:
//	std::set<ActorInfo> seenActors;
//	std::set<ObjectInfo*> seenObjects;
};

#endif //ACTOR_KNOWLEDGE_H