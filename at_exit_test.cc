
#include "base/at_exit.h"
#include "base/logging.h"
#include "base/bind.h"
#include "base/callback.h"

using namespace base;

void f1() {
  AtExitManager am;
  base::Callback<void()> c = base::Bind([]() { LOG(INFO) << "f1"; });
  AtExitManager::RegisterTask(std::move(c));
  LOG(INFO) <<  "f1 done";
}

void callback1(void*) {
  LOG(INFO)<<"f2";
}

void AtExitTest() {
  f1();
  AtExitManager am;
  AtExitManager::RegisterCallback(callback1, nullptr);
  LOG(INFO) <<  "ATExitTest done";
}
