#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyAudio.generated.h"

UCLASS()
class UE_API UMyAudio : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyAudio")
	static void StartMicCapture();

	UFUNCTION(BlueprintCallable, Category = "MyAudio")
	static void StopMicCapture();

	UFUNCTION(BlueprintCallable, Category = "MyAudio")
	static TArray<uint8> GetMicAudioData();
};