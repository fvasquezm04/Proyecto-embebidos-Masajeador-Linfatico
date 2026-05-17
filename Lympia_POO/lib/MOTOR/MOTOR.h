#ifndef __MASSAGE_MOTOR_H
#define __MASSAGE_MOTOR_H__

#include <stdint.h>
#include "driver/ledc.h"

class Motor {
    private: 
        uint8_t _pin;
        ledc_channel_t _channel;
        ledc_timer_t _timer; 
        uint32_t _max_duty;
    
        public: 
            Motor(uint8_t gpio, ledc_channel_t channel);
            ~Motor(); 

            void init(); 

            void setIntensity(uint8_t porcentaje); 
 
};

#endif