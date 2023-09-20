// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoftPointerUtilsLibrary.generated.h"

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
class SOFTPOINTERUTILS_API USoftPointerUtilsLibrary : public UBlueprintFunctionLibrary
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

};
