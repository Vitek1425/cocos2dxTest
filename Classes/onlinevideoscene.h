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
	//�������� UI
	void createUI();

	//��������������� �����
	void playVideo();

	//������� � ������� ����
	void backToMainMenu();

	//��������� ��������� ���� ��������
	void setProgressWindowVisible(bool flag);

	cocos2d::MenuItemImage *m_backButton = nullptr;
	ProgressWindowNode *m_progressNode = nullptr;
};

#endif // ONLINEVIDEOSCENE_H