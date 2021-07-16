#include "test/gin_test.h"
#include "common_head.h"
#include "base/task/single_thread_task_executor.h"
#include "base/i18n/icu_util.h"
#include "gin/v8_initializer.h"
#include "gin/array_buffer.h"
#include "gin/public/isolate_holder.h"

using namespace base;
using namespace v8;

void GinTest() {
  base::i18n::InitializeICU();
  base::SingleThreadTaskExecutor main_thread_task_executor;
  gin::IsolateHolder::Initialize(gin::IsolateHolder::kStrictMode,
                                 gin::ArrayBufferAllocator::SharedInstance());
  gin::IsolateHolder instance_(
      base::ThreadTaskRunnerHandle::Get(),
      gin::IsolateHolder::IsolateType::kBlinkWorkerThread);

  v8::Persistent<v8::Context> context_;

  instance_.isolate()->Enter();
  HandleScope handle_scope(instance_.isolate());
  context_.Reset(instance_.isolate(), Context::New(instance_.isolate()));
  Local<Context>::New(instance_.isolate(), context_)->Enter();
  base::RunLoop().RunUntilIdle();

}
