#ifndef __FEEDBACK_SYSTEM__
#define __FEEDBACK_SYSTEM__

#include <stdint.h>

class FeedbackSystem {
    private: 
        uint8_t _pinLedVerde;
        uint8_t _pinLedAmarillo;
        uint8_t _pinLedRojo;
        uint8_t _pinBuzzer;
    
    public: 
        FeedbackSystem(uint8_t ledV, uint8_t ledA, uint8_t ledR, uint8_t buzzer); 
        ~FeedbackSystem(); 

        void init(); 

        void alertasOff(); 
        void alertasLow(); 
        void alertasOk(); 
        void alertasHigh();
};


#endif