#include "test/mojo_test.h"
#include "common_head.h"

#include "base/task/single_thread_task_executor.h"
#include "mojo/core/embedder/embedder.h"
#include "mojo/core/embedder/scoped_ipc_support.h"
#include "mojo/public/cpp/system/message_pipe.h"
#include "mojo/public/cpp/system/data_pipe.h"
#include "mojo/public/cpp/system/invitation.h"
#include "mojo/public/cpp/platform/platform_channel.h"

using namespace base;

void MojoTest() {
  TEST(mojo);
  mojo::core::Init();

  //test message pipe
  {
    mojo::MessagePipe pipe;
    mojo::ScopedMessagePipeHandle client = std::move(pipe.handle0);
    mojo::ScopedMessagePipeHandle server = std::move(pipe.handle1);
    mojo::WriteMessageRaw(client.get(), "hello", 5, nullptr, 0, MOJO_WRITE_MESSAGE_FLAG_NONE);

    std::vector<uint8_t> bytes;
    mojo::ReadMessageRaw(server.get(), &bytes, nullptr, MOJO_READ_MESSAGE_FLAG_NONE);
    std::string s(bytes.begin(), bytes.end());
    LOG(INFO) << s;
  }

  //test data pipe
  {
    mojo::ScopedDataPipeProducerHandle producer;
    mojo::ScopedDataPipeConsumerHandle consumer;
    mojo::CreateDataPipe(nullptr, producer, consumer);
    uint32_t num_bytes1 = 7;
    producer->WriteData("hihihi", &num_bytes1, MOJO_WRITE_DATA_FLAG_NONE);

    char buffer[64];
    uint32_t num_bytes = 64;
    consumer->ReadData(buffer, &num_bytes, MOJO_READ_DATA_FLAG_NONE);
    LOG(INFO) << buffer;
  }

  //test invitation
  {
    base::Thread ipc_thread("ipc!");
    ipc_thread.StartWithOptions(base::Thread::Options(base::MessagePumpType::IO, 0));
    mojo::core::ScopedIPCSupport ipc_support(ipc_thread.task_runner(), mojo::core::ScopedIPCSupport::ShutdownPolicy::CLEAN);

    mojo::PlatformChannel channel;
    mojo::OutgoingInvitation invitation;
    mojo::ScopedMessagePipeHandle pipe = invitation.AttachMessagePipe("arbitrary pipe name");
    base::LaunchOptions options;
    const char* argv[] = {"/home/SERAPHIC/liuy/v6_repo/v6.0/src/out/test/sub"};
    base::CommandLine command_line(1, argv);
    channel.PrepareToPassRemoteEndpoint(&options, &command_line);
    base::Process child_process = base::LaunchProcess(command_line, options);
    channel.RemoteProcessLaunchAttempted();
    mojo::OutgoingInvitation::Send(std::move(invitation), child_process.Handle(), channel.TakeLocalEndpoint());

    const char* msg = "this is server";
    mojo::WriteMessageRaw(pipe.get(), msg, strlen(msg), nullptr, 0, MOJO_WRITE_MESSAGE_FLAG_NONE);

    base::SingleThreadTaskExecutor executor;
    base::RunLoop run_loop;
    run_loop.Run();
  }
}
