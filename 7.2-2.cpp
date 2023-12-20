// 7.2-2.cpp 


#include"Header.h"
#include<thread>
#include<mutex>


using namespace std::chrono_literals;
consol_parameter cp;

std::mutex m;

void process(int j) {
	j++;
	Timer t("");

	std::unique_lock l{ m };
	cp.SetPosition(2, j);
	std::cout << std::this_thread::get_id() << std::endl;
	l.unlock();

	for (int i = 0; i < 10; i++)
	{
		l.lock();
		cp.SetPosition(15 + i, j);
		std::cout << "_";
		std::this_thread::sleep_for(100ms);

		l.unlock();

	}

	l.lock();
	cp.SetPosition(25, j);
	t.print();// 
	l.unlock();
}

int main()
{
	std::cout << "thread id";

	cp.SetPosition(17, 0);
	std::cout << "process";

	cp.SetPosition(35, 0);
	std::cout << "time";

	int s = 4;
	std::thread* t = new std::thread[s];
	for (int i = 0; i < s; i++)
	{
		t[i] = std::thread(process, i);
	}
	for (int i = 0; i < s; i++)
	{
		t[i].join();
	}
	cp.SetPosition(0, 6);

	return 0;
}
