#include <cstdio>
#include <thread>

#include "base/logging.h"
#include "base/threading/thread.h"
#include "base/run_loop.h"
#include "base/task/single_thread_task_executor.h"
#include "mojo/core/embedder/embedder.h"
#include "mojo/core/embedder/scoped_ipc_support.h"
#include "mojo/public/cpp/system/message_pipe.h"
#include "mojo/public/cpp/system/data_pipe.h"
#include "mojo/public/cpp/system/invitation.h"
#include "mojo/public/cpp/platform/platform_channel.h"


int main(int argc, char** argv) {
  base::CommandLine::Init(argc, argv);

  for(int i = 0;i<argc;i++){
    LOG(INFO) << argv[i];
  }
  mojo::core::Init();
  base::Thread ipc_thread("ipc!");
  ipc_thread.StartWithOptions(base::Thread::Options(base::MessagePumpType::IO, 0));
  mojo::core::ScopedIPCSupport ipc_support(ipc_thread.task_runner(), mojo::core::ScopedIPCSupport::ShutdownPolicy::CLEAN);

  mojo::IncomingInvitation invitation = mojo::IncomingInvitation::Accept(
      mojo::PlatformChannel::RecoverPassedEndpointFromCommandLine(*base::CommandLine::ForCurrentProcess()));
  mojo::ScopedMessagePipeHandle pipe = invitation.ExtractMessagePipe("arbitrary pipe name");

  std::vector<uint8_t> bytes;
  mojo::ReadMessageRaw(pipe.get(), &bytes, nullptr, MOJO_READ_MESSAGE_FLAG_NONE);
  std::string s(bytes.begin(), bytes.end());
  LOG(INFO) << s;

  base::SingleThreadTaskExecutor executor;
  base::RunLoop run_loop;
  run_loop.Run();
}
