#pragma once

#include <string>

#include "base/at_exit.h"
#include "base/logging.h"
#include "base/bind.h"
#include "base/callback.h"
#include "base/threading/thread.h"
#include "base/threading/thread_task_runner_handle.h"
#include "base/task/post_task.h"
#include "base/time/time.h"
#include "base/command_line.h"

//indicate using chromium 7x version, or chromium 9x
//#define OLD_VERSION

struct TestCase {
  TestCase(std::string name) {
    printf("============================= %s%s===========================\n", name.data(), std::string(20-name.size(),'=').data());
  }
};

#define TEST(name) TestCase __case{#name};
