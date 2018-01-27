#ifndef OFFLINEVIDEOSCENE_H
#define OFFLINEVIDEOSCENE_H

#include "cocos2d.h"

class ProgressWindowNode;

//����� ���������� ����� ��� ������� ��������� �����
class OfflineVideoScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(OfflineVideoScene);

	static cocos2d::Scene* createScene();
	virtual bool init() override;
private:
	//�������� ui
	void createUI();

	//���������� ������� �����
	void tryOpenVideo();

	//������ � ������� ����
	void backToMainMenu();

	//�������� ������
	void createVideoPlayer();

	//��������� ��������� ���� ��������
	void setProgressWindowVisible(bool flag);

	cocos2d::MenuItemImage *m_backButton = nullptr;
	ProgressWindowNode *m_progressNode = nullptr;
};

#endif // OFFLINEVIDEOSCENE_H