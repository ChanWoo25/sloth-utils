// Author Chanwoo Lee (https://github.com/ChanWoo25)
#include <Profiler.hpp>

namespace cwlee {

void Timer::update(const double & curr_dt)
{
  ++n_tick_;
  double dt = curr_dt + accumulated_dt_;
  accumulated_dt_ = 0.0;

  double prev_err = dt - mean_;
  mean_ += prev_err / n_tick_;
  double curr_err = dt - mean_;
  squared_err_sum_ += curr_err * prev_err;

  min_ = (dt < min_) ? dt : min_;
  max_ = (dt > max_) ? dt : max_;
}

std::string Timer::show() const
{
  std::stringstream ss;
  ss << std::to_string(mean_) << " \u00B1 "
      << std::to_string(get_std_())
      << " [" << std::to_string(min_) <<  "," << std::to_string(max_) <<  "][ms]";
  return ss.str();
}

inline void Timer::store(const double & dt) {
  accumulated_dt_ += dt;
}

inline bool Timer::have_stored() const {
  return accumulated_dt_ != 0.0;
}

inline double Timer::get_stored_value() const {
  return accumulated_dt_;
}

inline double Timer::get_var_() const
{
  if (n_tick_ < 2) { return 0.0; }
  else { return (squared_err_sum_ / (n_tick_ - 1)); }
}

inline double Timer::get_std_() const
{
  if (n_tick_ < 2) { return 0.0; }
  else { return std::sqrt(squared_err_sum_ / (n_tick_ - 1)); }
}

void Profiler::Start(const std::string & name) {
  Profiler::get_static_instance_().start_(name);
}

Duration Profiler::Stop(const std::string & name) {
  return Profiler::get_static_instance_().stop_(name);
}

Duration Profiler::Pause(const std::string & name) {
  return Profiler::get_static_instance_().pause_(name);
}

void Profiler::Restart(const std::string & name) {
  Profiler::get_static_instance_().restart_(name);
}

void Profiler::StopAndDisplay(const std::string & name)
{
  Duration t = Stop(name);
  LOG(INFO) << name << " >> " << t.count() << " ms";
}

std::string Profiler::DisplayAllTimeLogs() {
  return Profiler::get_static_instance_().display_all_time_logs_();
}

Profiler & Profiler::get_static_instance_()
{
  static Profiler instance;
  return instance;
}

inline void Profiler::start_(const std::string & name)
{
  std::lock_guard<std::mutex> lock(mutex_);
  start_map_[name] = HClock::now();
}

inline void Profiler::restart_(const std::string & name) {
  start_(name);
}

Duration Profiler::pause_(const std::string & name)
{
  auto chrono_end = HClock::now();
  std::lock_guard<std::mutex> lock(mutex_);

  auto stime_iter = start_map_.find(name);

  if (stime_iter == start_map_.end())
  {
    LOG(ERROR) << "Profiler must be start before pause or stop";
    return Duration();
  }

  auto timer_iter = timer_map_.find(name);

  if (timer_iter != timer_map_.end() && timer_iter->second.have_stored())
  {
    LOG(ERROR) << "Pause cannot be called twice before start";
    auto val = timer_iter->second.get_stored_value();
    timer_iter->second.update(0.0);
    return Duration(val);
  }
  else // Normal flow here
  {
    auto chrono_begin = stime_iter->second;
    start_map_.erase(stime_iter);
    auto duration = std::chrono::duration_cast<Duration>(chrono_end - chrono_begin);
    timer_map_[name].store(duration.count());
    return duration;
  }
};

Duration Profiler::stop_(const std::string & name)
{
  auto chrono_end = HClock::now();
  std::lock_guard<std::mutex> lock(mutex_);

  auto stime_iter = start_map_.find(name);
  if (stime_iter == start_map_.end())
  {
    LOG(ERROR) << "Profiler must be start before pause or stop";
    return Duration();
  }

  auto timer_iter = timer_map_.find(name);

  if (timer_iter != timer_map_.end() && timer_iter->second.have_stored())
  {
    LOG(ERROR) << "Stop cannot be called after pause!";
    auto val = timer_iter->second.get_stored_value();
    timer_iter->second.update(0.0);
    return Duration(val);
  }
  else // Normal flow here
  {
    auto chrono_begin = stime_iter->second;
    start_map_.erase(stime_iter);
    auto duration = std::chrono::duration_cast<Duration>(chrono_end - chrono_begin);
    timer_map_[name].update(duration.count());
    return duration;
  }
}

std::string Profiler::display_all_time_logs_()
{
  if (timer_map_.empty())
  {
    LOG(ERROR) << "There is no time logs";
    return std::string();
  }

  std::stringstream ss;
  ss << "\n****************************************************************\n";
  ss << " # Time Logs Summary";

  int max_name_len = 0;
  for(auto const & [name, _] : timer_map_)
  {
    auto name_len = static_cast<int>(name.length());
    max_name_len = (name_len > max_name_len) ? name_len : max_name_len;
  }

  std::string header;
  for (int i = 0; i < max_name_len; i++)
    header += ' ';

  ss << std::endl << "   " << header << " : avg time \u00B1      std [   min  ,   max  ][ms] ";
  for(auto const & [name, timer] : timer_map_)
  {
      ss << std::endl << ">> " << std::setw(max_name_len) << std::left
          << name << " : " << timer.show();
  }
  ss << "\n****************************************************************\n";
  return ss.str();
}

} // namespace cwlee
