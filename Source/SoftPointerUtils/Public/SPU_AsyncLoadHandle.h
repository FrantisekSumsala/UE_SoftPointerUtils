// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SPU_AsyncLoadHandle.generated.h"

struct FStreamableHandle;

/** Enum representing the status of an async load request. */
UENUM(BlueprintType)
enum class ESPU_AsyncLoadStatus : uint8
{
	InProgress,
	Stalled,
	Completed,
	Canceled,
	Active
};

DECLARE_DYNAMIC_DELEGATE(FSPU_AsyncLoadHandleDelegate);

/**
 * Handle managing an async load request, allowing to query its status and progress, force a synchronous completion
 * or to cancel the load request entirely.
 * Note: Functions as an UObject-based wrapper around the low level FStreamableHandle that is returned by the streaming
 * manager that offers a simplified API.
 */
UCLASS(BlueprintType)
class SOFTPOINTERUTILS_API USPU_AsyncLoadHandle final : public UObject
{
	GENERATED_BODY()

	friend class USPU_SoftPointerUtilsLibrary;
	
private:
	TSharedPtr<FStreamableHandle> StreamableHandle;

	UPROPERTY()
	FSPU_AsyncLoadHandleDelegate OnCompleteDelegate;

	UPROPERTY()
	FSPU_AsyncLoadHandleDelegate OnCancelDelegate;

public:
	/**
	 * Returns the status of the async load request.
	 * @return ESPU_AsyncLoadStatus enum value representing the status of the load request.
	 */
	UFUNCTION(BlueprintPure)
	ESPU_AsyncLoadStatus GetStatus() const;

	/**
	 * Returns the progress of the load request.
	 * @return The load progress normalized to range from 0 to 1.
	 */
	UFUNCTION(BlueprintPure)
	float GetProgress() const;

	/**
	 * Sets the delegate callback that will be executed once the load request managed by this handle is completed.
	 * @param Delegate The delegate to be called when the load request is completed.
	 * @return Whether the binding was successful - can only be done when the load is in progress. 
	 */
	UFUNCTION(BlueprintCallable)
	bool BindOnCompleteDelegate(const FSPU_AsyncLoadHandleDelegate& Delegate);

	/**
	 * Sets the delegate callback that will be executed if the load request managed by this handle is cancelled.
	 * @param Delegate The delegate to be called when the load request is cancelled.
	 * @return Whether the binding was successful - can only be done when the load is in progress. 
	 */
	UFUNCTION(BlueprintCallable)
	bool BindOnCancelDelegate(const FSPU_AsyncLoadHandleDelegate& Delegate);

	/**
	 * Finishes the load request synchronously without flushing other async loads. 
	 * @param Timeout The maximum amount of time in seconds that this action can take. If set to 0, this limit is infinite.
	 */
	UFUNCTION(BlueprintCallable)
	void ForceLoad(const float Timeout = 0.0f) const;

	/**
	 * Cancel this load request.
	 */
	UFUNCTION(BlueprintCallable)
	void CancelLoadRequest() const;

	/**
	 * Returns the internal FStreamableHandle pointer.
	 * @return TSharedPtr<FStreamableHandle> managing the low level load request.
	 */
	TSharedPtr<FStreamableHandle> GetLoadHandle() const;
	
private:
	void Initialize(TSharedPtr<FStreamableHandle> InWrappedHandle);
	
	void OnComplete();
	void OnCancel();

};
