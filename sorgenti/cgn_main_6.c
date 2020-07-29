/**
  Il FILE cgn_main.c è parte del
  Cognitrone: sistema di pattern recongnition
  Copyright (C) 2018  Francesco Sisini (francescomichelesisini@gmail.com)
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


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
      int c=iter%5;
      printf("\x1b[2J");
      printf("\x1b[%d;%dH%s",5,58,"___Scuola Sisini Presenta___");
      printf("\x1b[%d;%dH%s",7,50,"RETI NEURALI: Il Cognitrone di Kunihiko Fukushima");
      printf("\x1b[%d;%dH%s",8,60,"(Le basi della Machine Vision)");
      printf("\x1b[%d;%dH%s %d ",10,40,"Ciclo",iter);
      
      carica_segnale(&U[0],-1,&area);
      carica_segnale(&U[0],4,&area);
      
      //Strato 0

      calcola_segnale_eccitatore(&U[0]);
      
      inibizione_laterale(&U[0],&area);

      calcola_segnale_inibitore(&U[0],&area);

      print_object(estrai_array(x1,&U[0],0),12, 12,15,20,"U0 - sgn");
       
      trasmetti(&U[0],&U[1]);
      
      //Strato 1
      
      calcola_potenziale(&U[1],&area);
      
      calcola_segnale_eccitatore(&U[1]);
      
      inibizione_laterale(&U[1],&area);

      calcola_segnale_inibitore(&U[1],&area);
      
      calcola_rinforzo(&U[1],&area);
      
      print_object(estrai_array(x2,&U[1],0),12, 12,15,50,"U1 - sgn");

      trasmetti(&U[1],&U[2]);

      //Strato 2

      calcola_potenziale(&U[2],&area);
      
      calcola_segnale_eccitatore(&U[2]);
      
      inibizione_laterale(&U[2],&area);

      calcola_segnale_inibitore(&U[2],&area);
      
      calcola_rinforzo(&U[2],&area);

      print_object(estrai_array(x3,&U[2],0),12, 12,15,80,"U2 - sgn");

      trasmetti(&U[2],&U[3]);

      //Strato 3

      calcola_potenziale(&U[3],&area);
      
      calcola_segnale_eccitatore(&U[3]);

      inibizione_laterale(&U[3],&area);

      calcola_segnale_inibitore(&U[3],&area);
      
      calcola_rinforzo(&U[3],&area);
      
      print_object(estrai_array(x3,&U[3],0),12, 12,15,110,"U3 - sgn");

      getchar();
    }

  getchar();

    /*Riproduzione inversa*/
    
  filtra_max(&U[3]);
  
  print_object(estrai_array(x3,&U[3],0),12, 12,30,110,"U3");

  carica_segnale(&U[2],-1,&area);
  
  trasmetti_indietro(&U[3],&U[2],&area);

  getchar();

  print_object(estrai_array(x3,&U[2],0),12, 12,30,80,"U2");

  carica_segnale(&U[1],-1,&area);
  
  trasmetti_indietro(&U[2],&U[1],&area);

  getchar();

  print_object(estrai_array(x3,&U[1],0),12, 12,30,50,"U1");

  carica_segnale(&U[0],-1,&area);
  
  trasmetti_indietro(&U[1],&U[0],&area);

  getchar();

  print_object(estrai_array(x3,&U[0],0),12, 12,30,20,"U0");

  printf("\n");

}

