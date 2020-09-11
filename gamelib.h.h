#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


void crea_cunicoli();  //prototipo funzione della creazione percorso
void gioca();          //prototipo funzione principale
void termina_gioco();  //prototipo funzione chiusura del gioco



struct Scavatrice{
  struct Caverna* posizione;
  int serbatoio_energia ; //da 0 a 4, qundo è 0 non puoi abbatere, sotto 0 perdi
  int serbatoio_raccolta; //da 0 a 10 unità di melassa
};


enum Tipo_imprevisto{nessun_imprevisto, crollo, baco};
enum Quantita_melassa{ nessuna, poca, molta=3};
enum Tipo_caverna{normale=1, speciale, accidentata, uscita};


struct Caverna{
  struct Caverna* avanti;
  struct Caverna* sinistra;
  struct Caverna* destra;
  enum Quantita_melassa melassa;
  enum Tipo_imprevisto imprevisto;
  enum Tipo_caverna caverna;
};
