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
	int getAmmo(EWeaponType type);
	bool isLoaded(EWeaponType type);
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