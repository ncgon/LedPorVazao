#include "pico/stdlib.h"
#include "hardware/adc.h"

#define LED2 2
#define LED3 3

int main() {
    stdio_init_all();

    // Inicialização do ADC
    adc_init();
    adc_gpio_init(26);      // GP26 = ADC0
    adc_select_input(0);    // Seleciona ADC0

    // Inicializa GPIOs como saída

    gpio_init(LED2);
    gpio_set_dir(LED2, GPIO_OUT);
    gpio_init(LED3);
    gpio_set_dir(LED3, GPIO_OUT);

    
    // Desliga todos os LEDs
    gpio_put(LED2, 0);
    
    gpio_put(LED3, 0);

while (true) {
        uint16_t raw = adc_read(); // Leitura bruta: 0-4095 (12 bits)
        float voltage = (raw * 3.3f) / 4095.0f;

        // Verifica faixas e aciona os LEDs
        if (voltage >= 2.0) {
            gpio_put(LED2, 0);
            gpio_put(LED3, 0);


        } else if (voltage >= 1.0 && voltage<2.0) {
            gpio_put(LED2, 1);
            gpio_put(LED3, 0);
            
        } else {
            gpio_put(LED2, 1);
            gpio_put(LED3, 1);
        }

        sleep_ms(200);  // Correto: agora está dentro do while
    }

    return 0;  // Opcional, mas agora está dentro do main
}