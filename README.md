

## Projeto de Casa Inteligente com ESP32
### Descrição:

O objetivo do projeto é integrar um sistema de iluminação via LEDs através da assistente virtual Alexa pelo App no celular. Basta falar, por exemplo: **Alexa, ligar a luz da cozinha**.

**Atualização:** Foi integrado no projeto o protocolo MQTT onde, através do aplicativo [MQTT Dash](https://play.google.com/store/apps/details?id=net.routix.mqttdash&hl=pt_BR&gl=US), é possível ascender as lâmpadas e controlar as intensidades das mesmas com o envio de PWM aos Leds.

**MQTT configuração para utilização:**

 - MQTT Server (broker.hivemq.com)
 - Porta (1883)
 - Conexão WiFi padrão
 - Tópicos: 
	 - Snarloff/sala
	 - Snarloff/quarto
	 - Snarloff/cozinha
	 - Snarloff/intensidade
	 - Snarloff/intensidadequarto
	 - Snarloff/intensidadecozinha
	
![enter image description here](https://i.imgur.com/h6o0XE3.jpg)

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
 - PubSubClient.h
 - analogWrite.h
 

![Imagem do sistema pronto](https://i.imgur.com/dBPvS1R.jpg)

![gif](https://media.giphy.com/media/sOpYs0fNMMMSlWarwM/giphy-downsized-large.gif)
