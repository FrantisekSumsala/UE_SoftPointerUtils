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

void USPU_SoftPointerUtilsLibrary::AsyncLoadClass(const TSoftClassPtr<>& SoftClass, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	AsyncLoadClass(SoftClass, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}
void USPU_SoftPointerUtilsLibrary::AsyncLoadClass(const TSoftClassPtr<>& SoftClass, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadPath(SoftClass.ToSoftObjectPath(), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
}

void USPU_SoftPointerUtilsLibrary::AsyncLoadObject(const TSoftObjectPtr<>& SoftObject, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	AsyncLoadObject(SoftObject, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}
void USPU_SoftPointerUtilsLibrary::AsyncLoadObject(const TSoftObjectPtr<>& SoftObject, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadPath(SoftObject.ToSoftObjectPath(), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
}

void USPU_SoftPointerUtilsLibrary::AsyncLoadPath(const FSoftObjectPath& SoftPath, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	AsyncLoadPath(SoftPath, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}
void USPU_SoftPointerUtilsLibrary::AsyncLoadPath(const FSoftObjectPath& SoftPath, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	if (!ensureAlwaysMsgf(IsValidSoftPath(SoftPath), TEXT("Cannot load an invalid soft path!")))
		return;
	
	const TAsyncLoadPriority LoadPriority = bIsHighPriority ? FStreamableManager::AsyncLoadHighPriority : FStreamableManager::DefaultAsyncLoadPriority;
	UAssetManager::GetStreamableManager().RequestAsyncLoad(SoftPath, MoveTemp(OnLoaded), LoadPriority, false, false, MoveTemp(DebugName));
}

void USPU_SoftPointerUtilsLibrary::AsyncLoadClasses(const TArray<TSoftClassPtr<>>& SoftClasses, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	AsyncLoadClasses(SoftClasses, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}

void USPU_SoftPointerUtilsLibrary::AsyncLoadObjects(const TArray<TSoftObjectPtr<>>& SoftObjects, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	AsyncLoadObjects(SoftObjects, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}

void USPU_SoftPointerUtilsLibrary::AsyncLoadPaths(const TArray<FSoftObjectPath>& SoftPaths, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	AsyncLoadPaths(SoftPaths, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}
void USPU_SoftPointerUtilsLibrary::AsyncLoadPaths(TArray<FSoftObjectPath> SoftPaths, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
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

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadClassWithHandle(UObject* Outer, const TSoftClassPtr<>& SoftClass, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadClassWithHandle(Outer, SoftClass, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}
USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadClassWithHandle(UObject* Outer, const TSoftClassPtr<>& SoftClass, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadPathWithHandle(Outer, SoftClass.ToSoftObjectPath(), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
}

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadObjectWithHandle(UObject* Outer, const TSoftObjectPtr<>& SoftObject, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadObjectWithHandle(Outer, SoftObject, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}
USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadObjectWithHandle(UObject* Outer, const TSoftObjectPtr<>& SoftObject, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadPathWithHandle(Outer, SoftObject.ToSoftObjectPath(), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
}

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadPathWithHandle(UObject* Outer, const FSoftObjectPath& SoftPath, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadPathWithHandle(Outer, SoftPath, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}
USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadPathWithHandle(UObject* Outer, const FSoftObjectPath& SoftPath, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
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

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadClassesWithHandle(UObject* Outer, const TArray<TSoftClassPtr<>>& SoftClasses, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadClassesWithHandle(Outer, SoftClasses, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadObjectsWithHandle(UObject* Outer, const TArray<TSoftObjectPtr<>>& SoftObjects, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadObjectsWithHandle(Outer, SoftObjects, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}

USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadPathsWithHandle(UObject* Outer, const TArray<FSoftObjectPath>& SoftPaths, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
{
	return AsyncLoadPathsWithHandle(Outer, SoftPaths, FSPU_AsyncLoadDelegate::CreateLambda([OnLoaded]{OnLoaded.ExecuteIfBound();}), bIsHighPriority, MoveTemp(DebugName));
}
USPU_AsyncLoadHandle* USPU_SoftPointerUtilsLibrary::AsyncLoadPathsWithHandle(UObject* Outer, TArray<FSoftObjectPath> SoftPaths, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority, FString DebugName)
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
