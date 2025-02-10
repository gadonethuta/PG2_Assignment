#pragma once

//BGMやSFXをシングルトンででこからでも呼べる

class AudioMaster {
private:
	static AudioMaster* instance;

	int bgmHandle_[3];
	int sfxHandle_[10];

	AudioMaster();

public:
	static AudioMaster* GetInstance() {
		if (instance == nullptr) {
			instance = new AudioMaster();
		}
		return instance;
	}

	void PlayBGM(int bgmFile);
	void PlaySFX(int sfxFile);
	void StopBGM();
	void StopSFX();

	//コピーを防ぐためにコピーコンストラクタと代入演算子を削除する
	AudioMaster(const AudioMaster&) = delete;
	AudioMaster& operator=(const AudioMaster&) = delete;
};

