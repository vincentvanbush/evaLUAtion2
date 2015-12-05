#pragma once

#include "Object.h"
#include "Misc.h"
#include "Evacharacter.h"
#include "Action.h"
#include "PlayerAgent.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class EVALUATION2_API UPlayerAgent : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = References)
		AEvaCharacter* ControlledCharacter;

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)		//TODO uncomment after Action class is done
		UAction* decideNextAction();			//corresponds to whatToDoNow method

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void selectWeapon(EWeaponType weapon);

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void moveDirection(FVector direction);

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void moveTo(FVector target);

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void reload();

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void rotate(FVector direction);

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void shootAt(AEvaCharacter* enemy);

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void shootAtPoint(FVector vect);

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void wait();

	UFUNCTION(BlueprintCallable, Category = EvaluationActions)
		void continueAction();

protected:
	//TODO add CurrentActorKnowledge

};
