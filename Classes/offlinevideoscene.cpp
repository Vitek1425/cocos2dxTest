#include "offlinevideoscene.h"

#include "apiclient.h"
#include "progresswindownode.h"

#include "ui/UIVideoPlayer.h"

USING_NS_CC;

cocos2d::Scene * OfflineVideoScene::createScene()
{
	return OfflineVideoScene::create();
}

bool OfflineVideoScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	createUI();
	tryOpenVideo();

	return true;
}

void OfflineVideoScene::createUI()
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
	m_progressNode->setText("Loading video...");
	m_progressNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(m_progressNode, 2);
	m_progressNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	m_progressNode->setGlobalZOrder(1);
	m_progressNode->setVisible(false);
}

void OfflineVideoScene::tryOpenVideo()
{
	setProgressWindowVisible(true);
	//проверка на существование локальной копии видео, если она есть, то идет его открытие
	//иначе идет запрос на загрузку видео с последующим его открытием
	if (ApiClient::getInstance()->isLocalVideoCopyExist())
	{
		createVideoPlayer();
	}
	else
	{
		//запрос на загрузку видео
		ApiClient::getInstance()->requestVideoUrl([&](const std::string &url) {
			if (url.empty())
			{
				MessageBox("Cannot load video", "Error");
			}
			else
			{
				ApiClient::getInstance()->loadVideo(url, [&]() {
					if (ApiClient::getInstance()->isLocalVideoCopyExist())
					{
						createVideoPlayer();
					}
					else
					{
						MessageBox("Cannot load video", "Error");
					}
				});
			}
		});
	}
	setProgressWindowVisible(false);
}

void OfflineVideoScene::backToMainMenu()
{
	Director::getInstance()->popScene();
}

void OfflineVideoScene::createVideoPlayer()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN) && !defined(CC_PLATFORM_OS_TVOS)
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto videoPlayer = experimental::ui::VideoPlayer::create();
	videoPlayer->setContentSize(visibleSize);
	videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	videoPlayer->setPosition(visibleSize / 2);
	videoPlayer->setFileName(ApiClient::getInstance()->localVideoCopyPath());
	this->addChild(videoPlayer);
	videoPlayer->play();
#else
	MessageBox("Cannot create video player on this platform", "Error");
#endif
}

void OfflineVideoScene::setProgressWindowVisible(bool flag)
{
	m_backButton->setVisible(!flag);
	m_progressNode->setVisible(flag);
}
