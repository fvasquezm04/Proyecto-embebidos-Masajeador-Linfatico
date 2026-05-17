#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "FSR.h"
#include "MOTOR.h"
#include "FEEDBACK.h"
#include "UART.h"

class Manager {
    private:
        Fsr _fsrIzq; 
        Fsr _fsrDer;
        Motor _motor; 
        FeedbackSystem _ui; 
        Uart _uart;

        int _vMin;
        int _vMax; 
        uint8_t _motorIntensidad;
        
    public: 
        Manager(
            adc_oneshot_unit_handle_t adc_handle, 
            uint8_t pinFsr1,
            uint8_t pinFsr2, 
            uint8_t pinMotor, 
            ledc_channel_t motorChannel, 
            uint8_t ledV, uint8_t ledA, uint8_t ledR,
            uint8_t buzzer
        );
        ~Manager();

        void setConfig(int vMinMv, int vMaxMv, uint8_t intensidadFija); 
        void init();
        void update();
};


#endif