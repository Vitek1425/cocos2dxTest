#include "progresswindownode.h"

USING_NS_CC;

void ProgressWindowNode::setText(const std::string & text)
{
	m_text = text;
	if (m_textLabel)
	{
		m_textLabel->setString(m_text);
	}
}

bool ProgressWindowNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void ProgressWindowNode::onEnter()
{
	Node::onEnter();

	createItems();
}

void ProgressWindowNode::createItems()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->setContentSize(visibleSize);
	
	auto background = Sprite::create("whiteBox.png");
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Vec2::ZERO);
	this->addChild(background);
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	background->setScale(51.2);

	auto progressIcon = Sprite::create("progressIcon.png");
	progressIcon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	progressIcon->setPosition(Vec2::ZERO);
	progressIcon->schedule([progressIcon](float f) {

		auto rotateBy = RotateBy::create(0, 40.0f);
		progressIcon->runAction(rotateBy);

	}, 0.166f, "update_progressIcon");
	this->addChild(progressIcon);
	progressIcon->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	m_textLabel = LabelTTF::create(m_text, "Arial", 22);
	m_textLabel->setColor(Color3B::BLACK);
	m_textLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.8);
	this->addChild(m_textLabel);
}
