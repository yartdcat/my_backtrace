
#include "base/at_exit.h"
#include "base/logging.h"
#include "base/bind.h"
#include "base/callback.h"

using namespace base;

void f1() {
  LOG(INFO) << "enter local function";
  AtExitManager am;
  //base::OnceCallback<void()> c =
      //base::Bind([]() { LOG(INFO) << "f1"; });
  //AtExitManager::RegisterTask(std::move(c));

}

void AtExitTest() {
  f1();
  AtExitManager am;
  AtExitManager::RegisterTask(base::BindOnce([]() { LOG(INFO) << "f2"; }));
}
