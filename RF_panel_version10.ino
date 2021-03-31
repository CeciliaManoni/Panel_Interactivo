// Incluimos las librerías necesarias
  #include <SPI.h> // Librería para la comunicación SPI
  #include <nRF24L01.h> // Librerías para el funcionamiento del módulo NRF24L01
  #include <RF24.h>
  #include<DFRobotDFPlayerMini.h>
  #include <PCF8574.h>
  #include <Wire.h>
   #include <Adafruit_NeoPixel.h>  //carga la libreria para LEDs inteligentes
  
  // Declaramos los pines de control del módulo NRF24L01
  #define CE 9
  #define CSN 10
  #define pinFunction A1
  #define pinAccessory A0
  #define NUMPIXELS 1  // el numero de leds que quiero usar de la tira de leds  
  
  
  RF24 radio(CE, CSN); // Se crea el objeto tipo RF24
  
  PCF8574 pcf(0x20);  // Se crea el objeto tipo PCF para comunicacion I2C
  
  Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, 7, NEO_GRB + NEO_KHZ800); //define objetos pixels que son las tira de leds
  Adafruit_NeoPixel pixels3 = Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800); 
  Adafruit_NeoPixel pixels4 = Adafruit_NeoPixel(NUMPIXELS, 5, NEO_GRB + NEO_KHZ800); 
  Adafruit_NeoPixel pixels5 = Adafruit_NeoPixel(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800); 
  Adafruit_NeoPixel pixels6 = Adafruit_NeoPixel(NUMPIXELS, 3, NEO_GRB + NEO_KHZ800); 
  Adafruit_NeoPixel pixels7 = Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800); 
  
  DFRobotDFPlayerMini myDFPlayer; //Objeto de la librería para poder usar sus funciones

  
  const uint64_t canal[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL}; // Se declaran los canales (64 bits en hexadecimal) para transmisión RF
  
  unsigned int data_PT[1]; // Variable que enviamos mediante RF desde el panel hacia el tablero 
  unsigned int data_TP[2]; // Variable que recibimos mediante RF desde el tablero hacia el panel 
  
  int realSecuence[]={0,0,0,0,0,0,0,0,0,0}; // Arreglo para almacenar la respuesta del paciente
  int patientSecuence[]={0,0,0,0,0,0,0,0,0,0}; // Arreglo para almacenar la secuencia real a repetir
  int maxLevel = 10; // Cantidad máxima de niveles
  bool control = true; // Variables de control para el tablero y la colchoneta
  bool control_C = true;
  bool diferentes = false;
  bool diferentes_C = false;
  bool accessory = true;
  int encendido = 1;
  int estado = 1;
  int estado_S = 1;
  
  void setup()
  {
      // Comunicación serie
      Serial.begin(9600);

      // Configuración de pines
      pinMode(2, OUTPUT); // Pin digital 2 como salida  
      pinMode(3, OUTPUT); // Pin digital 3 como salida
      pinMode(7, OUTPUT); // Pin digital 3 como salida   
      pinMode(4, OUTPUT); // Pin digital 2 como salida  
      pinMode(5, OUTPUT); // Pin digital 3 como salida
      pinMode(6, OUTPUT); // Pin digital 3 como salida    
      pinMode(pinFunction, INPUT); // Pin digital 7 como entrada
      pinMode(pinAccessory, INPUT); // Pin digital 8 como entrada
      pinMode(CSN, OUTPUT); // Pin digital 10 como salida
      
      // Comunicación por radiofrecuencia
      radio.begin();  // Inicialización de la comunicación RF
      radio.setRetries(15,15); // Establece el retardo y el número de reintentos tras fallo en la comunicación RF
      radio.openWritingPipe(canal[0]); // Abro el canal "0" para escribir
      radio.openReadingPipe(1,canal[1]); // Abro el canal "1" para leer

      // Comunicación con módulo extensor de pines
      pcf.begin();
      Wire.begin();

      // Configuración de módulo reproductor de mp3
      myDFPlayer.begin(Serial);
      myDFPlayer.volume(10);
      myDFPlayer.play(encendido);
      delay(1000); //para que se logre escuchar el sonido de encendido
  }
 
  void loop()
  {
    // Lectura del interruptor accesorio para ir a la función que corresponde
    if(digitalRead(pinAccessory)){
      tablero();
    }
    else{
      colchoneta();
    }        
  }

//---------------------- Funciones accesorio TABLERO -------------------//
  void tablero(){
    // Lectura del interruptor modo de funcionamiento para ir a la función que corresponde
    if(digitalRead(pinFunction)){
        sonidos_T();
    }
    else{
        simon_T();
    }

  }

    void simon_T(){

      delay(20); // Doy tiempo de lectura al receptor A
      radio.stopListening(); // Paro de escuchar por el canal "1"

     // ************************ PARTE CORRESPONDIENTE A LA EMISIÓN PANEL ****************************
            
      data_PT[0] = 0; // La variable vale 0
                 
      // Se envía el valor de la variable data_PT[0] a través de RF
      radio.write(data_PT, sizeof(data_PT));
      delay(20); // Doy tiempo de escritura al emisor A     

      // ************************ PARTE CORRESPONDIENTE A LA RECEPCIÓN PANEL ****************************
      
    randomSeed(millis());    
    Serial.print("secuencia real:");
    for(int i=0; i<maxLevel; i++){  
      realSecuence[i]= random(2,8);
      Serial.print(realSecuence[i]);
      Serial.print(", ");   
    }
    Serial.println("termino la serie real.");

    for(int j=0;j<maxLevel;j++){
      for(int k=0; k<j+1; k++){
        switch(realSecuence[k]){
            case 2:
                      pixels2.setPixelColor(0, pixels2.Color(0,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels2.show(); // Actualiza los leds.
                      delay(1500);
                      myDFPlayer.play(2);
                      delay(1500);
                      pixels2.setPixelColor(0, pixels2.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels2.show(); // Actualiza los leds.
                      delay(500);
            break;
            case 3:
                      pixels3.setPixelColor(0, pixels3.Color(255,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels3.show(); // Actualiza los leds.
                      delay(1500);
                      myDFPlayer.play(3);
                      delay(1500);
                      pixels3.setPixelColor(0, pixels3.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels3.show(); // Actualiza los leds.
                      delay(500);
            break;
            case 4:
                      pixels4.setPixelColor(0, pixels4.Color(0,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels4.show(); // Actualiza los leds.
                      delay(1500);
                      myDFPlayer.play(4);
                      delay(1500);
                      pixels4.setPixelColor(0, pixels4.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels4.show(); // Actualiza los leds.
                      delay(500);
            break;
            case 5:
                      pixels5.setPixelColor(0, pixels5.Color(255,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels5.show(); // Actualiza los leds.
                      delay(1500);
                      myDFPlayer.play(5);
                      delay(1500);
                      pixels5.setPixelColor(0, pixels5.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels5.show(); // Actualiza los leds.
                      delay(500);
            break;
            case 6:
                      pixels6.setPixelColor(0, pixels6.Color(0,255,255)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels6.show(); // Actualiza los l
                      delay(1500);
                      myDFPlayer.play(6);
                      delay(1500);
                      pixels6.setPixelColor(0, pixels6.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels6.show(); // Actualiza los leds.
                      delay(500);
            break;
            case 7:
                      pixels7.setPixelColor(0, pixels7.Color(255,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels7.show(); // Actualiza los leds.
                      delay(1500);
                      myDFPlayer.play(7);
                      delay(1500);
                      pixels7.setPixelColor(0, pixels7.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels7.show(); // Actualiza los leds.
                      delay(500);
            break;
            default:
            break;
          }
      }
    
      radio.startListening(); // Comienzo a escuchar por el canal "1"
  
      for(int k=0; k<j+1; k++){
       while (control){
          // corrobora que no se haya cambiado el accesorio tablero
          if(digitalRead(pinAccessory) == false){
            control = false;
            k = maxLevel+1;
            j = maxLevel;
          }

          if(digitalRead(pinFunction)){
            control = false;
            k = maxLevel+1;
            j = maxLevel;
          }
            
          radio.read(data_TP, sizeof(data_TP));  
          delay(20);  
          Serial.print("Simon. Lo que llego en while control: ");
          Serial.print(data_TP[0]);
          Serial.print(", ");
          Serial.println(data_TP[1]);

          while(data_TP[0] == 1){
              switch(data_TP[1]){
                  case 2:
                            pixels2.setPixelColor(0, pixels2.Color(0,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels2.show(); // Actualiza los leds.
                            if(estado_S == 1){
                            myDFPlayer.play(2);
                            delay(1500);
                            estado_S=0;
                            }
                            
                  break;
                  case 3:
                            pixels3.setPixelColor(0, pixels3.Color(255,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels3.show(); // Actualiza los leds.
                            if(estado_S == 1){
                            myDFPlayer.play(3);
                            delay(1500);
                            estado_S=0;
                            }
                           
                  break;
                  case 4:
                            pixels4.setPixelColor(0, pixels4.Color(0,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels4.show(); // Actualiza los leds.
                            if(estado_S == 1){
                            myDFPlayer.play(4);
                            delay(1500);
                            estado_S=0;
                            }
 
                       break;
                  case 5:
                            pixels5.setPixelColor(0, pixels5.Color(255,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels5.show(); // Actualiza los leds.
                            if(estado_S == 1){
                            myDFPlayer.play(5);
                            delay(1500);
                            estado_S=0;
                            }
                            
                  break;
                  case 6:
                            pixels6.setPixelColor(0, pixels6.Color(0,255,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels6.show(); // Actualiza los leds.
                            if(estado_S == 1){
                            myDFPlayer.play(6);
                            delay(1500);
                            estado_S=0;
                            }
                           
                  break;
                  case 7:
                            pixels7.setPixelColor(0, pixels7.Color(255,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels7.show(); // Actualiza los leds.
                            if(estado_S == 1){
                            myDFPlayer.play(7);
                            delay(1500);
                            estado_S=0;
                            }
                            
                  break;
                  default:
                  break;
                }
            patientSecuence[k]= data_TP[1];
            control = false;
            //myDFPlayer.play(data_TP[1]);
            radio.read(data_TP, sizeof(data_TP));   
            delay(20); 
            Serial.print("Lo que llego en while nuevo: ");
            Serial.print(data_TP[0]);
            Serial.print(", ");
            Serial.println(data_TP[1]); 
          }
        }  
                          pixels2.setPixelColor(0, pixels2.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels2.show(); // Actualiza los leds.
                          pixels3.setPixelColor(0, pixels3.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels3.show(); // Actualiza los leds.
                          pixels4.setPixelColor(0, pixels4.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels4.show(); // Actualiza los leds.
                          pixels5.setPixelColor(0, pixels5.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels5.show(); // Actualiza los leds.
                          pixels6.setPixelColor(0, pixels6.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels6.show(); // Actualiza los leds.
                          pixels7.setPixelColor(0, pixels7.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels7.show(); // Actualiza los leds.
                          estado_S = 1;
               
        
        if(patientSecuence[k]==realSecuence[k]){
         control = true;  
         Serial.println("iguales");
        }
        else{
         Serial.println("diferentes");
         diferentes = true;
         k = j+1;         
        }
      }

      if(diferentes){
        myDFPlayer.play(8);
        delay(1500);
        Serial.println("Comencemos de nuevo.");
        j = maxLevel;
        control = true;
        diferentes = false;
      }
      else{
        if(j<(maxLevel-1)){
          myDFPlayer.play(9);
          delay(1500);
          Serial.println("Sumemos mas colores."); 
          }
        else{
          myDFPlayer.play(10);
          delay(3500);
          Serial.println("comencemos con una secuencia de colores nueva.");
          }
      }
      delay(800);
    }    
  }

  void sonidos_T(){
    Serial.println("Tablero. sonidos");
       
      // ************************ PARTE CORRESPONDIENTE A LA RECEPCIÓN PANEL ****************************
     
      radio.startListening(); // Comienzo a escuchar por el canal "1"
     
      // Siempre que haya información disponible vía RF...   
      while(radio.available())
      {
        // Se recibe el valor de la variable estado_pulsador_B[0] a través de RF
        radio.read(data_TP, sizeof(data_TP));    
        
        Serial.print("Sonidos.  Lo que llego: ");
        Serial.print(data_TP[0]);
        Serial.print(", ");
        Serial.println(data_TP[1]);
        
        // Si el valor de la variable data_TP[0] es igual a "1" se enciende el LED
        if (data_TP[0] == 1)
        {
          switch(data_TP[1]){
              case 2:   pixels2.setPixelColor(0, pixels2.Color(0,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                        pixels2.show(); // Actualiza los leds.         
                        if(estado==1){
                        myDFPlayer.play(11);
                        delay(1500);
                        estado=0;
                        }
              break;
              case 3:
                        pixels3.setPixelColor(0, pixels3.Color(255,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                        pixels3.show(); // Actualiza los leds.     
                        if(estado==1){
                        myDFPlayer.play(12);
                        delay(1500);
                        estado=0;
                        }
              break;
              case 4:
                        pixels4.setPixelColor(0, pixels4.Color(0,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                        pixels4.show(); // Actualiza los leds.     
                        if(estado==1){
                        myDFPlayer.play(13);
                        delay(1500);
                        estado=0;
                        }
              break;
              case 5:
                        pixels5.setPixelColor(0, pixels5.Color(255,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                        pixels5.show(); // Actualiza los leds.     
                        if(estado==1){
                        myDFPlayer.play(14);
                        delay(1500);
                        estado=0;
                        }
              break;
              case 6:
                        pixels6.setPixelColor(0, pixels6.Color(0,255,255)); // le asigno un color a cada led, en este caso todos iguales.
                        pixels6.show(); // Actualiza los leds.     
                        if(estado==1){
                        myDFPlayer.play(15);
                        delay(1500);
                        estado=0;
                        }
              break;
              case 7:
                        pixels7.setPixelColor(0, pixels7.Color(255,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                        pixels7.show(); // Actualiza los leds.     
                        if(estado==1){
                        myDFPlayer.play(16);
                        delay(1500);
                        estado=0;
                        }
              break;
        //}
        }
        }
        // Si el valor de la variable data_TP[0] es igual a "0" se apaga el LED
        else
        {
         
                          pixels2.setPixelColor(0, pixels2.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels2.show(); // Actualiza los leds.
                          pixels3.setPixelColor(0, pixels3.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels3.show(); // Actualiza los leds.
                          pixels4.setPixelColor(0, pixels4.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels4.show(); // Actualiza los leds.
                          pixels5.setPixelColor(0, pixels5.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels5.show(); // Actualiza los leds.
                          pixels6.setPixelColor(0, pixels6.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels6.show(); // Actualiza los leds.
                          pixels7.setPixelColor(0, pixels7.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels7.show(); // Actualiza los leds.
                          estado = 1;
               
       
        }      
      }    
      delay(20); // Doy tiempo de lectura al receptor A
     
      radio.stopListening(); // Paro de escuchar por el canal "1"
     
     
      // ************************ PARTE CORRESPONDIENTE A LA EMISIÓN PANEL ****************************
            
      data_PT[0] = 1; // La variable vale 1
                 
      // Se envía el valor de la variable data_PT[0] a través de RF
      radio.write(data_PT, sizeof(data_PT));
      delay(20); // Doy tiempo de escritura al emisor A     
      
  }
//---------------------------------- Fin tablero ------------------------------------//



//-------------------------------- Funciones accesorio COLCHONETA -------------------------------//
  void colchoneta(){
    
    if(digitalRead(pinFunction)){
        sonidos_C();
    }
    else{
        simon_C();
    }
  }

  void simon_C(){
    Serial.println("colchoneta. simon");
    Serial.print("secuencia real:");
    randomSeed(analogRead(A2));
    for(int i=0; i<maxLevel; i++){            
      realSecuence[i]= random(2,8);
      Serial.print(realSecuence[i]);
      Serial.print(", ");    
    }
    Serial.println("termino la serie real");
    
    for(int j=0;j<maxLevel;j++){
      for(int k=0; k<j+1; k++){
         switch(realSecuence[k]){
            case 2:
                      pixels2.setPixelColor(0, pixels2.Color(0,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels2.show(); // Actualiza los leds.
                      myDFPlayer.play(2);
                      delay(1500);
                      pixels2.setPixelColor(0, pixels2.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels2.show(); // Actualiza los leds.
                      delay(500);
            break;
            case 3:
                      pixels3.setPixelColor(0, pixels3.Color(255,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels3.show(); // Actualiza los leds.
                      myDFPlayer.play(3);
                      delay(1500);
                      pixels3.setPixelColor(0, pixels3.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels3.show(); // Actualiza los leds.
                      delay(500);
                    
            break;
            case 4:
                      pixels4.setPixelColor(0, pixels4.Color(0,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels4.show(); // Actualiza los leds.
                      myDFPlayer.play(4);
                      delay(1500);
                      pixels4.setPixelColor(0, pixels4.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels4.show(); // Actualiza los leds.
                      delay(500);
                 break;
            case 5:
                      pixels5.setPixelColor(0, pixels5.Color(255,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels5.show(); // Actualiza los leds.
                      myDFPlayer.play(5);
                      delay(1500);
                      pixels5.setPixelColor(0, pixels5.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels5.show(); // Actualiza los leds.
                      delay(500);
                   
            break;
            case 6:
                      pixels6.setPixelColor(0, pixels6.Color(0,255,255)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels6.show(); // Actualiza los l
                      myDFPlayer.play(6);
                      delay(1500);
                      pixels6.setPixelColor(0, pixels6.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels6.show(); // Actualiza los leds.
                      delay(500);
            break;
            case 7:
                      pixels7.setPixelColor(0, pixels7.Color(255,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels7.show(); // Actualiza los leds.
                      myDFPlayer.play(7);
                      delay(1500);
                      pixels7.setPixelColor(0, pixels7.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                      pixels7.show(); // Actualiza los leds.
                      delay(500);
            break;
            default:
            break;
          }
      }
  
      for(int k=0; k<j+1; k++){
        while (control_C){
          for(int i=2; i<8;i++){
              while(pcf.readButton(i)){
               switch(i){
                  case 2:
                            pixels2.setPixelColor(0, pixels2.Color(0,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels2.show(); // Actualiza los leds.
                            myDFPlayer.play(2);
                            delay(1000);// se utiliza para que se escuche el sonido sin que se vuelva a repetir al seguir teniendo el pulsador apretado
                           
                  break;
                  case 3:
                            pixels3.setPixelColor(0, pixels3.Color(255,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels3.show(); // Actualiza los leds.
                            myDFPlayer.play(3);
                            delay(1000);
                            
                  break;
                  case 4:
                            pixels4.setPixelColor(0, pixels4.Color(0,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels4.show(); // Actualiza los leds.
                            myDFPlayer.play(4);
                            delay(1000);
                            
                  break;
                  case 5:
                            pixels5.setPixelColor(0, pixels5.Color(255,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels5.show(); // Actualiza los leds.
                            myDFPlayer.play(5);
                            delay(1000);
                            
                  break;
                  case 6:
                            pixels6.setPixelColor(0, pixels6.Color(0,255,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels6.show(); // Actualiza los l
                            myDFPlayer.play(6);
                            delay(1000);
                            
                  break;
                  case 7:
                            pixels7.setPixelColor(0, pixels7.Color(255,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels7.show(); // Actualiza los leds.
                            myDFPlayer.play(7);
                            delay(1000);
                            
                  break;
                  default:
                  break;
                }
              control_C=false;
              patientSecuence[k]=i;
              Serial.print("secuencia paciente: ");
              Serial.println(patientSecuence[k]);
            }
             switch(i){
                case 2:
                          pixels2.setPixelColor(0, pixels2.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels2.show(); // Actualiza los leds.
                break;
                case 3:
                          pixels3.setPixelColor(0, pixels3.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels3.show(); // Actualiza los leds.
                break;
                case 4:
                          pixels4.setPixelColor(0, pixels4.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels4.show(); // Actualiza los leds.
                     break;
                case 5:
                          pixels5.setPixelColor(0, pixels5.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels5.show(); // Actualiza los leds.
                break;
                case 6:
                          pixels6.setPixelColor(0, pixels6.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels6.show(); // Actualiza los leds.
                break;
                case 7:
                        pixels7.setPixelColor(0, pixels7.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                         pixels7.show(); // Actualiza los leds.
                break;
                default:
                break;
              }
          }   
        } 
        if(patientSecuence[k]==realSecuence[k]){
         control_C = true;  
         Serial.println("iguales");
        }
        else{
         Serial.println("diferentes");
         diferentes_C = true;
         k = j+1;         
        } 
      }
      if(diferentes_C){
        myDFPlayer.play(8);
        delay(1500);
        Serial.println("comencemos de nuevo.");
        j = maxLevel;
        control_C = true;
        diferentes_C = false;
      }
      else{
        if(j<(maxLevel-1)){
          myDFPlayer.play(9);
          delay(1500);
          Serial.println("Sumemos mas colores."); 
          }
        else{
          myDFPlayer.play(10);
          delay(3500);
          Serial.println("comencemos con una secuencia de colores nueva.");
          }
      }
    delay (800);
    }
  }

  void sonidos_C(){   
    Serial.println("colchoneta. sonidos");
     for(int i=2; i<8;i++){
      if(pcf.readButton(i)){
          switch(i){
                  case 2:
                            pixels2.setPixelColor(0, pixels2.Color(0,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels2.show(); // Actualiza los leds.
                            myDFPlayer.play(11);
                            delay(1000);
                           
                  break;
                  case 3:
                            pixels3.setPixelColor(0, pixels3.Color(255,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels3.show(); // Actualiza los leds.
                            myDFPlayer.play(12);
                            delay(1000);
                  break;
                  case 4:
                            pixels4.setPixelColor(0, pixels4.Color(0,255,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels4.show(); // Actualiza los leds.
                            myDFPlayer.play(13);
                            delay(1000);
                  break;
                  case 5:
                            pixels5.setPixelColor(0, pixels5.Color(255,0,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels5.show(); // Actualiza los leds.
                            myDFPlayer.play(14);
                            delay(1000);
                  break;
                  case 6:
                            pixels6.setPixelColor(0, pixels6.Color(0,255,255)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels6.show(); // Actualiza los l
                            myDFPlayer.play(15);
                            delay(1000);
                  break;
                  case 7:
                            pixels7.setPixelColor(0, pixels7.Color(255,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                            pixels7.show(); // Actualiza los leds.
                            myDFPlayer.play(16);
                            delay(1000);
                            
                  break;
                  default:
                  break;
                }
        delay(500);
      }
      else{
          switch(i){
                case 2:
                          pixels2.setPixelColor(0, pixels2.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels2.show(); // Actualiza los leds.
                break;
                case 3:
                          pixels3.setPixelColor(0, pixels3.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels3.show(); // Actualiza los leds.
                break;
                case 4:
                          pixels4.setPixelColor(0, pixels4.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels4.show(); // Actualiza los leds.
                     break;
                case 5:
                          pixels5.setPixelColor(0, pixels5.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels5.show(); // Actualiza los leds.
                break;
                case 6:
                          pixels6.setPixelColor(0, pixels6.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels6.show(); // Actualiza los leds.
                break;
                case 7:
                          pixels7.setPixelColor(0, pixels7.Color(0,0,0)); // le asigno un color a cada led, en este caso todos iguales.
                          pixels7.show(); // Actualiza los leds.
                break;
                default:
                break;
              }
           }
    }
   
  }

//---------------------------------- Fin colchoneta ------------------------------------//
  
  
  
 
