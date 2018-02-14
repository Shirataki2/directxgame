#pragma once
#include "DxLib.h"
#include <assert.h>
class Task;
class TaskList;
class TaskIter;

class TaskList {
	friend Task;
	friend TaskIter;
	char *Buffer;      //メモリ領域
	Task *ActiveTask;  //先頭のActiveダミータスク
	Task *FreeTask;    //先頭のFreeダミータスク
	size_t TaskSize;   //タスクの最大サイズ
	size_t TaskCount;  //タスクの最大数
	Task *GetTask(size_t i);
public:
	TaskList(size_t size, size_t count);
	~TaskList();

	void* New(size_t size);
	void Delete(void *p);
};

class Task
{
	friend TaskList;
	friend TaskIter;
private:
	Task *prev, *next;

	//new deleteを無効にする
	void *operator new(size_t t) {}
	void operator delete(void *p) {}

public:
	Task(TaskList *list);
	virtual ~Task();
};



class TaskIter {
	TaskList *m_list;
	Task *m_pTask;
public:
	TaskIter(TaskList *list);
	bool HasNext();
	Task* Next();
	void Remove();
};
