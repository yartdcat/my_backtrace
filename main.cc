#include <cstdio>
#include <thread>

#include "common_head.h"
#include "test/at_exit_test.h"
#include "test/bind_callback_test.h"
#include "test/task_test.h"
#include "test/pump_test.h"
#include "test/mojo_test.h"
#include "test/v8_test.h"
#include "test/gin_test.h"

int main(int argc, char* argv[]) {
  base::CommandLine::Init(argc, argv);
  logging::LoggingSettings settings;
  settings.logging_dest = logging::LOG_TO_STDERR;
  logging::InitLogging(settings);

  BindCallBackTest();
  TaskTest();
  //PumpTest();
  GinTest();
  V8Test();
  MojoTest();
  AtExitTest();
}
