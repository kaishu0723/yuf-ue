// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAudio.h"
#include "AudioDevice.h"
#include "AudioCaptureCore.h"
#include "AudioCapture.h" // この行が最も重要です

// FAudioCaptureのインスタンスを保持するためのポインタ
static TUniquePtr<FAudioCapture> AudioCapture;

// キャプチャした音声データを溜めておくためのバイト配列バッファ
static TArray<uint8> AudioBuffer;

void UMyAudio::StartMicCapture()
{
	if (AudioCapture.IsValid())
	{
		return;
	}

	// エンジンのオーディオデバイスを取得
	FAudioDevice* AudioDevice = GEngine->GetMainAudioDeviceRaw();
	if (!AudioDevice)
	{
		return;
	}

	// FAudioCaptureのインスタンスを生成
	AudioCapture = FAudio::CreateAudioCapture();

	// 音声がキャプチャされるたびに呼び出される処理
	FOnAudioCaptureFunction OnCapture = [=](const float* InAudio, int32 NumSamples, int32 InSampleRate, int32 InChannels)
		{
			// float (-1.0～1.0) のデータを int16 (-32768～32767) に変換
			TArray<int16> PcmData;
			PcmData.AddUninitialized(NumSamples);
			for (int32 i = 0; i < NumSamples; ++i)
			{
				PcmData[i] = static_cast<int16>(FMath::Clamp(InAudio[i] * 32767.0f, -32768.0f, 32767.0f));
			}

			// int16の配列をバイトデータ(uint8)としてバッファに追加
			AudioBuffer.Append(reinterpret_cast<const uint8*>(PcmData.GetData()), PcmData.Num() * sizeof(int16));
		};

	// キャプチャを開始
	AudioCapture->StartCapturingAudio(OnCapture);
}

void UMyAudio::StopMicCapture()
{
	if (AudioCapture.IsValid())
	{
		AudioCapture->StopCapturingAudio();
		AudioCapture.Reset();
		AudioBuffer.Empty();
	}
}

TArray<uint8> UMyAudio::GetMicAudioData()
{
	TArray<uint8> ReturnData = AudioBuffer;
	AudioBuffer.Empty();
	return ReturnData;
}