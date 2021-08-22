#include "PrintWatch.h"

using namespace Pinetime::Applications::Screens;

PrintWatch::PrintWatch(DisplayApp* app, System::SystemTask& systemTask)
  : Screen(app), systemTask {systemTask} {

  extruderTemp = 215;
  bedTemp = 60;
  hostName = "fluiddpi";

  // Create the extruder ui part
  extruderValueLabel = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_font(extruderValueLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
  lv_label_set_text_fmt(extruderValueLabel, "E1: %d°", extruderTemp);
  lv_label_set_align(extruderValueLabel, LV_LABEL_ALIGN_LEFT);
  lv_obj_align(extruderValueLabel, nullptr, LV_ALIGN_CENTER, -20, -75);

  // Create the duration ui part
  durationBar = lv_bar_create(lv_scr_act(), nullptr);
  lv_obj_set_size(durationBar, 200, 15);
  lv_bar_set_range(durationBar, 10, 300);
  lv_obj_align(durationBar, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
  lv_bar_set_anim_time(durationBar, 1000);
  lv_obj_set_style_local_radius(durationBar, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
  lv_obj_set_style_local_bg_color(durationBar, LV_BAR_PART_BG, LV_STATE_DEFAULT, lv_color_hex(0x222222));
  lv_obj_set_style_local_bg_opa(durationBar, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_OPA_100);
  lv_obj_set_style_local_bg_color(durationBar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(0x5A8483));
  lv_bar_set_value(durationBar, 235, LV_ANIM_OFF);
  
}

PrintWatch::~PrintWatch() {
  app->SetTouchMode(DisplayApp::TouchModes::Gestures);
  systemTask.PushMessage(System::Messages::EnableSleeping);
  lv_obj_clean(lv_scr_act());
}

bool PrintWatch::Refresh() {
  if (printwatchStarted) {
    // TODO: implement
  }
  return running;
}