#include "MenuElement.h"

MenuElement::MenuElement(bool isImage, char * name,int fontHandle)
	:m_isImage(isImage),
	m_name(name)
{
	if (m_isImage) {
		m_imgHandle = LoadGraph(m_name);
	}
	if (fontHandle != -1) m_fontHandle = fontHandle;
}

MenuElement::~MenuElement()
{
}

void MenuElement::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void MenuElement::SetTextColors(int normal, int select, int execute) {
	m_txtColorNormal = normal;
	m_txtColorSelected = select;
	m_txtColorExecuted = execute;
	m_txtColor = m_txtColorNormal;

}

int MenuElement::Draw()
{
	if (m_isImage) {
		DrawGraph(m_x, m_y, m_imgHandle, TRUE);
	}
	else if(m_fontHandle!=-1){
		DrawStringToHandle(m_x, m_y, m_name, m_txtColor, m_fontHandle);
	}
	else {
		DrawString(m_x, m_y, m_name, m_txtColor);
	}

	return 0;
}

int MenuElement::Selected()
{
	m_txtColor = m_txtColorSelected;
	return 0;
}

int MenuElement::Disselected()
{
	m_txtColor = m_txtColorNormal;
	return 0;
}

int MenuElement::Execute()
{
	m_txtColor = m_txtColorExecuted;
	Draw();
	return 0;
}
