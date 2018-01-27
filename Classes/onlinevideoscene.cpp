#include "onlinevideoscene.h"

#include "apiclient.h"
#include "progresswindownode.h"

#include "ui/UIVideoPlayer.h"

USING_NS_CC;

Scene * OnlineVideoScene::createScene()
{
	return OnlineVideoScene::create();
}

bool OnlineVideoScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	createUI();
	playVideo();

	return true;
}

void OnlineVideoScene::createUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	m_backButton = MenuItemImage::create("backButton.png", "backButton.png",
		[&](Ref* pSender) {
		backToMainMenu();
	});

	m_backButton->setPosition(Vec2(origin.x + visibleSize.width - m_backButton->getContentSize().width / 2,
								   origin.y - m_backButton->getContentSize().height / 2 + visibleSize.height));

	auto menu = Menu::create(m_backButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	m_progressNode = ProgressWindowNode::create();
	m_progressNode->setText("Downloading video...");
	m_progressNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(m_progressNode, 2);
	m_progressNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	m_progressNode->setGlobalZOrder(1);
	m_progressNode->setVisible(false);
}

void OnlineVideoScene::playVideo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) && !defined(CC_PLATFORM_OS_TVOS)
	setProgressWindowVisible(true);
	ApiClient::getInstance()->requestVideoUrl([&](const std::string &url) {
		if (url.empty())
		{
			MessageBox("Cannot open video", "Error");
		}
		else
		{	
			auto visibleSize = Director::getInstance()->getVisibleSize();
			auto videoPlayer = experimental::ui::VideoPlayer::create();
			videoPlayer->setContentSize(visibleSize);
			videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
			videoPlayer->setPosition(visibleSize / 2);
			videoPlayer->setURL(url);
			this->addChild(videoPlayer);
			videoPlayer->play();
		}
		setProgressWindowVisible(false);
	});
#else
	MessageBox("Cannot create video player on this platform", "Error");
#endif
}

void OnlineVideoScene::backToMainMenu()
{
	Director::getInstance()->popScene();
}

void OnlineVideoScene::setProgressWindowVisible(bool flag)
{
	m_backButton->setVisible(!flag);
	m_progressNode->setVisible(flag);
}
