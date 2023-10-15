// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SPU_SoftPointerUtilsLibrary.generated.h"

/* TODO TASK LIST
 * Test that everything compiles and works in every UE version starting with 5.0
 * Once this is feature complete, clean it up, apply UE coding standards and create proper documentation
 * Fill out the copyright, readme, validate the entire content of the plugin
 * Research what needs to be done to publish this on the UE marketplace
 */

class USPU_AsyncLoadHandle;

DECLARE_DELEGATE(FSPU_AsyncLoadDelegate);
DECLARE_DYNAMIC_DELEGATE(FSPU_DynamicAsyncLoadDelegate);

/**
 * Blueprint function library containing utility functions for working with and async loading of soft pointers.
 * Note: Async loading of soft pointers is implemented using UAssetManager's FStreamableManager.
 */
UCLASS()
class SOFTPOINTERUTILS_API USPU_SoftPointerUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Obtains a reference to the internal soft path from a soft class pointer.
	 * @param SoftClass Soft class pointer to obtain the soft path from.
	 * @return Reference to the internal soft path.
	 */
	UFUNCTION(BlueprintPure)
	static const FSoftObjectPath& SoftClassToSoftPath(const TSoftClassPtr<UObject>& SoftClass);

	/**
	 * Obtains a reference to the internal soft path from a soft object pointer.
	 * @param SoftObject Soft object pointer to obtain the soft path from.
	 * @return Reference to the internal soft path.
	 */
	UFUNCTION(BlueprintPure)
	static const FSoftObjectPath& SoftObjectToSoftPath(const TSoftObjectPtr<UObject>& SoftObject);

	/**
	 * Converts a soft path to an FString (primarily for debugging purposes).
	 * @param SoftPath The soft path to convert.
	 * @return FString containing the asset path to the referenced resource.
	 */
	UFUNCTION(BlueprintPure)
	static FString SoftPathToString(const FSoftObjectPath& SoftPath);

	/**
	 * Checks whether the soft class pointer is valid - references an actual class.
	 * @param SoftClass The soft class pointer to check.
	 * @return True if the soft class pointer references an actual class, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsValidSoftClass(const TSoftClassPtr<UObject>& SoftClass);

	/**
	 * Checks whether the soft object pointer is valid - references an actual asset.
	 * @param SoftObject The soft object pointer to check.
	 * @return True if the soft object pointer references an actual asset, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsValidSoftObject(const TSoftObjectPtr<UObject>& SoftObject);

	/**
	 * Checks whether the soft path is valid - contains a valid asset path.
	 * @param SoftPath The soft path to check.
	 * @return True if the soft path contains a valid asset path, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsValidSoftPath(const FSoftObjectPath& SoftPath);

	/**
	 * Checks whether the class referenced by a soft class pointer is already loaded.
	 * @param SoftClass The soft class pointer to check.
	 * @return True if the class referenced by the soft class pointer is loaded, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsSoftClassLoaded(const TSoftClassPtr<UObject>& SoftClass);

	/**
	 * Checks whether the asset referenced by a soft object pointer is already loaded.
	 * @param SoftObject The soft object pointer to check.
	 * @return True if the asset referenced by the soft object pointer is loaded, false otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsSoftObjectLoaded(const TSoftObjectPtr<UObject>& SoftObject);

	/**
	 * Async loads the given soft class pointer, allowing for a callback to be executed once it is loaded.
	 * @param SoftClass The soft class pointer to load.
	 * @param OnLoaded The callback to execute once the class is loaded.
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default).
	 * @param DebugName Optional name identifying the load request, used for debugging.
	 */
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadClass(const TSoftClassPtr<UObject>& SoftClass, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static void AsyncLoadClass(const TSoftClassPtr<>& SoftClass, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	/**
	 * Async loads the given soft object pointer, allowing for a callback to be executed once it is loaded.
	 * @param SoftObject The soft object pointer to load.
	 * @param OnLoaded The callback to execute once the asset is loaded.
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default).
	 * @param DebugName Optional name identifying the load request, used for debugging.
	 */
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadObject(const TSoftObjectPtr<UObject>& SoftObject, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static void AsyncLoadObject(const TSoftObjectPtr<>& SoftObject, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	/**
	 * Async loads the resource referenced by the given soft path, allowing for a callback to be executed once it is loaded.
	 * @param SoftPath The soft path to load.
	 * @param OnLoaded The callback to execute once the resource is loaded.
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default).
	 * @param DebugName Optional name identifying the load request, used for debugging.
	 */
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadPath(const FSoftObjectPath& SoftPath, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static void AsyncLoadPath(const FSoftObjectPath& SoftPath, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	/**
	 * Async loads an array of soft class pointers, allowing for a callback to be executed once they are loaded.
	 * @param SoftClasses The soft class pointers to load.
	 * @param OnLoaded The callback to execute once the classes are loaded.
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default).
	 * @param DebugName Optional name identifying the load request, used for debugging.
	 */
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadClasses(const TArray<TSoftClassPtr<UObject>>& SoftClasses, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
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

	/**
	 * Async loads an array of soft object pointers, allowing for a callback to be executed once they are loaded.
	 * @param SoftObjects The soft object pointers to load.
	 * @param OnLoaded The callback to execute once the assets are loaded.
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default).
	 * @param DebugName Optional name identifying the load request, used for debugging.
	 */
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadObjects(const TArray<TSoftObjectPtr<UObject>>& SoftObjects, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
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

	/**
	 * Async loads an array of soft paths, allowing for a callback to be executed once they are loaded.
	 * @param SoftPaths The soft paths to load.
	 * @param OnLoaded The callback to execute once the resources are loaded.
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default).
	 * @param DebugName Optional name identifying the load request, used for debugging.
	 */
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay=2))
	static void AsyncLoadPaths(const TArray<FSoftObjectPath>& SoftPaths, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static void AsyncLoadPaths(TArray<FSoftObjectPath> SoftPaths, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("ArrayDelegate"));

	/**
	 * Async loads the given soft class pointer, allowing for a callback to be executed once it is loaded. Returns a load
	 * handle that can be used to manage the load request.
	 * @param Outer Outer object for the created load handle.
	 * @param SoftClass The soft class pointer to load. 
	 * @param OnLoaded The callback to execute once the class is loaded. 
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default). 
	 * @param DebugName Optional name identifying the load request, used for debugging. 
	 * @return Pointer to an USPU_AsyncLoadHandle instance managing the load request if a valid load request is made, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadClassWithHandle(UObject* Outer, const TSoftClassPtr<UObject>& SoftClass, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static USPU_AsyncLoadHandle* AsyncLoadClassWithHandle(UObject* Outer, const TSoftClassPtr<>& SoftClass, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	/**
	 * Async loads the given soft object pointer, allowing for a callback to be executed once it is loaded. Returns a load
	 * handle that can be used to manage the load request.
	 * @param Outer Outer object for the created load handle.
	 * @param SoftObject The soft object pointer to load. 
	 * @param OnLoaded The callback to execute once the asset is loaded. 
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default). 
	 * @param DebugName Optional name identifying the load request, used for debugging. 
	 * @return Pointer to an USPU_AsyncLoadHandle instance managing the load request if a valid load request is made, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadObjectWithHandle(UObject* Outer, const TSoftObjectPtr<UObject>& SoftObject, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static USPU_AsyncLoadHandle* AsyncLoadObjectWithHandle(UObject* Outer, const TSoftObjectPtr<>& SoftObject, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	/**
	 * Async loads the given soft path, allowing for a callback to be executed once it is loaded. Returns a load
	 * handle that can be used to manage the load request.
	 * @param Outer Outer object for the created load handle.
	 * @param SoftPath The soft path to load. 
	 * @param OnLoaded The callback to execute once the resource is loaded. 
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default). 
	 * @param DebugName Optional name identifying the load request, used for debugging. 
	 * @return Pointer to an USPU_AsyncLoadHandle instance managing the load request if a valid load request is made, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadPathWithHandle(UObject* Outer, const FSoftObjectPath& SoftPath, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static USPU_AsyncLoadHandle* AsyncLoadPathWithHandle(UObject* Outer, const FSoftObjectPath& SoftPath, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));

	/**
	 * Async loads an array of soft class pointers, allowing for a callback to be executed once they are loaded. Returns a load
	 * handle that can be used to manage the load request.
	 * @param Outer Outer object for the created load handle.
	 * @param SoftClasses The soft class pointers to load. 
	 * @param OnLoaded The callback to execute once the classes are loaded. 
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default). 
	 * @param DebugName Optional name identifying the load request, used for debugging. 
	 * @return Pointer to an USPU_AsyncLoadHandle instance managing the load request if a valid load request is made, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadClassesWithHandle(UObject* Outer, const TArray<TSoftClassPtr<UObject>>& SoftClasses, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
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

	/**
	 * Async loads an array of soft object pointers, allowing for a callback to be executed once they are loaded. Returns a load
	 * handle that can be used to manage the load request.
	 * @param Outer Outer object for the created load handle.
	 * @param SoftObjects The soft object pointers to load. 
	 * @param OnLoaded The callback to execute once the assets are loaded. 
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default). 
	 * @param DebugName Optional name identifying the load request, used for debugging. 
	 * @return Pointer to an USPU_AsyncLoadHandle instance managing the load request if a valid load request is made, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadObjectsWithHandle(UObject* Outer, const TArray<TSoftObjectPtr<UObject>>& SoftObjects, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
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

	/**
	 * Async loads an array of soft paths, allowing for a callback to be executed once they are loaded. Returns a load
	 * handle that can be used to manage the load request.
	 * @param Outer Outer object for the created load handle.
	 * @param SoftPaths The soft paths to load. 
	 * @param OnLoaded The callback to execute once the resources are loaded. 
	 * @param bIsHighPriority Whether to treat this load request as higher priority (false by default). 
	 * @param DebugName Optional name identifying the load request, used for debugging. 
	 * @return Pointer to an USPU_AsyncLoadHandle instance managing the load request if a valid load request is made, nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="Outer", AdvancedDisplay=3))
	static USPU_AsyncLoadHandle* AsyncLoadPathsWithHandle(UObject* Outer, const TArray<FSoftObjectPath>& SoftPaths, FSPU_DynamicAsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("SingleDelegate"));
	static USPU_AsyncLoadHandle* AsyncLoadPathsWithHandle(UObject* Outer, TArray<FSoftObjectPath> SoftPaths, FSPU_AsyncLoadDelegate OnLoaded, const bool bIsHighPriority = false, FString DebugName = TEXT("ArrayDelegate"));

};
