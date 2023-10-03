// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/AssetManager.h"
#include "SPU_SoftPointerUtilsLibrary.generated.h"

/* TODO TASK LIST
 * 1) Implement the necessary C++ functionality - IsValid, IsLoaded, LoadSync, LoadAsync (with support for arrays)
 * 2) Figure out if there is any additional functionality we might want for C++
 * 3) Research what support blueprints have for soft pointers, what is missing and what to make blueprint usable
 * 4) Research the possibility of creating a custom wrapper for the async load handle with streamlined API, possibly with a variant for blueprints
 * 5) Once this is feature complete, clean it up, apply UE coding standards and create proper documentation
 * 6) Fill out the copyright, readme, validate the entire content of the plugin
 * 7) Research what needs to be done to publish this on the UE marketplace
 */

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
	
	static TSharedPtr<FStreamableHandle> LoadAsync(const TSoftClassPtr<>& SoftClass, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority = false);
	static TSharedPtr<FStreamableHandle> LoadAsync(const TSoftObjectPtr<>& SoftObject, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority = false);
	static TSharedPtr<FStreamableHandle> LoadAsync(const FSoftObjectPath& SoftPath, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority = false);

	static TSharedPtr<FStreamableHandle> LoadAsync(const TArray<TSoftClassPtr<>>& SoftClasses, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority = false);
	static TSharedPtr<FStreamableHandle> LoadAsync(const TArray<TSoftObjectPtr<>>& SoftObjects, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority = false);
	static TSharedPtr<FStreamableHandle> LoadAsync(const TArray<FSoftObjectPath>& SoftPaths, const FStreamableDelegate& OnLoaded, const bool bIsHighPriority = false);
	//TODO: test the batched variant for c++, test if the request object is working, make it usable in blueprints,
	//      change the API so that they are created on demand, handle blueprint callbacks

	UFUNCTION(BlueprintCallable)
	static void AsyncLoadSoftClass(const TSoftClassPtr<UObject>& SoftClass);

	UFUNCTION(BlueprintCallable)
	static void AsyncLoadSoftObject(const TSoftObjectPtr<UObject>& SoftObject);

	UFUNCTION(BlueprintCallable)
	static void AsyncLoadSoftPath(const FSoftObjectPath& SoftPath);
	
};
