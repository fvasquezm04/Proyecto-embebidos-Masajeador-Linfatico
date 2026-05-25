#include "WEBSERVER.h"
#include "index_html.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include <string.h>

#define AP_SSID    "Masajeador"
#define AP_CHANNEL 1
#define AP_MAX_STA 4

float WebServer::_pct   = 0.0f;
int   WebServer::_vProm = 0;

WebServer::WebServer() : _server(nullptr) {}
WebServer::~WebServer() {}

void WebServer::_initWifi() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    esp_netif_init();
    esp_event_loop_create_default(); /* ESP_ERR_INVALID_STATE = already exists, safe to ignore */
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t ap_cfg;
    memset(&ap_cfg, 0, sizeof(ap_cfg));
    memcpy(ap_cfg.ap.ssid, AP_SSID, strlen(AP_SSID));
    ap_cfg.ap.ssid_len       = (uint8_t)strlen(AP_SSID);
    ap_cfg.ap.channel        = AP_CHANNEL;
    ap_cfg.ap.authmode       = WIFI_AUTH_OPEN;
    ap_cfg.ap.max_connection = AP_MAX_STA;

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &ap_cfg);
    esp_wifi_start();
}

esp_err_t WebServer::_handleData(httpd_req_t* req) {
    const char* estado;
    float pct = _pct;

    if (pct < 30.0f)      estado = "insuficiente";
    else if (pct < 80.0f) estado = "\xc3\xb3ptimo";  /* óptimo UTF-8 */
    else                  estado = "excesivo";

    char json[128];
    snprintf(json, sizeof(json),
        "{\"pct\":%.1f,\"vProm\":%d,\"estado\":\"%s\"}",
        pct, _vProm, estado);

    httpd_resp_set_type(req, "application/json; charset=utf-8");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    httpd_resp_sendstr(req, json);
    return ESP_OK;
}

esp_err_t WebServer::_handleIndex(httpd_req_t* req) {
    httpd_resp_set_type(req, "text/html; charset=utf-8");
    httpd_resp_send(req, INDEX_HTML, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

void WebServer::_startServer() {
    httpd_config_t config   = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    if (httpd_start(&_server, &config) != ESP_OK) return;

    httpd_uri_t u_data;
    memset(&u_data, 0, sizeof(u_data));
    u_data.uri     = "/data";
    u_data.method  = HTTP_GET;
    u_data.handler = _handleData;
    httpd_register_uri_handler(_server, &u_data);

    httpd_uri_t u_index;
    memset(&u_index, 0, sizeof(u_index));
    u_index.uri     = "/";
    u_index.method  = HTTP_GET;
    u_index.handler = _handleIndex;
    httpd_register_uri_handler(_server, &u_index);
}

void WebServer::init() {
    _initWifi();
    _startServer();
}

void WebServer::setData(float pct, int vProm) {
    _pct   = pct;
    _vProm = vProm;
}
