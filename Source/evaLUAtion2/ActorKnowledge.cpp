#include "evaLUAtion2.h"
#include "ActorKnowledge.h"
#include "Navigation.h"
#include "EvaGameState.h"
#include "Configuration.h"
#include "Navigation/PathFollowingComponent.h"

//#include "main/Configuration.h"
//#include "entities/Actor.h"
//#include "main/GameFactory.h"
//#include "main/RandomGenerator.h"

ActorKnowledge::ActorKnowledge(AEvaCharacter * character) : character(character) {
	navigation = new Navigation(character->GetWorld()->GetGameState<AEvaGameState>());
}

Vector4d ActorKnowledge::getPosition() {
	return character->getPosition();
}

Vector4d ActorKnowledge::getDirection() {
	return character->getDirection();
}

int ActorKnowledge::getHealth() {
	return character->health;
}

int ActorKnowledge::getArmour() {
	return character->armour;
}

uint8 ActorKnowledge::getWeaponType() {
	return static_cast<uint8>(character->currentWeapon);
}

int ActorKnowledge::getAmmo(EWeaponType type) {
	return character->ammo[(int)type];
}

bool ActorKnowledge::isLoaded(EWeaponType type) {
	return character->loaded[(int)type];
}

unsigned short ActorKnowledge::getTeam() {
	return (unsigned short)character->team;
}

const char * ActorKnowledge::getName() {
	// TODO: this may be causing memory leaks but how to really handle this?
	char *ret = new char[256];
	strcpy(ret, character->getName().c_str());
	return ret;
}

ActorInfo ActorKnowledge::getSelf() {
	return character->getActorInfo();
}

Vector4d ActorKnowledge::getLongDestination() {
	return character->getLongDestination();
}

Vector4d ActorKnowledge::getShortDestination()
{
	UPawnMovementComponent *pmc = character->GetMovementComponent();
	auto pfc_p = pmc->PathFollowingComp;
	UPathFollowingComponent& pfc = *pfc_p; // inaczej sie chyba nie da xD
	return Vector4d(pfc.GetCurrentTargetLocation());
}

ActorInfoVectorWrapper ActorKnowledge::getSeenActors()
{
	return ActorInfoVectorWrapper(character->SeenAllInfo());
}

ActorInfoVectorWrapper ActorKnowledge::getSeenFriends()
{
	return ActorInfoVectorWrapper(character->SeenFriendsInfo());
}

ActorInfoVectorWrapper ActorKnowledge::getSeenFoes()
{
	return ActorInfoVectorWrapper(character->SeenFoesInfo());
}

Navigation* ActorKnowledge::getNavigation()
{
	return navigation;
}

bool ActorKnowledge::isMoving()
{
	return character->GetVelocity().Size() != 0.0;
}

float ActorKnowledge::getEstimatedTimeToReach(Vector4d a, Vector4d b)
{
	FVector A = a.toFVector();
	FVector B = b.toFVector();
	UNavigationSystem* UNS = GEngine->GetWorld()->GetNavigationSystem();
	float PathLengthInCm = -1.0f;
	UNS->GetPathCost(A, B, PathLengthInCm);
	float Speed = UConfiguration::RetrieveFromGameState()->GetFloat("actor.speed"); // TODO sprawdzic w jakich toto jednostkach jest
	return PathLengthInCm / Speed;
}