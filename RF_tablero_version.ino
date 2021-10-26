// Incluimos las librerías necesarias
  #include <SPI.h> // Librería para la comunicación SPI
  // Librerías para el funcionamiento del módulo NRF24L01
  #include <nRF24L01.h>
  #include <RF24.h>
 
  // Declaramos los pines de control del módulo NRF24L01
  #define CE 9
  #define CSN 10
 
  // Se crea el objeto tipo RF24
  RF24 radio(CE, CSN);
 
  // Se declaran los canales (64 bits en hexadecimal) para transmisión RF
  const uint64_t canal[2] = {0xF0F0F0F0E1LL,0xF0F0F0F0D2LL};
 
  // Variable que enviamos mediante RF desde el tablero a la pared
  unsigned int data_TP[2];
 
  // Variable que recibimos mediante RF desde el panel al tablero
  unsigned int data_PT[1];

  int btn = 2; // Pin digital 2 para el pulsador
  int btn2 = 3; // Pin digital 3 para el pulsador
  int btn3 = 4; // Pin digital 4 para el pulsador
  int btn4 = 5; // Pin digital 5 para el pulsador
  int btn5 = 6; // Pin digital 6 para el pulsador
  int btn6 = 7; // Pin digital 6 para el pulsador 
  void setup()
  {
      Serial.begin(9600);
      pinMode(btn, INPUT); // Pin digital 2 como salida    
      pinMode(btn2, INPUT); // Pin digital 3 como entrada
      pinMode(btn3, INPUT); // Pin digital 4 como entrada
      pinMode(btn4, INPUT); // Pin digital 5 como entrada
      pinMode(btn5, INPUT); // Pin digital 6 como entrada
      pinMode(btn6, INPUT); // Pin digital 6 como entrada
      pinMode(CSN, OUTPUT); // Pin digital 10 como salida
     
      radio.begin();  // Inicialización de la comunicación RF
     
      
      // Establece el retardo y el número de reintentos tras fallo en la comunicación RF
      radio.setRetries(5,5);
      
     
      radio.openWritingPipe(canal[1]); // Abro el canal "1" para escribir
      radio.openReadingPipe(1,canal[0]); // Abro el canal "0" para leer
  }
 
  void loop()
  {
      // ************************ PARTE CORRESPONDIENTE A LA RECEPCIÓN tablero ****************************
      radio.startListening(); // Comienzo a escuchar por el canal "0"
      
      // Siempre que haya información disponible vía RF...   
      while(radio.available())
      {
        // Se recibe el valor de la variable estado_pulsador_A[0] a través de RF
        radio.read(data_PT, sizeof(data_PT));    
        
      }
      delay(20); // Doy tiempo de lectura al receptor B
     
      radio.stopListening(); // Paro de escuchar por el canal "0"
       // Si el valor de la variable estado_pulsador_A[0] es igual a "1" se enciende el LED
        if (data_PT[0] == 1)
        {
          sonidos();
        }
        else
        {
          simon();
        }   
         
  }
  void simon(){
    Serial.println("simon");
    for(int i=2; i<8;i++){ 
          while(digitalRead(i)){
            data_TP[0] = 1; // La variable vale 1
            data_TP[1] = i;
            radio.write(data_TP, sizeof(data_TP));
            delay(20);
          }
            data_TP[0] = 0; // La variable vale 0
            data_TP[1] = i;
            radio.write(data_TP, sizeof(data_TP));
            delay(20);  
        }   
    }
    
  void sonidos(){
       Serial.println("sonidos");
   for(int i=2; i<8; i++){
       if(digitalRead(i)){
       data_TP[0]=1;
       data_TP[1]=i;   
       } 
       else{
        data_TP[0]=0;
      }   
    }    
      // Se envía el valor de la variable estado_pulsador_B[0] a través de RF
      radio.write(data_TP, sizeof(data_TP));
      delay(20); // Doy tiempo de escritura al emisor B   
    }  
    
