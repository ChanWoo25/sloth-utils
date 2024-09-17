#include <iostream>
#include <glog/logging.h>
#include <filesystem>

static int count = 0;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);

  // auto log_dir = fs::current_path() / "log";
  // if (!fs::exists(log_dir)) {
  //   fs::create_directory(log_dir);
  // }
  // FLAGS_log_dir = log_dir;
  // FLAGS_v = 1;

  FLAGS_logtostderr = true;
  FLAGS_minloglevel = google::INFO;

  static int count = 0;

  LOG(INFO) << "Found " << ++count << " main";
  LOG(INFO) << "INFO 레벨의 로그";
  LOG(WARNING) << "WARNING 레벨의 로그";

  // default 설정 시, ERROR 레벨 이상부터 stderr 로 출력된다.
  LOG(ERROR) << "ERROR 레벨의 로그";

  // FATAL의 경우, Stack trace를 출력하고 프로그램을 종료시킨다.
  LOG(FATAL) << "FATAL 레벨의 로그";
}
