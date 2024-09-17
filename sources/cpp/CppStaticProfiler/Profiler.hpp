#pragma once
// Author Chanwoo Lee (https://github.com/ChanWoo25)
#include <string>
#include <sstream>
#include <chrono>
#include <map>
#include <vector>
#include <mutex>
#include <cmath>
#include <iomanip>
// Open-sources
#include <gflags/gflags.h>
#include <glog/logging.h>
// User-defined
#include <NonCopyableClass.hpp>

namespace cwlee {

using HClock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double, std::milli>;

class Timer
{
public:
  void update(const double & curr_dt);

  inline void store(const double & dt);

  inline bool have_stored() const;

  inline double get_stored_value() const;

  std::string show() const;

private:
  int64_t n_tick_ = 0;
  double mean_ = 0.0;
  // Error between dt and mean is approximated for efficiency.
  double squared_err_sum_ = 0.0;
  double min_ = std::numeric_limits<double>::max();
  double max_ = std::numeric_limits<double>::min();
  double accumulated_dt_ = 0.0;

  inline double get_var_() const;
  inline double get_std_() const;
};

class Profiler : public NonCopyableClass
{
public:
  static void Start(const std::string & name);

  static Duration Stop(const std::string & name);

  static Duration Pause(const std::string & name);

  static void Restart(const std::string & name);

  static void StopAndDisplay(const std::string & name);

  static std::string DisplayAllTimeLogs();

private:
  std::map<std::string, HClock::time_point> start_map_;
  std::map<std::string, Timer> timer_map_;
  std::mutex mutex_;

  static Profiler & get_static_instance_();

  inline void start_(const std::string & name);

  inline void restart_(const std::string & name);

  Duration pause_(const std::string & name);

  Duration stop_(const std::string & name);

  std::string display_all_time_logs_();
};

} // namespace cwlee
