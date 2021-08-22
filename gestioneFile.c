#include "input.h"
#include "gestioneFile.h"
/**
 * Leggo i dati di un file binario e creo un vettore dinamico con i dati del file
 * @param vettore vettore da popolare
 * @param fp puntatore al file binario
 */
void leggiDaFileBinario(VD *vettore, FILE *fp){

    fread(&vettore->numInserimenti, sizeof(int), 1, fp);

    vettore->datiSoggetti = (RecordSoggetto *) malloc(vettore->numInserimenti * sizeof(RecordSoggetto));

    if(vettore->datiSoggetti == NULL)
        exit(-1);

    fread(vettore->datiSoggetti, sizeof(RecordSoggetto), vettore->numInserimenti, fp);
}
/**
 * Chiude un file eseguendo i controlli sul file passato
 * @param fp puntatore al file da chiudere
 * @return NULL se tutto è andato a buon fine
 */
FILE * chiudiFile(FILE * fp){
    if(fp != NULL)
        fclose(fp);
    return NULL;
}
/**
 *  Legge i dati di un vettore dinamico e crea un file binario con i dati letti
 * @param elenco puntatore alla struttura soggetto
 * @param nomeFile Nome del file sul quale si vuole salvare i dati
 * @param nElementi numero degli elementi presenti nel vettore dinamico
 */
void salvaDati(RecordSoggetto *elenco, char *nomeFile, int nElementi){

    FILE *fp = NULL;
    fp = fopen(nomeFile, "wb");      //test
    if (!fp){
        printf("\nApertura file non riuscita");
        exit(-1);
    }else {
        fwrite(&nElementi, sizeof(int), 1, fp);
        fwrite(elenco, sizeof(RecordSoggetto), nElementi, fp);

        fclose(fp);
    }
}
/*Legge il file binario suggerito dall'utente e carica il contenuto nel vettore dinamico*/
void caricaDati(VD *vettore, char *nomefile){
    FILE *fp = NULL;

    fp = fopen(nomefile, "rb");      //apre il file in modalita' lettura
    if(!fp)
        exit(-1);                    //Esce se l'apertura del file non va a buon fine
    else {
        leggiDaFileBinario(vettore, fp);    //Legge il file, esegue allocazione in memoria e lo carica nel vettore dinamico
        chiudiFile(fp);                     //Chiude il file
        printf("\nDati caricati!");
    }
}
/*Richiede all'utente di inserire il nome del file che si desidera aprire, successivamente la funzione "caricaDati"
 * legge il file e carica l'elenco presente nel file nel vettore dinamico*/
void accediDataBaseFile(VD *vettore){
    char file[NOME_FILE_MAX+1];
    printf("\nInserisci il nome del file da aprire: ");
    scanf("%s", file);
    caricaDati(vettore, file);
}
/*Richiede all'utente l'inserimento del nome del file sul quale si vuole salvare,
 * successivamente salva i dati sul file*/
void salvataggio(VD *vettore){

    char nomeFile[NOME_FILE_MAX+1];

    printf("Inserisci il nome del file sul quale vuoi salvare i dati:");
    scanf("%s", nomeFile);

    salvaDati(vettore->datiSoggetti, nomeFile, vettore->numInserimenti);
    printf("\nDati salvati!");
}
/*Salva in un file binario il contenuto criptato del vettore dinamico*/
void salvaDatiCriptati(RecordSoggetto *elenco, char *nomeFile, int nElementi) {
    FILE *fp = NULL;
    decryptData(elenco, nElementi);         //Encrypt dei dati
    fp = fopen(nomeFile, "wb");      //Apretura file
    if (!fp){
        printf("\nApertura file non riuscita");
        exit(-1);
    }else {
        fwrite(&nElementi, sizeof(int), 1, fp);
        fwrite(elenco, sizeof(RecordSoggetto), nElementi, fp);  //Scrittura del file con i dati criptati

        fclose(fp);
    }
}
/*Legge il file binario suggerito dall'utente, carica il contenuto nel vettore dinamico e decripta i dati ottenuti da file */
void caricaDatiCriptati(VD *vettore, char *nomefile){
    FILE *fp = NULL;

    fp = fopen(nomefile, "rb");      //Apre il file in modalita' lettura
    if(!fp)
        exit(-1);                    //Esce se l'apertura del file non va a buon fine
    else {
        leggiDaFileBinario(vettore, fp);    //Legge il file, esegue allocazione in memoria e lo carica nel vettore dinamico
        chiudiFile(fp);                     //Chiude il file
        printf("\nDati caricati e criptati!");
    }
    decryptData(vettore->datiSoggetti, vettore->numInserimenti);   //Decrypt dei dati in base alle informazioni fornite
}
/*Chiede all'utente il nome del file da caricare e successivamente la procedura "caricaDatiCriptati" decripta i file*/
void accediDataBaseFileCriptato(VD *vettore){
    char file[NOME_FILE_MAX+1];
    printf("\nInserisci il nome del file da aprire: "); //Richiesta nome file
    scanf("%s", file);                                  //Acquisizione nome file
    caricaDatiCriptati(vettore, file);                  //Carica i dati nel vettore e decripta il contenuto
}
/*Chiede all'utente il nome del fine sul quale effettuare il salvataggio dei dati criptati, successivamente li salva nel file criptati*/
void salvataggioCriptato(VD *vettore){
    char nomeFile[NOME_FILE_MAX+1];
    printf("Inserisci il nome del file sul quale vuoi salvare i dati:");    //Richiesta nome file
    scanf("%s", nomeFile);                                                  //Acquisizione nome file
    //test -> funziona ok ma e' da spostare decodificaDati(vettore);
    salvaDatiCriptati(vettore->datiSoggetti, nomeFile, vettore->numInserimenti);    //Salva i dati nel file e ne cripta il contenuto
    printf("\nDati salvati!");
}
/****-----Decrypt------*****/
/*Controllo sui dati salvati sul vettore e decripta in base alle info fornite*/
void decryptData(RecordSoggetto *elenco, int nElementi){     //Encrypt & Decrypt
    int i;
    int j;
    //Effettua il ciclo
    for (i = 0; (i < nElementi); i++) {
        /*decrypt nome e cognome*/
        for (j = 0; j < NOME_MAX; ++j) {
            if (elenco[i].nome[j] == 'a')
                elenco[i].nome[j] = 'z';
            if (elenco[i].cognome[j] == 'a')
                elenco[i].cognome[j] = 'z';
            if (elenco[i].nome[j] == 'b')
                elenco[i].nome[j] = 'y';
            if (elenco[i].cognome[j] == 'b')
                elenco[i].cognome[j] = 'y';
            if (elenco[i].nome[j] == 'A')
                elenco[i].nome[j] = 'Z';
            if (elenco[i].cognome[j] == 'A')
                elenco[i].cognome[j] = 'Z';
            if (elenco[i].nome[j] == 'B')
                elenco[i].nome[j] = 'Y';
            if (elenco[i].cognome[j] == 'B')
                elenco[i].cognome[j] = 'Y';
        }
    }
}

