#include <vector>
#include <string>
#include <fstream>
#include <glog/logging.h>

#include <opencv2/core/core.hpp>
#include <Initializer.hpp>

// I think your code should works at least c++14. (cw, 2022-12-31)
void cpp_version_preprocess()
{
#if __cplusplus >= 202002L
  LOG(INFO) << "~ c++20 supported!";
#elif __cplusplus >= 201703L
  LOG(INFO) << "~ c++17 supported!";
#elif __cplusplus >= 201402L
  LOG(INFO) << "~ c++14 supported!";
#elif __cplusplus >= 201103L
  LOG(INFO) << "~ c++11 supported!";
#elif __cplusplus >= 199711L
  LOG(INFO) << "~ c++98 supported!";
#else
  LOG(ERROR) << "~ pre-c++98 supported! \n How old your compiler is....??";
#endif
  return;
}


void test()
{
  const int N = 20;
  const int M = 16;
  std::vector<cv::KeyPoint> ref_keypoints;
  std::vector<cv::KeyPoint> cur_keypoints;
  std::vector<std::pair<int, int>> cur2ref_matches;

  for(int i = 0; i < N; i++) {
    ref_keypoints.emplace_back( cv::KeyPoint(Random::get<int>(0, 240-1),
                                             Random::get<int>(0, 180-1),
                                             1.0) );
  }

  for(int i = 0; i < M; i++) {
    ref_keypoints.emplace_back( cv::KeyPoint(Random::get<int>(0, 240-1),
                                             Random::get<int>(0, 180-1),
                                             1.0) );
  }

  for(int i = 0; i < M; i++) {
    cur2ref_matches.emplace_back(std::pair<int, int>(i, i+1));
  }

  cvlab::Initializer initializer(0.0, ref_keypoints);
  initializer.try_with(1.0, cur_keypoints, cur2ref_matches);
}

int main(int argc, char* argv[])
{
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = true;

  LOG(INFO) << "This is Template cmake project!";
  cpp_version_preprocess();

  test();

  return EXIT_SUCCESS;
}
