#include "gamelib.h"

int main(void){

    int scelta=0;

  do{

        printf("Inserisci l'operazione da effettuare: \n");
        printf(" 1. Crea cunicoli\n 2. Gioca\n 3. Termina gioco\n 4.Esci\n");
        scanf("%d",&scelta);


        system("cls");

        switch(scelta){
            case 1:
                crea_cunicoli();
                break;

           case 2:
                gioca();
                break;

            case 3:
                printf("Chiusura gioco!\n");
                termina_gioco();
                break;


            default:
                printf("Opzione non valida.....\n");
                break;
        }

    }while(scelta!=4);


    return 0;
}
