#include "test/pump_test.h"
#include "common_head.h"

#include "base/message_loop/message_pump.h"

using namespace base;

class PumpDelegate : public MessagePump::Delegate {
  public:
    ~PumpDelegate() override {
    }

    NextWorkInfo DoWork() override{
      LOG(INFO) << "do work";
      //run this function per second
      return {TimeTicks::Now()+TimeDelta::FromSeconds(1),TimeTicks::Now()};
    }
    bool DoIdleWork() override {
      LOG(INFO) << "do idle";
      //true will execute continuously infinite, false will wait
      return false;
    }
    void BeforeWait() override {

    }

   private:
    void OnBeginNativeWork() override {

    }
    void OnEndNativeWork() override{

    }
};

void PumpTest() {
  TEST(pump);
  auto pump = MessagePump::Create(MessagePumpType::DEFAULT);
  PumpDelegate delegate;
  base::Thread thread("pump test");
  thread.Start();
  thread.task_runner()->PostDelayedTask(
      FROM_HERE, base::Bind(&MessagePump::Quit, base::Unretained(pump.get())),
      TimeDelta::FromSeconds(2));
  pump->Run(&delegate);

}
