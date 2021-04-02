/***********************
  File Name   :   ThreadPool.h
  Description :   declare a singleton class that assign threads to different tasks
********************/
#pragma once
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <condition_variable>
#include <future>

#include "WorkQueue.h"
#include "Task.h"

class ThreadPool
{
public:
	~ThreadPool();

	// Singleton Methods
	static ThreadPool& GetInstance();
	static void DestroyInstance();

	template <typename Fun, typename ... Args>
	std::future<std::result_of_t<Fun(Args...)>> Submit(Fun func, Args... args);

	void DoWork();
	void Start(unsigned int _size);
	void Stop();
	std::atomic_int& getItemsProcessed();

private:
	// Make the threadpool a singleton
	ThreadPool();
	ThreadPool(unsigned int _size);

	// The ThreadPool is non-copyable.
	ThreadPool(const ThreadPool& _kr) = delete;
	ThreadPool& operator= (const ThreadPool& _kr) = delete;

protected:
	static ThreadPool* threadPool;

private:
	// An atomic boolean variable to indicate when all the work items in the queue have been finished.
	std::atomic_bool isfinished;

	// A WorkQueue of tasks which are packaged tasks
	std::unique_ptr<WorkQueue<std::unique_ptr<BasicTask>> > workQueue;

	// Create a pool of worker threads
	std::vector<std::thread> workerThreads;

	// A variable to hold the number of threads we want
	unsigned int numberOfThreads;

	// An atomic variable to keep track of how many items have been processed.
	std::atomic_int itemsProcessed{ 0 };
};

/***********************
 Description :   Push a task to the work queue
********************/
template <typename Fun, typename ... Args>
std::future<std::result_of_t<Fun(Args...)>>
ThreadPool::Submit(Fun func, Args... args)
{
	using ResultT = std::result_of_t<Fun(Args...)>;
	std::unique_ptr<Task<ResultT>> 
		task(std::make_unique<Task<ResultT>>(std::bind(func, args...)));
	std::future<ResultT> f = task->task.get_future();
	workQueue->push(std::move(task));
	return f;
}
#endif
