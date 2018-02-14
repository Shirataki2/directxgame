#include "GameObject.h"


GameObject::GameObject(TaskList *list, double x, double y, double angle)
	:Task(list),
	x(x),y(y),angle(angle),scale(1),alpha(1),
	alive(true)
{
}



GameObject::~GameObject()
{
}

int GameObject::Move()
{
	return 0;
}


int GameObject::Draw()
{
	DrawGraph(x, y, textureHandle, TRUE);
	return 0;
}

bool GameObject::IsHit(GameObject * obj)
{
	double
		dx = obj->x - x,
		dy = obj->y - y,
		hit = obj->colSize + this->colSize;
	return dx*dx + dy*dy < hit * hit;
}

bool GameObject::IsHit(TaskList * list)
{
	for (TaskIter i(list); i.HasNext();) {
		GameObject *obj = static_cast<GameObject*>(i.Next());
		if (IsHit(obj)) return true;
	}
	return false;
}

void GameObject::SetTexture(Texture * texture)
{
	textureHandle = texture->GetHandle();
}
