#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AS_BaseStats.generated.h"

// Macro wajib GAS untuk membuat fungsi otomatis (Getter, Setter, Init)
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MYFIRSTGAME_SABDA_API UAS_BaseStats : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAS_BaseStats();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "BaseStats")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAS_BaseStats, Health)

		UPROPERTY(BlueprintReadOnly, Category = "BaseStats")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAS_BaseStats, MaxHealth)

		UPROPERTY(BlueprintReadOnly, Category = "BaseStats")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UAS_BaseStats, MoveSpeed)
};