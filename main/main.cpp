#include <stdio.h>
#include "esp32_wifi_board.h"
#include "oled_display.h"
#include "font_awesome_symbols.h"

extern "C" void app_main(void)
{
    Esp32WifiBoard &board = Esp32WifiBoard::GetInstance();
    auto display = board.GetDisplay();
    display->SetStatus("状态展示区...");
    display->SetIcon(FONT_AWESOME_EMOJI_LAUGHING);
    //display->SetEmotion("sleepy");
    
    std::string message = "对话展示区：Hello, GXG!还有中文内容，跑马灯效果！";
    display->SetChatMessage("system", message);
}