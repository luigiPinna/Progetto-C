#include "input.h"
#include "generazioniCasuali.h"
#include "controlliInput.h"

/*Controlla se l'inserimento dell'utente e' corretto, alternativamente rilascia un messaggio di errore e riacquisisce l'input*/
void controlloAltezza(RecordSoggetto *input){
    while (input->altezza < MIN || input->altezza > ALTEZZA_MAX) {
        printf("\nErrore! Inserisci un valore in cm tra %d e %d:\n", MIN, ALTEZZA_MAX);
        scanf("%d", &input->altezza);
    }
}
/*Controlla se l'inserimento dell'utente e' corretto, alternativamente rilascia un messaggio di errore e riacquisisce l'input*/
void controlloPeso(RecordSoggetto *input){
    while (input->peso < MIN || input->peso > PESO_MAX){
        printf("\nErrore! Inserisci un valore in KG tra %d e %d:\n", MIN, PESO_MAX);
        scanf("%f", &input->peso);
    }
}
/*Controlla se l'inserimento dell'utente e' corretto, alternativamente rilascia un messaggio di errore e riacquisisce l'input*/
void controlloLatitudine(RecordSoggetto *input){
    while (input->ultimaPosizione.latitudine < MIN_GRADI_GPS || input->ultimaPosizione.latitudine > MAX_GRADI_GPS){
        printf("\nErrore! Inserisci un valore tra %d e %d:\n", MIN_GRADI_GPS, MAX_GRADI_GPS);
        scanf("%lf", &input->ultimaPosizione.latitudine);
    }
}
/*Controlla se l'inserimento dell'utente e' corretto, alternativamente rilascia un messaggio di errore e riacquisisce l'input*/
void controlloLongitudine(RecordSoggetto *input){
    while (input->ultimaPosizione.longitudine < MIN_GRADI_GPS || input->ultimaPosizione.longitudine > MAX_GRADI_GPS) {
        printf("\nErrore! Inserisci un valore tra %d e %d:\n", MIN_GRADI_GPS, MAX_GRADI_GPS);
        scanf("%lf", &input->ultimaPosizione.longitudine);
    }
}
/*Controlla se l'inserimento dell'utente e' corretto, alternativamente rilascia un messaggio di errore e riacquisisce l'input*/
void controlloBoolBarba(RecordSoggetto *input){
    while (!(input->barba == ZERO || input->barba==UNO)) {
        printf("\nErrore! Ha la barba? [SI->'1' | NO->'0']:\n");
        scanf("%d", &input->barba);
    }
}
/*Controlla se l'inserimento dell'utente e' corretto, alternativamente rilascia un messaggio di errore e riacquisisce l'input*/
void controlloBoolCicatrici(RecordSoggetto *input){
    while (!(input->cicatriciVolto == ZERO || input->cicatriciVolto==UNO)) {
        printf("\nErrore! Ha cicatrici in volto? [SI->'1' | NO->'0']:\n");
        scanf("%d", &input->cicatriciVolto);
    }
}
/*Controlla se l'inserimento dell'utente e' corretto, alternativamente rilascia un messaggio di errore e riacquisisce l'input*/
void controlloStato(RecordSoggetto *input){
    while (input->stato < ZERO || input->stato > ENUM_MAX) {    //LIBERO=0, RICERCATO=1, IN_ARRESTO=2, EVASO=3
        printf("\nErrore! Inserisci un valore tra %d e %d:\n", LIBERO, EVASO);
        scanf("%d", &input->stato);
    }
}
void controlloTipoCapelli(RecordSoggetto *input){
    while (input->lunghezzaCapelli < ZERO || input->lunghezzaCapelli > ENUM_MAX) {  //CORTI=0,MEDI=1,LUNGHI=2,ALTRO=3
        printf("\nErrore! Inserisci un valore tra %d e %d:\n", ALTRO, LUNGHI);
        scanf("%d", &input->lunghezzaCapelli);
    }
}