#ifndef WIFI_BOARD_H
#define WIFI_BOARD_H

#include "board.h"

class WifiBoard : public Board {
protected:
    bool wifi_config_mode_ = false;

    WifiBoard();
    virtual std::string GetBoardJson() override;

public:
    virtual std::string GetBoardType() override;
    virtual Mqtt* CreateMqtt() override;
    virtual Udp* CreateUdp() override;
};

#endif // WIFI_BOARD_H
