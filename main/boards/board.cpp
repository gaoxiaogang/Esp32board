#include "board.h"
#include "settings.h"
#include "display.h"

#include <esp_log.h>
#include <esp_ota_ops.h>
#include <esp_chip_info.h>
#include <esp_random.h>

#define TAG "Board"

Board::Board() {
    //# TODO
    //ESP_LOGI(TAG, "UUID=%s SKU=%s", uuid_.c_str(), BOARD_NAME);
}



Display* Board::GetDisplay() {
    static NoDisplay display;
    return &display;
}
