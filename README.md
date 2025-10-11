# About

This is a thin wrapper around [ReactivePlusPlus](https://github.com/victimsnino/ReactivePlusPlus) for Unreal Engine.
This does not add support for ReactiveX within Blueprint. I am working on a separate plugin for that, and will update
this readme with more information on that when it is released.

# Usage

Add "RppUnreal" to your `PublicDependencyModuleNames` in your desired Build.cs you want to use this in.

If you are going to use anything that takes in a scheduler (delay, throttle, debounce, observe_on, etc.) you will very
likely want to use the `GetScheduler` function in the RppRunLoopSubsystem, which you can get by just calling
`RppRunLoopSubsystem::Get(this)->GetScheduler();` from any UObject.
`GetScheduler` returns a run_loop scheduler that is tied to Unreal Engine's tick in the main thread.
I may replace this with a custom scheduler in the future that uses Unreal Engine's FTimerManager, more exhaustively, but
this is sufficient for now.

# Updating RPP

If you want to update ReactivePlusPlus, overwrite Source/ThirdParty/rpp folder with the src/rpp/rpp folder from the
version of [ReactivePlusPlus](https://github.com/victimsnino/ReactivePlusPlus).
In the future, this will likely be done automatically, either by a Git subtree, submodule, or a script.