#include "test/task_test.h"
#include "common_head.h"

#include "base/task/single_thread_task_executor.h"
#include "base/task/task_executor.h"

using namespace base;

void TaskTest() {
  TEST(task);
  base::SingleThreadTaskExecutor main_task_executor_{base::MessagePumpType::DEFAULT};
  RunLoop loop;
  //RegisterTaskExecutor(1, base::GetTaskExecutorForCurrentThread());
  base::ThreadTaskRunnerHandle::Get()->PostTask(
      FROM_HERE, base::Bind([]() { LOG(INFO) << "current task"; }));
  //base::PostTask(FROM_HERE, {1},
                 //base::Bind([]() { LOG(INFO) << "post task"; }));
#ifndef OLD_VERSION
  base::GetTaskExecutorForCurrentThread()->PostDelayedTask(
	  FROM_HERE, {}, base::Bind(&RunLoop::QuitWhenIdle, base::Unretained(&loop)), base::TimeDelta::FromSecondsD(.1));
  loop.Run();
#endif
}
