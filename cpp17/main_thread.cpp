#include <iostream>
#include <thread>
#include <glog/logging.h>
#include <mutex>

std::mutex mtx;

struct MInt
{
  std::mutex mtx;
  int num = 0;
};

void plus1(MInt & mi)
{
  mi.mtx.lock();
  mi.num++;
  mi.mtx.unlock();
}

void printThreadID()
{
  mtx.lock();
  // critical section
  std::cout << std::this_thread::get_id() << std::endl;
  mtx.unlock();
}

int main(int argc, char * argv[])
{
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_alsologtostderr = true;
  FLAGS_minloglevel = google::INFO;

  MInt mi;
  std::thread t1(plus1, std::ref(mi));
  std::thread t2(plus1, std::ref(mi));
  LOG(INFO) << "Num: " << mi.num;

  t1.join();
  t2.join();

  return EXIT_SUCCESS;
}
