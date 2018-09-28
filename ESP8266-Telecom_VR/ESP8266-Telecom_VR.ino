/*
     Legrand In One-SWK Web Server WiFi
     Télécommande des Volets Roulants 868.3 MHz
	   HD@UIP 09-2015 
 
 Telecom_VR 
 version V3
 
 WeMos D1 mini (ESP8266-12E)
 Pins used :
  * D1 mini   GPIO 4, 5 12,13
  * Interscenario Legrand sur les pins  D2,  D3,  D6,  D5
 */

#include <SPI.h>
#include <ESP8266WiFi.h>

// Réseau Wifi
const char* ssid = "my_SSID_name"; // RDC -> freebox_SWK_extension 
const char* password = "my_SSID_passwd";
WiFiServer server(80);


// Boutons de la telecommande
byte pinUp = 13;       // GPIO 4 -> Bouton I de l'Interscenario = Lève TOUT
byte pinStop = 12;     // GPIO 5 -> Bouton II de l'Interscenario = STOP
byte pinDownS = 4;   // GPIO 12 -> Bouton III de l'Interscenario = Baisse SUD
byte pinDown = 5;    // GPIO 13 -> Bouton IV de l'Interscenario = Baisse TOUT

int delayms = 200;          // Duree de l'appui sur le bouton
int shadow_delayms = 15500; // Duree descente volets Sud
byte inChar; 
String readString;

void setup() {
// Configuration des sorties vers l'optocoupleur
pinMode(pinUp, OUTPUT);
pinMode(pinStop, OUTPUT);
pinMode(pinDownS, OUTPUT);
pinMode(pinDown, OUTPUT);

digitalWrite(pinUp, LOW);
digitalWrite(pinStop, LOW);
digitalWrite(pinDownS, LOW);
digitalWrite(pinDown, LOW);

Serial.begin(115200);
Serial.println();
Serial.println("Telecom_VR_V3");
Serial.println();

// Connexion au réseau WiFi
Serial.print("Connecting to : ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
// Start the server
server.begin();
Serial.println("Server started");
// Print the IP address
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
}

void checkSerialInput() {
  // Si quelquechose attend sur le port serie, on le lit
  if (Serial.available() > 0) {
    // Recuperation du caractere:
    inChar = Serial.read();
    // Selon le charactere on active ou desactive des sorties
    switch (inChar) {

    case '1':
      digitalWrite(pinUp,HIGH);
      delay(delayms);
      digitalWrite(pinUp,LOW);
      Serial.println("Leve Tout");
      break;
      
    case '2':
      digitalWrite(pinStop,HIGH);
      delay(delayms);
      digitalWrite(pinStop,LOW);
      Serial.println("STOP");
      break;

      case '3':
      digitalWrite(pinDownS,HIGH);
      delay(delayms);
      digitalWrite(pinDownS,LOW);
      Serial.println("Baisse Sud");
      delay(shadow_delayms);
      digitalWrite(pinStop,HIGH);
      delay(delayms);
      digitalWrite(pinStop,LOW);
      Serial.println("STOP");
      break; 
      
      case '4':
      digitalWrite(pinDownS,HIGH);
      delay(delayms);
      digitalWrite(pinDownS,LOW);
      Serial.println("Baisse Sud");
      break; 
      
    case '5':
      digitalWrite(pinDown,HIGH);
      delay(delayms);
      digitalWrite(pinDown,LOW);
      Serial.println("Baisse Tout");
      break;            
    }
  }
}  

void loop() {

  // Boucle gestion des entrées par le port série
  checkSerialInput(); 

  // Vérifie si un client est connecté
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Boucle gestion des entrées via le serveur web
  if (client) {
    Serial.println("new client");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); 
        // Lecture caractere par caractere de la requete HTTP
        if (readString.length() < 100) {
          // Enregistrement des caracteres dans une chaine
         readString.concat(c); 
        } 
        // Si le caractere lu est une fin de ligne, fini de la lecture de la requete
        // On peut maintenant repondre
        if (c == '\n') {
          Serial.println(readString); // Affiche la requete recue sur la console
          // Genere la reponse HTML data header
          if(readString.indexOf('?') >= 0) { 
            // Parametres, pas de rafraichissement de la page
            client.println("HTTP/1.1 204 no content");
            client.println();
          }
          else {
            // Sinon, envoi de la page HTML
            client.println(F("HTTP/1.1 200 OK")); 
            client.println(F("Content-Type: text/html"));
            client.println(F(""));
            client.println(F("<HTML>"));
            client.println(F("<HEAD>"));
            client.println(F("<TITLE>Legrand VR Web</TITLE>"));
            client.println(F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"));
            // favicon arduino
            client.println(F("<link rel=\"icon\" href=\"http://arduino.cc/favicon.ico\" type=\"image/x-icon\">")); 
            client.println(F("<link rel=\"shortcut icon\" href=\"http://arduino.cc/favicon.ico\" type=\"image/x-icon\">")); 
            // Jquery pour presentation
            client.println(F("<link rel=\"stylesheet\" href=\"http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.css\" />"));
            client.println(F("<script src=\"http://code.jquery.com/jquery-1.8.2.min.js\"></script>"));
            client.println(F("<script src=\"http://code.jquery.com/mobile/1.2.0/jquery.mobile-1.2.0.min.js\"></script>"));
            client.println(F("</HEAD>"));
            client.println(F("<BODY>"));
            client.println(F("<div data-role=\"page\">"));
            client.println(F("<div data-role=\"header\" data-theme=\"c\">"));
            client.println(F("<H1>SWK T&#233;l&#233;commande</H1>"));
            client.println(F("<H1>Volets Roulants</H1>"));
            client.println(F("</div><!-- /header -->"));
            client.println(F("<div data-role=\"content\">"));
            // Boutons d'action
            client.println(F("<a href=\"/?up\"\"    target=\"inlineframe\" data-role=\"button\" data-icon=\"star\" data-theme=\"d\">Leve Tout</a>")); 
            client.println(F("<a href=\"/?shadow\"\"    target=\"inlineframe\" data-role=\"button\" data-icon=\"star\" data-theme=\"e\">Soleil</a>")); //c
            client.println(F("<a href=\"/?down\"\" target=\"inlineframe\" data-role=\"button\" data-icon=\"star\" data-theme=\"a\">Baisse Tout</a>")); 
            client.println(F("</div><!-- /content -->"));
            client.println(F("<div data-role=\"footer\" data-theme=\"c\">"));
            client.println(F("Version 3")); 
            client.println(F("</div><!-- /footer -->"));
            client.println(F("<IFRAME name=inlineframe style=\"display:none\" >"));          
            client.println(F("</IFRAME>"));
            client.println(F("</div><!-- /page -->"));
            client.println(F("</BODY>"));
            client.println(F("</HTML>"));
          }
          delay(1);
          // Arret de la connexion du client web
          client.stop();
          // Interpretation des parametres recus en GET 
          if (readString.indexOf("up") > 0) {
            digitalWrite(pinUp,HIGH);
            delay(delayms);
            digitalWrite(pinUp,LOW);
            Serial.println("Leve Tout");
          }
          if (readString.indexOf("shadow") > 0) {
            digitalWrite(pinDownS,HIGH);
            delay(delayms);
            digitalWrite(pinDownS,LOW);
            Serial.println("Baisse Sud");
            delay(shadow_delayms);
            digitalWrite(pinStop,HIGH);
            delay(delayms);
            digitalWrite(pinStop,LOW);
            Serial.println("STOP");            
          }
          if (readString.indexOf("down") > 0) {
            digitalWrite(pinDown,HIGH);
            delay(delayms);
            digitalWrite(pinDown,LOW);
            Serial.println("Baisse Tout");
          }
          Serial.println("======"); 
          // Reinitialisation de la chaine de caractere
          readString="";
        }
      }
    }
  }
} 

