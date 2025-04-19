#include <string.h>
#include "esp_http_server.h"
#include "agwifi.h"
#include "agHttpServer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED 4
int led_state = 0;

extern const char index_start[] asm("_binary_index_html_start");
extern const char index_end[] asm("_binary_index_html_end");

static esp_err_t homePage_get_handler(httpd_req_t *req) {
    httpd_resp_set_type(req, "text/html");

    const uint32_t index_len = index_end - index_start;
    httpd_resp_send(req, index_start, index_len);

    return ESP_OK;
}

static esp_err_t api_get_handler(httpd_req_t *req){
    // ip/api?l=1
    char* buf;
    size_t buf_len;
    buf_len = httpd_req_get_url_query_len(req) + 1;
    if(buf_len > 1){
        buf = malloc(buf_len); // Reservar memoria para la cadena
        if(httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK){
            char param[10];
            if(httpd_query_key_value(buf, "l", param, sizeof(param)) == ESP_OK){
                led_state = atoi(param);
                printf("Led: %d\n", led_state);
            }
        }

        free(buf); // Liberar memoria
    }

    // Establecer nivel lógico 0 ó 1
    gpio_set_level(LED, led_state);

    // Respuesta
    httpd_resp_set_hdr(req, "Content-Type", "application/json");
    char res[30];
    sprintf(res, "{ \"led\": %d }", led_state);

    httpd_resp_send(req, res, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static const httpd_uri_t homePage = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = homePage_get_handler
};

static const httpd_uri_t api = {
    .uri = "/api",
    .method = HTTP_GET,
    .handler = api_get_handler
};

void web_server_init(void){
    esp_err_t err = agHttpServer_initialize_http_server();

    if(err != ESP_OK){
        printf("Error al iniciar el servidor HTTP: %s\n", esp_err_to_name(err));
        return;
    }

    httpd_handle_t server = agHttpServer_get_http_server();

    httpd_register_uri_handler(server, &homePage);
    httpd_register_uri_handler(server, &api);
}

void app_main(void){
    agwifi_connect_to_wifi_network();

    if(!agwifi_is_wifi_connected()){
        printf("No hay ninguna conexión.\n");
    }else{
        agwifi_print_wifi_network_information();

        web_server_init();
    }

    // Definiendo salidas
    gpio_reset_pin(LED);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    // Establecer nivel lógico 0 ó 1
    gpio_set_level(LED, led_state);
}