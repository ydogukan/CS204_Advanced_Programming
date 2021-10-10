#include <iostream>
#include <thread>
#include <random>
#include <time.h>
#include <mutex>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "ydogukan_Yildirim_Dogukan_hw7_HW7DynIntQueue.h"

using namespace std;

int total_box_count, filledBoxCount = 0, packagedBoxCount = 0; // global variables for threads
HW7DynIntQueue fillingQueue = HW7DynIntQueue();
HW7DynIntQueue packagingQueue = HW7DynIntQueue();
mutex fillingMutex, packagingMutex, coutMutex; // three different mutexes for different operations

int random_range(const int& min, const int& max) { // returns a random integer within the given range
	static mt19937 generator(time(0));
	uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

void producer(int min_production, int max_production) {
	for (int i = 0; i < total_box_count; i++) {
		this_thread::sleep_for(chrono::seconds(random_range(min_production, max_production))); // the time it takes to produce a box

		fillingMutex.lock(); // Locking the fillingMutex while enqueuing the fillingQueue, then unlocking it after the operation
		fillingQueue.enqueue(i + 1);
		int size = fillingQueue.getCurrentSize(); // Getting the size here so that there are no inconsistencies
		fillingMutex.unlock();

		time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // getting the current time, then putting it into a different structure to display it later
		struct tm* ptm = new struct tm;
		localtime_s(ptm, &tt);

		coutMutex.lock(); // Locking the coutMutex when it's time to print something so that that there are no issues trying to get a clear output
		cout << "Producer has enqueued a new box " << i + 1 << " to filling queue (filling queue size is " << size << "): " << put_time(ptm, "%X") << endl;
		coutMutex.unlock();

		delete ptm; // deleting to prevent memory leak
	}
}

void fillerWorker(int fillerID, int min_filling_time, int max_filling_time) {
	int boxID;
	while (filledBoxCount < total_box_count) {
		fillingMutex.lock(); 

		if (!fillingQueue.isEmpty()) {
			fillingQueue.dequeue(boxID);
			int filling_size = fillingQueue.getCurrentSize(); // Getting the size here so that there are no inconsistencies
			fillingMutex.unlock();
			filledBoxCount++;

			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // getting the current time, then putting it into a different structure to display it later
			struct tm* ptm = new struct tm;
			localtime_s(ptm, &tt);

			coutMutex.lock(); // Locking the coutMutex when it's time to print something so that that there are no issues trying to get a clear output
			cout << "Filler " << fillerID << " started filling the box " << boxID << " (filling queue size is " << filling_size << "): " << put_time(ptm, "%X") << endl;
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(min_filling_time, max_filling_time))); // the time it takes to fill a box

			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // getting the current time, then putting it into a different structure to display it later
			localtime_s(ptm, &tt);

			coutMutex.lock(); // Locking the coutMutex when it's time to print something so that that there are no issues trying to get a clear output
			cout << "Filler " << fillerID << " finished filling the box " << boxID << ": " << put_time(ptm, "%X") << endl;
			coutMutex.unlock();

			packagingMutex.lock(); // Locking the packagingMutex while enqueuing the packagingQueue, then unlocking it after the operation
			packagingQueue.enqueue(boxID);
			int packaging_size = packagingQueue.getCurrentSize(); // Getting the size here so that there are no inconsistencies
			packagingMutex.unlock();

			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // getting the current time, then putting it into a different structure to display it later
			localtime_s(ptm, &tt);

			coutMutex.lock(); // Locking the coutMutex when it's time to print something so that that there are no issues trying to get a clear output
			cout << "Filler " << fillerID << " put box " << boxID << " into packaging queue (packaging queue size is " << packaging_size << "): " << put_time(ptm, "%X") << endl;
			coutMutex.unlock();

			delete ptm; // deleting to prevent memory leak
		}
		
		else {
			fillingMutex.unlock();
		}
	}
}

void packagerWorker(int packagerID, int min_packaging_time, int max_packaging_time) {
	int boxID;
	while (packagedBoxCount < total_box_count) {
		packagingMutex.lock();

		if (!packagingQueue.isEmpty()) {
			packagingQueue.dequeue(boxID);
			int size = packagingQueue.getCurrentSize(); // Getting the size here so that there are no inconsistencies
			packagingMutex.unlock();
			packagedBoxCount++;

			time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // getting the current time, then putting it into a different structure to display it later
			struct tm* ptm = new struct tm;
			localtime_s(ptm, &tt);

			coutMutex.lock(); // Locking the coutMutex when it's time to print something so that that there are no issues trying to get a clear output
			cout << "Packager " << packagerID << " started packaging the box " << boxID << " (packaging queue size is " << size << "): " << put_time(ptm, "%X") << endl;
			coutMutex.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(min_packaging_time, max_packaging_time))); // the time it takes to package a box

			tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // getting the current time, then putting it into a different structure to display it later
			localtime_s(ptm, &tt);

			coutMutex.lock(); // Locking the coutMutex when it's time to print something so that that there are no issues trying to get a clear output
			cout << "Packager " << packagerID << " finished packaging the box " << boxID << ": " << put_time(ptm, "%X") << endl;
			coutMutex.unlock();

			delete ptm; // deleting to prevent memory leak
		}

		else {
			packagingMutex.unlock();
		}
	}
}

int main() {
	int min_production, max_production, min_filling_time, max_filling_time, min_packaging_time, max_packaging_time;

	cout << "Please enter the total number of items: ";
	cin >> total_box_count;

	cout << "Please enter the min-max waiting time range of producer:" << endl;
	cout << "Min: ";
	cin >> min_production;
	cout << "Max: ";
	cin >> max_production;

	cout << "Please enter the min-max waiting time range of filler workers:" << endl;
	cout << "Min: ";
	cin >> min_filling_time;
	cout << "Max: ";
	cin >> max_filling_time;

	cout << "Please enter the min-max waiting time range of packager workers:" << endl;
	cout << "Min: ";
	cin >> min_packaging_time;
	cout << "Max: ";
	cin >> max_packaging_time;

	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // getting the current time, then putting it into a different structure to display it later
	struct tm* ptm = new struct tm;
	localtime_s(ptm, &tt);

	cout << "Simulation starts " << put_time(ptm, "%X") << endl;

	thread producerThread(producer, min_production, max_production);
	thread fillerWorker1Thread(fillerWorker, 1, min_filling_time, max_filling_time);
	thread fillerWorker2Thread(fillerWorker, 2, min_filling_time, max_filling_time);
	thread packagerWorker1Thread(packagerWorker, 1, min_packaging_time, max_packaging_time);
	thread packagerWorker2Thread(packagerWorker, 2, min_packaging_time, max_packaging_time);
	producerThread.join();
	fillerWorker1Thread.join();
	fillerWorker2Thread.join();
	packagerWorker1Thread.join();
	packagerWorker2Thread.join();

	tt = chrono::system_clock::to_time_t(chrono::system_clock::now()); // getting the current time, then putting it into a different structure to display it later
	localtime_s(ptm, &tt);

	cout << "End of the simulation ends: " << put_time(ptm, "%X") << endl;
	delete ptm; // deleting to prevent memory leak

	return 0;
}