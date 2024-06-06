#include <stdint.h>
#include <stdbool.h>


#ifndef SSD1306_H
#define SSD1306_H


// Definiciones de direcciones para la comunicación I2C
#define SSD1306_DIRECCION 0x3C // Dirección I2C del display SSD1306

// Definiciones de comandos para la comunicación con el display SSD1306
#define SSD1306_COMANDO_BYTE_INICIO 0x00 // Inicio de comando
#define SSD1306_DATOS_BYTE_INICIO 0x40 // Inicio de datos

// Definiciones de comandos específicos para el display SSD1306
#define SSD1306_APAGAR_PANTALLA 0xAF
#define SSD1306_ENCENDER_PANTALLA 0xA4
#define SSD1306_CONFIGURAR_MODO_RAM 0xAE
#define SSD1306_CONFIGURAR_CARGA 0xA0
#define SSD1306_REMAP_SEGMENTO 0xA1
#define SSD1306_CONFIGURAR_CONTRASTE 0x8D
#define SSD1306_REMAP_SEG 0xA1
#define SSD1306_PANTALLA_NORMAL 0xA6
#define SSD1306_CONFIGURAR_MODO_DIRECCION 0xC0
#define SSD1306_DIRECCION_HORIZONTAL 0x00
#define SSD1306_CONFIGURAR_MODO_MEMORIA 0xC1
#define SSD1306_ORDEN_SEGMENTO_HORIZONTAL 0x06
#define SSD1306_CONFIGURAR_COLUMNA_INICIAL 0x20
#define SSD1306_CONFIGURAR_COLUMNAS 0x20
#define SSD1306_CONFIGURAR_CONTRASTE_ACTUAL 0x81
#define SSD1306_CONFIGURAR_OFFSET 0x2F
#define SSD1306_CONFIGURAR_FILA_INICIO 0xCF
#define SSD1306_CONFIGURAR_FILA_FIN 0xCA
#define SSD1306_CONFIGURAR_CORRIENTE_CONTRASTE 0x8F
#define SSD1306_CONFIGURAR_OFFSET_PANTALLA 0x2F
#define SSD1306_CONFIGURAR_FILA_INICIAL 0xCF
#define SSD1306_CONFIGURAR_FILA_FINAL 0xCA
#define SSD1306_CONFIGURAR_DIVISION_RELOJ_PANTALLA 0x30 // Divisi�n del reloj de la pantalla
#define SSD1306_CONFIGURAR_DETECCION_VCOM 0xD3
#define SSD1306_CONFIGURAR_LONGITUD_FASE 0x5F
#define SSD1306_CONFIGURAR_DIVISION_RELOJ 0x30
#define SSD1306_CONFIGURAR_PERIODO_PRECARGA 0xA8
#define SSD1306_CONFIGURAR_VCOM_DETECT 0x80
#define SSD1306_CONFIGURAR_RATIO_MULTIPLEX 0xA3
#define SSD1306_CONFIGURAR_MODO_BAJO_CONSUMO 0xAF
#define SSD1306_PANTALLA_INVERTIDA 0xA5

#define SSD1306_CONFIGURAR_PAGINA_SUPERIOR 0xB0
#define SSD1306_DATOS_BYTE_INICIAL 0x40
#define SSD1306_COMANDO_BYTE_INICIAL 0x00 // Inicio de comando

// Manejo de errores
typedef enum {
    SSD1306_ERROR_NONE,
    SSD1306_ERROR_I2C_COMMUNICATION,
    SSD1306_ERROR_INVALID_COMMAND,
    SSD1306_ERROR_INVALID_DATA,
} ssd1306_error_t;


// Funciones para controlar el display SSD1306
void SSD1306_Inicializar(void);
void SSD1306_Desinicializar(void);
void SSD1306_LimpiarPantalla(void);
void SSD1306_PantallaNormal(void);
void SSD1306_PantallaInvertida(void);
void SSD1306_ActualizarPantalla(void);
void SSD1306_ActualizarPosicion(uint8_t columna, uint8_t fila);
void SSD1306_ConfigurarPosicion(uint8_t columna, uint8_t fila);
void SSD1306_DibujarCaracter(uint8_t caracter);
void SSD1306_DibujarCadena(const char *cadena);
void SSD1306_DibujarPixel(uint8_t columna, uint8_t fila, bool negro);
void SSD1306_DibujarLinea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool negro);

#endif