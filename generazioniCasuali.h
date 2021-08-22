#ifndef PROGETTOC_GENERAZIONICASUALI_H
#define PROGETTOC_GENERAZIONICASUALI_H

#define MIN 0
#define UNO 1
#define ALTEZZA_MAX 250     //Valore Altezza massima consentito da input
#define PESO_MAX 200        //Valore Peso massimo consentito da input
#define MAX_GRADI_GPS 360
#define MIN_GRADI_GPS (-360)

#define CENTO 100
#define LETTERA_A 65        //valori ascii dei caratteri corrispondenti
#define LETTERA_F 70        //valori ascii dei caratteri corrispondenti
#define LETTERA_MIN_A 97    //valori ascii dei caratteri corrispondenti
#define LETTERA_MIN_Z 122   //valori ascii dei caratteri corrispondenti
#define NUMERO_0_CHAR 48    //valori ascii dei caratteri corrispondenti
#define NUMERO_9_CHAR 57    //valori ascii dei caratteri corrispondenti
#define NUM_NOMI 15         //Numero di possibili nomi inseriti per la generazione casuale

/*Subroutine di generazione casuale dei tratti distintivi del soggetto/criminale*/
void generaRecord(VD *vettore);
RecordSoggetto acquisisciPersonaCasuale();
void riempiVettoreColore(char v[],int dim);
void riempiVettoreImpronta(char v[],int dim);
void generaNome(char *stringaNome);
void generaCognome(char *stringaNome);
void generaResidenza(char *stringaNome);

/*Subroutine di generazione casuale di numeri o caratteri*/
int generaIntero(int min, int max);
float generaFloat(int min, int max);
double generaDouble(int min, int max);
char generaChar(int min, int max);
_Bool generaBooleano();
int generaInteroEnum();

#endif //PROGETTOC_GENERAZIONICASUALI_H
