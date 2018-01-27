#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "cocos2d.h"

class ProgressWindowNode;

//главная сцена приложения
class MainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
private:
	//создание ui
	void createUI();

	//открытие сцены воспроизводящей видео онлайн
	void openOnlineVideoScene();

	//открытие сцены воспроизводящей видео оффлайн
	void openOfflineVideoScene();

	//установка видимости окна загрузки
	void setProgressWindowVisible(bool flag);
	
	//загрузка числа воспроизведений
	void loadSettings();

	cocos2d::MenuItemLabel *m_onlineVideoItem = nullptr;
	cocos2d::LabelTTF *m_onlineVideoCountLabel = nullptr;
	cocos2d::MenuItemLabel *m_offlineVideoItem = nullptr;
	cocos2d::LabelTTF *m_offlineVideoCountLabel = nullptr;

	ProgressWindowNode *m_progressNode = nullptr;
};

#endif // MAINSCENE_H