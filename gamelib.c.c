#include "gamelib.h"


//prototipi delle funzioni necessarie
static void ins_caverna(struct Caverna**);
static void canc_caverna(struct Caverna**);
static void stampa_cunicoli(struct Caverna*);
static void chiudi_cunicoli();

static void cancella_cunicolo(struct Caverna**);
static void avanza(struct Caverna**,struct Scavatrice*);
static void abbati(struct Caverna**,struct Scavatrice*);
static void aggira(struct Caverna**,struct Scavatrice*);
static void controllo_serbatoio(struct Scavatrice*);
static void scontro_finale();

static struct Caverna* primo_cunicolo_arvais=NULL;
static struct Caverna* primo_cunicolo_hartornen=NULL;

static struct Scavatrice arvais={NULL,4,0};
static struct Scavatrice hartornen={NULL,4,0};
int conta_caverne=0;

static int fine=0;   //assume 0 se non è stato chiusa la mappa, 1 se è stata chiusa
static int turnog=0; // variabile che conta i turni
static bool esci=0;  //se è 0 il giocatore non ha travato l'usciata se è 1 allora esce



//stampa menu' per gestire la mappa
void crea_cunicoli() {

//scelta da menu da parte dell'utente
do{

  int choose=0;

  printf("Turno arvais!\n\n");

        printf("Inserisci l'operazione da effettuare: \n");
        printf(" 1.Inserisci caverna\n 2. Cancella ultima caverna\n 3. Stampa cunicolo\n 4. Chiudi cunicoli\n");
        scanf("%d",&choose);

        system("cls");
        switch(choose){
              case 1:
                  ins_caverna(&*&primo_cunicolo_arvais);
                  break;

              case 2:
                  canc_caverna(&*&primo_cunicolo_arvais);
                  break;

              case 3:
                  stampa_cunicoli(primo_cunicolo_arvais);
                  break;

              case 4:
                  chiudi_cunicoli();
                  break;

              default:
                  printf("Opzione non valida.....\n");
                  break;
          }
}while (fine!=1);
conta_caverne=0;
fine=0;


 do{

  int choose=0;

  printf("Turno hartornen!\n\n");

        printf("Inserisci l'operazione da effettuare: \n");
        printf(" 1.Inserisci caverna\n 2. Cancella ultima caverna\n 3. Stampa cunicolo\n 4. Chiudi cunicoli\n");
        scanf("%d",&choose);

        system("cls");
        switch(choose){
              case 1:
                  ins_caverna(&*&primo_cunicolo_hartornen);
                  break;

              case 2:
                  canc_caverna(&*&primo_cunicolo_hartornen);
                  break;

              case 3:
                  stampa_cunicoli(primo_cunicolo_hartornen);
                  break;

              case 4:
                  chiudi_cunicoli();
                  break;

              default:
                  printf("Opzione non valida.....\n");
                  break;
          }
 }while (fine!=1);
}


static void ins_caverna(struct Caverna** cunicolo){
  time_t t;
  srand((unsigned) time(&t));  //randomizza il generatore dei numeri casuali

struct Caverna* head= NULL; //creazione della caverna
head = (struct Caverna*) malloc(sizeof(struct Caverna)); //alloco memoria
head->avanti=NULL;
head->sinistra=NULL;
head->destra=NULL;

conta_caverne++;


int choose=0;

do{

printf("Stato caverna:\n normale\n speciale\n accidentata\n\n");
scanf("%d", &choose);

head->caverna=choose;
if(choose<1||choose>3){
printf("Scelta sbagliata!\n\n");
}

}while(choose<1||choose>3);


int i=rand() % 101;

if(i>=0 && i<=50){
head->melassa=nessuna;
printf("Nessuna melassa trovata!\n\n");
system("cls");
}

else if (i>50 && i<=80){
head->melassa=poca;
printf("Poca melassa!\n\n");
}

else{
 head->melassa=molta;
 printf("Molta melassa!\n\n");
}

i=rand() % 101;

if(i>=0 && i<=50){
head->imprevisto=nessun_imprevisto;
printf("Nessun imprevisto!\n\n");
}

else if (i>50 && i<=85){
head->imprevisto=crollo;
printf("Si ha un crollo!\n\n");
}

else{
 head->imprevisto=baco;
 printf("È presente un baco!\n\n");
}

if(*cunicolo==NULL){   //il caso in cui non è presente nessuna caverna
  *cunicolo=head;
}

else{                 //il caso in cui ci sono le caverne

int choose=0;

do{

 printf("Dove vuoi inserire la caverna:\n 1.avanti\n 2.sinistra\n 3.destra\n");
 scanf("%d", &choose);
 system("cls");

}while(choose<1 || choose>3);

if(choose==1){
head->avanti=*cunicolo;
*cunicolo=head;
}

else if(choose==2){
head->sinistra=*cunicolo;
*cunicolo=head;
}

else if(choose==3){
head->destra=*cunicolo;
*cunicolo=head;
  }
 }
}


static void canc_caverna (struct Caverna** cunicolo){

   if(*cunicolo==NULL){  //controllo se esiste un *cunicolo
     printf("Nessun cunicolo presente!\n\n");
   }
     else if(conta_caverne<=0){
        printf("Tute le caverne sono state cancellate!\n\n");
        *cunicolo=NULL;
      }
       else{   //il caso in cui esiste almeno una caverna

       struct Caverna* temp=*cunicolo; //variabile temporanea per non modificare la variabile esistente

       if(temp->avanti!=NULL){
         *cunicolo=temp->avanti; //la seconda caverna diventa la prima
       }

       else if(temp->sinistra!=NULL){
         *cunicolo=temp->sinistra;
       }
           else if(temp->destra!=NULL){
             *cunicolo=temp->destra;
           }
           free(temp);
           temp=NULL;
           system("cls");

       conta_caverne--; //decrementa il numero delle caverne

     }
  }



static void stampa_cunicoli(struct Caverna* cunicolo){

     if(cunicolo==NULL){
     printf("Nessun cunicolo presente!\n\n");
}

   else{
      struct Caverna* temp=cunicolo;  //puntatore usato per scansionare il *cunicolo

   while(true){ //sempre vero

     switch(temp->melassa){
        case 0:
          printf("Nessuna melassa!\n");
          break;

          case 1:
          printf("Poca melassa!\n");
          break;

          case 3:
          printf("Molta mellasa!\n");
          break;

        }

     switch(temp->imprevisto){
       case 0:
         printf("Nessun_imprevisto!\n");
         break;

         case 1:
         printf("C'è un crollo!\n");
         break;

         case 2:
         printf("C'è un baco!\n");
         break;

     }

     switch(temp->caverna){
       case 1:
         printf("Caverna normale!\n");
         break;

         case 2:
         printf("Caverna speciale!\n");
         break;

         case 3:
         printf("Caverna accidentata!\n");
         break;

        case 4:
        printf("Uscita!\n");
        break;
   }

   if(temp->avanti!=NULL){
     printf("\n\nAvanti\n"); //controlla qualle delle prossime uscite sono aperte
     temp=temp->avanti;
   }

  else if(temp->sinistra!=NULL){
    printf("\n\nsinistra\n");
    temp=temp->sinistra;
  }

  else if(temp->destra!=NULL){
    printf("\n\ndestra\n");
    temp=temp->destra;
  }

  else{
    break;
  }
  printf("\n\n");

  }
 }
}


static void chiudi_cunicoli(){

  if(conta_caverne<10){
    printf("Non puoi chiudere il cunicolo finchè non ci sono 10 caverne!\n\n");
}

 else{
   printf("Puoi chiudere la mappa, le 10 caverne sono state create!\n\n");
   fine=1;
   printf("\n\n");
 }
}



void gioca(){

 if(primo_cunicolo_arvais!=NULL && primo_cunicolo_hartornen!=NULL){

  arvais.posizione=primo_cunicolo_arvais;
  hartornen.posizione=primo_cunicolo_hartornen;

do{
  int choose=0;

printf("ARVAIS tocca a te!\n\n");

 do{
     printf(" Inserisci l'operazione da effettuare!\n");
     printf(" 1.Avanza\n 2.Abbati\n");
     scanf("%d",&choose);

     system("cls");
     switch(choose){
           case 1:
               avanza(&*&primo_cunicolo_arvais,&arvais);
               turnog++;
               break;

           case 2:
               abbati(&*&primo_cunicolo_arvais,&arvais);
               turnog++;
               break;



           default:
               printf("Opzione non valida.....\n");
               break;
     }

}while(choose<1||choose>2);
scontro_finale();

  if(arvais.serbatoio_energia<=0) {
  esci=1;
  }

  choose=0;

printf("HARTORNEN tocca a te!\n\n");

 do{
     printf(" Inserisci l'operazione da effettuare!\n");
     printf(" 1.Avanza\n 2.Abbati\n");
     scanf("%d",&choose);

     system("cls");
     switch(choose){
           case 1:
               avanza(&*&primo_cunicolo_hartornen,&hartornen);
               turnog++;
               break;

           case 2:
               abbati(&*&primo_cunicolo_hartornen,&hartornen);
               turnog++;
               break;



           default:
               printf("Opzione non valida.....\n");
               break;
     }


 } while(choose<1||choose>2);
scontro_finale();

//printf("Controllo serbatoio dei giocatori!");
 if(hartornen.serbatoio_energia<=0){
  esci=1;
}

}while(esci==0);

if(arvais.serbatoio_energia<=0){
  printf("Arvais perde perchè ha il suo serbatoio_energia e vuoto....e vince hartornen!\n");
 }

else if(hartornen.serbatoio_energia<=0){
  printf("Hartornen perde perchè ha il suo serbatoio_energia e vuoto ...e vince arvais!\n");
 }

else if(arvais.serbatoio_raccolta > hartornen.serbatoio_raccolta){
  printf("COMPLIMENTI..!! Ha vinto arvais!\n");
 }

else if (hartornen.serbatoio_raccolta > arvais.serbatoio_raccolta ){
  printf("COMPLIMENTI..!!Ha vinto hartornen!\n");
 }

else {
  printf("Parità!\n Non ha vinto nessuno!\n");
 }

}
else{
  printf("Non poi giocare finche non crei almeno 10 caverne\n");
}

 termina_gioco();
 printf("\n\n");
}


 static void avanza(struct Caverna** cunicolo,struct Scavatrice* giocatore){

   time_t t;
   srand((unsigned) time(&t));
   int c =rand() % 101;


 if( c<25){
   printf("C'è stato un crollo improvviso..! E sei costretto ad aggirare\n\n");
   aggira(cunicolo,giocatore);
   return;
   }

 else{

  struct Caverna* temp=*cunicolo;

   if((*cunicolo)->avanti!=NULL){
     giocatore->posizione = giocatore->posizione ->avanti;
     *cunicolo= temp->avanti;
     free(temp);
     temp=NULL;
     printf("Sei andato avanti!\n\n");
   }

   else if((*cunicolo)->sinistra!=NULL){
     giocatore->posizione = giocatore->posizione ->sinistra;
     *cunicolo= temp->sinistra;
     free(temp);
     temp=NULL;
     printf("Sei andato a sinistra!\n\n");

   }

   else if((*cunicolo)->destra!=NULL){
    giocatore->posizione= giocatore->posizione ->destra;
     *cunicolo= temp->destra;
     free(temp);
     temp=NULL;
     printf("Sei andato a destra!\n\n");
    }

   else{
     printf("Il cunicolo è finito, non puoi avanzare\n\n");
   }return;

  if((*cunicolo)->melassa==poca){
     int a;
     printf("Hai trovato poca melassa dove la vuoi mettere:\n\n 1.Raccolta\n 2.Energia\n");
     scanf("%d", &a);

    if(a==1){
      giocatore->serbatoio_raccolta++;
     }

    else{
        giocatore->serbatoio_energia++;
      }
  }

  else if((*cunicolo)->melassa==molta){
    int a;
    printf("Hai trovato molta melassa dove la vuoi mettere:\n\n 1.Raccolta\n 2.Energia\n");
    scanf("%d", &a);
    controllo_serbatoio(giocatore);

   if(a==1){
     giocatore->serbatoio_raccolta+=3;
    }

   else{
       giocatore->serbatoio_energia+=3;
  }
 }

 else if((*cunicolo)->melassa==nessuna){
 printf("Non hai trovato nessuna melassa!\n\n");
   }
printf("\n\n");


  if((*cunicolo)->imprevisto==crollo){
    printf("C`e stato un crollo!\n Viene cosumata 1 unità melassa dal serbatoio di energia!\n\n");
      controllo_serbatoio(giocatore);
      giocatore->serbatoio_energia--;
    }

  else if((*cunicolo)->imprevisto==baco){
    printf("C`e stato un baco!\n Il serbatoio di energia viene svuotato!\n\n");
      giocatore->serbatoio_energia=0;
  }

  else if((*cunicolo)->imprevisto==nessun_imprevisto){
    printf("Nessun imprevisto presente!\n\n");
  }

 if((*cunicolo)->caverna==normale){
   printf("La tua caverna è normale!\n\n");
  }

  else if((*cunicolo)->caverna==speciale){
    printf("La tua caverna è speciale:\n Hai guadagnato 1 unità di melassa!\n\n");
      controllo_serbatoio(giocatore);
    giocatore->serbatoio_energia++;
  }

 else if((*cunicolo)->caverna==accidentata){
   printf("La tua caverna è accidentata:\n Hai perso 1 unità di melassa!\n\n");//
    controllo_serbatoio(giocatore);
   giocatore->serbatoio_energia--;
  }
 }
}

 static void abbati(struct Caverna** cunicolo,struct Scavatrice* giocatore ){

    int choose=0;

    while(choose<1||choose>3){
      printf("In che direzione vuoi abbatere:\n 1.avanti\n 2.sinistra\n 3.destra\n");
      scanf("%d", &choose);

   if(choose<1||choose>3){
     printf("Scelta sbagliata!\n\n");
  }
   }

   struct Caverna* head= NULL;  //creazione della nuova caverna
 	  head = (struct Caverna*) malloc(sizeof(struct Caverna)); //alloco memoria
 	  head->avanti=NULL;
 	  head->sinistra=NULL;
 	  head->destra=NULL;

  if(choose==1 && (*cunicolo)->avanti==NULL){  //controllo in che direzione vuole abbatere e se quella direzione e aperta
  cancella_cunicolo(cunicolo);
    head->avanti=*cunicolo;          //collego la caverna creata
    *cunicolo=head;                 //la caverna che ho creato diventa la prima in testa
    giocatore->posizione=*cunicolo;
    free(head->avanti);
    head->avanti=NULL;
    printf("Sei andato avanti!\n\n");

  }

  else if(choose==2 && (*cunicolo)->sinistra==NULL){
   cancella_cunicolo(cunicolo);
    head->sinistra=*cunicolo;
    *cunicolo=head;
    giocatore->posizione=*cunicolo;
    free(head->sinistra);
    head->sinistra=NULL;
    printf("Sei andato a sinistra!\n\n");
  }

  else if(choose==3 && (*cunicolo)->destra==NULL){
    cancella_cunicolo(cunicolo);
     head->destra=*cunicolo;
    *cunicolo=head;
    giocatore->posizione=*cunicolo;
    free(head->destra);
    head->destra=NULL;
    printf("Sei andato a destra!\n\n");
  }

  else{
    printf("Non puoi abbatere nelle direzione scelte perché sono aperte!\n\n Scegli un'altra\n\n");
    free(head);   //dato che non mi serve la caverna, la cancello
    head=NULL;
    abbati(cunicolo,giocatore);
    return;
  }

  giocatore->serbatoio_energia--;

//le proprietà della nuova caverna
  int c = 5 * turnog;
  if(c>78){
    c=78;
  }

  time_t t;
   srand((unsigned) time(&t));
   int b =rand() % 101;

if(b>=0||b<c){     //controllo se la varibile b è compreso tra 0 e la probabilità che aumenta del 5% per ogni turno passato
  (*cunicolo)->caverna=uscita;

  int a = 0;

  do{
   printf("Hai tovato l'uscita, cosa vuoi fare?\n\n Vuoi uscire o rimanere a giocare:\n 1.esci\n 2.continua a giocare!\n\n");
   scanf("%d",&a);

   if(a<1 || a>2){
     printf("Scelta sbagliata!\n\n");
   }
  }while(a<1 || a>2);

   if(a==1){
    esci=1;
    return;
   }

   else{
     printf("Continua a giocare!\n\n");
   }
}

else{
  if(b>=c && b<c+20){
     (*cunicolo)->caverna=accidentata;
     printf("Caverna accidentata!\n\n");
    }

   else if(b>=c+20 && b>=(100-(c+20))/2){
      (*cunicolo)->caverna=speciale;
      printf("Caverna speciale!\n\n");
    }

    else{
     (*cunicolo)->caverna=normale;
      printf("Caverna normale!\n\n");
    }
}

b=rand() % 101;

if(b>=0 && b<=40){
  (*cunicolo)->melassa=nessuna;
   printf("Nessuna melassa presente!\n\n");
 }

 else if(b>40 && b<=80){
   (*cunicolo)->melassa=poca;
   printf("C'è poca melassa!\n\n");

  int a;
  printf("Hai trovato poca melassa dove la vuoi mettere:\n 1.Raccolta\n 2.Energia\n");
  scanf("%d", &a);
  controllo_serbatoio(giocatore);

 if(a==1){
   giocatore->serbatoio_raccolta++;
  }

 else{
     giocatore->serbatoio_energia++;
   }
 }

  else {
   (*cunicolo)->melassa=molta;
   printf("C'è molta melassa!\n\n");

  int a;
  printf("Hai trovato molta melassa dove la vuoi mettere:\n 1.Raccolta\n 2.Energia\n");
  scanf("%d", &a);
  controllo_serbatoio(giocatore);

 if(a==1){
   giocatore->serbatoio_raccolta+=3;
  }
 else{
     giocatore->serbatoio_energia+=3;
}
 }

b=rand() % 101;

if(b>=0 && b<=40){
  (*cunicolo)->imprevisto=nessun_imprevisto;
   printf("Nessun imprevisto presente!\n\n");
 }

 else if(b>40 && b<=80){
    (*cunicolo)->imprevisto=crollo;
    printf("C'è stato un crollo!\n\n");

    controllo_serbatoio(giocatore);
    giocatore->serbatoio_energia--;
 }

  else {
   (*cunicolo)->imprevisto=baco;
   printf("È presente un baco!\n\n");

  giocatore->serbatoio_energia=0;
  }
}


static void aggira(struct Caverna** cunicolo,struct Scavatrice* giocatore){

 if((*cunicolo)->avanti!=NULL || (*cunicolo)->destra!=NULL ||(*cunicolo)->sinistra!=NULL ) {

    struct Caverna* head= NULL;   //creazione della caverna
    head = (struct Caverna*) malloc(sizeof(struct Caverna)); //alloco memoria
    head->avanti=NULL;
    head->sinistra=NULL;
    head->destra=NULL;


     head->avanti=(*cunicolo)->avanti; //la nuova caverna punta alla prossima
     (*cunicolo)->avanti=head;         //gli assegno la nuova caverna
     giocatore->posizione=giocatore->posizione->avanti; //sposto il giocatore nella caverna che ho creato

     struct Caverna* temp=(*cunicolo)->avanti;
     *cunicolo=temp;
     free(temp); // cancello la caverna
     temp=NULL;
     printf("Sei entrato nella caverna!\n\n");

     int i=rand() % 101;

     if(i>=0 && i<=50){
       (*cunicolo)->melassa=nessuna;
       printf("Nessuna melassa trovata!\n\n");
     }

     else if (i>50 && i<=80){
       (*cunicolo)->melassa=poca;
       printf("Hai trovato poca melassa!\n\n");

       int a;
       printf("Hai trovato poca melassa dove la vuoi mettere:\n 1.Raccolta\n 2.Energia\n");
       scanf("%d", &a);
       controllo_serbatoio(giocatore);

      if(a==1){
        giocatore->serbatoio_raccolta++;
       }

      else{
          giocatore->serbatoio_energia++;
        }
     }

     else{
         (*cunicolo)->melassa=molta;
         printf("Molta melassa!\n\n");

         int a;
         printf("Hai trovato molta melassa dove la vuoi mettere:\n 1.Raccolta\n 2.Energia\n");
         scanf("%d", &a);

        controllo_serbatoio(giocatore);

          if(a==1){
          giocatore->serbatoio_raccolta+=3;
         }

        else{
            giocatore->serbatoio_energia+=3;
       }
     }

      i=rand() % 101;

     if(i>=0 && i<=50){
       (*cunicolo)->imprevisto=nessun_imprevisto;
       printf("Nessun imprevisto!\n\n");
     }

     else if (i>50 && i<=85){
        (*cunicolo)->imprevisto=crollo;
        printf("Si ha un crollo!\n\n");

       controllo_serbatoio(giocatore);
       giocatore->serbatoio_energia--;

     }else{
         (*cunicolo)->imprevisto=baco;
         printf("È presente un baco!\n\n");
        controllo_serbatoio(giocatore);
         giocatore->serbatoio_energia=0;
     }

    i=rand() % 101;

     if(i>=0 && i<=40){
       (*cunicolo)->caverna=normale;
       printf("Caverna normale!\n\n");
     }

    else if(i>40 && i<=80){
      (*cunicolo)->caverna=speciale;
      printf("Caverna speciale!\n\n Hai guadagnato 1 unità di melassa!\n\n");
      controllo_serbatoio(giocatore);
      giocatore->serbatoio_energia++;
    }

    else{
      (*cunicolo)->caverna=accidentata;
      printf("Caverna accidentata!\n\n Hai perso 1 unità di melassa!\n\n");
      controllo_serbatoio(giocatore);
      giocatore->serbatoio_energia--;
    }
   }

   else{
     printf("Non puoi aggirare!\n Sei arrivato all'ultima caverna\n\n");
   }

}


static void cancella_cunicolo(struct Caverna** cunicolo){

  struct Caverna* temp=*cunicolo;

	while(temp->avanti != NULL || temp->destra != NULL || temp->sinistra != NULL){  //finche una porta è aperta
		if(temp->avanti!=NULL){
    *cunicolo=temp->avanti;
		free(temp);
    temp=*cunicolo;   //assegno la prossima caverna
		}

    else if(temp->sinistra!=NULL){
      *cunicolo=temp->sinistra;
	  	free(temp);
      temp=*cunicolo;
     }

    else if(temp->destra!=NULL){
     *cunicolo=temp->destra;
     free(temp);
     temp=*cunicolo;
    }

  }
}

 void termina_gioco(){

//cancello il cunicolo di arvais
  if(primo_cunicolo_arvais!=NULL){
     cancella_cunicolo(&primo_cunicolo_arvais);
     free(primo_cunicolo_arvais);
     primo_cunicolo_arvais=NULL;
   }

   //cancello il cunicolo di hartornen
  if( primo_cunicolo_hartornen!=NULL){
      cancella_cunicolo(&primo_cunicolo_hartornen);
      free(primo_cunicolo_hartornen);
      primo_cunicolo_hartornen=NULL;
    }

  //reseto tutti i contatori
 arvais.posizione=NULL;
 arvais.serbatoio_energia=4;
 arvais.serbatoio_raccolta=0;
 hartornen.posizione=NULL;
 hartornen.serbatoio_energia=4;
 hartornen.serbatoio_raccolta=0;

conta_caverne=0;
fine=0;             //assume 0 se non è stato chiusa la mappa, 1 se è stata chiusa
turnog=0;          //conta turni
esci=0;          //se è 0 il giocatore non ha travato l'usciata se è 1 allora esce
printf("GAME OVER!\n\n");
system("cls");
}



static void scontro_finale(){

 time_t t;
 srand((unsigned) time(&t));
 int a=rand() % 101;

 int s=3 * turnog;
 if(a>=0 || a<s){
  printf("Le due scavatrice si sono incontrate nel percorso, vincerà qulla che ha piu melassa!\n\n");

if(arvais.serbatoio_raccolta > hartornen.serbatoio_raccolta){
    printf("VINCE ARVAIS!\n\n");
  }

  else if (hartornen.serbatoio_raccolta > arvais.serbatoio_raccolta ){
  printf("VINCE HARTORNEN!\n\n");
}
else if (hartornen.serbatoio_raccolta==arvais.serbatoio_raccolta ){
  printf("Parità...Non ha vinto nessuno!\n\n");
}
  }

  else {
    printf("Le scavatrice non si sono anora incontrate!\n\n");
    }

}

static void controllo_serbatoio(struct Scavatrice*giocatore){

  if(giocatore->serbatoio_energia<0){
   giocatore->serbatoio_energia=0;
  }

 if(giocatore->serbatoio_raccolta<0){
  giocatore->serbatoio_raccolta=0;
 }

 if(giocatore->serbatoio_raccolta>10){
  giocatore->serbatoio_raccolta=10;
 }

 if(giocatore->serbatoio_energia>4){
  giocatore->serbatoio_energia=4;
 }

}
