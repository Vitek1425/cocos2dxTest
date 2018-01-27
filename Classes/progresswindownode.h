#ifndef PROGRESSWINDOWNODE_H
#define PROGRESSWINDOWNODE_H

#include "cocos2d.h"

#include <string>

//node для показа процесса загрузки

class ProgressWindowNode : public cocos2d::Node
{
public:
	CREATE_FUNC(ProgressWindowNode);

	void setText(const std::string &text);
protected:
	bool init() override;
	void onEnter() override;
private:
	void createItems();

	cocos2d::LabelTTF *m_textLabel = nullptr;
	std::string m_text;
};

#endif // PROGRESSWINDOWNODE_H