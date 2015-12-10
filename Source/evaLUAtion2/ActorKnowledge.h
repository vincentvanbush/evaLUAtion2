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
	EWeaponType getWeaponType();
	int getAmmo(EWeaponType type);
	bool isLoaded(EWeaponType type);
	unsigned short getTeam();
	const char* getName();
	/** get ActorInfo about oneself*/
	ActorInfo getSelf();
	Vector4d getLongDestination();
private:
	AEvaCharacter * character;
//	void updateSpotting();
//	Navigation * getNavigation();
//	bool isMoving();
//	/** get list of friends seen from current position
//	*/
//	std::vector<ActorInfo> getSeenFriends();
//	/** get list of foes seen from current position
//	*/
//	std::vector<ActorInfo> getSeenFoes();
//	/** get list of all actors seen from current position
//	*/
//	std::vector<ActorInfo> getSeenActors();
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
//	Actor * actor;
};

#endif //ACTOR_KNOWLEDGE_H