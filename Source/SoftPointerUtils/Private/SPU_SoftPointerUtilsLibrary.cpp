// Fill out your copyright notice in the Description page of Project Settings.

#include "SPU_SoftPointerUtilsLibrary.h"

const FSoftObjectPath& USPU_SoftPointerUtilsLibrary::SoftClassToSoftPath(const TSoftClassPtr<>& SoftClass)
{
	return SoftClass.ToSoftObjectPath();
}

const FSoftObjectPath& USPU_SoftPointerUtilsLibrary::SoftObjectToSoftPath(const TSoftObjectPtr<>& SoftObject)
{
	return SoftObject.ToSoftObjectPath();
}

FString USPU_SoftPointerUtilsLibrary::SoftPathToString(const FSoftObjectPath& SoftPath)
{
	return SoftPath.ToString();
}

bool USPU_SoftPointerUtilsLibrary::IsValidSoftClass(const TSoftClassPtr<>& SoftClass)
{
	return !SoftClass.IsNull();
}

bool USPU_SoftPointerUtilsLibrary::IsValidSoftObject(const TSoftObjectPtr<>& SoftObject)
{
	return !SoftObject.IsNull();
}

bool USPU_SoftPointerUtilsLibrary::IsValidSoftPath(const FSoftObjectPath& SoftPath)
{
	return !SoftPath.IsNull();
}

bool USPU_SoftPointerUtilsLibrary::IsSoftClassLoaded(const TSoftClassPtr<>& SoftClass)
{
	return SoftClass.IsValid();
}

bool USPU_SoftPointerUtilsLibrary::IsSoftObjectLoaded(const TSoftObjectPtr<>& SoftObject)
{
	return SoftObject.IsValid();
}

TSharedPtr<FStreamableHandle> USPU_SoftPointerUtilsLibrary::LoadAsync(const TSoftClassPtr<>& SoftClass, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	return LoadAsync(SoftClass.ToSoftObjectPath(), OnLoaded, bIsHighPriority);
}

TSharedPtr<FStreamableHandle> USPU_SoftPointerUtilsLibrary::LoadAsync(const TSoftObjectPtr<>& SoftObject, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	return LoadAsync(SoftObject.ToSoftObjectPath(), OnLoaded, bIsHighPriority);
}

TSharedPtr<FStreamableHandle> USPU_SoftPointerUtilsLibrary::LoadAsync(const FSoftObjectPath& SoftPath, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	//TODO: reconsider whether we should do this instead of letting the streaming manager handle it
	if (!ensureAlwaysMsgf(IsValidSoftPath(SoftPath), TEXT("Cannot load an invalid soft path!")))
		return nullptr;
	
	const TAsyncLoadPriority loadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	return UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftPath, OnLoaded, loadPriority);
}

TSharedPtr<FStreamableHandle> USPU_SoftPointerUtilsLibrary::LoadAsync(const TArray<TSoftClassPtr<>>& SoftClasses, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	const int32 NumSoftClasses = SoftClasses.Num();
	TArray<FSoftObjectPath> SoftPaths;
	SoftPaths.Reserve(NumSoftClasses);
	
	for (const TSoftClassPtr<>& SoftClass : SoftClasses)
		SoftPaths.Add(SoftClass.ToSoftObjectPath());
	
	return LoadAsync(SoftPaths, OnLoaded, bIsHighPriority);
}

TSharedPtr<FStreamableHandle> USPU_SoftPointerUtilsLibrary::LoadAsync(const TArray<TSoftObjectPtr<>>& SoftObjects, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	const int32 NumSoftObjects = SoftObjects.Num();
	TArray<FSoftObjectPath> SoftPaths;
	SoftPaths.Reserve(NumSoftObjects);
	
	for (const TSoftObjectPtr<>& SoftObject : SoftObjects)
		SoftPaths.Add(SoftObject.ToSoftObjectPath());
	
	return LoadAsync(SoftPaths, OnLoaded, bIsHighPriority);
}

TSharedPtr<FStreamableHandle> USPU_SoftPointerUtilsLibrary::LoadAsync(const TArray<FSoftObjectPath>& SoftPaths, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	//TODO: reconsider how we should handle this, even more so when a single invalid soft path invalidates all the other requested assets
	for (const FSoftObjectPath& target : SoftPaths)
	{
		if (!ensureAlwaysMsgf(IsValidSoftPath(target), TEXT("Cannot load an invalid soft path!")))
			return nullptr;
	}
	
	const TAsyncLoadPriority loadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	return UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftPaths, OnLoaded, loadPriority);
}

void USPU_SoftPointerUtilsLibrary::AsyncLoadSoftClass(const TSoftClassPtr<>& SoftClass)
{
	AsyncLoadSoftPath(SoftClass.ToSoftObjectPath());
}

void USPU_SoftPointerUtilsLibrary::AsyncLoadSoftObject(const TSoftObjectPtr<>& SoftObject)
{
	AsyncLoadSoftPath(SoftObject.ToSoftObjectPath());
}

void USPU_SoftPointerUtilsLibrary::AsyncLoadSoftPath(const FSoftObjectPath& SoftPath)
{
	if (!ensureAlwaysMsgf(IsValidSoftPath(SoftPath), TEXT("Cannot load an invalid soft path!")))
		return;
	
	// const TAsyncLoadPriority loadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftPath);
}
