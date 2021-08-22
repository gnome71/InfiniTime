#include "PrintWatch.h"

using namespace Pinetime::Applications::Screens;

PrintWatch::PrintWatch(DisplayApp* app, System::SystemTask& systemTask)
  : Screen(app), systemTask {systemTask} {

  
}

PrintWatch::~PrintWatch() {
  app->SetTouchMode(DisplayApp::TouchModes::Gestures);
  systemTask.PushMessage(System::Messages::EnableSleeping);
}

bool PrintWatch::Refresh() {
  if (printwatchStarted) {
    // TODO: implement
  }
  return running;
}