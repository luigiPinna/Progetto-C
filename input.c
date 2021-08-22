#include "input.h"
#include "controlliInput.h"
#include "generazioniCasuali.h"
#include "output.h"
#include "gestioneFile.h"
#include "gestione.h"

/*Avvia l'intero programma Criminali.
 * Permette la gestione e ricerca di criminali sulla base di tratti somatici distintivi.
 * Consente le operazioni di inserimento, modifica, eliminazione, ricerca, ordinamento ed esportazione dei
 * dati inerenti ai soggetti memorizzati nel sistema o su file.
 *
 Contiene lo switch case con tutte le possibili scelte del menu e per ogni case la procedura che consente di effettuare l'operazione scelta
 */
void avviaProgrammaCriminali(){
    srand(time(NULL));

    VD dati;
    SceltaMenu sceltaMenu;                  //Variabile che accoglie la scelta input dell'utente da menu

    inizializzaVettoreDinamico(&dati);      //Inizializza il vettore dinamico a NULL e il numero di elementi a 0
    do {
        sceltaMenu = menuPrincipale();      //Stampa menu e acquisisce la scelta dell'utente
        printf("\n");
        switch (sceltaMenu) {               //Esegue l'azione in base alla scelta
            case ESCI:
                printf("Grazie. Arrivederci!\n");
                break;
            case INSERISCI:
                /*permette l'inserimento del soggetto in tutte le sue caratteristiche*/
                inserisciRecord(&dati);
                printf("\nNum. inserimenti:[%d]", dati.numInserimenti);      //Stampa a video il numero di inserimenti ogni volta ceh vengono generati
                break;
            case STAMPA:
                /*Permette la stampa del record singolo o, in alternativa scelta dall'utente, la stampa di tutti i soggetti*/
                /*contiene la procedura "stampaElencoCriminali"*/
                stampaRecord(&dati);
                break;
            case GENERA:
                /*Genera un record casuale*/
                generaRecord(&dati);
                printf("--------------------");
                printf("\nNum. inserimenti:[%d]", dati.numInserimenti);      //Stampa a video il numero di inserimenti ogni volta che vengono generati
                break;
            case CANCELLA:
                /*Permette di cancellare tutti i soggetti o quello/i desiderato/i dall'utente (contiene "eliminaCriminale")*/
                eliminaSoggetti(&dati);
                break;
            case CERCA:
                /*Ricerca tramite nome o cognome un soggetto all'interno del data base*/
                cercaSoggetto(&dati);
                break;
            case CONFRONTO:
                /*Contiene la subroutine "confrontaRecord" per confrontare 2 soggetti piu' altri controlli*/
                confronto(&dati);
                break;
            case CARICA_DATI:
                /*Richiede all'utente il nome del file con l'elenco dei soggetti e, se esistente, lo salva nel vettore dinamico (contiene "caricaDati")*/
                accediDataBaseFile(&dati);
                break;
            case SALVA_DATI:
                /*Richiede all'utente il nome del file sul quale salvare l'elenco criminali e procede con il salvataggio su bile binario*/
                salvataggio(&dati);
                break;
            case ORDINA:
                /*Ordina alfabeticamente per cognome tutti i soggetti/criminali presenti nell'elenco*/
                ordinaAlfabeticamente(dati.datiSoggetti, dati.numInserimenti);
                break;
            case CARICA_DATI_CRIPTATI:
                /*Carica i dati criptati da file e decripta il contenuto*/
                accediDataBaseFileCriptato(&dati);
                break;
            case SALVA_DATI_CRIPTATI:
                /*Salva su file i dati inseriti nel vettore dinamico criptandoli in base a delle regole prescelte*/
                salvataggioCriptato(&dati);
                break;
            case ORDINA_CONFRONTO:
                /*Confronta i soggetti con uno scelto dall'utente e li ordina in base alla similarita'*/
                ordinaPerConfronto(dati.datiSoggetti,dati.datiSoggetti, dati.numInserimenti);
                break;
            default:
                printf("Scelta non valida. Prova ancora!\n");
        }
    } while (sceltaMenu != ESCI);   //Riesegue il blocco fino a quando l'utente digita ESCI
    free(dati.datiSoggetti);    //Libera il vettore a fine programma
}

/*Aquisisce dall'utente i tratti distintivi di un soggetto*/
RecordSoggetto acquisisciPersona(){

    RecordSoggetto persona;
    //Acquisizione nome
    printf("\nNome (max %d caratteri): ", NOME_MAX);
    scanf("%[^\n]s", persona.nome);
    svuotaBuffer();
    //Acquisizione cognome
    printf("Cognome (max %d caratteri): ", NOME_MAX);
    scanf("%[^\n]s", persona.cognome);
    svuotaBuffer();
    //Acquisizione altezza
    printf("Altezza - valore tra 0 e 250 [cm]:");
    scanf("%d", &persona.altezza);
    controlloAltezza(&persona);
    svuotaBuffer();
    //Acquisizione peso
    printf("Peso - valore tra 0 e 300 [kg]:");
    scanf("%f", &persona.peso);
    controlloPeso(&persona);
    svuotaBuffer();
    //Acquisizione colore degli occhi
    printf("Colore degli occhi [RR/GG/BB] (max %d caratteri):", COLORE_MAX);
    inserisciColoreOcchi(&persona);
    //Acquisizione colore dei capelli
    printf("Colore dei capelli [RR/GG/BB] (max %d caratteri):", COLORE_MAX);
    inserisciColoreCapelli(&persona);
    //Acquisizione Tipo di capelli
    printf("Tipo di capelli\n [CORTI->%d, MEDI->%d, LUNGHI->%d, ALTRO->%d:", CORTI,MEDI,LUNGHI,ALTRO);
    scanf("%d", &persona.lunghezzaCapelli);
    controlloTipoCapelli(&persona);
    svuotaBuffer();
    //Controllo barba si o no
    printf("Ha la barba? [SI->'1' | NO->'0']:");
    scanf("%d", &persona.barba);
    controlloBoolBarba(&persona);
    svuotaBuffer();
    //Controllo presenza cicatrici cicatrici
    printf("Ha cicatrici in volto? [SI->'1' | NO->'0']:");
    scanf("%d", &persona.cicatriciVolto);
    controlloBoolCicatrici(&persona);
    svuotaBuffer();
    //Inserimento impronta digitale
    printf("Inserisci l'impronta digitale (max %d caratteri): ", IMPRONTA_MAX);
    inserisciImpronta(&persona);
    //Acquisizione Residenza
    printf("Residenza (max %d caratteri): ", RESIDENZA_MAX);
    scanf("%512[^\n]s", persona.residenza);
    svuotaBuffer();
    //Acquisizione posizione GPS
    printf("Ultima posizione GPS");
    printf("\nLatitudine:");    //Latitudine
    scanf("%lf", &persona.ultimaPosizione.latitudine);
    controlloLatitudine(&persona);  //Controllo input latitudine
    svuotaBuffer();
    printf("Longitudine:");     //Longitudine
    scanf("%lf", &persona.ultimaPosizione.longitudine);
    controlloLongitudine(&persona); //Controllo input longitudine
    svuotaBuffer();
    //Acquisizione stato soggetto
    printf("Stato soggetto\n [LIBERO->%d, RICERCATO->%d, IN ARRESTO->%d, EVASO->%d:", LIBERO, RICERCATO, IN_ARRESTO, EVASO);
    scanf("%d", &persona.stato);
    controlloStato(&persona);       //Verifica lo stato inserito
    svuotaBuffer();
    return persona;
}
/**
 * Permette l'inserimento di tutti i caratteri distintivi del soggetto
 * @param vettore: verranno salvati tutti i soggetti inseriti
 */
void inserisciRecord(VD *vettore){
    RecordSoggetto soggetto;
    printf("***Inserisci i dati***");
    soggetto = acquisisciPersona();
    aggiungiSoggetto(vettore, soggetto);
}
/*Aggiunge un elemento al vettore dinamico ed effettua l'allocazione o la riallocazione di memoria ad ogni inserimento*/
void aggiungiSoggetto(VD *vettore, RecordSoggetto soggetto){
    vettore->numInserimenti++;
    if(vettore->datiSoggetti == NULL)
        vettore->datiSoggetti = (RecordSoggetto *) malloc(vettore->numInserimenti * sizeof(RecordSoggetto));
    else
        vettore->datiSoggetti = (RecordSoggetto *) realloc(vettore->datiSoggetti,vettore->numInserimenti * sizeof(RecordSoggetto));
    if(vettore->datiSoggetti == NULL)
        exit(-1);
    vettore->datiSoggetti[vettore->numInserimenti-1] = soggetto;
}
/*Visualizza il menu all'utente e ne acquisisce la scelta*/
SceltaMenu menuPrincipale(){
    SceltaMenu sceltaMenu;

    //Stampa il menu e le possibile scelte
    printf("\n*********************************************\n");
    printf("************ MENU PRINCIPALE ****************\n");
    printf("*********************************************\n");
    printf("\t%d -->\tESCI\n", ESCI);
    printf("\t%d -->\tINSERISCI\n", INSERISCI);
    printf("\t%d -->\tSTAMPA\n", STAMPA);
    printf("\t%d -->\tGENERA\n", GENERA);
    printf("\t%d -->\tCANCELLA\n", CANCELLA);
    printf("\t%d -->\tRICERCA\n", CERCA);
    printf("\t%d -->\tCONFRONTA\n", CONFRONTO);
    printf("\t%d -->\tCARICA DATI\n", CARICA_DATI);
    printf("\t%d -->\tSALVA SU FILE\n", SALVA_DATI);
    printf("\t%d -->\tORDINA DATI\n", ORDINA);
    printf("\t%d -->\tCARICA DATI CRIPTATI\n", CARICA_DATI_CRIPTATI);
    printf("\t%d -->\tSALVA DATI CRIPTATI\n", SALVA_DATI_CRIPTATI);
    printf("\t%d -->\tORDINA PER CONFRONTO\n", ORDINA_CONFRONTO);

    //Acquisizione input dall'utente
    printf("\t----------------------------");
    printf("\n\tSCELTA: ");
    scanf("%d", &sceltaMenu);
    svuotaBuffer();

    return sceltaMenu;
}
/*Procedura che svuota il buffer*/
void svuotaBuffer(){
    char c;
    do{
        c=getchar();
    }while(c!='\n');
}
/*Permette l'inserimento dell'impronta digitale*/
void inserisciImpronta(RecordSoggetto *rgb){
    int i;
    printf("\n");
    for (i = 0; i < IMPRONTA_MAX; ++i) {
        printf("->");
        scanf("%c", &rgb->impronta[i]);
        svuotaBuffer();
        while(rgb->impronta[i]=='\0'){   //controllo spazi vuoti input utente
            printf("Errore, inserisci numeri e/o lettere senza spazi vuoti. Riprova!");
            printf("|");
            scanf("%c", &rgb->impronta[i]);
            svuotaBuffer();
        }
    }
}
/*Permette l'inserimento dei caratteri RGB -> Colore Occhi*/
void inserisciColoreOcchi(RecordSoggetto *rgb){
    int i;
    printf("\n");
    for (i = 0; i < COLORE_MAX; ++i) {
        printf("|");
        scanf("%c", &rgb->coloreOcchi[i]);
        svuotaBuffer();
        while((rgb->coloreOcchi[i]<LETTERA_A||rgb->coloreOcchi[i]>LETTERA_F)&&    //controllo numeri e caratteri input utente
        (rgb->coloreOcchi[i]<NUMERO_0_CHAR||rgb->coloreOcchi[i]>NUMERO_9_CHAR)){
            printf("Errore, inserisci valori tra 0-9 e tra A-F. Riprova!");
            printf("|");
            scanf("%c", &rgb->coloreOcchi[i]);
            svuotaBuffer();
        }
    }
}
/*Permette l'inserimento dei caratteri RGB -> Colore Capelli*/
void inserisciColoreCapelli(RecordSoggetto *rgb) {
    int i;
    printf("\n");
    for (i = 0; i < COLORE_MAX; ++i) {
        printf("|");
        scanf("%c", &rgb->coloreCapelli[i]);
        svuotaBuffer();
        while ((rgb->coloreCapelli[i] < LETTERA_A || rgb->coloreCapelli[i] > LETTERA_F) &&      //controllo numeri e caratteri input utente
               (rgb->coloreCapelli[i] < NUMERO_0_CHAR || rgb->coloreCapelli[i] > NUMERO_9_CHAR)) {
            printf("Errore, inserisci valori tra 0-9 e tra A-F. Riprova!");
            printf("|");
            scanf("%c", &rgb->coloreCapelli[i]);
            svuotaBuffer();
        }
    }
}
/*Identifica la presenza di barba in base al booleano inserito*/
void identificaBarba(_Bool barba){  //"Ha la barba? [SI->'1' | NO->'0']:;
    barba == 1 ? printf("Barba:\t\t\t\t[SI]") : printf("Barba:\t\t\t\t[NO]");
}
/*Identifica la presenza di cicatrici in viso in base al booleano inserito*/
void identificaCicatrici(_Bool cicatrici){  //"Ha cicatrici? [SI->'1' | NO->'0']:;
    cicatrici == 1 ? printf("Cicatrici in volto:\t\t[SI]") : printf("Cicatrici in volto:\t\t[NO]");
}
/*Identifica lo stato del soggetto in base all'input utente*/
void identificaStatoSoggetto(RecordSoggetto statoSoggetto){

    if(statoSoggetto.stato == LIBERO)
        printf("\nStato soggetto: \t\tLIBERO");
    if(statoSoggetto.stato == RICERCATO)
        printf("\nStato soggetto: \t\tRICERCATO");
    if(statoSoggetto.stato == IN_ARRESTO)
        printf("\nStato soggetto: \t\tIN ARRESTO");
    if(statoSoggetto.stato == EVASO)
        printf("\nStato soggetto: \t\tEVASO");
}
/*Identifica il colore dei capelli del soggetto in base all'input utente*/
void identificaCapelli(RecordSoggetto tipoCapelli){

    if(tipoCapelli.lunghezzaCapelli == CORTI)
        printf("\nTipo di capelli: \t\tCORTI");
    if(tipoCapelli.lunghezzaCapelli == MEDI)
        printf("\nTipo di capelli: \t\tMEDI");
    if(tipoCapelli.lunghezzaCapelli == LUNGHI)
        printf("\nTipo di capelli: \t\tLUNGHI");
    if(tipoCapelli.lunghezzaCapelli == ALTRO)
        printf("\nTipo di capelli: \t\tALTRO");
}
/*Inizializza un vettore dinamico a NULL e il numero di inserimenti a 0*/
void inizializzaVettoreDinamico(VD *vettore){
    vettore->datiSoggetti = NULL;
    vettore->numInserimenti = 0;
}