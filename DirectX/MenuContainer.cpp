#include "MenuContainer.h"

SoundObject MenuContainer::*selectSound = NULL;
SoundObject MenuContainer::*executeSound = NULL;
MenuElement **elements = NULL;

bool MenuContainer::IsLoadingResources()
{
	bool rs1 = CheckHandleASyncLoad(selectSound->GetHandle());
	bool rs2 = CheckHandleASyncLoad(executeSound->GetHandle());
	return rs1 || rs2;
}

MenuContainer::MenuContainer(
	int nElem,
	bool isImage,
	int fontHandle
	)
	:m_nElem(nElem), 
	m_isImage(isImage),
	m_pSelect(0)
{
	selectSound = new SoundObject("Data/Sound/Lab/cursor1.mp3");
	executeSound = new SoundObject("Data/Sound/Lab/decision22.mp3");
	m_fontHandle = fontHandle;
}


void MenuContainer::SetSource(int id, char *name)
{
	names[id] = name;
	elements[id] = new MenuElement(m_isImage, names[id],m_fontHandle);

}

void MenuContainer::SetSource(int numid, int texid)
{
	ids[numid] = texid;
	handles[numid] = GD::Res->Find(texid)->GetHandle();
	elements[numid] = new MenuElement(texid);
}

void MenuContainer::SetTextColors(int normal, int select, int execute) {
	m_txtColorNormal = normal;
	m_txtColorSelected = select;
	m_txtColorExecuted = execute;
	for (size_t i = 0; i < m_nElem; i++)
	{
		elements[i]->SetTextColors(normal, select, execute);
	}
}


void MenuContainer::SetPosition(int x,int y , int interval)
{
	for (size_t i = 0; i < m_nElem; i++)
	{
		elements[i]->SetPosition(x, y + interval*i);
	}
}

void MenuContainer::SetSelect(int id)
{
	for (size_t i = 0; i < m_nElem; i++)
	{
		i == id ? elements[i]->Selected() :
			elements[i]->Disselected();
	}
}

int MenuContainer::GetSelect()
{
	return m_pSelect;
}

void MenuContainer::Update()
{

	if (PUSHED(GD::Up)) {
		m_pSelect = (m_pSelect + 1) % m_nElem;
		selectSound->Play();
	}
	if (PUSHED(GD::Down)) {
		m_pSelect = (m_pSelect + m_nElem - 1) % m_nElem;
		selectSound->Play();
	}
	SetSelect(m_pSelect);
}

void MenuContainer::Draw()
{
	for (size_t i = 0; i < m_nElem; i++)
	{
		elements[i]->Draw();
	}
}

void MenuContainer::Execute()
{
	executeSound->Play();
	elements[m_pSelect]->Execute();
}


MenuContainer::~MenuContainer()
{
	DeleteSoundMem(selectSound->GetHandle());
	DeleteSoundMem(executeSound->GetHandle());
	delete &selectSound;
	delete &executeSound;
}
