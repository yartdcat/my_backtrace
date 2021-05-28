#include "common_head.h"

using namespace base;

struct T {
  void operator()() {
    LOG(INFO) << "OK";
  }
  int a  = 2;
};

void BindCallBackTest() {
  TEST(bind_callback);
  //repeating can use move, once can use copy
  std::string t = "tmp";
  auto cb1 = base::Bind([](std::string s){LOG(INFO) <<"ok";}, std::move(t));
  auto cb2 = base::BindOnce([](std::string s){LOG(INFO) <<"ok";}, t);
  base::BindOnce(cb1);
  //base::Bind(std::move(cb2));   repeating can't use OnceBack as Functor
  base::BindOnce(std::move(cb2));
  //bound args will be unwrap
  int a = 10;
  base::BindOnce([](const int & p){LOG(INFO) << "ok";}, std::cref(a));
  base::BindOnce([](const int* p){LOG(INFO) << "ok";}, base::Unretained(&a));
}
