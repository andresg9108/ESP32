# ESP32

## Proyecto final:
https://github.com/platzi/curso-progamacion-microcontroladores-esp32

// main/CMakeLists.txt
idf_component_register(SRCS "webapp.c"
                    INCLUDE_DIRS "."
                    EMBED_FILES index.html chroma.png)

// Cargando los archivos HTML y PNG
extern const char index_start[] asm("_binary_index_html_start");
extern const char index_end[] asm("_binary_index_html_end");
extern const char chroma_start[] asm("_binary_chroma_png_start");
extern const char chroma_end[] asm("_binary_chroma_png_end");

// Configuración
static const httpd_uri_t api = {
  .uri = "/api",
  .method = HTTP_GET,
  .handler = api_get_handler
};
static const httpd_uri_t home = {
  .uri = "/",
  .method = HTTP_GET,
  .handler = home_get_handler
};
static const httpd_uri_t chroma = {
  .uri = "/chroma.png",
  .method = HTTP_GET,
  .handler = chroma_get_handler
};

// Controladores
static esp_err_t home_get_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "text/html");

  const uint32_t index_len = index_end - index_start;
  httpd_resp_send(req, index_start, index_len);

  return ESP_OK;
}
static esp_err_t chroma_get_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "image/png");

  const uint32_t chroma_len = chroma_end - chroma_start;
  httpd_resp_send(req, chroma_start, chroma_len);

  return ESP_OK;
}

// Inicializando el servidor
void web_server_init() {
  httpd_handle_t server = NULL;
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();

  if (httpd_start(&server, &config) == ESP_OK) {
    httpd_register_uri_handler(server, &api);
    httpd_register_uri_handler(server, &home);
    httpd_register_uri_handler(server, &chroma);
    return;
  }
  printf("Error al iniciar servidor\n");
}