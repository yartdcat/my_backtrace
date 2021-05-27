#include <stdio.h>
#include <unistd.h>
#include <thread>

#include "common_head.h"
#include "test/at_exit_test.h"
#include "test/bind_callback_test.h"


int main(int argc, char* argv[]) {
  BindCallBackTest();
  AtExitTest();
}
