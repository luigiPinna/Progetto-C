#ifndef PROGETTOC_INPUT_H
#define PROGETTOC_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define NOME_MAX 63                 //Dimensione massima delle stringhe per nome e cognome
#define COLORE_MAX 6                //Dimensione massima del vettore di caratteri colore RGB
#define IMPRONTA_MAX 16             //Dimensione massima del vettore di caratteri impronta digitale
#define RESIDENZA_MAX 511           //Dimensione massima della stringa residenza
#define ZERO 0
#define PERCENTUALE_CONFRONTO 7.69  //(100/13) numero impiegato per fare i calcoli sui confronti tra soggetti

typedef enum {ALTRO, CORTI, MEDI, LUNGHI} TipoCapelli;              //Enumerazione tipologie di capelli
typedef enum {LIBERO, RICERCATO, IN_ARRESTO, EVASO} StatoSoggetto;  //Enumerazione tipologie di Stato Soggetto

//Enumerazione con tutte le possibili scelte del menu
typedef enum {ESCI, INSERISCI, STAMPA, GENERA, CANCELLA, CERCA, CONFRONTO, CARICA_DATI, SALVA_DATI, ORDINA, CARICA_DATI_CRIPTATI,SALVA_DATI_CRIPTATI, ORDINA_CONFRONTO} SceltaMenu;

/*Struttura con la posizione GPS(Latitudine e Longitudine*/
typedef struct {
    double latitudine;
    double longitudine;
}PosizioneGPS;

/*Struttura che contiene i caratteri distintivi del soggetto/criminale */
typedef struct {
    char nome[NOME_MAX+1];
    char cognome[NOME_MAX+1];
    int altezza;
    float peso;
    char coloreOcchi[COLORE_MAX];   //Valore esadecimale tra 0 e 9 - A e F
    char coloreCapelli[COLORE_MAX]; //Valore esadecimale tra 0 e 9 - A e F
    TipoCapelli lunghezzaCapelli;
    _Bool barba;
    _Bool cicatriciVolto;
    char impronta[IMPRONTA_MAX];
    char residenza[RESIDENZA_MAX+1];
    PosizioneGPS ultimaPosizione;
    StatoSoggetto stato;
} RecordSoggetto;

/*Struttura che contiene il vettore dinamico in cui verranno memorizzati i criminali e una variabile che contiene il numero di soggetti inseriti*/
typedef struct {
    RecordSoggetto *datiSoggetti;
    int numInserimenti;
}VD;

/*Avvia l'intero programma Criminali*/
void avviaProgrammaCriminali();

/*Inizializzazione vettore dinamico principale, che accogliera' tutti i soggetti*/
void inizializzaVettoreDinamico(VD *vettore);

/*Subroutine di input - Menu, inserimento da utente e aggiunta elemento nel DB*/
RecordSoggetto acquisisciPersona();
void aggiungiSoggetto(VD *vettore, RecordSoggetto soggetto);
void inserisciRecord(VD *vettore);  //ok
SceltaMenu menuPrincipale();

/*Cicli di inserimento input utente*/
void inserisciColoreCapelli(RecordSoggetto *rgb);
void inserisciColoreOcchi(RecordSoggetto *rgb);
void inserisciImpronta(RecordSoggetto *rgb);
/*Svuota il buffer*/
void svuotaBuffer();

/*Identificazioni di input*/
void identificaBarba(_Bool barba);
void identificaCicatrici(_Bool cicatrici);
void identificaCapelli(RecordSoggetto tipoCapelli);
void identificaStatoSoggetto(RecordSoggetto statoSoggetto);

#endif //PROGETTOC_INPUT_H
