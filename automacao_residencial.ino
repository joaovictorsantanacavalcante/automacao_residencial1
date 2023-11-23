//Programa: Automacao Residencial com Arduino e Ethernet Shield
//Autor: MakerHero
 
#include <SPI.h>
#include <Ethernet.h>
String readString;

int pino_rele1 = 3;
int pino_rele2 = 4;
int pino_rele3 = 5;
int pino_rele4 = 6;
boolean ligado = true;
boolean ligado_2 = true;
boolean ligado_3 = true;
boolean ligado_4 = true;
 
byte mac[] = { 0xA4, 0x28, 0x72, 0xCA, 0x55, 0x2F };
byte ip[] = { 10, 0, 0, 200 };
byte gateway[] = { 10, 0, 0, 1 };
byte subnet[] = { 255, 255, 255, 0 };

EthernetServer server(80);
 
void setup()
{
  Serial.begin(9600);
  pinMode(pino_rele1, OUTPUT);
  pinMode(pino_rele2, OUTPUT);
  pinMode(pino_rele3, OUTPUT);
  pinMode(pino_rele4, OUTPUT);
 
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
 

  digitalWrite(pino_rele1, HIGH);
  digitalWrite(pino_rele2, HIGH);
  digitalWrite(pino_rele3, HIGH);
  digitalWrite(pino_rele4, HIGH);
}
 
void loop()
{
  EthernetClient client = server.available();
  if (client) {
    while (client.connected())
    {
      if (client.available())
      {
        
        char c = client.read();
        if (readString.length() < 100) { 
          readString += c;          
        }
        if (c == 'n')          
        {
         
          //Ligaa o Rele 1
          if (readString.indexOf("?ligar") > 0)
          {
            digitalWrite(pino_rele1, LOW);
            ligado = false;
          }
          else
          {
            //Desliga o Rele 1
            if (readString.indexOf("?desligar") > 0)
            {
              digitalWrite(pino_rele1, HIGH);
              ligado = true;
            }
          }
 
          if (readString.indexOf("?2_ligar") > 0)
          {
            digitalWrite(pino_rele2, LOW);
            ligado_2 = false;
          }
          else
          {

            if (readString.indexOf("?2_desligar") > 0)
            {
              digitalWrite(pino_rele2, HIGH);
              ligado_2 = true;
            }
          }


          if (readString.indexOf("?3_ligar") > 0)
          {
            digitalWrite(pino_rele3, LOW);
            ligado_3 = false;
          }
          else
          {

            if (readString.indexOf("?3_desligar") > 0)
            {
              digitalWrite(pino_rele3, HIGH);
              ligado_3 = true;
            }
          }


          if (readString.indexOf("?4_ligar") > 0)
          {
            digitalWrite(pino_rele4, LOW);
            ligado_4 = false;
          }
          else
          {

            if (readString.indexOf("?4_desligar") > 0)
            {
              digitalWrite(pino_rele4, HIGH);
              ligado_4 = true;
            }
          }

          readString = "";
 
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          client.println("<head>");
          client.println("<title>CETEP Info - Automacao Residencial</title>");
          client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
          client.println("<meta name='viewport' content='width=720, initial-scale=0.5' />");
          client.println("<link rel='stylesheet' type='text/css' href='http://10.0.0.100/automacao_residencial/automacao_residencial.css'/>");
          client.println("<script type='text/javascript' src='http://10.0.0.100/automacao_residencial/automacao_residencial.js'></script>");
          client.println("</head>");
          client.println("<body>");

          client.println("<div id='wrapper'><img alt='CETEP Info' src='http://10.0.0.100/automacao_residencial/cetep_logo.png'/><br/>");

          client.println("<div id='div1'>Rele 1</div>");
          client.println("<div id='div2'>Rele 2</div>");
          client.println("<div id='div3'>Rele 3</div>");
          //client.println("<div id='div4'>Rele 4</div>");

          client.print("<div id='rele'></div><div id='estado' style='visibility: hidden;'>");
          client.print(ligado);
          client.println("</div>");
          client.println("<div id='botao'></div>");

          
          client.print("<div id='rele_2'></div><div id='estado_2' style='visibility: hidden;'>");
          client.print(ligado_2);
          client.println("</div>");
          client.println("<div id='botao_2'></div>");

          client.print("<div id='rele_3'></div><div id='estado_3' style='visibility: hidden;'>");
          client.print(ligado_3);
          client.println("</div>");
          client.println("<div id='botao_3'></div>");

          /*client.print("<div id='rele_4'></div><div id='estado_4' style='visibility: hidden;'>");
          client.print(ligado_4);
          client.println("</div>");
          client.println("<div id='botao_4'></div>");*/
          
                    
          client.println("</div>");
       
          client.println("<script>AlteraRele1()</script>");
          client.println("<script>AlteraRele2()</script>");
          client.println("<script>AlteraRele3()</script>");
          //client.println("<script>AlteraRele4()</script>");
          client.println("</div>"); 
          
          client.println("</body>");
          client.println("</html>"); 
 
          delay(1);
          client.stop();
        }
      }      
    }
  }
}