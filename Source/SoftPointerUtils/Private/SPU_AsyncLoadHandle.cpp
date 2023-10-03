// Fill out your copyright notice in the Description page of Project Settings.

#include "SPU_AsyncLoadHandle.h"
#include "Engine/StreamableManager.h"

ESPU_AsyncLoadStatus USPU_AsyncLoadHandle::GetStatus() const
{
	if (StreamableHandle->WasCanceled())
		return ESPU_AsyncLoadStatus::Canceled;
	
	if (StreamableHandle->HasLoadCompleted())
		return ESPU_AsyncLoadStatus::Completed;
	
	if (StreamableHandle->IsStalled())
		return ESPU_AsyncLoadStatus::Stalled;
	
	if (StreamableHandle->IsLoadingInProgress())
		return ESPU_AsyncLoadStatus::InProgress;
	
	return ESPU_AsyncLoadStatus::Active;
}

float USPU_AsyncLoadHandle::GetProgress() const
{
	return StreamableHandle->GetProgress();
}

bool USPU_AsyncLoadHandle::BindOnCompleteDelegate(const FSPU_AsyncLoadHandleDelegate& Delegate)
{
	OnCompleteDelegate = Delegate;
	return StreamableHandle->BindCompleteDelegate(FStreamableDelegate::CreateUObject(this, &USPU_AsyncLoadHandle::OnComplete));
}

bool USPU_AsyncLoadHandle::BindOnCancelDelegate(const FSPU_AsyncLoadHandleDelegate& Delegate)
{
	OnCancelDelegate = Delegate;
	return StreamableHandle->BindCancelDelegate(FStreamableDelegate::CreateUObject(this, &USPU_AsyncLoadHandle::OnCancel));
}

void USPU_AsyncLoadHandle::ForceLoad(const float Timeout, const bool bStartStalledHandles) const
{
	StreamableHandle->WaitUntilComplete(Timeout, bStartStalledHandles);
}

void USPU_AsyncLoadHandle::CancelLoadRequest() const
{
	StreamableHandle->CancelHandle();
}

TSharedPtr<FStreamableHandle> USPU_AsyncLoadHandle::GetLoadHandle() const
{
	return StreamableHandle;
}

void USPU_AsyncLoadHandle::Initialize(TSharedPtr<FStreamableHandle> InWrappedHandle)
{
	StreamableHandle = InWrappedHandle;
}

void USPU_AsyncLoadHandle::OnComplete()
{
	OnCompleteDelegate.ExecuteIfBound();
}

void USPU_AsyncLoadHandle::OnCancel()
{
	OnCancelDelegate.ExecuteIfBound();
}
