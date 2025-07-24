#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundWaveProcedural.h"
#include "MyBlueprintFunctionLibrary.generated.h"


UCLASS()
class UE_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "MyCategory")
    static FString BytesToString(const TArray<uint8>& Bytes);
    UFUNCTION(BlueprintCallable, Category = "MyCategory")
    static USoundWaveProcedural* CreateProceduralSoundWave(const FString& Base64String);
};