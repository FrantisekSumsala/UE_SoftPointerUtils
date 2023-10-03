// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SPU_AsyncLoadHandle.generated.h"

struct FStreamableHandle;

UENUM(BlueprintType)
enum class ESPU_AsyncLoadStatus : uint8
{
	InProgress,
	Stalled,
	Completed,
	Canceled,
	Active
};

DECLARE_DYNAMIC_DELEGATE(FAsyncLoadDelegate);

UCLASS(BlueprintType)
class SOFTPOINTERUTILS_API USPU_AsyncLoadHandle : public UObject
{
	GENERATED_BODY()

	friend class USPU_SoftPointerUtilsLibrary;
	
private:
	TSharedPtr<FStreamableHandle> LoadHandle;

	UPROPERTY()
	FAsyncLoadDelegate OnCompleteDelegate;

	UPROPERTY()
	FAsyncLoadDelegate OnCancelDelegate;

public:
	UFUNCTION(BlueprintPure)
	ESPU_AsyncLoadStatus GetStatus() const;

	UFUNCTION(BlueprintPure)
	float GetProgress() const;
	// GetProgress
	
	UFUNCTION(BlueprintCallable)
	bool BindOnCompleteDelegate(const FAsyncLoadDelegate& Delegate);
	// BindCompleteDelegate

	UFUNCTION(BlueprintCallable)
	bool BindOnCancelDelegate(const FAsyncLoadDelegate& Delegate);
	// BindCancelDelegate
	
	UFUNCTION(BlueprintCallable)
	void ForceLoad(const float Timeout = 0.0f, const bool bStartStalledHandles = true) const;
	// WaitUntilComplete
	
	UFUNCTION(BlueprintCallable)
	void CancelLoadRequest() const;
	// CancelHandle
	
	//TODO: non-wrapped functions - verify that we have wrapped all relevant functions
	// - BindUpdateDelegate - could not be bound for some reason and seemed like would not be invoked anyway
	// - HasUpdateDelegate - pointless without BindUpdateDelegate
	// - ReleaseHandle - weirder version of CancelHandle, probably more suited for internal purposes and thus redundant
	// - IsActive - replaced by unifying GetStatus()
	// - IsLoadingInProgress - replaced by unifying GetStatus()
	// - IsStalled - replaced by unifying GetStatus()
	// - HasLoadCompleted - replaced by unifying GetStatus()
	// - WasCanceled - replaced by unifying GetStatus()
	// - GetRequestedAssets - seems like intended for internal purposes
	// - GetLoadedAssets - seems like intended for internal purposes
	// - HasCompleteDelegate - seems kind of pointless
	// - HasCancelDelegate - seems kind of pointless

	TSharedPtr<FStreamableHandle> GetLoadHandle() const;
	
private:
	void Initialize(TSharedPtr<FStreamableHandle> InWrappedHandle);
	
	void OnComplete();
	void OnCancel();

};
