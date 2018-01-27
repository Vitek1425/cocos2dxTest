#include "mainscene.h"

#include <string>

#include "apiclient.h"
#include "onlinevideoscene.h"
#include "offlinevideoscene.h"
#include "progresswindownode.h"

USING_NS_CC;

#define ONLINE_VIDEO_COUNT_SETTINGS_KEY "onlineVideoCount"
#define OFFLINE_VIDEO_COUNT_SETTINGS_KEY "offlineVideoCount"

Scene* MainScene::createScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	createUI();
	loadSettings();

	return true;
}

void MainScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto mainmenu = Menu::create();

	auto onlineVideoLabel = LabelTTF::create("Show video online", "Arial", 32);
	m_onlineVideoItem = MenuItemLabel::create(onlineVideoLabel);
	m_onlineVideoItem->setCallback([&](cocos2d::Ref *sender) {
		openOnlineVideoScene();
	});
	mainmenu->addChild(m_onlineVideoItem);
    
	m_onlineVideoCountLabel = LabelTTF::create("Online views count 0", "Arial", 20);
	this->addChild(m_onlineVideoCountLabel);

	auto offlineVideoLabel = LabelTTF::create("Show video offline", "Arial", 32);
	m_offlineVideoItem = MenuItemLabel::create(offlineVideoLabel);
	m_offlineVideoItem->setCallback([&](cocos2d::Ref *sender) {
		openOfflineVideoScene();
	});
	mainmenu->addChild(m_offlineVideoItem);

	m_offlineVideoCountLabel = LabelTTF::create("Offline views count 0", "Arial", 20);
	this->addChild(m_offlineVideoCountLabel);

	//позиционирование элементов
	m_onlineVideoItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 0 * 40 - 100));
	m_onlineVideoCountLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 1 * 40 - 100));
	m_offlineVideoItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 2 * 40 - 100));
	m_offlineVideoCountLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 3 * 40 - 100));

	mainmenu->setPosition(Vec2::ZERO);
	this->addChild(mainmenu, 1);

	m_progressNode = ProgressWindowNode::create();
	m_progressNode->setText("Connect to server...");
	m_progressNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(m_progressNode, 2);
	m_progressNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	m_progressNode->setGlobalZOrder(1);
	m_progressNode->setVisible(false);
}

void MainScene::openOnlineVideoScene()
{
	//включение окна загрузки, окно отключитс€ после выполнени€ запроса на проверку соединени€ с интернетом
	setProgressWindowVisible(true);
	ApiClient::getInstance()->checkConnection([&](bool flag) {
		setProgressWindowVisible(false);
		if (flag)
		{
			int onlineVideoCount = UserDefault::getInstance()->getIntegerForKey(ONLINE_VIDEO_COUNT_SETTINGS_KEY, 0);
			UserDefault::getInstance()->setIntegerForKey(ONLINE_VIDEO_COUNT_SETTINGS_KEY, onlineVideoCount + 1);
			loadSettings();

			auto scene = OnlineVideoScene::create();
			Director::getInstance()->pushScene(scene);
		}
		else
		{
			MessageBox("Cannot connect to server", "network error");
		}
	});;
}

void MainScene::openOfflineVideoScene()
{
	//включение окна загрузки, окно отключитс€ после выполнени€ запроса на проверку соединени€ с интернетом
	setProgressWindowVisible(true);
	ApiClient::getInstance()->checkConnection([&](bool flag) {
		setProgressWindowVisible(false);

		//проверка, нужно ли загружать сцену
		bool needLoadOfflineScene = true;
		if (!flag)
		{
			MessageBox("Cannot connect to server", "network error");
			if (!ApiClient::getInstance()->isLocalVideoCopyExist())
			{
				needLoadOfflineScene = false;
			}
		}

		if(needLoadOfflineScene)
		{
			int offlineVideoCount = UserDefault::getInstance()->getIntegerForKey(OFFLINE_VIDEO_COUNT_SETTINGS_KEY, 0);
			UserDefault::getInstance()->setIntegerForKey(OFFLINE_VIDEO_COUNT_SETTINGS_KEY, offlineVideoCount + 1);
			loadSettings();

			auto scene = OfflineVideoScene::create();
			Director::getInstance()->pushScene(scene);
		}
	});;
}

void MainScene::setProgressWindowVisible(bool flag)
{
	m_progressNode->setVisible(flag);
	m_offlineVideoItem->setEnabled(!flag);
	m_onlineVideoItem->setEnabled(!flag);
}

void MainScene::loadSettings()
{
	int onlineVideoCount = UserDefault::getInstance()->getIntegerForKey(ONLINE_VIDEO_COUNT_SETTINGS_KEY, 0);
	m_onlineVideoCountLabel->setString(String::createWithFormat("Online views count %d", onlineVideoCount)->_string);

	int offlineVideoCount = UserDefault::getInstance()->getIntegerForKey(OFFLINE_VIDEO_COUNT_SETTINGS_KEY, 0);
	m_offlineVideoCountLabel->setString(String::createWithFormat("Offline views count %d", offlineVideoCount)->_string);
}
