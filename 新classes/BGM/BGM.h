#ifndef __BGM_H__
#define __BGM_H__
#include "cocos2d.h"

USING_NS_CC;

class BGM
{
public:
	static void playBGM(const std::string& BGMName);
	static void playSE(const std::string& SEName);
	static void stopALL();
};

#endif 