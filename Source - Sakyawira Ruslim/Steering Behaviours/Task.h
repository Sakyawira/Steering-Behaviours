#pragma once
#include <future>
class BasicTask
{
public:
	virtual ~BasicTask() {};
	virtual void execute() = 0;
};

template <typename Res>
class Task : public BasicTask
{
public:
	Task(std::function<Res()> func)
		: task(func) {
	}

	void execute()
	{
		task();
	}

	std::packaged_task<Res()> task;
};
