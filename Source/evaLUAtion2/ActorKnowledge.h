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
	int moving() const { return 0; };
	int shooting() const { return 1; };
	int changingweapon() const { return 2; };
	int dying() const { return 3; };
	int reloading() const { return 4; };
	int waiting() const { return 5; };

	int chaingun() const { return 0; };
	int railgun() const { return 1; };
	int rocketlauncher() const { return 2; };
	int shotgun() const { return 3; };
	int weaponsize() const { return 4; };

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