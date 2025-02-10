#include "AudioMaster.h"
#include <Novice.h>

AudioMaster::AudioMaster() {
	for (int i = 0; i < 3; i++) {
		bgmHandle_[i] = -1;
	}
	for (int i = 0; i < 10; i++) {
		sfxHandle_[i] = -1;
	}
}

void AudioMaster::PlayBGM(int bgmFile) {
	for (int i = 0; i < 3; i++) {
		if (bgmHandle_[i] == -1 || !Novice::IsPlayingAudio(bgmHandle_[i])) {
			bgmHandle_[i] = Novice::PlayAudio(bgmFile, 1, 0.7f);
			break;
		}
	}
}

void AudioMaster::PlaySFX(int sfxFile) {
	for (int i = 0; i < 10; i++) {
		if (sfxHandle_[i] == -1 || !Novice::IsPlayingAudio(sfxHandle_[i])) {
			sfxHandle_[i] = Novice::PlayAudio(sfxFile, 0, 0.5f);
			break;
		}
	}
}

void AudioMaster::StopBGM() {
	for (int i = 0; i < 3; i++) {
		if (Novice::IsPlayingAudio(bgmHandle_[i])) {
			Novice::StopAudio(bgmHandle_[i]);
		}
	}
}

void AudioMaster::StopSFX() {
	for (int i = 0; i < 10; i++) {
		if (Novice::IsPlayingAudio(sfxHandle_[i])) {
			Novice::StopAudio(sfxHandle_[i]);
		}
	}
}
