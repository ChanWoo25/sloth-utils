#include <vector>
#include <string>
#include <fstream>
#include <glog/logging.h>
#include <iostream>

#include <Eigen/Core>

using namespace std;

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

void studyMemory()
{
  Eigen::Matrix<double, 3, 3> d33;
  d33.setConstant(1.5);
  cout << "This matrix is stored in stack memory: " << d33.data() << endl;
  cout << d33 << endl;

  Eigen::Matrix<double, Eigen::Dynamic, 3> dX3;
  dX3.resize(4, 3);
  dX3.setOnes();
  cout << "This matrix is stored in Heap memory: " << dX3.data() << endl;
  cout << dX3 << endl;

  Eigen::Matrix<double, 3, Eigen::Dynamic> d3X;
  d3X.resize(3, 4);
  d3X.setZero();
  cout << "This matrix is stored in Heap memory: " << d3X.data() << endl;
  cout << d3X << endl;

  Eigen::Vector4d v4; v4.setLinSpaced(1, 6);
  Eigen::Vector2f v2(1.0, 2.0);
  Eigen::Vector3i v3(1, 2, 3);
  Eigen::Array4d a4(1.0, 2.0, 3.0, 4.0);
  Eigen::VectorXd v5(5);
  cout << v4.transpose() << ", " << v4.data() << endl;
  cout << v2.transpose() << ", " << v2.data() << endl;
  cout << v3.transpose() << ", " << v3.data() << endl;
  cout << a4.transpose() << ", " << a4.data() << endl;
  cout << v5.transpose() << ", " << v5.data() << endl; // 쓰레기값

  Eigen::VectorXd v6 = Eigen::VectorXd::Zero(5);
  Eigen::ArrayXd a7 = Eigen::ArrayXd::Random(7);
  cout << v6.transpose() << ", " << v6.data() << endl;
  cout << a7.transpose() << ", " << a7.data() << endl;
}

void studyInit()
{
  Eigen::MatrixXd m(3, 3);
  m << (Eigen::Matrix2d() << 1, 2, 3, 4).finished(),
       Eigen::MatrixXd::Zero(2, 1),
       Eigen::MatrixXd::Ones(1, 2),
       9;
  cout << m << endl;

  
}

int main(int argc, char* argv[])
{
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_logtostderr = true;

  // studyMemory();
  studyInit();

  // Eigen::MatrixXd A;
  // A.setRandom(3, 3);

  // Eigen::MatrixXd B, C;
  // B = A.cwiseAbs();  // Means that Cefficient-wise Absolute operation |m|
  // C = A.cwiseAbs2(); // Means that Cefficient-wise Absolute Square operation |m|^2 == m^2
  // Eigen::IOFormat fmt(4, Eigen::DontAlignCols, ", ", ", ");
  // LOG(INFO) << '\n' << A.format(fmt);
  // LOG(INFO) << '\n' << B;
  // LOG(INFO) << '\n' << C;
  // LOG(INFO) << "Coeff-wise min: " << A.cwiseMin(B);
  // LOG(INFO) << "Coeff-wise max: " << A.cwiseMax(C);

  return EXIT_SUCCESS;
}
