#include "FEEDBACK.h"
#include "driver/gpio.h"

FeedbackSystem::FeedbackSystem(uint8_t ledV, uint8_t ledA, uint8_t ledR, uint8_t buzzer){
    _pinLedVerde = ledV; 
    _pinLedAmarillo = ledA; 
    _pinLedRojo = ledR; 
    _pinBuzzer = buzzer; 
}

FeedbackSystem::~FeedbackSystem(){
    gpio_set_level((gpio_num_t)_pinLedVerde, 0);
    gpio_set_level((gpio_num_t)_pinLedAmarillo, 0);
    gpio_set_level((gpio_num_t)_pinLedRojo, 0);
    gpio_set_level((gpio_num_t)_pinBuzzer, 0);
}

void FeedbackSystem::init(){
    gpio_config_t io_conf = {};
    
    io_conf.pin_bit_mask = (1ULL << _pinLedVerde) | (1ULL << _pinLedAmarillo) | (1ULL << _pinLedRojo) | (1ULL << _pinBuzzer);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;

    gpio_config(&io_conf);
}

void FeedbackSystem::alertasOff(){
    gpio_set_level((gpio_num_t)_pinLedVerde, 0);
    gpio_set_level((gpio_num_t)_pinLedAmarillo, 0);
    gpio_set_level((gpio_num_t)_pinLedRojo, 0);
    gpio_set_level((gpio_num_t)_pinBuzzer, 0);
}

void FeedbackSystem::alertasLow(){
    gpio_set_level((gpio_num_t)_pinLedVerde, 0);
    gpio_set_level((gpio_num_t)_pinLedAmarillo, 1);
    gpio_set_level((gpio_num_t)_pinLedRojo, 0);
    gpio_set_level((gpio_num_t)_pinBuzzer, 0);
}

void FeedbackSystem::alertasOk(){
    gpio_set_level((gpio_num_t)_pinLedVerde, 1);
    gpio_set_level((gpio_num_t)_pinLedAmarillo, 0);
    gpio_set_level((gpio_num_t)_pinLedRojo, 0);
    gpio_set_level((gpio_num_t)_pinBuzzer, 0);
}

void FeedbackSystem::alertasHigh(){
    gpio_set_level((gpio_num_t)_pinLedVerde, 0);
    gpio_set_level((gpio_num_t)_pinLedAmarillo, 0);
    gpio_set_level((gpio_num_t)_pinLedRojo, 1);
    gpio_set_level((gpio_num_t)_pinBuzzer, 1);
}


