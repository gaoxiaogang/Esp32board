#ifndef BOARD_H
#define BOARD_H

#include <mqtt.h>
#include <udp.h>
#include <string>

class AudioCodec;
class Display;
class Board {
private:

protected:
    Board();

public:
    virtual ~Board() = default;
    virtual std::string GetBoardType() = 0;
    virtual AudioCodec* GetAudioCodec() = 0;
    virtual Display* GetDisplay();
    virtual Mqtt* CreateMqtt() = 0;
    virtual Udp* CreateUdp() = 0;
};


#endif // BOARD_H