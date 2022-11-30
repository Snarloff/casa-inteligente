

## Projeto de Casa Inteligente com ESP32 (Luís Estareli e Pedro Inocente)
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

Além disso, para a conexão com a Alexa App, foi utilizada um serviço de controle de dispositivos IOT, o [Sinric Pro](https://sinric.pro/pt-index.html), e o protocolo MQTT.

### Como utilizar (resumo)

Primeiramente, instale o software de desenvolvimento **Arduino IDE**. Dentro dele, configure a placa **ESP32** acrescentando a URL adicional `[https://dl.espressif.com/dl/package_esp32_index.json](https://dl.espressif.com/dl/package_esp32_index.json)` na configuração. Após selecionar a opção ESP32 Dev Module, instale as bibliotecas citadas na aba conclusão em `incluir biblioteca`.

Entre na plataforma **Sinric Pro**, crie sua conta e  adicione os dispositivos de acordo com os cômodos abaixos no formato SWITCH e pegue as **Keys**. No código, você irá ver partes faltando nas primeiras linhas, configure de acordo com sua configuração do Sinric e de Wi-Fi.

Observe no cabeçalho do código os pinos necessários e reserve-os para a utilização do código.
Já no aplicativo da Alexa, configure um novo plugue instalando o Sinric Pro. Ao conectar sua conta, você irá observar os Switchs, coloque-os como favoritos e configure novas rotinas para ativá-los. Para isso, crie a rotina e em *Adicionar ação*, selecione **Casa Inteligente**, selecione o plugue e coloque-o para ativar ou desativar, de acordo com sua necessidade.

No aplicativo do MQTT, clique no mais e configure com o IP e a Porta. Após isso, abra-o e clique novamente no mais e adicione um botão. Esse botão terá uma opção chamada **tópico**, e é lá que você irá colocar os tópicos citados lá em cima. Além disso, no on e off, coloque os valores **on** e **off** ao invés de 0 e 1.

Preste bem atenção! Esse é apenas um mini-tutorial avançado para a utilização do código, ao caso do não compreendimento total ou parcial do mesmo, busque ajuda externa em sites complementares.

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

Simulação (BETA): https://wokwi.com/projects/349702844559917651
