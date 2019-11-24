# Arduíno Uno
Testes de componentes para Arduíno Uno.

## Comunicação I2C
Funcionando para 1 arduino master + 2 arduinos slaves.

1 arduino master + 2 arduinos slaves + 1 sensor RFID ainda em construção...

## Comunicação Serial UART + Sensor Ultrasonico

Comunicação feita para que o arduino receba o dado do sensor ultrasônico e avise a Haspberry Pi de que algo em certa distância passou por ele.

## RFID
Funcionando para 3 sensores RFIDs.

Cada ID é armazenado em sua respectiva posição do vetor de Strings IDs[], assim mantendo o último valor armazenado na posição.

O pacote em String no formato "ID_1%ID_2%...%ID_N" é montado na variável de mesmo nome, pacote.

## Referências

RFID:

https://www.filipeflop.com/blog/controle-acesso-leitor-rfid-arduino/

https://www.youtube.com/watch?v=f_f_5cL0Pd0

https://github.com/miguelbalboa/rfid
