#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GAS_CharacterBase.generated.h"

class UAbilitySystemComponent;
class UAS_PlayerStats;

UCLASS()
class MYFIRSTGAME_SABDA_API AGAS_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGAS_CharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	class UAbilitySystemComponent* AbilitySystemComponent;

	// Use AS_BaseStats so both Player and Enemy can share the same logic
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	class UAS_BaseStats* BaseStats;

	UFUNCTION(BlueprintPure, Category = "Cooldown")
	float GetCooldownTimeRemaining(FGameplayTag CooldownTag) const;

protected:
	// Called when a controller possesses this character
	virtual void PossessedBy(AController* NewController) override;
};