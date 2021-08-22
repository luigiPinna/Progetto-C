#include "input.h"
#include "output.h"

/*Permette la stampa del record singolo o, in alternativa scelta dall'utente, la stampa di tutti i soggetti inseriti presenti nel vettore*/
void stampaRecord(VD *vettore){
    int id;
    //Acquisizione id contatto
    printf("Quale contatto vuoi stampare?\nInserisci l'id o premi 0 per stamparli tutti->");
    scanf("%d", &id);
    svuotaBuffer();
    printf("\n");
    if(vettore->numInserimenti>=1) { //Controlla se sono presenti piu' soggetti nel vettore
        if (id == 0) {                           //se l'utente preme '0' stampa tutti i soggetti del DB
            stampaElencoCriminali(vettore->datiSoggetti, vettore->numInserimenti);
            printf("\nContatti stampati!");
        }
        if (id <= vettore->numInserimenti && id != 0) {   //l'utente sceglie quale soggetto stampare
            stampaSoggetto(vettore->datiSoggetti[id - 1]);
        }
        if (id > vettore->numInserimenti) {                               //se il soggetto non e' presente appare la scritta di errore
            printf("Non esiste un contatto con l\'id specificato.");
        }
        printf("\n");
    }else{
        printf("\nAttenzione! Non sono presenti soggetti in elenco.\n");
    }
}
/*Procedura che permette di stampare tutti i criminali inseriti*/
void stampaElencoCriminali(RecordSoggetto *elenco, int nElementi) {
    int i;
    int j=1;

    for (i = 0; i < nElementi; ++i) {
        printf("\t SOGGETTO %d",j);
        stampaSoggetto(elenco[i]);
        j++;
        printf("\n\t*****************\t\n");
    }
}
/**
 * Permette la stampa del record di un criminale
 * @param soggetto riceve in incresso un soggetto da stampare
 */
void stampaSoggetto(RecordSoggetto soggetto){
    int i;
    printf("\nNome: \t\t\t\t%s", soggetto.nome);
    printf("\nCognome: \t\t\t%s", soggetto.cognome);
    printf("\nAltezza: \t\t\t%d cm", soggetto.altezza);
    printf("\nPeso: \t\t\t\t%.2f kg", soggetto.peso);
    printf("\nColore Occhi [RR/GG/BB]: \t");
    //Stampa colore occhi
    for (i = 0; i < COLORE_MAX; ++i) {
        printf("[%c]", soggetto.coloreOcchi[i]);
    }
    printf("\nColore Capelli [RR/GG/BB]:\t");
    //Stampa colore capelli
    for (i = 0; i < COLORE_MAX; ++i) {
        printf("[%c]", soggetto.coloreCapelli[i]);
    }
    identificaCapelli(soggetto);        //Identifica l'input utente ed effettua la sua stampa
    printf("\n");
    identificaBarba(soggetto.barba);    //Identifica l'input utente ed effettua la sua stampa
    printf("\n");
    identificaCicatrici(soggetto.cicatriciVolto);   //Identifica l'input utente ed effettua la sua stampa
    printf("\nImpronta digitale:\t\t");
    //Stampa impronta digitale
    for (i = 0; i < IMPRONTA_MAX; ++i) {
        printf("|%c|", soggetto.impronta[i]);
    }
    printf("\nResidenza: \t\t\t%s", soggetto.residenza);
    //Stampa posizione GPS
    printf("\nUltima posizione GPS:\t\t");
    printf("Latitudine: %.6lf", soggetto.ultimaPosizione.latitudine);
    printf(" | Longitudine: %.6lf", soggetto.ultimaPosizione.longitudine);
    identificaStatoSoggetto(soggetto);  //Identifica l'input utente ed effettua la sua stampa
}
/*Accoglie la procedura confrontaRecord e l'inserimento dell'utente*/
void confronto(VD *vettore) {
    int primoId;            //Prima persona da confrontare
    int secondoId;          //Seconda persona da confrontare
    int confronto;          //Accogliera' il return della funzione "confrontaRecord"

    /*Input untente*/
    printf("Quali soggetti vuoi confrontare?\nInserisci i loro id:");
    printf("\nIn elenco sono presenti [%d] soggetti", vettore->numInserimenti);
    printf("\nPrimo id:");
    scanf("%d", &primoId);
    printf("Secondo id:");
    scanf("%d", &secondoId);

    //Controlla se sono presenti piu' soggetti nel vettore per effettuare efficacemente un confronto
    if (vettore->numInserimenti > 1) {
        //Se il confronto avviene con un soggetto non presente visualizza messaggio di errore
        if(primoId > vettore->numInserimenti || secondoId > vettore->numInserimenti ){
            printf("Stai confrontando con un soggetto che non e' presente in elenco.\nIl numero attuale dei soggetti e' %d. Riprova!", vettore->numInserimenti);
        }
        else {
            confronto = confrontaRecord(&vettore->datiSoggetti[primoId], &vettore->datiSoggetti[secondoId]);
            printf("\nI soggetti selezionati sono similari al %d%%", confronto);
        }
    } else {
        printf("Non ci sono abbastanza soggetti per effettuare il confronto! Grazie");
    }
}

/*Riceve in ingresso due puntatori a due differenti record e restituisce un valore in
 * percentuale in relazione alla similarità tra i due record*/
int confrontaRecord(RecordSoggetto *recordUno, RecordSoggetto *recordDue ){
    double confronto=0;     //Variabile che conterra' i calcoli per il confronto sulla somiglianza
    int percentuale;        //Percentuale di somiglianza da restituire

/*Confronti di tutti i tratti del soggetto*/
    if(strcmp(recordUno->nome, recordDue->nome) == 0)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    if(strcmp(recordUno->cognome, recordDue->cognome) == 0)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    if(recordUno->altezza==recordDue->altezza)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    if(recordUno->peso==recordDue->peso)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    confronto=confronto+confrontaColoreOcchi(recordUno,recordDue);
    confronto=confronto+confrontaColoreCapelli(recordUno,recordDue);
    if(recordUno->lunghezzaCapelli==recordDue->lunghezzaCapelli)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    if(recordUno->barba==recordDue->barba)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    if(recordUno->cicatriciVolto==recordDue->cicatriciVolto)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    confronto=confronto+confrontaImpronta(recordUno,recordDue);
    if(strcmp(recordUno->residenza, recordUno->residenza) == 0)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    if(recordUno->ultimaPosizione.latitudine==recordDue->ultimaPosizione.latitudine)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    if(recordUno->ultimaPosizione.longitudine==recordDue->ultimaPosizione.longitudine)
        confronto=confronto+PERCENTUALE_CONFRONTO;
    if(recordUno->stato==recordDue->stato)
        confronto=confronto+PERCENTUALE_CONFRONTO;

    percentuale=confronto;  //assegna alla variabile intera il valore float
    /*Se i due soggetti sono uguali piu' del 99.3% risultano uguali al 100% */
    if(confronto>99.3)
        percentuale=100;

    return percentuale;
}
/*Permette di confrontare l'impronta digitale tra 2 soggetti*/
float confrontaImpronta(RecordSoggetto *recordUno, RecordSoggetto *recordDue){
    int i;
    int conta=0;
    float percentuale =0;
    for(i = 0; i < IMPRONTA_MAX; i++){
        if (recordUno->impronta[i] == recordDue->impronta[i]) {
            conta++;
        }
    }
    if (conta==COLORE_MAX){
        percentuale=PERCENTUALE_CONFRONTO;
    }
    return percentuale;
}
/*Confronta il colore occhi tra 2 soggetti*/
float confrontaColoreOcchi(RecordSoggetto *recordUno, RecordSoggetto *recordDue){
    int i;
    int conta=0;
    float percentuale =0;
    for(i = 0; i < COLORE_MAX; i++){
        if (recordUno->coloreOcchi[i] == recordDue->coloreOcchi[i]) {
            conta++;
        }
    }
    if (conta==COLORE_MAX){
        percentuale=PERCENTUALE_CONFRONTO;
    }
    return percentuale;
}
/*Confronta il colore dei capelli tra 2 soggetti*/
float confrontaColoreCapelli(RecordSoggetto *recordUno, RecordSoggetto *recordDue){
    int i;
    int conta=0;
    float percentuale =0;
    for(i = 0; i < COLORE_MAX; i++){
        if (recordUno->coloreCapelli[i] == recordDue->coloreCapelli[i]) {
            conta++;
        }
    }
    if (conta==COLORE_MAX){
        percentuale=PERCENTUALE_CONFRONTO;
    }
    return percentuale;
}