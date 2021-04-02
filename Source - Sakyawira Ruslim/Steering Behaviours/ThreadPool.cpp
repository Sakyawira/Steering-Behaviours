/***********************
  File Name   :   ThreadPool.cpp
  Description :   define a singleton class that assign threads to different tasks
********************/
#include "ThreadPool.h"

// Static Variables
ThreadPool* ThreadPool::threadPool = nullptr;

/***********************
 Description :   Creates as many threads as exists in the user's hardware
********************/
ThreadPool::ThreadPool()
	:workQueue(new WorkQueue<std::unique_ptr<BasicTask>>())
{
	isfinished = false;   // Set out finished to false to begin
	numberOfThreads = std::thread::hardware_concurrency();
}

/***********************
 Description :   Creates as many threads as the passed in parameter
********************/
ThreadPool::ThreadPool(unsigned int _size)
{
	isfinished = false;   // Set out finished to false to begin
	// Create a pool of threads equal to specified size
	numberOfThreads = _size;
}

/***********************
 Description :   Join all threads
********************/
ThreadPool::~ThreadPool()
{
	isfinished = true;
	if (workerThreads.size() != 0)
	{
		for (unsigned int i = 0; i < numberOfThreads; i++)
		{

			workerThreads[i].join();
		}
	}
}

/***********************
 Description :   Return the static instance / create a new one if none exists
********************/
ThreadPool& ThreadPool::GetInstance()
{
	if (threadPool == nullptr)
	{
		threadPool = new ThreadPool();
	}
	return (*threadPool);
}

/***********************
 Description :   Delete the Threadpool instance
********************/
void ThreadPool::DestroyInstance()
{
	delete threadPool;
	threadPool = 0;
}

/***********************
 Description :   Starts the threads to do work, reassign the number of threads
********************/
void ThreadPool::Start(unsigned int _size)
{
	numberOfThreads = _size;
	for (unsigned int i = 0; i < numberOfThreads; i++)
	{
		workerThreads.push_back(std::thread(&ThreadPool::DoWork, this));
	}
}

/***********************
 Description :   Stops the threads from doing work
********************/
void ThreadPool::Stop()
{
	isfinished = true;
}

/***********************
 Description :   Ask a thread to take a task off the work queue and process it, loop it until we ask the thread to stop
********************/
void ThreadPool::DoWork()
{
	// Entry point of  a thread.
	// std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << "starting........" << std::endl;
	while (!isfinished)
	{
		std::unique_ptr<BasicTask> WorkItem;
		// If there is an item in the queue to be processed; just take it off the q and process it
		if (workQueue->blocking_pop(WorkItem, 5000))
		{
			// std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << " is working on item in the work queue" << std::endl;
			WorkItem->execute();
			// std::cout << std::endl << "Thread with id " << std::this_thread::get_id() << " finished processing item " << std::endl;
			// Sleep to simulate work being done
			// std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1001));
			itemsProcessed++;
		}
		else
		{
			continue;
		}
	}
}

/***********************
 Description :   Gets the amount of items have been processed
********************/
std::atomic_int& ThreadPool::getItemsProcessed()
{
	return itemsProcessed;
}