#ifndef ACTOR_KNOWLEDGE_H
#define ACTOR_KNOWLEDGE_H
#include <vector>
#include <set>
#include "ActorInfo.h"
#include "EvaCharacter.h"

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
	std::vector<ActorInfo> getSeenFriends();
	std::vector<ActorInfo> getSeenFoes();
	std::vector<ActorInfo> getSeenActors();
private:
	AEvaCharacter * character;
//	Navigation * getNavigation();
//	bool isMoving();
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