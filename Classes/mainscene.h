#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "cocos2d.h"

class ProgressWindowNode;

//������� ����� ����������
class MainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
private:
	//�������� ui
	void createUI();

	//�������� ����� ��������������� ����� ������
	void openOnlineVideoScene();

	//�������� ����� ��������������� ����� �������
	void openOfflineVideoScene();

	//��������� ��������� ���� ��������
	void setProgressWindowVisible(bool flag);
	
	//�������� ����� ���������������
	void loadSettings();

	cocos2d::MenuItemLabel *m_onlineVideoItem = nullptr;
	cocos2d::LabelTTF *m_onlineVideoCountLabel = nullptr;
	cocos2d::MenuItemLabel *m_offlineVideoItem = nullptr;
	cocos2d::LabelTTF *m_offlineVideoCountLabel = nullptr;

	ProgressWindowNode *m_progressNode = nullptr;
};

#endif // MAINSCENE_H