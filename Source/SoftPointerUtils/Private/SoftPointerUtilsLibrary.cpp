// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftPointerUtilsLibrary.h"

const FSoftObjectPath& USoftPointerUtilsLibrary::SoftClassToSoftPath(const TSoftClassPtr<>& SoftClass)
{
	return SoftClass.ToSoftObjectPath();
}

const FSoftObjectPath& USoftPointerUtilsLibrary::SoftObjectToSoftPath(const TSoftObjectPtr<>& SoftObject)
{
	return SoftObject.ToSoftObjectPath();
}

FString USoftPointerUtilsLibrary::SoftPathToString(const FSoftObjectPath& SoftPath)
{
	return SoftPath.ToString();
}

bool USoftPointerUtilsLibrary::IsValidSoftClass(const TSoftClassPtr<>& SoftClass)
{
	return !SoftClass.IsNull();
}

bool USoftPointerUtilsLibrary::IsValidSoftObject(const TSoftObjectPtr<>& SoftObject)
{
	return !SoftObject.IsNull();
}

bool USoftPointerUtilsLibrary::IsValidSoftPath(const FSoftObjectPath& SoftPath)
{
	return !SoftPath.IsNull();
}

bool USoftPointerUtilsLibrary::IsSoftClassLoaded(const TSoftClassPtr<>& SoftClass)
{
	return SoftClass.IsValid();
}

bool USoftPointerUtilsLibrary::IsSoftObjectLoaded(const TSoftObjectPtr<>& SoftObject)
{
	return SoftObject.IsValid();
}

TSharedPtr<FStreamableHandle> USoftPointerUtilsLibrary::LoadAsync(const TSoftClassPtr<>& SoftClass, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	return LoadAsync(SoftClass.ToSoftObjectPath(), OnLoaded, bIsHighPriority);
}

TSharedPtr<FStreamableHandle> USoftPointerUtilsLibrary::LoadAsync(const TSoftObjectPtr<>& SoftObject, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	return LoadAsync(SoftObject.ToSoftObjectPath(), OnLoaded, bIsHighPriority);
}

TSharedPtr<FStreamableHandle> USoftPointerUtilsLibrary::LoadAsync(const FSoftObjectPath& SoftPath, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority)
{
	if (!ensureAlwaysMsgf(IsValidSoftPath(SoftPath), TEXT("Cannot load an invalid soft path!")))
		return nullptr;
	
	const TAsyncLoadPriority loadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	return UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftPath, OnLoaded, loadPriority);
}
