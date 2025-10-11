// RppRunLoopSubsystem.h
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimerManager.h"

// RPP v2 headers
#include <rpp/rpp.hpp>

#include "RppRunLoopSubsystem.generated.h"

/**
 * UGameInstanceSubsystem that hosts a single RPP run-loop scheduler
 * and pumps it on the Game Thread each frame using FTimerManager.
 *
 * Usage:
 *   auto sched = URppRunLoopSubsystem::Get(this).GetScheduler();
 *   observable | rpp::ops::observe_on(sched) | ... ;
 *
 * Notes:
 *  - We use a "per-frame" pump via SetTimerForNextTick (next frame), which is cheap and safe.
 *  - We drain all "ready" tasks (non-blocking) using run-loop's dispatch_if_ready().
 */
UCLASS()
class RPPUNREAL_API URppRunLoopSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Helper to access the subsystem from any UObject with a World.
	template <typename TWorldContext>
	static URppRunLoopSubsystem& Get(const TWorldContext* ContextObject)
	{
		check(ContextObject);
		UGameInstance* GI = ContextObject->GetWorld() ? ContextObject->GetWorld()->GetGameInstance() : nullptr;
		check(GI);
		auto* Subsystem = GI->GetSubsystem<URppRunLoopSubsystem>();
		check(Subsystem);
		return *Subsystem;
	}

	rpp::schedulers::run_loop GetScheduler() const { return RunLoop; }

	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);

		if (TryGetTimerManager())
		{
			OnTick();
		}
	}

	virtual void Deinitialize() override
	{
		if (auto* timerManager = TryGetTimerManager())
		{
			timerManager->ClearTimer(TickTimerHandle);
		}

		Super::Deinitialize();
	}

private:
	rpp::schedulers::run_loop RunLoop;

	FTimerHandle TickTimerHandle;

	FTimerManager* TryGetTimerManager() const
	{
		if (!GetGameInstance()) return nullptr;
		UWorld* World = GetGameInstance()->GetWorld();
		return World ? &World->GetTimerManager() : nullptr;
	}

	void OnTick()
	{
		if (FTimerManager* timerManager = TryGetTimerManager())
		{
			TickTimerHandle = timerManager->SetTimerForNextTick([this]()
			{
				RunLoop.dispatch_if_ready();
				OnTick();
			});
		}
	}
};
