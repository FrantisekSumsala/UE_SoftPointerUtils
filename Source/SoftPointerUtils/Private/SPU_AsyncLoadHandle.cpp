// Fill out your copyright notice in the Description page of Project Settings.

#include "SPU_AsyncLoadHandle.h"
#include "Engine/StreamableManager.h"

ESPU_AsyncLoadStatus USPU_AsyncLoadHandle::GetStatus() const
{
	if (LoadHandle->WasCanceled())
		return ESPU_AsyncLoadStatus::Canceled;
	
	if (LoadHandle->HasLoadCompleted())
		return ESPU_AsyncLoadStatus::Completed;
	
	if (LoadHandle->IsStalled())
		return ESPU_AsyncLoadStatus::Stalled;
	
	if (LoadHandle->IsLoadingInProgress())
		return ESPU_AsyncLoadStatus::InProgress;
	
	return ESPU_AsyncLoadStatus::Active;
}

float USPU_AsyncLoadHandle::GetProgress() const
{
	return LoadHandle->GetProgress();
}

bool USPU_AsyncLoadHandle::BindOnCompleteDelegate(const FAsyncLoadDelegate& Delegate)
{
	OnCompleteDelegate = Delegate;
	return LoadHandle->BindCompleteDelegate(FStreamableDelegate::CreateUObject(this, &USPU_AsyncLoadHandle::OnComplete));
}

bool USPU_AsyncLoadHandle::BindOnCancelDelegate(const FAsyncLoadDelegate& Delegate)
{
	OnCancelDelegate = Delegate;
	return LoadHandle->BindCancelDelegate(FStreamableDelegate::CreateUObject(this, &USPU_AsyncLoadHandle::OnCancel));
}

void USPU_AsyncLoadHandle::ForceLoad(const float Timeout, const bool bStartStalledHandles) const
{
	LoadHandle->WaitUntilComplete(Timeout, bStartStalledHandles);
}

void USPU_AsyncLoadHandle::CancelLoadRequest() const
{
	LoadHandle->CancelHandle();
}

TSharedPtr<FStreamableHandle> USPU_AsyncLoadHandle::GetLoadHandle() const
{
	return LoadHandle;
}

void USPU_AsyncLoadHandle::Initialize(TSharedPtr<FStreamableHandle> InWrappedHandle)
{
	LoadHandle = InWrappedHandle;
}

void USPU_AsyncLoadHandle::OnComplete()
{
	OnCompleteDelegate.ExecuteIfBound();
}

void USPU_AsyncLoadHandle::OnCancel()
{
	OnCancelDelegate.ExecuteIfBound();
}
