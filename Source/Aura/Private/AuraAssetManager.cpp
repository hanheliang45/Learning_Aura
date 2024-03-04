// Copyright Heliang Han 


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"

const UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	return *Cast<UAuraAssetManager>(GEngine->AssetManager);
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();
}
