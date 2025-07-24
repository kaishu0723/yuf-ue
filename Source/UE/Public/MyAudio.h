// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AudioCapture.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyAudio.generated.h"

/**
 * 
 */
UCLASS()
class UE_API UMyAudio : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "MyAudio", meta = (Keywords = "Audio Microphone Mic Capture Start"))
    static void StartMicCapture();

    UFUNCTION(BlueprintCallable, Category = "MyAudio", meta = (Keywords = "Audio Microphone Mic Capture Stop"))
    static void StopMicCapture();

    UFUNCTION(BlueprintCallable, Category = "MyAudio", meta = (Keywords = "Audio Microphone Mic Capture Get Data Buffer"))
    static TArray<uint8> GetMicAudioData();
};
