#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AS_Resource.generated.h"

// Required GAS macro to auto-generate accessor functions (Getter, Setter, Init)
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MYFIRSTGAME_SABDA_API UAS_Resource : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAS_Resource();

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Resource")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAS_Resource, Mana)

		UPROPERTY(BlueprintReadOnly, Category = "Resource")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAS_Resource, MaxMana)

		UPROPERTY(BlueprintReadOnly, Category = "Resource")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UAS_Resource, Stamina)

		UPROPERTY(BlueprintReadOnly, Category = "Resource")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UAS_Resource, MaxStamina)
};