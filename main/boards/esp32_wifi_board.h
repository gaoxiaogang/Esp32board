#include "wifi_board.h"
#include "oled_display.h"

#include <esp_log.h>
#include <driver/i2c_master.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_vendor.h>

LV_FONT_DECLARE(font_puhui_14_1);
LV_FONT_DECLARE(font_awesome_14_1);

class Esp32WifiBoard : public WifiBoard {
private:
    i2c_master_bus_handle_t display_i2c_bus_;
    esp_lcd_panel_io_handle_t panel_io_ = nullptr;
    esp_lcd_panel_handle_t panel_ = nullptr;
    Display* display_ = nullptr;

    void InitializeDisplayI2c();

    void InitializeSsd1306Display();

    Esp32WifiBoard();

public:
    
    static Esp32WifiBoard& GetInstance() {
        static Esp32WifiBoard instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    Esp32WifiBoard(const Esp32WifiBoard&) = delete;
    Esp32WifiBoard& operator=(const Esp32WifiBoard&) = delete;

    virtual AudioCodec* GetAudioCodec() override;
    virtual Display* GetDisplay() override;
};
