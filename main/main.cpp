#include <stdio.h>
#include "board.h"
#include "oled_display.h"
#include "font_awesome_symbols.h"
#include "application.h"

#include <nvs.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include <esp_err.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define TAG "main"

extern "C" void app_main(void)
{
    // Initialize the default event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize NVS flash for WiFi configuration
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Erasing NVS flash to fix corruption");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Launch the application
    Application::GetInstance().Start();
    // The main thread will exit and release the stack memory

    /*
    auto &board = Board::GetInstance();
    auto display = board.GetDisplay();
    display->SetStatus("状态展示区...");
    display->SetIcon(FONT_AWESOME_EMOJI_LAUGHING);
    //display->SetEmotion("sleepy");
    
    std::string message = "对话展示区：Hello, GXG!还有中文内容，跑马灯效果！";
    display->SetChatMessage("system", message);
    */
}