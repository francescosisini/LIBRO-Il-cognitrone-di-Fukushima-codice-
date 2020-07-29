#include <stdio.h>
#include "cgn_testate.h"

int main()
{
  AREA area;
  STRATO U[LAYERS];
  double x0[NEURONS];
  double x1[NEURONS];
  double x2[NEURONS];
  double x3[NEURONS];
  
  
  inizializza_aree(&area);

  inizializza_connessioni(&U[0], &area,1,INIT_B);

  inizializza_connessioni(&U[1], &area,INIT_A,INIT_B);

  inizializza_connessioni(&U[2], &area,INIT_A,INIT_B);

  inizializza_connessioni(&U[3], &area,INIT_A,INIT_B);
    
  for(int iter=0;iter<20;iter++)
    {
      printf("\x1b[2J");
      int c=iter%5;
      printf("\x1b[%d;%dH%s",5,58,"___Scuola Sisini Presenta___");
      printf("\x1b[%d;%dH%s",7,50,"RETI NEURALI: Il Cognitrone di Kunihiko Fukushima");
      printf("\x1b[%d;%dH%s",8,60,"(Le basi della Machine Vision)");
      printf("\x1b[%d;%dH%s %d ",10,40,"Ciclo",iter);
  
      if(c==0)
        {
          carica_segnale(&U[0],-1,&area);
          carica_segnale(&U[0],0,&area);
        }
      
      if(c==1)
        {
          carica_segnale(&U[0],-1,&area);
          carica_segnale(&U[0],1,&area);
        }
      if(c==2)
        {
          carica_segnale(&U[0],-1,&area);
          carica_segnale(&U[0],2,&area);
        }
      if(c==3)
        {
          carica_segnale(&U[0],-1,&area);
          carica_segnale(&U[0],3,&area);
        }
      if(c==4)
        {
          carica_segnale(&U[0],-1,&area);
          carica_segnale(&U[0],4,&area);
        }
  

      calcola_segnale_eccitatore(&U[0]);
  
      calcola_segnale_inibitore(&U[0],&area);

      print_object(estrai_array(x1,&U[0],0),12, 12,15,20,"U0 - sgn");
       
      trasmetti(&U[0],&U[1]);
      
      //Strato 1
      
      calcola_potenziale(&U[1],&area);
      
      calcola_segnale_eccitatore(&U[1]);
    
      calcola_segnale_inibitore(&U[1],&area);
      
      calcola_rinforzo(&U[1],&area);
      
      print_object(estrai_array(x2,&U[1],0),12, 12,15,50,"U1 - sgn");

      trasmetti(&U[1],&U[2]);

      //Strato 2

      calcola_potenziale(&U[2],&area);
      
      calcola_segnale_eccitatore(&U[2]);

      calcola_segnale_inibitore(&U[2],&area);
      
      calcola_rinforzo(&U[2],&area);

      print_object(estrai_array(x3,&U[2],0),12, 12,15,75,"U2 - sgn");

      trasmetti(&U[2],&U[3]);

      //Strato 3

      calcola_potenziale(&U[3],&area);
      
      calcola_segnale_eccitatore(&U[3]);

      calcola_segnale_inibitore(&U[3],&area);
      
      calcola_rinforzo(&U[3],&area);
      
      print_object(estrai_array(x3,&U[3],0),12, 12,15,100,"U3 - sgn");

      getchar();
    }

  getchar();
}

