#include "AudioChannel.h"

namespace nc {

	bool AudioChannel::isPlaying() {

		if (channel == nullptr) return false;

		bool isPlaying;
		channel->isPlaying(&isPlaying);

		return isPlaying;
	}

	void AudioChannel::Stop() {
		if (isPlaying()) {
			channel->stop();
		}
	}

	void AudioChannel::SetPitch(float pitch) {
		if (isPlaying()) {
			channel->setPitch(pitch);
		}
	}

	void AudioChannel::SetVolume(float volume) {
		if (isPlaying()) {
			channel->setVolume(volume);
		}
	}

	float AudioChannel::GetPitch() {

		float pitch;

		if (isPlaying()) {
			channel->getPitch(&pitch);
		}
		return pitch;
	}

	float AudioChannel::GetVolume() {

		float volume;

		if (isPlaying()) {
			channel->getPitch(&volume);
		}
		return volume;
	}

}