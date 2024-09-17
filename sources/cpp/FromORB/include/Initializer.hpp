#pragma once

#include <vector>
#include <iostream>

#include <opencv2/core/core.hpp>

#include "./effolkronium_random.hpp"
using Random = effolkronium::random_static;

/**
 * @brief 이벤트: 무조건 match가 생긴다. ORB에서는
 *
 */

namespace cvlab
{

class Initializer
{
private:
  std::vector<cv::KeyPoint>        ref_keypoints_; // length N
  std::vector<cv::KeyPoint>        cur_keypoints_; // length M
  std::vector<std::pair<int, int>> cur2ref_matches_; // length M & each elements range: [0, N-1]
  std::vector<std::vector<int>>    ransac_8point_sets_; // randomly selected 8 pairs in `cur2ref_matches_`

  // Calibration Matrix
  cv::Mat K_;
  cv::Mat dist_coeff_;

  double ref_t_sec_;
  double cur_t_sec_;

  int ransac_max_iter_=10;

public:
  Initializer(const double & t,
              const std::vector<cv::KeyPoint> & ref_keypoints);
  ~Initializer();

  void try_with(const double & t,
                const std::vector<cv::KeyPoint> & cur_keypoints,
                const std::vector<std::pair<int, int>> & cur2ref_matches);

  void reset();
  void test();
};

Initializer::Initializer(const double & t,
                         const std::vector<cv::KeyPoint> & ref_keypoints)
{
  ref_keypoints_ = ref_keypoints;
  ref_t_sec_ = t;
}

Initializer::~Initializer()
{
}

void Initializer::try_with(const double & t,
                           const std::vector<cv::KeyPoint> & cur_keypoints,
                           const std::vector<std::pair<int, int>> & cur2ref_matches)
{
  this->reset(); // clean before initialization.

  cur_keypoints_ = cur_keypoints;
  cur2ref_matches_ = cur2ref_matches;

  const int n_matches = cur2ref_matches.size();

  std::vector<int> indices;
  indices.reserve(n_matches);
  for (int i = 0; i < n_matches; i++) {
    indices.push_back(i);
  }

  ransac_8point_sets_.reserve(8 * n_matches);
  for (int i = 0; i < ransac_max_iter_; i++)
  {
    auto available_indices = indices;
    std::vector<int> v8points;

    for (int j = 0; j < 8; j++)
    {
      int idx = Random::get<int>(0, available_indices.size()-1);
      v8points.push_back(available_indices[idx]);
      available_indices[idx] = available_indices.back();
      available_indices.pop_back();
    }

    ransac_8point_sets_.emplace_back(v8points);

    std::cout <<  i << "-th shuffle: ";
    for (auto & e : v8points)
      std::cout << " " << e << ", ";
    std::cout << std::endl;
  }
}

void Initializer::reset()
{
  cur_keypoints_.clear();
  cur2ref_matches_.clear();
  ransac_8point_sets_.clear();
}


}



// namespace ORB_SLAM2
// {

// // THIS IS THE INITIALIZER FOR MONOCULAR SLAM. NOT USED IN THE STEREO OR RGBD CASE.
// class Initializer
// {
//     typedef pair<int,int> Match;

// public:

//     // Fix the reference frame
//     Initializer(const Frame &ReferenceFrame, float sigma = 1.0, int iterations = 200);

//     // Computes in parallel a fundamental matrix and a homography
//     // Selects a model and tries to recover the motion and the structure from motion
//     bool Initialize(const Frame &CurrentFrame, const vector<int> &vMatches12,
//                     cv::Mat &R21, cv::Mat &t21, vector<cv::Point3f> &vP3D, vector<bool> &vbTriangulated);


// private:

//     void FindHomography(vector<bool> &vbMatchesInliers, float &score, cv::Mat &H21);
//     void FindFundamental(vector<bool> &vbInliers, float &score, cv::Mat &F21);

//     cv::Mat ComputeH21(const vector<cv::Point2f> &vP1, const vector<cv::Point2f> &vP2);
//     cv::Mat ComputeF21(const vector<cv::Point2f> &vP1, const vector<cv::Point2f> &vP2);

//     float CheckHomography(const cv::Mat &H21, const cv::Mat &H12, vector<bool> &vbMatchesInliers, float sigma);

//     float CheckFundamental(const cv::Mat &F21, vector<bool> &vbMatchesInliers, float sigma);

//     bool ReconstructF(vector<bool> &vbMatchesInliers, cv::Mat &F21, cv::Mat &K,
//                       cv::Mat &R21, cv::Mat &t21, vector<cv::Point3f> &vP3D, vector<bool> &vbTriangulated, float minParallax, int minTriangulated);

//     bool ReconstructH(vector<bool> &vbMatchesInliers, cv::Mat &H21, cv::Mat &K,
//                       cv::Mat &R21, cv::Mat &t21, vector<cv::Point3f> &vP3D, vector<bool> &vbTriangulated, float minParallax, int minTriangulated);

//     void Triangulate(const cv::KeyPoint &kp1, const cv::KeyPoint &kp2, const cv::Mat &P1, const cv::Mat &P2, cv::Mat &x3D);

//     void Normalize(const vector<cv::KeyPoint> &vKeys, vector<cv::Point2f> &vNormalizedPoints, cv::Mat &T);

//     int CheckRT(const cv::Mat &R, const cv::Mat &t, const vector<cv::KeyPoint> &vKeys1, const vector<cv::KeyPoint> &vKeys2,
//                        const vector<Match> &vMatches12, vector<bool> &vbInliers,
//                        const cv::Mat &K, vector<cv::Point3f> &vP3D, float th2, vector<bool> &vbGood, float &parallax);

//     void DecomposeE(const cv::Mat &E, cv::Mat &R1, cv::Mat &R2, cv::Mat &t);
// };

// } //namespace ORB_SLAM
