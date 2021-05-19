#include <stdio.h>
#include <unistd.h>

#include "base/at_exit.h"
#include "test/at_exit_test.h"

int main(int argc, char* argv[]) {

  AtExitTest();
}
