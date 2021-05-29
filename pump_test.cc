#include "test/pump_test.h"
#include "common_head.h"
#include "build/build_config.h"
#include "build/buildflag.h"

#include "base/message_loop/message_pump.h"

using namespace base;

class PumpDelegate : public MessagePump::Delegate {
  public:
    ~PumpDelegate() override {
    }

	bool DoIdleWork() override {
		LOG(INFO) << "do idle";
		//for true here will go continue new loop to DoWork, false will fall into wait
		return false;
	}

#ifdef OLD_VERSION
	bool DoWork() override{
      LOG(INFO) << "do work";
	  return false;
    }

	void BeforeDoInternalWork() override {

	}

	NextWorkInfo DoSomeWork() override {
		return {};
	}

	bool DoDelayedWork(TimeTicks* next_delayed_work_time) override {
		return true;
	}
#else
    NextWorkInfo DoWork() override{
      LOG(INFO) << "do work";
      bool always_wait = true;
      if(always_wait){
        // always wait
        return {TimeTicks::Max()};
      } else {
        // run this function per second
        return {TimeTicks::Now() + TimeDelta::FromSeconds(1), TimeTicks::Now()};
      }
    }


    void BeforeWait() override {

    }

   private:
    void OnBeginNativeWork() override {

    }
    void OnEndNativeWork() override{

    }
#endif
};

void PumpTest() {
  TEST(pump);
  auto pump = MessagePump::Create(MessagePumpType::DEFAULT);
  PumpDelegate delegate;
  base::Thread thread("pump test");
  thread.Start();
  //signify waiting
  thread.task_runner()->PostDelayedTask(
      FROM_HERE,
      base::Bind(&MessagePump::ScheduleWork, base::Unretained(pump.get())),
      TimeDelta::FromSeconds(1));
  //stop, firstly wakeup loop
  thread.task_runner()->PostDelayedTask(FROM_HERE,
                                        base::Bind(
                                            [](MessagePump* p) {
                                              p->Quit();
                                              p->ScheduleWork();
                                            },
                                            pump.get()),
                                        TimeDelta::FromSeconds(2));
  pump->Run(&delegate);
}
