#ifndef ONLINEVIDEOSCENE_H
#define ONLINEVIDEOSCENE_H

#include "cocos2d.h"

class ProgressWindowNode;

class OnlineVideoScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(OnlineVideoScene);

	static cocos2d::Scene* createScene();
	virtual bool init() override;
private:
	//создание UI
	void createUI();

	//воспроизведение видео
	void playVideo();

	//возврат в главное меню
	void backToMainMenu();

	//установка видимости окна загрузки
	void setProgressWindowVisible(bool flag);

	cocos2d::MenuItemImage *m_backButton = nullptr;
	ProgressWindowNode *m_progressNode = nullptr;
};

#endif // ONLINEVIDEOSCENE_H