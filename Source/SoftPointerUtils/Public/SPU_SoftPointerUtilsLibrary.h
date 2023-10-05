// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SPU_SoftPointerUtilsLibrary.generated.h"

/* TODO TASK LIST
 * Probably separate this into C++ only utils static class and blueprint only function library for better clarity
 * Find a free plugin with heavy assets to properly stress test the async loads
 * Test that everything compiles and works in every UE version starting with 5.0
 * Once this is feature complete, clean it up, apply UE coding standards and create proper documentation
 * Fill out the copyright, readme, validate the entire content of the plugin
 * Research what needs to be done to publish this on the UE marketplace
 */

class USPU_AsyncLoadHandle;

DECLARE_DELEGATE(FSPU_AsyncLoadDelegate);
DECLARE_DYNAMIC_DELEGATE(FSPU_DynamicAsyncLoadDelegate);

UCLASS()
class SOFTPOINTERUTILS_API USPU_SoftPointerUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static const FSoftObjectPath& SoftClassToSoftPath(const TSoftClassPtr<UObject>& SoftClass);
	
	UFUNCTION(BlueprintPure)
	static const FSoftObjectPath& SoftObjectToSoftPath(const TSoftObjectPtr<UObject>& SoftObject);

	UFUNCTION(BlueprintPure)
	static FString SoftPathToString(const FSoftObjectPath& SoftPath);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsValidSoftClass(const TSoftClassPtr<UObject>& SoftClass);
	
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsValidSoftObject(const TSoftObjectPtr<UObject>& SoftObject);

	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsValidSoftPath(const FSoftObjectPath& SoftPath);
	
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsSoftClassLoaded(const TSoftClassPtr<UObject>& SoftClass);
	
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsSoftObjectLoaded(const TSoftObjectPtr<UObject>& SoftObject);

	static void AsyncLoadClass(const TSoftClassPtr<>& SoftClass, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static void AsyncLoadObject(const TSoftObjectPtr<>& SoftObject, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static void AsyncLoadPath(const FSoftObjectPath& SoftPath, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	template<typename ClassType>
	static void AsyncLoadClasses(const TArray<TSoftClassPtr<ClassType>>& SoftClasses, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("ArrayDelegate"))
	{
		static_assert(TIsDerivedFrom<ClassType, UObject>::Value, "Soft class pointers must inherit from UObject!");
	
		const int32 NumSoftClasses = SoftClasses.Num();
		TArray<FSoftObjectPath> SoftPaths;
		SoftPaths.Reserve(NumSoftClasses);
		for (const TSoftClassPtr<>& SoftClass : SoftClasses)
			SoftPaths.Add(SoftClass.ToSoftObjectPath());
	
		return AsyncLoadPaths(MoveTemp(SoftPaths), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
	}

	template<typename ObjectType>
	static void AsyncLoadObjects(const TArray<TSoftObjectPtr<ObjectType>>& SoftObjects, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("ArrayDelegate"))
	{
		static_assert(TIsDerivedFrom<ObjectType, UObject>::Value, "Soft object pointers must inherit from UObject!");

		const int32 NumSoftObjects = SoftObjects.Num();
		TArray<FSoftObjectPath> SoftPaths;
		SoftPaths.Reserve(NumSoftObjects);
		for (const TSoftObjectPtr<>& SoftObject : SoftObjects)
			SoftPaths.Add(SoftObject.ToSoftObjectPath());
	
		return AsyncLoadPaths(MoveTemp(SoftPaths), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
	}
	
	static void AsyncLoadPaths(TArray<FSoftObjectPath> SoftPaths, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("ArrayDelegate"));
	
	static USPU_AsyncLoadHandle* AsyncLoadClassWithHandle(UObject* Outer, const TSoftClassPtr<>& SoftClass, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static USPU_AsyncLoadHandle* AsyncLoadObjectWithHandle(UObject* Outer, const TSoftObjectPtr<>& SoftObject, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static USPU_AsyncLoadHandle* AsyncLoadPathWithHandle(UObject* Outer, const FSoftObjectPath& SoftPath, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	template<typename ClassType>
	static USPU_AsyncLoadHandle* AsyncLoadClassesWithHandle(UObject* Outer, const TArray<TSoftClassPtr<ClassType>>& SoftClasses, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("ArrayDelegate"))
	{
		static_assert(TIsDerivedFrom<ClassType, UObject>::Value, "Soft class pointers must inherit from UObject!");
		
		const int32 NumSoftClasses = SoftClasses.Num();
		TArray<FSoftObjectPath> SoftPaths;
		SoftPaths.Reserve(NumSoftClasses);
		for (const TSoftClassPtr<>& SoftClass : SoftClasses)
			SoftPaths.Add(SoftClass.ToSoftObjectPath());
	
		return AsyncLoadPathsWithHandle(Outer, MoveTemp(SoftPaths), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
	}

	template<typename ObjectType>
	static USPU_AsyncLoadHandle* AsyncLoadObjectsWithHandle(UObject* Outer, const TArray<TSoftObjectPtr<ObjectType>>& SoftObjects, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("ArrayDelegate"))
	{
		static_assert(TIsDerivedFrom<ObjectType, UObject>::Value, "Soft object pointers must inherit from UObject!");

		const int32 NumSoftObjects = SoftObjects.Num();
		TArray<FSoftObjectPath> SoftPaths;
		SoftPaths.Reserve(NumSoftObjects);
		for (const TSoftObjectPtr<>& SoftObject : SoftObjects)
			SoftPaths.Add(SoftObject.ToSoftObjectPath());
	
		return AsyncLoadPathsWithHandle(Outer, MoveTemp(SoftPaths), MoveTemp(OnLoaded), bIsHighPriority, MoveTemp(DebugName));
	}
	
	static USPU_AsyncLoadHandle* AsyncLoadPathsWithHandle(UObject* Outer, TArray<FSoftObjectPath> SoftPaths, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("ArrayDelegate"));

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadClass(const TSoftClassPtr<UObject>& SoftClass, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadObject(const TSoftObjectPtr<UObject>& SoftObject, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadPath(const FSoftObjectPath& SoftPath, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadClasses(const TArray<TSoftClassPtr<UObject>>& SoftClasses, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadObjects(const TArray<TSoftObjectPtr<UObject>>& SoftObjects, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadPaths(const TArray<FSoftObjectPath>& SoftPaths, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadClassWithHandle(UObject* Outer, const TSoftClassPtr<UObject>& SoftClass, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadObjectWithHandle(UObject* Outer, const TSoftObjectPtr<UObject>& SoftObject, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadPathWithHandle(UObject* Outer, const FSoftObjectPath& SoftPath, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadClassesWithHandle(UObject* Outer, const TArray<TSoftClassPtr<UObject>>& SoftClasses, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadObjectsWithHandle(UObject* Outer, const TArray<TSoftObjectPtr<UObject>>& SoftObjects, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadPathsWithHandle(UObject* Outer, const TArray<FSoftObjectPath>& SoftPaths, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

};
