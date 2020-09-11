//MINGOLLA DANIELE              MATRICOLA N. 300738

#include <stdlib.h>
#include <stdio.h>
#include "gamelib.h"
int main(){
  system("clear");
  //la variabile scelta serve ad entrare in crea mappa,gioca o ad uscire dal programma
  //La variabile modifica è settata ad 1 ogni qual volta viene creata una mappa,così il programma riconosce se è già presente un percorso
  //La variabile sceltamodifica assume valore 1 o 2 a seconda che l'utente voglia modificare il percorso esistente o crearne uno nuovo
  unsigned short int scelta=0,modifica=0,sceltamodifica=0;
  //I printf di questa tipologia servono a modificare il colore del testo nei printf successivi
  printf("\033[1;31m");
  //Vari printf seguiti da una pausa per la creazione di una breve intro
  printf("\t\tINGRANDISCI LO SCHERMO PER EVITARE GLITCH GRAFICI\n");
  sleep(2);
  system("clear");
  printf("\t\t\t\tA GAME CREATED BY...\n");
  sleep(2);
  system("clear");
  printf("\t\t\t\tDANIELE MINGOLLA    MATRICOLA N. 300738\n");
  sleep(2);
  system("clear");
  printf("\033[1;31m");
  printf("\t                              .___.\n");
  printf("\t          /)               ,-^     ^-. \n");
  printf("\t         //               /           \\\n");
  printf("\t.-------| |--------------/  __     __  \\-------------------.__\n");
  printf("\t|WMWMWMW| |>>>>>>>>>>>>> | />>\\   />>\\ |>>>>>>>>>>>>>>>>>>>>>>:>\n");
  printf("\t`-------| |--------------| \\__/   \\__/ |-------------------'^^\n");
  printf("\t         \\\\               \\    /|\\    /\n");
  printf("\t          \\)               \\   \\_/   /\n");
  printf("\t                            |       |\n");
  printf("\t                            |+H+H+H+|\n");
  printf("\t                            \\       /\n");
  printf("\t                             ^-----^\n");
  printf("\tÈ venerdì 13 giugno 1980,\n\ted un gruppo di studenti universitari ");
  printf("del Corso di Laurea in Informatica\n\tsi trasferisce in vacanza al Campeggio Lake Trasymeno,che sta per riaprire.\n");
  sleep(4);
  printf("\tVentitre anni prima, nello stesso campeggio, un ragazzino di nome Gieson\n\tera annegato ");
  printf("per colpa della negligenza di un programmatore,\n\ta causa di un segmentation fault nel suo programma di noleggio delle barche,\n");
  printf("\talla famiglia di Gieson era stata affidata una barca con un motore difettoso.\n");
  sleep(5);
  printf("\tGieson però infesta ancora il campeggio, e nutre vendetta nei confronti\n\tdegli informatici poco attenti.\n");
  printf("\tGiacomo e Marzia, rimangono isolati dagli altri quando...\n");
  printf("\033[0m");
  sleep(4);
  system("clear");
        do{
            printf("\033[1;31m");
            printf("\t                              .___.\n");
            printf("\t          /)               ,-^     ^-. \n");
            printf("\t         //               /           \\\n");
            printf("\t.-------| |--------------/  __     __  \\-------------------.__\n");
            printf("\t|WMWMWMW| |>>>>>>>>>>>>> | />>\\   />>\\ |>>>>>>>>>>>>>>>>>>>>>>:>\n");
            printf("\t`-------| |--------------| \\__/   \\__/ |-------------------'^^\n");
            printf("\t         \\\\               \\    /|\\    /\n");
            printf("\t          \\)               \\   \\_/   /\n");
            printf("\t                            |       |\n");
            printf("\t                            |+H+H+H+|\n");
            printf("\t                            \\       /\n");
            printf("\t                             ^-----^\n");
            puts("");
           printf("\t\tOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO\n");
           printf("\t\tO                                                 O\n");
           printf("\t\t8                1......CREA MAPPA                8\n");
           printf("\t\tO                2...........GIOCA                O\n");
           printf("\t\t8                3............ESCI                8\n");
           printf("\t\tO                                                 O\n");
           printf("\t\tOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO\n");
           printf("\n\t\t\t\tSCELTA...    ");
           printf("\033[0m");

          //controllo sull'input
          while (scanf("%hu",&scelta) != 1 || scelta >3|| scelta <1){
               printf("\033[1;31m");
                  printf("\n\t\tSCELTA NON CORRETTA! REINSERISCI IL VALORE: ");
                   printf("\033[0m");
              while (getchar() != '\n');
          }
          switch(scelta){
                 case 1:
                        //se modifica ha valore 1 allora in memoria è presente un percorso
                        if(modifica==1){
                            printf("\033[1;31m");
                            printf("\n\t\t\tÈ PRESENTE UN PERCORSO!\n\n\t\t\t1......MODIFICA PERCORSO ESISTENTE\n\t\t\t2...........CREA UN NUOVO PERCORSO\n\n\t\t\tSCELTA: ");
                            while (scanf("%hu",&sceltamodifica) != 1 || sceltamodifica>2 || sceltamodifica<1){
                                    printf("\n\t\tSCELTA NON CORRETTA! REINSERISCI LA SCELTA: ");
                                    while (getchar() != '\n');
                                }
                                 printf("\033[0m");
                                 //se l'untente digita 1 il percorso preesistente rimane intatto ma può modificarlo a piacimento
                                if (sceltamodifica == 1){
                                    system("clear");
                                    crea_mappa();
                                }
                                //se l'utente digita 2,cioè decide di creare un nuovo percorso,libero la memoria allocato al percorso precedente richiamando un'apposita funzione e poi richiamo il crea mappa
                                else if(sceltamodifica == 2){
                                    system("clear");
                                    termina_gioco();
                                    crea_mappa();
                                }
                        }
                        else{
                            //creando una mappa, modifica viene settata ad 1
                            system("clear");
                            crea_mappa();
                            modifica=1;
                        }
                        break;
                 case 2:
                        //nel momento in cui inizia il gioco,modifica viene settata di nuovo a 0 poichè al termine del gioco la mappa creata non esisterà più
                        gioca();
                        modifica=0;
                        break;
                 case 3:
                    //viene liberata la memoria allocata per l'intero percorso richiamando l'apposita funzione
                       system("clear");
                       termina_gioco();
                 default:
                       break;
         }
    }while(scelta!=3);
}
