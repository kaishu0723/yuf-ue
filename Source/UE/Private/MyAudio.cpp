// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAudio.h"
#include "AudioDevice.h"
#include "AudioCaptureCore.h"
#include "AudioCapture.h" // ���̍s���ł��d�v�ł�

// FAudioCapture�̃C���X�^���X��ێ����邽�߂̃|�C���^
static TUniquePtr<FAudioCapture> AudioCapture;

// �L���v�`�����������f�[�^�𗭂߂Ă������߂̃o�C�g�z��o�b�t�@
static TArray<uint8> AudioBuffer;

void UMyAudio::StartMicCapture()
{
	if (AudioCapture.IsValid())
	{
		return;
	}

	// �G���W���̃I�[�f�B�I�f�o�C�X���擾
	FAudioDevice* AudioDevice = GEngine->GetMainAudioDeviceRaw();
	if (!AudioDevice)
	{
		return;
	}

	// FAudioCapture�̃C���X�^���X�𐶐�
	AudioCapture = FAudio::CreateAudioCapture();

	// �������L���v�`������邽�тɌĂяo����鏈��
	FOnAudioCaptureFunction OnCapture = [=](const float* InAudio, int32 NumSamples, int32 InSampleRate, int32 InChannels)
		{
			// float (-1.0�`1.0) �̃f�[�^�� int16 (-32768�`32767) �ɕϊ�
			TArray<int16> PcmData;
			PcmData.AddUninitialized(NumSamples);
			for (int32 i = 0; i < NumSamples; ++i)
			{
				PcmData[i] = static_cast<int16>(FMath::Clamp(InAudio[i] * 32767.0f, -32768.0f, 32767.0f));
			}

			// int16�̔z����o�C�g�f�[�^(uint8)�Ƃ��ăo�b�t�@�ɒǉ�
			AudioBuffer.Append(reinterpret_cast<const uint8*>(PcmData.GetData()), PcmData.Num() * sizeof(int16));
		};

	// �L���v�`�����J�n
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