#include "AS_BaseStats.h"

UAS_BaseStats::UAS_BaseStats()
{
	// Default constructor
}

void UAS_BaseStats::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp Health between 0 and MaxHealth
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (GetHealth() <= 0.0f)
		{
			UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
			if (ASC)
			{
				// Fire the Event.Death tag to trigger GA_Death
				FGameplayTag DeathTag = FGameplayTag::RequestGameplayTag(FName("Event.Death"));
				ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(DeathTag));
			}
		}
	}
}