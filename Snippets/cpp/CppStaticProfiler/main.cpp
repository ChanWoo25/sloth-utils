#include <vector>
#include <string>
#include <fstream>
#include <glog/logging.h>
#include <Profiler.hpp>

void howToUseProfiler()
{
  cwlee::Profiler::Start("1. iii-loop");
  for (int i = 0; i < 10; i++)
  {
    cwlee::Profiler::Start("2. j-loop");
    long sum = 0;
    for (int j = 0; j < 10000; j++) {
      sum += (i + 1) * j;
    }
    LOG(INFO) << sum;
    cwlee::Profiler::StopAndDisplay("2. j-loop");
  }
  cwlee::Profiler::StopAndDisplay("1. iii-loop");
  LOG(INFO) << '\n' << cwlee::Profiler::DisplayAllTimeLogs();
}

int main(int argc, char* argv[])
{
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = true;

  howToUseProfiler();

  return EXIT_SUCCESS;
}
