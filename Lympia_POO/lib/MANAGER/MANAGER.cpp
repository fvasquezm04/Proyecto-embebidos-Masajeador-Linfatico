#include "MANAGER.h"
#include <stdio.h>

Manager::Manager(
    adc_oneshot_unit_handle_t adc_handle, 
    uint8_t pinFsr1,
    uint8_t pinFsr2, 
    uint8_t pinMotor, 
    ledc_channel_t motorChannel, 
    uint8_t ledV, uint8_t ledA, uint8_t ledR,
    uint8_t buzzer
): _fsrIzq(pinFsr1, adc_handle), 
    _fsrDer(pinFsr2, adc_handle), 
    _motor(pinMotor, motorChannel), 
    _ui(ledV, ledA, ledR, buzzer),
    _uart(UART_NUM_0, 1, 3)
{
    _vMin = 200; 
    _vMax = 3000;
    _motorIntensidad = 50;
}

void Manager::init(){
    _fsrIzq.init();
    _fsrDer.init(); 
    _motor.init();
    _ui.init(); 
    _uart.init();

    _motor.setIntensity(_motorIntensidad);
}

Manager::~Manager(){

}

void Manager::setConfig(int vMinMv, int vMaxMv, uint8_t intensidadFija){
    _vMin = vMinMv; 
    _vMax = vMaxMv; 
    _motorIntensidad = intensidadFija;
}


void Manager::update(){
    int vIzq = _fsrIzq.read();
    int vDer = _fsrDer.read();

    int vPromedio = (vIzq + vDer) / 2; 
    float porcentaje = 0.0;

    if (vPromedio > _vMin){
        float valorMedido = vPromedio - _vMin; 
        float rangoTotal = _vMax - _vMin;

        porcentaje = (valorMedido / rangoTotal) * 100;
    }

    if (porcentaje < 0.0f) porcentaje = 0.0f; 
    if (porcentaje > 100.0f) porcentaje = 100.0f;

    char mensaje_uart[100];
    sprintf(mensaje_uart, "FSR Izq: %d mV | FSR Der: %d mV | Promedio: %d mV | Presion: %.1f%%\r\n", 
            vIzq, vDer, vPromedio, porcentaje);
    _uart.sendUart(mensaje_uart);

    if (porcentaje >= 0.0f && porcentaje < 30.0f){
        _ui.alertasLow(); 
    }
    else if (porcentaje >= 30.0f && porcentaje < 80.0f){
        _ui.alertasOk(); 
    }
    else if (porcentaje >= 80.0f && porcentaje <= 100.0f){
        _ui.alertasHigh(); 
    }
}
    