#ifndef OFFLINEVIDEOSCENE_H
#define OFFLINEVIDEOSCENE_H

#include "cocos2d.h"

class ProgressWindowNode;

//сцена содержащая плеер для оффлайн просмотра видео
class OfflineVideoScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(OfflineVideoScene);

	static cocos2d::Scene* createScene();
	virtual bool init() override;
private:
	//создание ui
	void createUI();

	//попытаться открыть видео
	void tryOpenVideo();

	//воврат в главное меню
	void backToMainMenu();

	//создание плеера
	void createVideoPlayer();

	//установка видимости окна загрузки
	void setProgressWindowVisible(bool flag);

	cocos2d::MenuItemImage *m_backButton = nullptr;
	ProgressWindowNode *m_progressNode = nullptr;
};

#endif // OFFLINEVIDEOSCENE_H