#include <vector>
#include <string>
#include <fstream>
#include <glog/logging.h>

#include <Eigen/Core>

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

int main(int argc, char* argv[])
{
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = true;

  LOG(INFO) << "This is Template cmake project!";
  cpp_version_preprocess();

  Eigen::MatrixXd A;
  A.setRandom(3, 3);

  Eigen::MatrixXd B, C;
  B = A.cwiseAbs();  // Means that Cefficient-wise Absolute operation |m|
  C = A.cwiseAbs2(); // Means that Cefficient-wise Absolute Square operation |m|^2 == m^2
  Eigen::IOFormat fmt(4, Eigen::DontAlignCols, ", ", ", ");
  LOG(INFO) << '\n' << A.format(fmt);
  LOG(INFO) << '\n' << B;
  LOG(INFO) << '\n' << C;
  // LOG(INFO) << "Coeff-wise min: " << A.cwiseMin(B);
  // LOG(INFO) << "Coeff-wise max: " << A.cwiseMax(C);

  return EXIT_SUCCESS;
}
