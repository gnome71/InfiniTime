#include "PrintWatch.h"
#include "../DisplayApp.h"
#include "components/ble/PrintWatchService.h"

using namespace Pinetime::Applications::Screens;

PrintWatch::PrintWatch(DisplayApp* app, Controllers::PrintWatchService& printwatch)
  : Screen(app), printwatchService(printwatch) {

  extruderTemp = printwatchService.getExtruderTemp();
  bedTemp = printwatchService.getBedTemp();
  hostName = printwatchService.getHost();
  eta = printwatchService.getDuration();

  // Create the host ui part
  hostLabel = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text(hostLabel, hostName.c_str());
  lv_obj_align(hostLabel, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
  
  // Create the extruder ui part
  extruderArc = lv_arc_create(lv_scr_act(), nullptr);
  lv_arc_set_bg_angles(extruderArc, 0, 180);
  lv_arc_set_rotation(extruderArc, 180);
  lv_arc_set_range(extruderArc, 10, 300);
  lv_arc_set_value(extruderArc, std::stoi(extruderTemp));
  lv_obj_set_size(extruderArc, 105, 105);
  lv_arc_set_adjustable(extruderArc, true);
  lv_obj_align(extruderArc, hostLabel, LV_ALIGN_OUT_BOTTOM_MID, -65, 15);
  extruderValueLabel = lv_label_create(extruderArc, nullptr);
  lv_label_set_text_fmt(extruderValueLabel, "%s", extruderTemp.c_str());
  lv_obj_align(extruderValueLabel, extruderArc, LV_ALIGN_CENTER, 0, 0);
  extruderLabel = lv_label_create(extruderArc, nullptr);
  lv_label_set_text(extruderLabel, "E1");
  lv_obj_align(extruderLabel, nullptr, LV_ALIGN_CENTER, 0, 30);

  // Create the bed ui part
  bedArc = lv_arc_create(lv_scr_act(), nullptr);
  lv_arc_set_bg_angles(bedArc, 0, 180);
  lv_arc_set_rotation(bedArc, 180);
  lv_arc_set_range(bedArc, 10, 110);
  lv_arc_set_value(bedArc, std::stoi(bedTemp));
  lv_obj_set_size(bedArc, 105, 105);
  lv_arc_set_adjustable(bedArc, true);
  lv_obj_align(bedArc, hostLabel, LV_ALIGN_OUT_BOTTOM_MID, 65, 15);
  bedValueLabel = lv_label_create(bedArc, nullptr);
  lv_label_set_text_fmt(bedValueLabel, "%s", bedTemp.c_str());
  lv_obj_align(bedValueLabel, bedArc, LV_ALIGN_CENTER, 0, 0);
  bedLabel = lv_label_create(bedArc, nullptr);
  lv_label_set_text(bedLabel, "Bed");
  lv_obj_align(bedLabel, nullptr, LV_ALIGN_CENTER, 0, 30);

  // Create the duration ui part
  durationBar = lv_bar_create(lv_scr_act(), nullptr);
  lv_obj_set_size(durationBar, 200, 15);
  lv_bar_set_range(durationBar, 0, 300);
  lv_obj_align(durationBar, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
  lv_bar_set_anim_time(durationBar, 1000);
  lv_obj_set_style_local_radius(durationBar, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
  lv_obj_set_style_local_bg_color(durationBar, LV_BAR_PART_BG, LV_STATE_DEFAULT, lv_color_hex(0x222222));
  lv_obj_set_style_local_bg_opa(durationBar, LV_BAR_PART_BG, LV_STATE_DEFAULT, LV_OPA_100);
  lv_obj_set_style_local_bg_color(durationBar, LV_BAR_PART_INDIC, LV_STATE_DEFAULT, lv_color_hex(0x5A8483));
  lv_bar_set_value(durationBar, std::stoi(eta), LV_ANIM_OFF);
}

PrintWatch::~PrintWatch() {
  app->SetTouchMode(DisplayApp::TouchModes::Gestures);
  lv_obj_clean(lv_scr_act());
}

bool PrintWatch::Refresh() {
  //if (printwatchStarted) {
    if (hostName != printwatchService.getHost()) {
      hostName = printwatchService.getHost();
      lv_label_set_text(hostLabel, hostName.c_str());
      lv_obj_align(hostLabel, nullptr, LV_ALIGN_IN_TOP_MID, 0, 0);
    }
    if (extruderTemp != printwatchService.getExtruderTemp()) {
      extruderTemp = printwatchService.getExtruderTemp();
      lv_label_set_text_fmt(extruderValueLabel, "%s", extruderTemp.c_str());
      lv_arc_set_value(extruderArc, std::stoi(extruderTemp));
    }
    if (bedTemp != printwatchService.getBedTemp()) {
      bedTemp = printwatchService.getBedTemp();
      lv_label_set_text_fmt(bedValueLabel, "%s", bedTemp.c_str());
      lv_arc_set_value(bedArc, std::stoi(bedTemp));
    }
    if (eta != printwatchService.getDuration()) {
      eta = printwatchService.getDuration();
      lv_bar_set_value(durationBar, std::stoi(eta), LV_ANIM_OFF);
    }
  //}
  
  return running;
}