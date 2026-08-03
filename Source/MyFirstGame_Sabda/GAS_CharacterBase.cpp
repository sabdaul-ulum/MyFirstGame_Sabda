#include "GAS_CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AS_BaseStats.h"

AGAS_CharacterBase::AGAS_CharacterBase()
{
	// Create the Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the Attribute Set (Now using the shared AS_BaseStats)
	BaseStats = CreateDefaultSubobject<UAS_BaseStats>(TEXT("BaseStats"));
}

UAbilitySystemComponent* AGAS_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGAS_CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Initialize GAS on the server side (Crucial step to activate the ability system)
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}