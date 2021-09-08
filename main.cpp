#include "ohlog.h"

int main() {
  ohlog::Logger::get("log.txt");
  DLOG("This is some debug message");
  DLOGA("This is another debug message, %s", "but it has arguments");
  ILOG("This is a normal info message");
  ILOGA("This is %i and that is %f", 420, 69.69);
  WLOG("Oh noes. A warning");
  WLOGA("A warning %s arguments", "with");
  ELOG("An error. That's certainly bad");
  ELOGA("An error %s. That's even %s", "with arguments", "worse");
  ILOGA("But you could also just %s to a file", "pipe the output");
  bool doRun = true;

  std::thread t0([&doRun]() {
    while(doRun) {
      DLOG("Logger one here");
    }
  });

  std::thread t1([&doRun]() {
    while(doRun) {
      DLOG("Logger two here");
    }
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  doRun = false;
  t0.join();
  t1.join();

  return 0;
}
