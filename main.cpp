#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <syncstream>
#include <string>

/*
№.20
Усі обчислення: A1,A2,A3,A4,B1,B2,C
“Повільні” обчислення:A1,A3
Залежності: B1(A1,A2), C(B1,B2)
*/

void slow(const std::string& name)
{
	std::this_thread::sleep_for(std::chrono::seconds(7));
	std::osyncstream(std::cout) << name << std::endl;
}

void quick(const std::string& name)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::osyncstream(std::cout) << name << std::endl;
}

void thread1_work(std::future<void> f1, std::future<void> f2)
{
	slow("A1");
	f1.wait();
	quick("B1");
	f2.wait();
	quick("C");
}


void work()
{
	std::promise<void> p1;
	std::promise<void> p2;
	auto f1 = p1.get_future();
	auto  f2 = p2.get_future();

	auto t1 = std::chrono::steady_clock::now();

	auto th1 = std::async(std::launch::async, thread1_work, move(f1), move(f2));
	auto th2 = std::async(std::launch::async, slow, "A3");

	quick("A2");
	p1.set_value();
	quick("B2");
	p2.set_value();
	quick("A4");

	th1.wait();
	th2.wait();

	auto t2 = std::chrono::steady_clock::now();

	double time = std::chrono::duration<double>(t2 - t1).count();

	std::osyncstream(std::cout) << "Taken time: " << time << std::endl;
	std::osyncstream(std::cout) << "Work is done!";
}


int main()
{
	work();
}