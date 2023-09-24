// Fill out your copyright notice in the Description page of Project Settings.

#include "AsyncLoadRequest.h"
#include "Engine/StreamableManager.h"

EAsyncLoadRequestStatus UAsyncLoadRequest::GetStatus() const
{
	if (LoadHandle->WasCanceled())
		return EAsyncLoadRequestStatus::Canceled;
	
	if (LoadHandle->HasLoadCompleted())
		return EAsyncLoadRequestStatus::Completed;
	
	if (LoadHandle->IsStalled())
		return EAsyncLoadRequestStatus::Stalled;
	
	if (LoadHandle->IsLoadingInProgress())
		return EAsyncLoadRequestStatus::InProgress;
	
	return EAsyncLoadRequestStatus::Active;
}

float UAsyncLoadRequest::GetProgress() const
{
	return LoadHandle->GetProgress();
}

bool UAsyncLoadRequest::BindOnCompleteDelegate(const FAsyncLoadDelegate& Delegate)
{
	OnCompleteDelegate = Delegate;
	return LoadHandle->BindCompleteDelegate(FStreamableDelegate::CreateUObject(this, &UAsyncLoadRequest::OnComplete));
}

bool UAsyncLoadRequest::BindOnCancelDelegate(const FAsyncLoadDelegate& Delegate)
{
	OnCancelDelegate = Delegate;
	return LoadHandle->BindCancelDelegate(FStreamableDelegate::CreateUObject(this, &UAsyncLoadRequest::OnCancel));
}

void UAsyncLoadRequest::ForceLoad(const float Timeout, const bool bStartStalledHandles) const
{
	LoadHandle->WaitUntilComplete(Timeout, bStartStalledHandles);
}

void UAsyncLoadRequest::CancelLoadRequest() const
{
	LoadHandle->CancelHandle();
}

TSharedPtr<FStreamableHandle> UAsyncLoadRequest::GetLoadHandle() const
{
	return LoadHandle;
}

void UAsyncLoadRequest::Initialize(TSharedPtr<FStreamableHandle> InWrappedHandle)
{
	LoadHandle = InWrappedHandle;
}

void UAsyncLoadRequest::OnComplete()
{
	OnCompleteDelegate.ExecuteIfBound();
}

void UAsyncLoadRequest::OnCancel()
{
	OnCancelDelegate.ExecuteIfBound();
}
