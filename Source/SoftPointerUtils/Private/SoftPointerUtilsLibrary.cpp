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
