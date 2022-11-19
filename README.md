## Projeto de Casa Inteligente com ESP32
### Descrição:

O objetivo do projeto é integrar um sistema de iluminação via LEDs através da assistente virtual Alexa pelo App no celular. Basta falar, por exemplo: **Alexa, ligar a luz da cozinha**.

### Materiais Utilizados:

Foram utilizadas 3 lâmpadas de **LED** nas cores verde, amarelo e azul, 3 **resistores** equiparentes, **ESP32 WiFi**, **Display Oled Ssd1306**, uma **protoboard** de 400 pinos e cabos **jumpers**.

Além disso, para a conexão com a Alexa App, foi utilizada um serviço de controle de dispositivos IOT, o [Sinric Pro](https://sinric.pro/pt-index.html).

### Conclusão

Para finalizar, algumas informações abaixo:

 - Cômodos (Cozinha, sala e quarto)
 - Dados (conexão WiFi, Keys do Sinric Pro)
 - Utilizado o Arduino IDE 2.0.2 para codificar
 
 Pacotes:
 - Arduino.h
 - WiFi.h
 - Wire.h
 - SinricPro.h
 - SinricProSwitch.h
 - SSD1306Wire.h
