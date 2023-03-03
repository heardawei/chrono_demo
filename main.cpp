#include <chrono>
#include <format>
#include <iostream>
#include <type_traits>

#include <cassert>

namespace chrono = std::chrono;

using std::cout;
using std::format;

// time_point、sys_days、sys_seconds、year_month_day、hh_mm_ss类型都可以通过标准格式字符串输入输出
// 格式字符串参考：https://zh.cppreference.com/w/cpp/chrono/parse

void date_time_to_string()
{
  auto time_point_us = chrono::system_clock::now();
  auto time_point_ms = chrono::floor<chrono::milliseconds>(time_point_us);
  auto time_point_s = chrono::floor<chrono::seconds>(time_point_us);
  auto time_point_day = chrono::floor<chrono::days>(time_point_us);

  auto seconds = chrono::sys_seconds(time_point_s);
  auto days = chrono::sys_days(time_point_day);

  chrono::year_month_day ymd(days);
  chrono::month_day_last mdl(ymd.month());
  chrono::year_month_day_last ymdl(ymd.year(), mdl);
  chrono::year_month_weekday ymwd(days);
  chrono::weekday_last wdl(ymwd.weekday());
  chrono::year_month_weekday_last ymwdl(ymd.year(), ymd.month(), wdl);

  auto hms_us = chrono::hh_mm_ss(time_point_us - time_point_day);
  auto hms_ms = chrono::hh_mm_ss(time_point_ms - time_point_day);
  auto hms = chrono::hh_mm_ss(time_point_s - time_point_day);

  auto c1 = std::is_same_v<decltype(days), decltype(time_point_day)>;
  auto c2 = std::is_same_v<decltype(seconds), decltype(time_point_s)>;
  assert(c1 && c2);

  cout << format("time_point_us : {}\n", time_point_us);
  cout << format("ymd + hms_us  : {} {}\n", ymd, hms_us);
  cout << format("time_point_ms : {:%F %T}\n", time_point_ms);
  cout << format("ymd + hms_ms  : {} {}\n", ymd, hms_ms);
  cout << format("time_point_s  : {:%F %T}\n", time_point_s);
  cout << format("ymd + hms     : {} {}\n", ymd, hms);
  cout << format("{0:%F} is: {0}\n", ymdl);
  cout << format("{0:%F} is: {0}\n", ymwd);
  cout << format("{0:%F} is: {0}\n", ymwdl);

  const std::chrono::zoned_time cur_time{std::chrono::current_zone(),
                                         std::chrono::system_clock::now()};
  auto local_time = cur_time.get_local_time();
  std::chrono::local_time<std::chrono::system_clock::duration> loc;
  std::cout << cur_time.get_local_time() << '\n';
}

void string_to_date_time()
{
  chrono::time_point<chrono::system_clock, chrono::microseconds> tp_us;
  std::istringstream("2000-01-01 23:59:59.123456") >>
      chrono::parse("%F %T", tp_us);
  std::cout << tp_us << std::endl;

  chrono::year_month_day ymd;
  std::istringstream("2000-01-01 23:59:59.123456") >> chrono::parse("%F", ymd);
  std::cout << ymd << std::endl;

  // chrono::hh_mm_ss<chrono::microseconds> hms;
  // std::istringstream("2000-01-01 23:59:59.123456") >>
  //     chrono::parse("%T", tp_us);
  // std::cout << hms << std::endl;
}

int main()
{
  date_time_to_string();
  std::cout << "-----------------------------------------------\n";
  string_to_date_time();
  return 0;
}