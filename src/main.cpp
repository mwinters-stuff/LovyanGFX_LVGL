//================================================================//
//  LovyanGFX & LVGL Example for ILI9488
//  Displays a simple button in the center of the screen.
//================================================================//

#define LGFX_USE_V1 // Use LovyanGFX V1
#include <LovyanGFX.hpp>
#include <lvgl.h>
#include <Arduino.h>
#include <LGFX_ILI9488_S3.hpp>
#include "demos/widgets/lv_demo_widgets.h"

// --- LovyanGFX Setup ---
// Create an instance of our custom display class.
LGFX gfx;

// --- LVGL Variables ---
static lv_disp_draw_buf_t draw_buf;

// Use a buffer of 1/10th of the screen size.
// LV_COLOR_DEPTH is defined in lv_conf.h.
#define buffer_size  gfx.screenWidth *gfx.screenHeight / 10
static lv_color_t buf1[buffer_size];
static lv_color_t buf2[buffer_size];

// --- LVGL Display Driver Callback ---
// This function is called by LVGL to flush the rendered frame buffer to the display.
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  if (gfx.getStartCount() == 0)
  {
    gfx.endWrite();
  }
  gfx.pushImageDMA(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::rgb565_t*)color_p);
  lv_disp_flush_ready(disp); // Inform LVGL that flushing is done
}

// LVGL touchpad read callback using LovyanGFX
void my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
  uint16_t x, y;
  if (gfx.getTouch(&x, &y)) {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = x;
    data->point.y = y;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("LVGL Button Example with LovyanGFX");

  // 1. Initialize LovyanGFX
  gfx.begin();
  gfx.setRotation(0); // Set to portrait mode (0 or 2)
  gfx.fillScreen(TFT_BLACK); // Fill background before LVGL UI

  // 2. Initialize LVGL
  lv_init();

  // 3. Initialize the LVGL display buffer
  lv_disp_draw_buf_init(&draw_buf, buf1, buf2, buffer_size);

  // 4. Initialize and register the LVGL display driver
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = gfx.screenWidth;
  disp_drv.ver_res = gfx.screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  // Register LVGL input device for touch
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  uint16_t parameters[8] = {
    293,
    3879,
    277,
    221,
    3859,
    3882,
    3868,
    239,
  };
  gfx.setTouchCalibrate(parameters);

  lv_demo_widgets();
  
  // gfx.calibrateTouch(parameters, TFT_RED, TFT_BLACK);
  // for(int i = 0; i < 8; i++ ){
  //   Serial.println(parameters[i]);
  // }
  Serial.println("Setup complete. UI should be visible.");
}

lgfx::touch_point_t tp;
void loop()
{
  // Let LVGL handle its tasks, like animations and events
 lv_timer_handler(); 
 delay(1);

}