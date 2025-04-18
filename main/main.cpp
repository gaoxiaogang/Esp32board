#include <stdio.h>
#include "board.h"
#include "oled_display.h"
#include "font_awesome_symbols.h"

#include <esp_log.h>
#include <esp_err.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void monitorTask(void *pvParameters) {
    static char taskInfoBuffer[256];  // 使用静态缓冲区
    while (1) {
        vTaskList(taskInfoBuffer);
        ESP_LOGI("TaskMonitor", "Task List:\n%s", taskInfoBuffer);
        vTaskDelay(pdMS_TO_TICKS(10000));  // 延长间隔
    }
}

extern "C" void app_main(void)
{
    // Initialize the default event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    auto &board = Board::GetInstance();
    auto display = board.GetDisplay();
    display->SetStatus("状态展示区...");
    display->SetIcon(FONT_AWESOME_EMOJI_LAUGHING);
    //display->SetEmotion("sleepy");
    
    std::string message = "对话展示区：Hello, GXG!还有中文内容，跑马灯效果！";
    display->SetChatMessage("system", message);
    
    xTaskCreate(monitorTask, "MonitorTask", 4096*2, NULL, 1, NULL);
}