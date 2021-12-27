#ifndef T_NTP_HANDLER_H
#define T_NTP_HANDLER_H

class NtpHandlerInterface {

public:

    virtual void ntpInitialized() = 0;
};

#endif