
#include "ssd1306.h"
#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/i2c_host/i2c1.h"

// Prototipos de funciones privadas
static void SSD1306_EnviarComando(uint8_t comando){
    I2C1_Write(SSD1306_DIRECCION, SSD1306_COMANDO_BYTE_INICIAL, 1);
    I2C1_Write(SSD1306_DIRECCION, comando);

}
static void SSD1306_EnviarDatos(uint8_t datos){
    I2C1_Write(SSD1306_DIRECCION, SSD1306_DATOS_BYTE_INICIAL, 1);
    I2C1_Write(SSD1306_DIRECCION, datos, 1);
}

// Implementación de las funciones declaradas en ssd1306.h

void SSD1306_Inicializar(void) {
    // Inicializar la comunicación I2C
    I2C1_Initialize();

    // Enviar comandos de inicialización a la pantalla SSD1306
    SSD1306_EnviarComando(SSD1306_APAGAR_PANTALLA);            // Apagar la pantalla
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_MODO_RAM);  // Configurar el modo de datos de la RAM de la pantalla
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_CARGA);       // Configurar la carga de la pantalla
    SSD1306_EnviarComando(0x1F);                     // Configurar el contraste
    SSD1306_EnviarComando(0x1F); 
    SSD1306_EnviarComando(SSD1306_REMAP_SEGMENTO);       // Remapear los segmentos
    SSD1306_EnviarComando(SSD1306_PANTALLA_NORMAL);       // Configurar la pantalla en modo normal
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_MODO_DIRECCION);       // Configurar el modo de dirección
    SSD1306_EnviarComando(SSD1306_DIRECCION_HORIZONTAL);  // Configurar la dirección horizontal
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_MODO_MEMORIA);       // Configurar el modo de memoria
    SSD1306_EnviarComando(SSD1306_ORDEN_SEGMENTO_HORIZONTAL); // Configurar el orden horizontal de los segmentos
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_COLUMNA_INICIAL);       // Configurar la columna inicial
    SSD1306_EnviarComando(0x00);                           // Columna inicial = 0
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_CORRIENTE_CONTRASTE);  // Configurar la corriente de contraste
    SSD1306_EnviarComando(0x8F);                           // Corriente de contraste = 0x8F
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_OFFSET_PANTALLA);    // Configurar el desplazamiento de la pantalla
    SSD1306_EnviarComando(0x00);                           // Desplazamiento de la pantalla = 0
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_FILA_INICIAL);          // Configurar la fila inicial
    SSD1306_EnviarComando(0x00);                           // Fila inicial = 0
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_FILA_FINAL);            // Configurar la fila final
    SSD1306_EnviarComando(0x7F);                           // Fila final = 127 (63 filas)
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_LONGITUD_FASE);       // Configurar la longitud de la fase
    SSD1306_EnviarComando(0x0E);                           // Longitud de la fase = 0x0E
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_DIVISION_RELOJ_PANTALLA);   // Configurar la división del reloj de la pantalla
    SSD1306_EnviarComando(0x0F);                           // División del reloj = 0x0F
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_PERIODO_PRECARGA);   // Configurar el período de precarga
    SSD1306_EnviarComando(0xF7);                           // Período de precarga = 0xF7
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_DETECCION_VCOM);     // Configurar la detección de VCOM
    SSD1306_EnviarComando(0x05);                           // Detección de VCOM = 0x05
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_RATIO_MULTIPLEX);    // Configurar la relación de multiplexación
    SSD1306_EnviarComando(0x3F);                           // Relación de multiplexación = 0x3F (64 filas)
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_MODO_BAJO_CONSUMO);    // Configurar el modo de bajo consumo
    SSD1306_EnviarComando(0x00);                           // Modo de bajo consumo = desactivado
    SSD1306_EnviarComando(SSD1306_ENCENDER_PANTALLA);        // Encender la pantalla

    
    
    // Limpiar la pantalla
    SSD1306_LimpiarPantalla();
}

void SSD1306_Desinicializar(void) {
    // Puedes agregar código para apagar la pantalla y realizar cualquier otra limpieza necesaria aquí
    SSD1306_EnviarComando(SSD1306_APAGAR_PANTALLA);
}

void SSD1306_LimpiarPantalla(void) {
    for (uint8_t pagina = 0; pagina < 8; pagina++) {
        SSD1306_ConfigurarPosicion(0, pagina);
        for (uint8_t columna = 0; columna < 128; columna++) {
            SSD1306_EnviarDatos(0x00);
        }
    }
}

void SSD1306_PantallaNormal(void) {
    SSD1306_EnviarComando(SSD1306_PANTALLA_NORMAL);
}

void SSD1306_PantallaInvertida(void) {
    SSD1306_EnviarComando(SSD1306_PANTALLA_INVERTIDA);
}

void SSD1306_ActualizarPantalla(void) {
    // No se requiere ninguna operación aquí. Esta función se puede utilizar para actualizaciones en búfer si es necesario.
}

void SSD1306_ActualizarPosicion(uint8_t columna, uint8_t fila) {
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_COLUMNA_INICIAL | (columna & 0x0F));
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_PAGINA_SUPERIOR | (fila & 0x0F));
    SSD1306_EnviarComando(SSD1306_CONFIGURAR_FILA_INICIAL | (fila >> 4));
}

void SSD1306_ConfigurarPosicion(uint8_t columna, uint8_t fila) {
    SSD1306_ActualizarPosicion(columna, fila);
}

void SSD1306_DibujarCaracter(uint8_t caracter) {
    // Puedes implementar esta función para dibujar un solo carácter en la pantalla utilizando una tabla de fuentes
}

void SSD1306_DibujarCadena(const char *cadena) {
    // Puedes implementar esta función para dibujar una cadena de caracteres en la pantalla utilizando la función DibujarCaracter
}

void SSD1306_DibujarPixel(uint8_t columna, uint8_t fila, bool negro) {
    uint8_t pagina = fila / 8;
    uint8_t mascara_bit = 1 << (fila % 8);
    SSD1306_ActualizarPosicion(columna, pagina);
    if (negro) {
        I2C1_Write(SSD1306_DIRECCION, SSD1306_COMANDO_BYTE_INICIAL, (SSD1306_DATOS_BYTE_INICIAL | (I2C1_Read(SSD1306_DIRECCION, SSD1306_COMANDO_BYTE_INICIAL) | ~mascara_bit)));
    } else {
        I2C1_Write(SSD1306_DIRECCION, SSD1306_COMANDO_BYTE_INICIAL, (SSD1306_DATOS_BYTE_INICIAL | (I2C1_Read(SSD1306_DIRECCION, SSD1306_COMANDO_BYTE_INICIAL) & ~mascara_bit)));
    }
}

void SSD1306_DibujarLinea(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool negro) {
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  int16_t stepx = dx != 0 ? (dx > 0 ? 1 : -1) : 0;
  int16_t stepy = dy != 0 ? (dy > 0 ? 1 : -1) : 0;
  int16_t error = 0;
  int16_t x = x0;
  int16_t y = y0;

  if (dx < 0) {
    dx = -dx;
  }
  if (dy < 0) {
    dy = -dy;
  }

  if (dx > dy) {
    for (int16_t i = 0; i <= dx; ++i) {
      SSD1306_DibujarPixel(x, y, negro);
      x += stepx;
      error += dy;
      if (error >= dx) {
        y += stepy;
        error -= dx;
      }
    }
  } else {
    for (int16_t i = 0; i <= dy; ++i) {
      SSD1306_DibujarPixel(x, y, negro);
      y += stepy;
      error += dx;
      if (error >= dy) {
        x += stepx;
        error -= dy;
      }
    }
  }
}