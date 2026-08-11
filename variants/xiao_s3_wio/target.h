#pragma once

#define RADIOLIB_STATIC_ONLY 1
#include <RadioLib.h>
#include <helpers/radiolib/RadioLibWrappers.h>
#include <helpers/ESP32Board.h>
#include <helpers/radiolib/CustomSX1262Wrapper.h>
#include <helpers/AutoDiscoverRTCClock.h>
#include <helpers/sensors/EnvironmentSensorManager.h>
#include <helpers/ui/MomentaryButton.h>

#ifdef DISPLAY_CLASS
  #include <helpers/ui/SSD1306Display.h>
#endif
#define HAS_USER_BUTTON 1
#include "XiaoS3WIOBoard.h"

extern XiaoS3WIOBoard board;
extern WRAPPER_CLASS radio_driver;
extern AutoDiscoverRTCClock rtc_clock;
extern EnvironmentSensorManager sensors;

#ifdef DISPLAY_CLASS
  extern DISPLAY_CLASS display;
#endif
extern MomentaryButton user_btn;

bool radio_init();
mesh::LocalIdentity radio_new_identity();

