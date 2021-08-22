#include "input.h"
#include "generazioniCasuali.h"
#include "output.h"
/**
 * Permette di generare casualmente tutte le caratteristiche di un soggetto
 * @param vettore puntatore al vettore che acquisisce tutte le informazioni dalla generazione e le salva
 */
void generaRecord(VD *vettore){

    RecordSoggetto soggetto;
    printf("*Dati generati casualmente*");
    soggetto = acquisisciPersonaCasuale();
    printf("\n");
    aggiungiSoggetto(vettore, soggetto);
}
/*Acquisisce, per ogni tratto distintivo del soggetto, delle informazioni casuali ed effettua la loro stampa istantanea*/
RecordSoggetto acquisisciPersonaCasuale(){
    RecordSoggetto persona;

    generaResidenza(persona.residenza);                         //Residenza casuale
    generaNome(persona.nome);                                   //Acquisizione nome casuale
    generaCognome(persona.cognome);                             //Acquisizione cognome casuale
    persona.altezza=generaIntero(MIN, ALTEZZA_MAX);             //Acquisizione altezza casuale
    persona.peso= generaFloat(MIN,PESO_MAX);                    //Acquisizione peso casuale
    riempiVettoreColore(persona.coloreOcchi, COLORE_MAX);       //Acquisizione colore degli occhi casuale
    riempiVettoreColore(persona.coloreCapelli, COLORE_MAX);     //Acquisizione colore dei capelli casuale
    persona.lunghezzaCapelli=generaInteroEnum();                //Acquisizione lunghezza capelli casuale

    /*Verifica: se il nome e' femminile NON presenta barba, se maschile casualmente definisce se ce l'ha o non ce l'ha*/
    if(strcmp(persona.nome, "Alessia")==0
        || strcmp(persona.nome, "Giulia")==0
        || strcmp(persona.nome, "Valentina")==0
        || strcmp(persona.nome, "Valentina")==0
        || strcmp(persona.nome, "Cinzia")==0
        || strcmp(persona.nome, "Marinella")==0
        || strcmp(persona.nome, "Sara")==0
        || strcmp(persona.nome, "Gianna")==0)
        persona.barba=0;
    else persona.barba=generaBooleano();                         //Acquisizione presenza di barba casuale per i nomi maschili

    persona.cicatriciVolto=generaBooleano();                    //Acquisizione presenza di cicatrici casuale
    riempiVettoreImpronta(persona.impronta,IMPRONTA_MAX);       //Inserimento casuale impronta digitale
    persona.ultimaPosizione.latitudine= generaDouble(MIN_GRADI_GPS,MAX_GRADI_GPS);//Latitudine casuale
    persona.ultimaPosizione.longitudine= generaDouble(MIN_GRADI_GPS,MAX_GRADI_GPS);//Longitudine casuale
    persona.stato=generaInteroEnum();//Acquisizione stato casuale

    /*STAMPA il soggetto generato casualmente*/
    stampaSoggetto(persona);

    return persona;
}
/*
 * *****----Subroutine per la generazione di parametri casuali------******
 * */
/*genera un numero tipo double casualmente*/
double generaDouble(int min, int max){
    double numCasuale;
    max*=10;
    numCasuale= min+rand()%(max-min+1);
    return (numCasuale*generaIntero(min,max))/100000;//Espressione divisa per 100k per ottentere 6 decimali
}
/*genera un intero casuale entro dei parametri min e max*/
int generaIntero(int min, int max){
    int numCasuale;
    numCasuale= min+rand()%(max-min+1);
    return numCasuale;
}
/*Genera un valore tipo float entro dei parametri min e max*/
float generaFloat(int min, int max){
    float numCasuale;
    max*=100;
    numCasuale= min+rand()%(max-min+1);
    return numCasuale/100000;
}
/*Genera un carattere minuscolo casuale*/
char generaChar(int min, int max){
    char carattereCasuale;
    carattereCasuale= min+rand()%(max-min+1);
    return carattereCasuale;
}
/*Genera casualmente un booleano (0 o 1)*/
_Bool generaBooleano(){
    int x;
    x= generaIntero(MIN, UNO);
    return x;
}
/*Genera casualmente un intero (che rappresentera' il valore di una enumerazione) entro una range equivalente all'enumerazione interessata*/
int generaInteroEnum(){
    int numCasuale;
    numCasuale= generaIntero(ZERO,3);//ALTRO=0, CORTI=1, MEDI=2, LUNGHI=3
    return numCasuale;
}
/*Popola un vettore con caratteri maiuscoli*/
void riempiVettoreColore(char v[],int dim){
    int i;
    int casuale;

    for (i = 0; i < dim; ++i) {
        casuale = generaIntero(MIN, CENTO);
        if (casuale>(CENTO/2)) {
            v[i] = generaChar(LETTERA_A, LETTERA_F);   /*Genera carattere tra la lettera 'A' e 'F'*/
        }else {
            v[i] = generaChar(NUMERO_0_CHAR, NUMERO_9_CHAR);
        }
    }
}
/*Popola un vettore con caratteri minuscoli e numeri casualmente*/
void riempiVettoreImpronta(char v[],int dim){
    int i;
    int casuale;
    for (i = 0; i < dim; ++i) {
        casuale = generaIntero(MIN, CENTO);
        if (casuale>(CENTO/2)) {
            v[i] = generaChar(LETTERA_MIN_A, LETTERA_MIN_Z); /*Genera carattere tra la lettera 'a' e 'z'*/
        }else{
            v[i] = generaChar(NUMERO_0_CHAR, NUMERO_9_CHAR);
        }
    }
}
/*Prende in ingresso un puntatore a stringa egli assegna casualmente un nome tra una lista di 10*/
void generaNome(char *stringaNome){
    int numCasuale;
    char nome[NUM_NOMI][NOME_MAX+1]={"Alessandro","Fabio","Giulio","Giuseppe","Alberto","Luca","Giovanni","Antonio","Sara","Marinella","Alessia","Giulia","Cinzia","Gianna","Valentina"};

    numCasuale= MIN + rand()%(14-MIN+1);   //genera un numero casuale tra 0 e il numero dei nomi(15-1)
/*Assegna il nome alla stringa passata in base al num casuale*/
        strcpy(stringaNome,nome[numCasuale]);
}
/*Prende in ingresso un puntatore a stringa e gli assegna casualmente un cognome tra una lista di 15*/
void generaCognome(char *stringaNome){
    int numCasuale;
    char cognome[NUM_NOMI][NOME_MAX+1]={"Casti","Pisu","Frau","Onidi","Carta","Sorrentino","Tola","Pinna","Pintus","Cadeddu","Erdas","Cogoni","Tola","Sorrentino","Congiu"};

    numCasuale= MIN + rand()%(14-MIN+1);   //genera un numero casuale tra 0 e il numero dei cognomi(15-1)
/*Assegna il nome alla stringa passata in base al num casuale*/
        strcpy(stringaNome,cognome[numCasuale]);
}
/*Prende in ingresso un puntatore a stringa e gli assegna casualmente una Residenza tra una lista di (15-1)*/
void generaResidenza(char *stringaNome){
    int numCasuale;
    char residenza[NUM_NOMI][RESIDENZA_MAX+1]={"Villasimius","Cagliari", "Oristano","Nuoro","Sanluri","Villacidro","Sassari", "Pompu","Orgosolo","Uta","Iglesias","Sinnai","Bosa", "Sanluri", "Baunei"};

    numCasuale= MIN + rand()%(14-MIN+1);   //genera un numero casuale tra 0 e 14 che corrisponde l'indice della matrice che contiene i nomi
/*Assegna il nome alla stringa passata in base al num casuale*/
    strcpy(stringaNome,residenza[numCasuale]);
}