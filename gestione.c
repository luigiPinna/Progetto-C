
#include "input.h"
#include "gestione.h"
#include "output.h"
/**
 * Permette l'eliminazione di tutti i soggetti oppure di uno a scelta dell'utente
 * @param vettore puntatore a vettore che contiene tutti i soggetti
 */
void eliminaSoggetti(VD *vettore){  //correggere se si preme 0, esce dal programma
    int scelta;
    int indice;
    do{
        printf("\nPremi [0] per cancellarli tutti, [1] per scegliere il soggetto");
        scanf("%d", &scelta);
        svuotaBuffer();
        if(vettore->numInserimenti>=1) {        //Controlla se sono presenti contatti, se presenti continua, altrimenti stampa messaggio
            switch (scelta) {                       //Breve menu per l'utente che puo' scegliere quale contatto cancellare o se cancellarli tutti
                case 0:
                    inizializzaVettoreDinamico(vettore);    //Se l'utente sceglie di cancellarli tutti inizializza il vettore
                    printf("\nElenco cancellato!");
                    break;
                case 1:
                    printf("Che soggetto vuoi eliminare?");
                    scanf("%d", &indice);
                    eliminaCriminale(vettore->datiSoggetti, indice, vettore->numInserimenti);   //Elimina un singolo criminale scelto dall'utente
                    printf("\nSoggetto eliminato!");
                    break;
                default:
                    printf("Inserimento errato!");
            }
        }else{
            printf("\nAttenzione! Non sono presenti soggetti in elenco.");
        }
    }while(scelta != 1 && scelta != 0);     //controllo inserimento utente, se errato richiede nuovamente l'inserimento
}
/**
 * Rimuove l'elemento in una posizione indice del vettore acquisita dall'utente
 * @param vettore Puntatore al vettore
 * @param indice indice dell'elemento da rimuovere
 */
RecordSoggetto *eliminaCriminale(RecordSoggetto *elenco, int indice, int nElementi){
    int i;
    indice--;
    VD vettore;
    for(i=indice; i<(nElementi-1); i++){
        elenco[i] = elenco[i+1];
    }
    rimuoviElementoInCoda(&vettore);
    return elenco;
}
/**
 * Rimuove l'elemento in coda del vettore
 * @param vettore Puntatore al vettore che contiene i soggetti
 */
void rimuoviElementoInCoda(VD *vettore){
    if(vettore->datiSoggetti != NULL) {
        vettore->numInserimenti--;
        vettore->datiSoggetti = (RecordSoggetto *) realloc(vettore->datiSoggetti, vettore->numInserimenti * sizeof(RecordSoggetto));
    }
}
/**
 * Restituisce la dimensione dell'array
 * @param vettore Puntatore al vettore
 * @return Attuale dimensione del vettore dinamico
 */
int dimensioneVettore(VD *vettore){
    return vettore->numInserimenti;
}
/**
 * Permette di ottenere un valore del vettore in una determinata posizione.
 * @param vettore Puntatore al vettore
 * @param posizione Posizione del valore
 * @return Elemento
 */
RecordSoggetto recuperaElemento(VD *vettore, int posizione){
    return vettore->datiSoggetti[posizione];
}
/**
 * Cerca e stampa gli elementi che contengono nel nome o cognome la stringa inserita dall'utente
 * @param vettore vettore dinamico in cui sono salvati i criminali
 */
void cercaSoggetto(VD *vettore){
    char *stringa;
    int i;
    int conta=0;
    RecordSoggetto aux;
    printf("Inserisci il nome o il cognome del soggetto che vuoi cercare");
    printf("\n\t[Rispetta le maiuscole iniziali]");
    scanf("%[^\n]s", stringa);
    for(i = 0; i < dimensioneVettore(vettore); i++){
        aux = recuperaElemento(vettore, i);
        if(strcmp(aux.nome, stringa) == 0  || strcmp(aux.cognome, stringa) == 0) {
            stampaSoggetto(aux);
            conta++;
        }
    }
    if (conta==0){
        printf("\nIl soggetto inserito non e' presente nell'elenco");
    }
}
/********************************FUNZIONI DI CONFRONTO e ORDINAMENTO*****************************/
/*Ordina il data base dei soggetti per cognome*/
void ordinaPerCognome(RecordSoggetto *elenco, int nElementi) {
    _Bool flag;
    int i;
    RecordSoggetto veicolo; //Variabile di tipo RecordSoggetto che funge da veicolo per gli spostamenti ordinati
    do {
        //variabile di flag assegnata a falso, sara' true quando tutti gli elementi saranno controllati (e ordidati)
        flag = false;
        //Fino a a num Elementi -1 perche' alla fine dei controlli l'ultimo elemento sara' nella sua giusta posizione
        for (i = 0; i < (nElementi - 1); i++) {
            //se l’elemento vettore[i+1] è maggiore del successivo
            if (strcmp(elenco[i + 1].cognome, elenco[i].cognome) < 0) {

                //assegna alla variabile veicolo il valore della casella corrispondente all’indice i
                veicolo = elenco[i];
                //scambia i valori tra la cella e la sua successiva
                elenco[i] = elenco[i + 1];
                //assegna alla posizione successiva il contenuto che e' stato copiato nella variabile veicolo
                elenco[i + 1] = veicolo;

                //setta la variabile flag come vera poiché è stato effettuato uno scambio
                flag = true;
            }
        }
    } while (flag); //finché flag permane vera il ciclo continua i controlli
    printf("\nElenco ordinato per cognome!\n");
}
/*Ordina il data base dei soggetti per nome*/
void ordinaPerNome(RecordSoggetto *elenco, int nElementi){
    _Bool flag;
    int i;
    RecordSoggetto veicolo; //Variabile di tipo RecordSoggetto che funge da veicolo per gli spostamenti ordinati
    do {
        //variabile di flag assegnata a falso, sara' true quando tutti gli elementi saranno controllati (e ordidati)
        flag = false;
        //Fino a a num Elementi -1 perche' alla fine dei controlli l'ultimo elemento sara' nella sua giusta posizione
        for (i = 0; i < (nElementi - 1); i++) {
            //se l’elemento vettore[i+1] è maggiore del successivo
            if (strcmp(elenco[i + 1].nome, elenco[i].nome) < 0) {

                //assegna alla variabile veicolo il valore della casella corrispondente all’indice i
                veicolo = elenco[i];
                //scambia i valori tra la cella e la sua successiva
                elenco[i] = elenco[i + 1];
                //assegna alla posizione successiva il contenuto che e' stato copiato nella variabile veicolo
                elenco[i + 1] = veicolo;

                //setta la variabile flag come vera poiché è stato effettuato uno scambio
                flag = true;
            }
        }
    } while (flag); //finché flag permane vera il ciclo continua i controlli
    printf("\nElenco ordinato per nome!\n");
}

/*Ordina i soggetti presenti nel vettore dinamico in ordine alfabetico per cognome o per nome in base alla scelta dell'utente*/
void ordinaAlfabeticamente(RecordSoggetto *elenco, int nElementi) {
    char scelta;

/*l'utente puo scegliere se ordinare l'elenco in base al nome o al cognome*/
    do {
        printf("\nOrdinamento elenco:\nper NOME [Digita 'n'] | per COGNOME [Digita 'c']");
        scanf("%c", &scelta);
        svuotaBuffer();
        if(scelta != 'n' && scelta != 'c'){     //Se la scelta e' errata visualizza errore
            printf("\n\tAttenzione! Scelta non valida");
        }
        if (scelta == 'c') {
            ordinaPerCognome(elenco,nElementi);     //Ordinamento elenco per cognome
        }
        if (scelta == 'n') {
            ordinaPerNome(elenco, nElementi);       //Ordinamento elenco per nome
        }
    }while(scelta != 'n' && scelta != 'c');
}
/*Permette di confrontare un soggetto scelto dal database con tutti gli altri presenti
 * Visualizza le somiglianze di tutti i soggetti con quello scelto
 * Ordina il database da quello con la somiglianza minore a quello con la somiglianza maggiore*/
void ordinaPerConfronto(RecordSoggetto *elenco, RecordSoggetto *criminale, int nElementi) {

    int id;                     //Id del soggetto da confrontare con tutti gli altri
    int i;                      //Contatore per i cicli
    int vettSomiglianze[100];   //vettore che conterra' le percentuali di somiglianze allo scopo di ordinarle successivamente

    printf("Quale soggetto vuoi confrontare con tutti gli altri?\nInserisci il suo id:");
    printf("\nIn elenco sono presenti [%d] soggetti :", nElementi);
    scanf("%d", &id);

/*Confronta il soggetto prescelto con tutti gli alti soggetti presenti nel database*/
    for (i = 0; i < nElementi; ++i) {

        vettSomiglianze[i] = confrontaRecord(&criminale[id], &elenco[i]);;   //vettore di interi allo scopo di salvare tutte le somiglianze dei soggetti
        printf("\nLa percentuale di somiglianza del criminale selezionato rispetto al soggetto con id:[%d] e' %d%%", i + 1, vettSomiglianze[i]);
    }
    //Esegue l'ordinamento in base alle somiglianze tra il soggetto selezionato e tutti gli altri
    ordinaConfronti(elenco,vettSomiglianze,nElementi);
}
/*Riceve il puntatore all'elemento selezionato dall'utente per effettuare il confronto, il vettore con i rusultati dei confronti e
 * il num elementi dell'intero database. Effettua l'ordinamento da quello che ha meno somiglianza a quello con maggiore somiglianza
 * rispetto al soggetto passato*/
void ordinaConfronti(RecordSoggetto *elenco, int *vett, int nElementi){
    int i;
    _Bool flag;
    RecordSoggetto veicolo;     //Variabile di tipo RecordSoggetto che funge da veicolo per gli spostamenti ordinati dei soggetti
    int veicoloSomiglianza;     //Variabile veicolo che conterra' una somiglianza per lo scambio
    /*ordina tutti gli elementi del vettore dal meno simile al piu' simile*/
    do {
        //variabile di flag assegnata a falso, sara' true quando tutti gli elementi saranno controllati (e ordidati)
        flag=false;
        //Fino a num Elementi -1 perche' alla fine dei controlli l'ultimo elemento sara' nella sua giusta posizione
        for (i=0; i<(nElementi-1); i++) {
            //se l’elemento vettore[i+1] è minore del successivo
            if (vett[i+1]<vett[i]) {

                //assegna alla variabile veicolo il valore della casella corrispondente all’indice i
                //sia per il vettore dinamico che per il vettore che accoglie le somiglianze tra i soggetti
                veicolo=elenco[i];
                veicoloSomiglianza=vett[i];
                //scambia i valori tra la cella e la sua successiva
                elenco[i]=elenco[i+1];
                vett[i]=vett[i+1];
                //assegna alla posizione successiva il contenuto che e' stato copiato nella variabile veicolo
                elenco[i+1]=veicolo;
                vett[i+1]=veicoloSomiglianza;
                //setta la variabile flag come vera poiché è stato effettuato uno scambio
                flag=true;
            }
        }
    }while (flag); //finché flag permane vera il ciclo continua i controlli
    printf("\nElenco ordinato per confronto!\n");
}
