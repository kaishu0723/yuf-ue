// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

FString UMyBlueprintFunctionLibrary::BytesToString(const TArray<uint8>& Bytes)
{
    if (Bytes.Num() == 0) return FString();

    // バイト列をnull終端してから変換
    TArray<uint8> NullTerminated = Bytes;
    NullTerminated.Add(0);

    return FString(FUTF8ToTCHAR(reinterpret_cast<const ANSICHAR*>(NullTerminated.GetData())));
}

#include "Misc/Base64.h"
USoundWaveProcedural* UMyBlueprintFunctionLibrary::CreateProceduralSoundWave(const FString& Base64String) {
    TArray<uint8> Bytes;
    FBase64::Decode(Base64String, Bytes);
	FWaveModInfo WaveInfo;
    if (!WaveInfo.ReadWaveInfo(Bytes.GetData(), Bytes.Num())) {
        return nullptr;
    }

    USoundWaveProcedural* ProcWave = NewObject<USoundWaveProcedural>();

    ProcWave->SetSampleRate(*WaveInfo.pSamplesPerSec);
    ProcWave->NumChannels = 1;
    ProcWave->Duration = (float)WaveInfo.SampleDataSize
        / ((*WaveInfo.pChannels)
            * (*WaveInfo.pBitsPerSample / 8.f)
            * (*WaveInfo.pSamplesPerSec));
    ProcWave->bLooping = false;

    ProcWave->QueueAudio(WaveInfo.SampleDataStart, WaveInfo.SampleDataSize);

    return ProcWave;
}