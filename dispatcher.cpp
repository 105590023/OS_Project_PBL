#include "dispatcher.h"
#include <iostream>

using namespace std;

queue<AbstractRequest*> Dispatcher::requests;
queue<Worker*> Dispatcher::workers;
mutex Dispatcher::requestsMutex;
mutex Dispatcher::workersMutex;
vetor<Worker*> Dispatcher::allWorkers;
vector<thread*> Dispatcher::threads;

/*-----INIT-----*/
bool Dispatcher::init(int workers)
{
	thread* t = 0;
	Worker* w = 0;
	for(int i = 0; i < workers; ++i)
	{
		w = new Worker;
		allWorkers.push_back(w);
		t = new thread(&Worker::run, w);
		thread.push_back(t);
	}
	return true;
}

/*-----STOP-----*/
bool Dispatcher::stop()
{
	for(int i = 0; i < allWorkers.size(); ++i)
	{
		allWorkers[i]->stop();
	}
	cout << "Stopped workers.\n";
	for(int j = 0; j < threads.size(); ++i)
	{
		threads[j]->join();
		cout << "Joined threads.\n";
	}
	
	return true;
}

/*-----ADD REQUEST-----*/
void Dispatcher::addRequest(AbstractRequest* request)
{
	workersMutex.lock();
	if(!workers.empty())
	{
		Worker* worker = workers.front();
		Worker->setRequest(request);
		condition_variable* cv;
		worker->getCondition(cv);
		cv->notify_one();
		workers.pop();
		workersMutex.unlock();
	}
	else
	{
		workersMutex.unlock();
		requestsMutex.lock();
		requests.push(request);
		requestsMutex.unlock();
	}
}
