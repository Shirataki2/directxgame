#include "Task.h"




Task * TaskList::GetTask(size_t i)
{
	return (Task *)(Buffer + TaskSize * i);
}

TaskList::TaskList(size_t size, size_t count)
	:TaskSize(size),
	TaskCount(count)
{
	//全タスク＋2つのダミー分の領域の確保
	Buffer = new char[TaskSize*(TaskCount + 2)];

	//アクティブなタスクの初期化(ダミーのみ)
	ActiveTask = GetTask(0);
	ActiveTask->prev = ActiveTask;
	ActiveTask->next = ActiveTask;

	//フリーなタスクの初期化(残り全部)
	FreeTask = GetTask(1);
	for (size_t i = 1; i < TaskCount + 2; i++)
	{
		GetTask(i)->prev = NULL;
		GetTask(i)->next = GetTask(i + 1);
	}
	GetTask(TaskCount + 1)->next = FreeTask;
}

TaskList::~TaskList()
{
	delete[] Buffer;
}

void * TaskList::New(size_t size)
{
	assert(size <= TaskSize);

	if (FreeTask->next == FreeTask) return NULL;
	Task *task = FreeTask->next;
	FreeTask->next = task->next;
	return task;
}

void TaskList::Delete(void * p)
{
	Task* task = (Task*)p;
	assert(task->prev != NULL);

	task->prev = NULL;
	task->next = FreeTask->next;
	FreeTask->next = task;
}

Task::Task(TaskList *list)
{
	this->prev = list->ActiveTask->prev;
	this->next = list->ActiveTask;
	this->prev->next = this;
	this->next->prev = this;
}


Task::~Task()
{
	prev->next = next;
	next->prev = prev;
}


TaskIter::TaskIter(TaskList * list)
	:m_list(list),
	m_pTask(list->ActiveTask)
{
}

bool TaskIter::HasNext()
{
	return m_pTask->next != m_list->ActiveTask;
}

Task * TaskIter::Next()
{
	return m_pTask = m_pTask->next;
}

void TaskIter::Remove()
{
	m_pTask = m_pTask->prev;
	delete m_pTask->next;
}
