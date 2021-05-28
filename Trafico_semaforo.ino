#define ROJO 0
#define VERDE 1

int led_Verde = 8;
int led_Rojo = 9;
int led_Azul = 3; 
int PIR = 2; //PIN usado para Sensor

int estado = ROJO;
int estado_led_azul=0;

unsigned long tiempo_inicial;
unsigned long tiempo_actual;
unsigned long tiempo_infraccion;

void setup() 
{
   Serial.begin(9600);
   pinMode (led_Verde, OUTPUT);
   pinMode (led_Rojo, OUTPUT);
   pinMode (led_Azul, OUTPUT);
   pinMode(PIR,INPUT);
   // Capturar el primer millis
   tiempo_inicial= millis();
   digitalWrite (led_Rojo, HIGH); 
   digitalWrite (led_Verde, LOW);
   digitalWrite (led_Azul,LOW);
   Serial.println("Comienzo en Rojo");
}

void loop()
 {
   tiempo_actual= millis();
      
  if (estado_led_azul==1)
     if (tiempo_actual-tiempo_infraccion>1000)
     {
       Serial.println (tiempo_actual-tiempo_infraccion);
       digitalWrite(led_Azul,LOW);
       Serial.println ("Apago el led azul");
       estado_led_azul = 0;
     }
     
   switch (estado)
   {
    case ROJO:  if (tiempo_actual-tiempo_inicial>2000) 
                {
                  digitalWrite (led_Rojo, LOW); 
                  digitalWrite (led_Verde, HIGH);
                  tiempo_inicial= millis();
                  estado=VERDE;
                  Serial.println("Cambio a Verde");
                }
                else
                {
                  if (digitalRead(PIR)==HIGH && estado_led_azul==0) 
                  {
                    Serial.println ("Estoy en rojo y detecto movimiento. Enciendo led azul");
                    digitalWrite(led_Azul,HIGH);
                    estado_led_azul = 1;
                    tiempo_infraccion=millis();
                    Serial.println (tiempo_infraccion);
                  }
                }
                break;
    case VERDE: if (tiempo_actual-tiempo_inicial>2000) 
                {
                  digitalWrite (led_Rojo, HIGH); 
                  digitalWrite (led_Verde, LOW);
                  tiempo_inicial= millis();
                  estado=ROJO;
                  Serial.println("Cambio a Rojo");
                }
                break;
   }
}
