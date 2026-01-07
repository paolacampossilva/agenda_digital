#include<LiquidCrystal.h>
  //Inicializando as entradas do lcd
  LiquidCrystal lcd(2,3,4,5,6,7);
  int s,m,h,a,d,state,state1,state2,dg,cnt,dt,mo;
  char months[13]={' ','1','2','3','4','5','6','7','8','9','10','11','12'};
  int l[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};

  //Inicializando cada barra
  byte bar1[8] = 
  {
          B11100,
          B11110,
          B11110,
          B11110,
          B11110,
          B11110,
          B11110,
          B11100
  };
  byte bar2[8] =
  {
          B00111,
          B01111,
          B01111,
          B01111,
          B01111,
          B01111,
          B01111,
          B00111
  };
  byte bar3[8] =
  {
          B11111,
          B11111,
          B00000,
          B00000,
          B00000,
          B00000,
          B11111,
          B11111
  };
  byte bar4[8] =
  {
          B11110,
          B11100,
          B00000,
          B00000,
          B00000,
          B00000,
          B11000,
          B11100
  };
  byte bar5[8] =
  {
          B01111,
          B00111,
          B00000,
          B00000,
          B00000,
          B00000,
          B00011,
          B00111
  };
  byte bar6[8] =
  {
          B00000,
          B00000,
          B00000,
          B00000,
          B00000,
          B00000,
          B11111,
          B11111
  };
  byte bar7[8] =
  {
          B00000,
          B00000,
          B00000,
          B00000,
          B00000,
          B00000,
          B00111,
          B01111
  };
  byte bar8[8] =
  {
          B11111,
          B11111,
          B00000,
          B00000,
          B00000,
          B00000,
          B00000,
          B00000
  };

  //SetUp Sensor de Temperatura
  const int sensorPin = A0;
  float vSensor,temperaturaC;

  //SetUp Buzzer
  const int buzzer = 11;
  int tempo; // velocidade da musica
  #define NOTE_B0  31
  #define NOTE_C1  33
  #define NOTE_CS1 35
  #define NOTE_D1  37
  #define NOTE_DS1 39
  #define NOTE_E1  41
  #define NOTE_F1  44
  #define NOTE_FS1 46
  #define NOTE_G1  49
  #define NOTE_GS1 52
  #define NOTE_A1  55
  #define NOTE_AS1 58
  #define NOTE_B1  62
  #define NOTE_C2  65
  #define NOTE_CS2 69
  #define NOTE_D2  73
  #define NOTE_DS2 78
  #define NOTE_E2  82
  #define NOTE_F2  87
  #define NOTE_FS2 93
  #define NOTE_G2  98
  #define NOTE_GS2 104
  #define NOTE_A2  110
  #define NOTE_AS2 117
  #define NOTE_B2  123
  #define NOTE_C3  131
  #define NOTE_CS3 139
  #define NOTE_D3  147
  #define NOTE_DS3 156
  #define NOTE_E3  165
  #define NOTE_F3  175
  #define NOTE_FS3 185
  #define NOTE_G3  196
  #define NOTE_GS3 208
  #define NOTE_A3  220
  #define NOTE_AS3 233
  #define NOTE_B3  247
  #define NOTE_C4  262
  #define NOTE_CS4 277
  #define NOTE_D4  294
  #define NOTE_DS4 311
  #define NOTE_E4  330
  #define NOTE_F4  349
  #define NOTE_FS4 370
  #define NOTE_G4  392
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_AS4 466
  #define NOTE_B4  494
  #define NOTE_C5  523
  #define NOTE_CS5 554
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define NOTE_F5  698
  #define NOTE_FS5 740
  #define NOTE_G5  784
  #define NOTE_GS5 831
  #define NOTE_A5  880
  #define NOTE_AS5 932
  #define NOTE_B5  988
  #define NOTE_C6  1047
  #define NOTE_CS6 1109
  #define NOTE_D6  1175
  #define NOTE_DS6 1245
  #define NOTE_E6  1319
  #define NOTE_F6  1397
  #define NOTE_FS6 1480
  #define NOTE_G6  1568
  #define NOTE_GS6 1661
  #define NOTE_A6  1760
  #define NOTE_AS6 1865
  #define NOTE_B6  1976
  #define NOTE_C7  2093
  #define NOTE_CS7 2217
  #define NOTE_D7  2349
  #define NOTE_DS7 2489
  #define NOTE_E7  2637
  #define NOTE_F7  2794
  #define NOTE_FS7 2960
  #define NOTE_G7  3136
  #define NOTE_GS7 3322
  #define NOTE_A7  3520
  #define NOTE_AS7 3729
  #define NOTE_B7  3951
  #define NOTE_C8  4186
  #define NOTE_CS8 4435
  #define NOTE_D8  4699
  #define NOTE_DS8 4978
  #define REST 0
  //Ativadores
  const int modo = 12;
  const int jump = 8;
  const int pause = 9;
  const int release = 10; 
  int tipo_clima,selecao_musica,pag = 0;
  bool stop = false;
  //tratamento de debouce
  unsigned long debounceDelay = 50;
  unsigned long lastDebounceTime = 0;

  void setup()
  {
    Serial.begin(9600);
    //Dando um segmento para cada barra
    lcd.createChar(1,bar1);
    lcd.createChar(2,bar2);
    lcd.createChar(3,bar3);
    lcd.createChar(4,bar4);
    lcd.createChar(5,bar5);
    lcd.createChar(6,bar6);
    lcd.createChar(7,bar7);
    lcd.createChar(8,bar8);

    state=1;
    state1=1;
    state2=1;
    //Coordenadas de cada byte
    lcd.begin(16, 2);
    pinMode(8,INPUT);
    pinMode(9,INPUT);
    pinMode(10,INPUT);
    s=0;
    m=0;
    h=0;
    dt=1;
    mo=1;
  }

  void custom0(int col)
  { //Segmentos para o número 0
    lcd.setCursor(col, 0); 
    lcd.write(2);  
    lcd.write(8); 
    lcd.write(1);
    lcd.setCursor(col, 1); 
    lcd.write(2);  
    lcd.write(6);  
    lcd.write(1);
  }

  void custom1(int col)
  {
    lcd.setCursor(col,0);
    lcd.write(32);
    lcd.write(32);
    lcd.write(1);
    lcd.setCursor(col,1);
    lcd.write(32);
    lcd.write(32);
    lcd.write(1);
  }

  void custom2(int col)
  {
    lcd.setCursor(col,0);
    lcd.write(5);
    lcd.write(3);
    lcd.write(1);
    lcd.setCursor(col, 1);
    lcd.write(2);
    lcd.write(6);
    lcd.write(6);
  }

  void custom3(int col)
  {
    lcd.setCursor(col,0);
    lcd.write(5);
    lcd.write(3);
    lcd.write(1);
    lcd.setCursor(col, 1);
    lcd.write(7);
    lcd.write(6);
    lcd.write(1); 
  }

  void custom4(int col)
  {
    lcd.setCursor(col,0);
    lcd.write(2);
    lcd.write(6);
    lcd.write(1);
    lcd.setCursor(col, 1);
    lcd.write(32);
    lcd.write(32);
    lcd.write(1);
  }

  void custom5(int col)
  {
    lcd.setCursor(col,0);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.setCursor(col, 1);
    lcd.write(7);
    lcd.write(6);
    lcd.write(1);
  }

  void custom6(int col)
  {
    lcd.setCursor(col,0);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.setCursor(col, 1);
    lcd.write(2);
    lcd.write(6);
    lcd.write(1);
  }

  void custom7(int col)
  {
    lcd.setCursor(col+0,0);
    lcd.write(8);
    lcd.write(8);
    lcd.write(1);
    lcd.setCursor(col, 1);
    lcd.write(32);
    lcd.write(32);
    lcd.write(1);
  }

  void custom8(int col)
  {
    lcd.setCursor(col, 0); 
    lcd.write(2);  
    lcd.write(3); 
    lcd.write(1);
    lcd.setCursor(col, 1); 
    lcd.write(2);  
    lcd.write(6);  
    lcd.write(1);
  }

  void custom9(int col)
  {
    lcd.setCursor(col, 0); 
    lcd.write(2);  
    lcd.write(3); 
    lcd.write(1);
    lcd.setCursor(col, 1); 
    lcd.write(7);  
    lcd.write(6);  
    lcd.write(1);
  }

  void printNumber(int value, int col) {
    if (value == 0) {
      custom0(col);
    } if (value == 1) {
      custom1(col);
    } if (value == 2) {
      custom2(col);
    } if (value == 3) {
      custom3(col);
    } if (value == 4) {
      custom4(col);
    } if (value == 5) {
      custom5(col);
    } if (value == 6) {
      custom6(col);
    } if (value == 7) {
      custom7(col);
    } if (value == 8) {
      custom8(col);
    } if (value == 9) {
      custom9(col);
    }      
  }

  void loop(){
    if (digitalRead(modo) == HIGH){
      if ((millis() - lastDebounceTime) > debounceDelay) {
        pag = (pag + 1) % 3;
        lcd.clear();
        while (digitalRead(modo) == HIGH); // Espera soltar o botão
      }
    }
    if(digitalRead(8)&&state == 1){
      cnt++;     
      state = 0;
      cnt = cnt % 5;
    }
    else if(!digitalRead(8)&&state == 0)
      state = 1;
    if (digitalRead(9)&&state1 == 1){
        dg = 1;
        state1 = 0;
        
        }
    else if(!digitalRead(9)&&state1 == 0)
      state1 = 1;
    
    if(digitalRead(10)&&state2 == 1){
        dg = -1;
        state2 = 0;
        }
    else if(!digitalRead(10)&state2 == 0)
        state2 = 1;
    switch(cnt){
      case 2:
      m = m + dg;
      dg = 0;  if(m > 59){
      m = 0;}
      if(m < 0){
        m = 59;}
        break;
      case 1:
        h = h + dg;
        dg = 0;if(h > 23){
        h = h - 24;}
        if(h < 0){
        h = 23;}
        break;
      case 3:
        dt = dt + dg;
        dg = 0;if(dt > l[mo]){
        dt = l[mo];}
        if(dt < 1){
        dt = 1;}
        break;
      case 4:
        mo = mo + dg;
        dg = 0;if(mo > 12){
        mo = 1;
        }
      if(mo < 1)
        mo = 12;
      if(dt > l[mo]){
        dt=1;
        mo++;
        mo = (1 + (mo-1) % 12);
      }break;
    }
    if(s > 59){
        s = 0;
        m++;
      if(m > 59){
          m = 0;
        h++;
        
        if(h > 23){
            h = 0;
            dt++;
    
        if(dt > l[mo]){
            dt = 1;
            mo++;
          }
            if(mo > 12){
            mo = 1;
          }
        } 
      }
    }
    if (pag == 0){ //Relogio
      selecao_musica = 0;
      h = h;
      d =(h)%10;
      printNumber(d, 3);
      d =(h)/10;
      printNumber(d, 0);

      d = m % 10;
      printNumber(d, 10);
      d = m/10;
      printNumber(d, 7);
      lcd.setCursor(14, 0);
      lcd.print(s/10);
      lcd.print(s%10);
      lcd.print(dt%10);

      if(cnt == 0){
        s++;
        lcd.setCursor(6, 0);
        lcd.print(" ");
        lcd.setCursor(6, 1);
        lcd.print(" ");
        lcd.setCursor(13,0);
        lcd.print(" ");
        delay(500);
        lcd.setCursor(6, 0);
        lcd.print(".");
        lcd.setCursor(6, 1);
        lcd.print(".");
        lcd.setCursor(13,0);
        lcd.print(":");
        delay(500);
      }
    }
    else if (pag == 1){ // Temperatura
      //Temperatura
      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (digitalRead(jump) == HIGH) {
          tipo_clima += 1;
          if (tipo_clima > 2){
            tipo_clima = 0;
          }
      }
    }
      vSensor = analogRead(sensorPin);
      temperaturaC = ((vSensor/1023)*5) - 0.5; // Covertendo tensao para Celcius
      temperaturaC = temperaturaC * 100;// Converte Celcius para Tensão novamente
      //Opiniao sobre o clima
      lcd.setCursor(0,1);
      if (temperaturaC < 30 && temperaturaC > 20){
        lcd.print("Esta agradavel^^");
      }else if (temperaturaC >= 30 && temperaturaC < 40){
        lcd.print("Esta bem calor!");
      }else if(temperaturaC <= 20 && temperaturaC > 0){;
        lcd.print("Esta friozinho   ");
      }
      else if (temperaturaC <= 0){
        lcd.print("ESTA CONGELANDO!!");
      }else if (temperaturaC >= 40){
        lcd.print("EU VOU DERRETER!!!");
      }
      lcd.setCursor(0,0);//Ainda tem que definir!!!
      lcd.print("Temp: ");
      if (tipo_clima == 0){ //Celsius 
        lcd.print(temperaturaC,2);
        lcd.print(" C ");
      }else if (tipo_clima == 1){ //Kelvin
        temperaturaC = temperaturaC + 273,15;
        lcd.print(temperaturaC,2); // Celcius -> Kelvin
        lcd.print(" K");
      }else if (tipo_clima == 2){ // Fahrenheit
        temperaturaC = (temperaturaC*1.8) + 32;
        lcd.print(temperaturaC,2); // Celcius -> Fahrenheit
        lcd.print(" F ");
      }
      delay(500);
    }
    else if (pag == 2){
    while (stop) {
      if (selecao_musica < 0){
        selecao_musica = 0;
      }
    // primeiro caso -> volta a tocar:
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (digitalRead(release) == HIGH) {
            stop = false;
            lastDebounceTime = millis();
            // Não altera selecao_musica aqui, mantém a atual
            break;  // Sai do loop while imediatamente
        }
    }
    // segundo caso -> quer pular a musica
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (digitalRead(jump) == HIGH) {
            selecao_musica = (selecao_musica + 1) % 2;
            Serial.println("Pulando para musica: " + String(selecao_musica));
            stop = false;
            lastDebounceTime = millis();
            break;  // Sai do loop while imediatamente
        }
    }
    // terceiro caso -> voltar pro relogio
    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (digitalRead(modo) == HIGH) {
            selecao_musica = -1;
            stop = false;
            lastDebounceTime = millis();
            break;  // Sai do loop while imediatamente
          }
        }
    }
      int notes,wholenote,divider,noteDuration;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Tocando agora:");
      if (selecao_musica == 0){
        tempo = 144;
        int melody[] = {
            //Baseado no modelo em  https://www.flutetunes.com/tunes.php?id=192
            
            NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
            NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
            NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
            NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST,4,

            REST,8, NOTE_D5, 4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
            NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
            NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
            NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

            NOTE_E5,2, NOTE_C5,2,
            NOTE_D5,2, NOTE_B4,2,
            NOTE_C5,2, NOTE_A4,2,
            NOTE_B4,1,

            NOTE_E5,2, NOTE_C5,2,
            NOTE_D5,2, NOTE_B4,2,
            NOTE_C5,4, NOTE_E5,4, NOTE_A5,2,
            NOTE_GS5,1,

            NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
            NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
            NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
            NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST,4,

            REST,8, NOTE_D5, 4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
            REST,8, NOTE_E5, 4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
            REST,8, NOTE_B4, 4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
            REST,8, NOTE_C5, 4,  NOTE_A4,8,  NOTE_A4,4, REST, 4,

          };
          // "sizeof" fornece o número de bytes, cada valor int é composto por dois bytes (16 bits)
          // há dois valores por nota (altura e duração), portanto, para cada nota há quatro bytes
        notes=sizeof(melody)/sizeof(melody[0])/2; 
        wholenote = (60000 * 4) / tempo; // isso calcula a duração de uma nota inteira em ms (60s/tempo)*4 batidas
        lcd.setCursor(0,1);
        lcd.print("Tetris OST");
        divider = 0, noteDuration = 0;
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
          if (digitalRead(pause) == HIGH){
              stop = true;
              break;
            }
            // calcula duração de cada nota
            divider = melody[thisNote + 1];
          if (divider > 0) {
            // nota regular, apenas prossiga
            noteDuration = (wholenote) / divider;
          } 
          else if (divider < 0) {
            // as notas pontilhadas são representadas com durações negativas!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // aumenta a duração em metade para notas pontilhadas
          }
          // só tocamos a nota durante 90% da duração, deixando 10% como pausa
          tone(buzzer, melody[thisNote], noteDuration*0.9);
          // Espera pela duração especificada antes de tocar a próxima nota.
          delay(noteDuration);
          // pára a geração da forma de onda antes da nota seguinte.
          noTone(buzzer);
        } 
      }
      else if (selecao_musica == 1){
        tempo = 120;
        int melody[] = {
          // Baseado no modelo em https://musescore.com/user/202909/scores/1141521
          
          NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
          NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
          NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,

          NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
          NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
          NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
          
          NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
          NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

          NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
          NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,

          NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
          NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

          NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
          NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
        };
          // "sizeof" fornece o número de bytes, cada valor int é composto por dois bytes (16 bits)
          // há dois valores por nota (altura e duração), portanto, para cada nota há quatro bytes
        notes=sizeof(melody)/sizeof(melody[0])/2; 
        wholenote = (60000 * 4) / tempo; // isso calcula a duração de uma nota inteira em ms (60s/tempo)*4 batidas
        lcd.setCursor(0,1);
        lcd.print("Imperial March");
        divider = 0, noteDuration = 0;
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
          if (digitalRead(pause) == HIGH){
              stop = true;
              break;
            }
            // calcula duração de cada nota
            divider = melody[thisNote + 1];
          if (divider > 0) {
            // nota regular, apenas prossiga
            noteDuration = (wholenote) / divider;
          } 
          else if (divider < 0) {
            // as notas pontilhadas são representadas com durações negativas!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // aumenta a duração em metade para notas pontilhadas
          }
          // só tocamos a nota durante 90% da duração, deixando 10% como pausa
          tone(buzzer, melody[thisNote], noteDuration*0.9);
          // Espera pela duração especificada antes de tocar a próxima nota.
          delay(noteDuration);
          // pára a geração da forma de onda antes da nota seguinte.
          noTone(buzzer);
        }
      }
      
    }
  }
  
  /*
    Créditos!
    Relogio:
      O código do relogio em si é o mais complexo, tentamos faze-lo sem ajudas externas mas o código foi considerado ineficiente, dessa forma damos os créditos ao código de "Shubham Sutar"
        Seu trabalho pode ser encontrado em seu tinkercard: https://www.tinkercad.com/users/9xMBjV4qpZZ?type=circuits ou em seu canal do youtube "Technical Shubham"(https://www.youtube.com/@technicalshubham789)

    Musicas:
      Encontre mais musicas publicadas em: https://github.com/robsoncouto/arduino-songs por Robson Couto, 2019! Um grande obrigado pela biblioteca de músicas incriveis >:D
      
    Assistência: 
      Agradecemos ao Professor Amaury Antonio de Castro Junior, pela ajuda na resolução de alguns problemas do nosso código!
  */