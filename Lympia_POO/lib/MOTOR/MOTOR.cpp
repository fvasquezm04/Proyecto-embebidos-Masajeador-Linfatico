#include "Motor.h"

Motor::Motor(uint8_t gpio, ledc_channel_t channel){
    _pin = gpio; 
    _channel = channel; 
    _timer = LEDC_TIMER_0; 
    _max_duty = 1023; 
}
Motor::~Motor(){
    ledc_stop(LEDC_LOW_SPEED_MODE, _channel, 0);
}

void Motor::init(){
    ledc_timer_config_t timer_conf= {};
    timer_conf.speed_mode = LEDC_LOW_SPEED_MODE;
    timer_conf.timer_num = _timer; 
    timer_conf.duty_resolution = LEDC_TIMER_10_BIT; 
    timer_conf.freq_hz = 5000; 
    timer_conf.clk_cfg = LEDC_AUTO_CLK;

    ledc_timer_config(&timer_conf); 

    ledc_channel_config_t channel_conf = {};
    channel_conf.gpio_num = _pin;
    channel_conf.speed_mode = LEDC_LOW_SPEED_MODE; 
    channel_conf.channel = _channel;
    channel_conf.intr_type = LEDC_INTR_DISABLE;
    channel_conf.timer_sel = _timer;
    channel_conf.duty = 0;
    channel_conf.hpoint = 0; 

    ledc_channel_config(&channel_conf); 
}

void Motor::setIntensity(uint8_t percentage){
    if (percentage > 100) percentage = 100;

    uint32_t duty = (percentage * _max_duty)/100; 

    ledc_set_duty(LEDC_LOW_SPEED_MODE, _channel, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, _channel);
}