#include "Port/Display.h"

#define DISP_HOR_RES         CONFIG_SCREEN_HOR_RES
#define DISP_VER_RES         CONFIG_SCREEN_VER_RES
#define DISP_BUF_SIZE        CONFIG_SCREEN_BUFFER_SIZE

//static lv_color_t lv_full_disp_buf[DISP_BUF_SIZE];
lv_color_t* lv_disp_buf_p;

static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv;

#if LV_USE_LOG
void my_print(lv_log_level_t level, const char* file, uint32_t line, const char* fun, const char* dsc)
{
    Serial.printf("%s@%d %s->%s\r\n", file, line, fun, dsc);
    Serial.flush();
}
#endif

static void disp_flush_cb(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
    int32_t w = (area->x2 - area->x1 + 1);
    int32_t h = (area->y2 - area->y1 + 1);

    M5.Lcd.startWrite();
    M5.Lcd.setAddrWindow(area->x1, area->y1, w, h);
    M5.Lcd.pushColors((uint16_t*) (&color_p->full), w * h, true);
    M5.Lcd.endWrite();

    lv_disp_flush_ready(disp);
}

static void disp_wait_cb(lv_disp_drv_t* disp_drv)
{
//    __wfi();
}

void lv_port_disp_init()
{
#if LV_USE_LOG
    lv_log_register_print_cb(
        reinterpret_cast<lv_log_print_g_cb_t>(my_print)); /* register print function for debugging */
#endif
    /* Move the malloc process to Init() to make sure that the largest heap can be used for this buffer.
     */
    lv_disp_buf_p = static_cast<lv_color_t*>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    if (lv_disp_buf_p == nullptr)
        LV_LOG_WARN("lv_port_disp_init malloc failed!\n");

    lv_disp_draw_buf_init(&disp_buf, lv_disp_buf_p, nullptr, DISP_BUF_SIZE);

    /*Initialize the display*/
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = DISP_HOR_RES;
    disp_drv.ver_res = DISP_VER_RES;
    disp_drv.flush_cb = disp_flush_cb;
    disp_drv.wait_cb = disp_wait_cb;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);
}
