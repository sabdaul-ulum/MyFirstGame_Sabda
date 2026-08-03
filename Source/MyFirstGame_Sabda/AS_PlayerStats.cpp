#include "AS_PlayerStats.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UAS_PlayerStats::UAS_PlayerStats()
{
	// Mengatur nilai awal darah saat game dimulai
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

	// Mendaftarkan variabel Health dan MaxHealth ke jaringan
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_PlayerStats, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAS_PlayerStats, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UAS_PlayerStats::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Memeriksa apakah atribut yang berubah adalah Health
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Batasi nilai Health agar tidak di bawah 0 dan tidak melebihi MaxHealth
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		// Cek apakah Health menyentuh 0 (Mati)
		if (GetHealth() <= 0.0f)
		{
			// Mendapatkan Target Aktor (Avatar Aktor) yang memiliki AttributeSet ini
			AActor* TargetActor = nullptr;
			if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
			{
				TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
			}

			if (TargetActor)
			{
				// Mengambil Ability System Component (ASC) dari Aktor tersebut
				UAbilitySystemComponent* ASC = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
				if (ASC)
				{
					// Buat sebuah Gameplay Tag untuk memicu Ability Kematian
					FGameplayTag DeathTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.Player.Death"));

					// Trigger Ability menggunakan Tag
					ASC->TryActivateAbilitiesByTag(FGameplayTagContainer(DeathTag));
				}
			}
		}
	}
}