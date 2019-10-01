#include <LiquidCrystal.h>
// Esta librería ha sido desarrollada para la version de Arduino 1.8.5
// y en caso de encontrarse BUGS en futuras versiones de Arduino
// El soporte lo encontrarán en el Canal de Youtube "Innova Domotics"
// https://www.youtube.com/c/innovadomotics en el vídeo dedicado al
// SENSOR DE HUELLA cuyas actualizaciones estarán en enlaces descargables 
// en la descripción del vídeo
//--------------------------------------------------------------------
// Esta librería no se ha testeado con versiones anteriores de Arduino
//--------------------------------------------------------------------

#include <InnovaS_Dactilar.h>

#include <SoftwareSerial.h>

// pin #2 - Entrada desde el Sensor  (cable verde)
// pin #3 - Salida de desde Arduino  (cable blanco)
LiquidCrystal lcd(4, 5, 6, 7, 8, 9); //Pines donde va conectada la pantalla la pantalla (RS, E, D4, D5, D6, D7)
SoftwareSerial MySerial(10, 11);
//-------------------------------------------------------
uint32_t ClaveSensorHuella = 0; // 0 -> CLAVE POR DEFECTO
//-------------------------------------------------------
InnovaS_Dactilar MySensorDactilar = InnovaS_Dactilar(&MySerial, ClaveSensorHuella);

void setup()
{ 
    Serial.begin(57600);
    Serial.println("Sensor de Huella");
  
    //Setea la velocidad de comunicacion con el sensor de huella
    //Iniciar verificando los valores de 9600 y 57600
    MySensorDactilar.begin(57600);
    
    if (MySensorDactilar.VerificarClave()) {
      Serial.println("Sensor de Huella Encontrado :)  :) ");
    } else {
      Serial.println("No fue posible encontrar al sensor de Huella  :(  :( ");
      while (1);
    }

    //PARA ESTO PRIMERO HAY QUE INGRESAR CON LA ANTERIOR CLAVE
    //LA MISMA QUE POR DEFECTO ES CERO (0)
    //POSTERIORMENTE LA NUEVA CLAVE SERA ASIGNADA AL INICIO
    
    int MyNuevaClave = 0;
    Serial.println("Cambiando Clave ...");
    CambiarClaveSH(MyNuevaClave);
{
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("Cambiando la");
lcd.setCursor(0,1);
lcd.print("Clave, Espere");
delay(1500);
}
}

void loop()                     
{ 
  delay(500);
}

void CambiarClaveSH(int NewKey) 
{
  int p = -1;
    p = MySensorDactilar.CambiarClave(NewKey);
    switch (p) {
    case SDACTILAR_CLAVEMODIFICADA:
      Serial.println("Exito - Clave Cambiada");
      break;
    case SDACTILAR_PAQUETE_ERROR:
      Serial.print("Error al recibir el paquete");
      break;
    default:
      Serial.print("Error Desconocido: 0x"); Serial.println(p, HEX);
      break;
    }
}
