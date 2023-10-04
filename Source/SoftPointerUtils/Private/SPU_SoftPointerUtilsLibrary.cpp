// Fill out your copyright notice in the Description page of Project Settings.

#include "SPU_SoftPointerUtilsLibrary.h"
#include "SPU_AsyncLoadHandle.h"
#include "Engine/AssetManager.h"

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

void USPU_SoftPointerUtilsLibrary::LoadAsync(const TSoftClassPtr<>& SoftClass, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return LoadAsync(SoftClass.ToSoftObjectPath(), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
}

void USPU_SoftPointerUtilsLibrary::LoadAsync(const TSoftObjectPtr<>& SoftObject, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return LoadAsync(SoftObject.ToSoftObjectPath(), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
}

void USPU_SoftPointerUtilsLibrary::LoadAsync(const FSoftObjectPath& SoftPath, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	if (!ensureAlwaysMsgf(IsValidSoftPath(SoftPath), TEXT("Cannot load an invalid soft path!")))
		return;
	
	const TAsyncLoadPriority LoadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftPath, MoveTemp(OnLoaded), LoadPriority, false, false, MoveTemp(DebugName));
}

void USPU_SoftPointerUtilsLibrary::LoadAsync(TArray<FSoftObjectPath> SoftPaths, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	bool ContainsValidPath = false;
	for (const FSoftObjectPath& SoftPath : SoftPaths)
	{
		if (IsValidSoftPath(SoftPath))
			ContainsValidPath = true;
	}

	if (!ensureAlwaysMsgf(ContainsValidPath, TEXT("Cannot load only invalid soft paths!")))
		return;
	
	const TAsyncLoadPriority LoadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	UAssetManager::GetStreamableManager().RequestAsyncLoad(MoveTemp(SoftPaths), MoveTemp(OnLoaded), LoadPriority, false, false, MoveTemp(DebugName));
}

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::LoadAsyncWithHandle(UObject* Outer, const TSoftClassPtr<>& SoftClass, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return LoadAsyncWithHandle(Outer, SoftClass.ToSoftObjectPath(), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
}

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::LoadAsyncWithHandle(UObject* Outer, const TSoftObjectPtr<>& SoftObject, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return LoadAsyncWithHandle(Outer, SoftObject.ToSoftObjectPath(), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
}

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::LoadAsyncWithHandle(UObject* Outer, const FSoftObjectPath& SoftPath, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	if (!ensureAlwaysMsgf(IsValidSoftPath(SoftPath), TEXT("Cannot load an invalid soft path!")))
		return nullptr;
	
	const TAsyncLoadPriority LoadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	const TSharedPtr<FStreamableHandle> StreamableHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftPath, MoveTemp(OnLoaded), LoadPriority, false, false, MoveTemp(DebugName));
	if (!StreamableHandle)
		return nullptr;

	USPU_AsyncLoadHandle* LoadHandle = NewObject<USPU_AsyncLoadHandle>(Outer);
	if (!LoadHandle)
		return nullptr;

	LoadHandle->Initialize(StreamableHandle);
	return LoadHandle;
}

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::LoadAsyncWithHandle(UObject* Outer, TArray<FSoftObjectPath> SoftPaths, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	bool ContainsValidPath = false;
	for (const FSoftObjectPath& SoftPath : SoftPaths)
	{
		if (IsValidSoftPath(SoftPath))
			ContainsValidPath = true;
	}

	if (!ensureAlwaysMsgf(ContainsValidPath, TEXT("Cannot load only invalid soft paths!")))
		return nullptr;
	
	const TAsyncLoadPriority LoadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	const TSharedPtr<FStreamableHandle> StreamableHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(MoveTemp(SoftPaths), MoveTemp(OnLoaded), LoadPriority, false, false, MoveTemp(DebugName));
	if (!StreamableHandle)
		return nullptr;

	USPU_AsyncLoadHandle* LoadHandle = NewObject<USPU_AsyncLoadHandle>(Outer);
	if (!LoadHandle)
		return nullptr;

	LoadHandle->Initialize(StreamableHandle);
	return LoadHandle;
}
