#include "AudioEngine.h"
#include "BGM.h"
#include "BGM/GlobalSetting.h"
USING_NS_CC;

void BGM::playBGM(const std::string &BGMName)
{
	AudioEngine::stop(BGMID);
	if(isPlayBGM)
		BGMID = AudioEngine::play2d(BGMName,true,globalVolume);
}

void BGM::playSE(const std::string& SEName)
{
	if(isPlaySE)
		AudioEngine::play2d(SEName,false,globalVolume);
}

void BGM::stopALL()
{
	AudioEngine::end();
}