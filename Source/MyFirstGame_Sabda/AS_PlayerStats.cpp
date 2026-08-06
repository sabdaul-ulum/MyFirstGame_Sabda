#include "AS_PlayerStats.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAS_PlayerStats::UAS_PlayerStats()
{
	// Set initial health values when the game starts
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UAS_PlayerStats::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_PlayerStats, Health, OldHealth);
}

void UAS_PlayerStats::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAS_PlayerStats, MaxHealth, OldMaxHealth);
}

void UAS_PlayerStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register Health and MaxHealth for network replication
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_PlayerStats, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_PlayerStats, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UAS_PlayerStats::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Check if the modified attribute is Health
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp Health so it stays between 0 and MaxHealth
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		// Check if Health has reached 0 (Dead)
		if (GetHealth() <= 0.0f)
		{
			// Get the target actor (Avatar Actor) that owns this AttributeSet
			AActor* TargetActor = nullptr;
			if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
			{
				TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
			}

			if (TargetActor)
			{
				// Get the Ability System Component (ASC) from the actor
				UAbilitySystemComponent* ASC = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
				if (ASC)
				{
					// Create a Gameplay Tag to trigger the Death Ability
					FGameplayTag DeathTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Player.Death"));

					// Trigger the Ability using the Tag
					ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(DeathTag));
				}
			}
		}
	}
}