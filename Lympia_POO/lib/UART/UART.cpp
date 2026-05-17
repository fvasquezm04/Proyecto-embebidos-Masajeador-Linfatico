#include "UART.h"

Uart::Uart(uart_port_t port, int txPin, int rxPin){
    _port = port; 
    _txPin = txPin; 
    _rxPin = rxPin; 
}

void Uart::init(){
    uart_config_t uart_config = {
		//Según notación 96008N1
        .baud_rate = 9600, // Recordar poner en platform.ini monitor_speed = 9600;
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE, 
        .stop_bits = UART_STOP_BITS_1, 
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, 
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_param_config(_port, &uart_config); 
    uart_set_pin(_port, _txPin, _rxPin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE); 
    uart_driver_install(_port, 1024, 1024, 0, NULL, 0); 
}

void Uart::sendUart(const char* mensaje){
    uart_write_bytes(_port, mensaje, strlen(mensaje));
}