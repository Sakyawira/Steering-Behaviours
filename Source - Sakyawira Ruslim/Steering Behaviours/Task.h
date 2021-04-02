/***********************
  File Name   :   Task.h
  Description :   A class that store a callback function to be executed in different threads
  Author      :   Sakyawira Nanda Ruslim
  Mail        :   Sakyawira@gmail.com
********************/
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