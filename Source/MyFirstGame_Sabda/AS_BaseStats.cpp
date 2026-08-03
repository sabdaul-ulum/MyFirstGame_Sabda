#include "AS_BaseStats.h"

UAS_BaseStats::UAS_BaseStats()
{
	// Constructor kosong
}

void UAS_BaseStats::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp Health antara 0 dan MaxHealth
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (GetHealth() <= 0.0f)
		{
			UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
			if (ASC)
			{
				// Tembakkan Tag Event.Death untuk memicu GA_Death
				FGameplayTag DeathTag = FGameplayTag::RequestGameplayTag(FName("Event.Death"));
				ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(DeathTag));
			}
		}
	}
}