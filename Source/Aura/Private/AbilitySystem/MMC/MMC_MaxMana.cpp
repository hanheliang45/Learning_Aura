// Copyright Heliang Han 


#include "AbilitySystem/MMC/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligentDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligentDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligentDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligentDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligent = 0.f;
	GetCapturedAttributeMagnitude(IntelligentDef, Spec, EvaluateParameters, Intelligent);
	Intelligent = FMath::Max(0.f, Intelligent);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f + Intelligent * 4.f + 12.f * PlayerLevel;
}
