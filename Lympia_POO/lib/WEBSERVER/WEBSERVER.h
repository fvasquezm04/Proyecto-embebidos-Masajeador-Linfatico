#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include "esp_http_server.h"

class WebServer {
private:
    httpd_handle_t _server;

    static float _pct;
    static int   _vProm;

    static esp_err_t _handleData(httpd_req_t* req);
    static esp_err_t _handleIndex(httpd_req_t* req);

    void _initWifi();
    void _initSpiffs();
    void _startServer();

public:
    WebServer();
    ~WebServer();

    void init();
    void setData(float pct, int vProm);
};

#endif
