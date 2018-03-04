#include "MenuElement.h"

MenuElement::MenuElement(bool isImage, char * name,int fontHandle)
	:m_isImage(false),
	m_name(name)
{
	if (fontHandle != -1) m_fontHandle = fontHandle;
}

MenuElement::MenuElement(int id, int fontHandle)
{
	m_isImage = true;
	m_imgID = id;
	m_imgHandle = GD::Res->Find(id)->GetHandle();
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
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, m_alpha);
		double _ = 0;
		DrawGraph(m_x - 30 * isSelect, m_y, m_imgHandle, TRUE);
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);
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
	isSelect = 1;
	m_alpha = 255;
	m_txtColor = m_txtColorSelected;
	return 0;
}

int MenuElement::Disselected()
{
	isSelect = 0;
	m_alpha = 96;
	m_txtColor = m_txtColorNormal;
	return 0;
}

int MenuElement::Execute()
{
	m_txtColor = m_txtColorExecuted;
	Draw();
	return 0;
}
