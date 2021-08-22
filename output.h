#ifndef PROGETTOC_OUTPUT_H
#define PROGETTOC_OUTPUT_H

/*Procedure di stampa a video*/
void stampaElencoCriminali(RecordSoggetto *elenco, int nElementi);
void stampaRecord(VD *vettore);
void stampaSoggetto(RecordSoggetto soggetto);

/*Subroutine di confronto soggetti*/
int confrontaRecord(RecordSoggetto *recordUno, RecordSoggetto *recordDue );
void confronto(VD *vettore);

/*Funzioni di confronto dei singoli caratteri distintivi tra 2 soggetti selezionati dall'utente*/
float confrontaColoreOcchi(RecordSoggetto *recordUno, RecordSoggetto *recordDue);
float confrontaColoreCapelli(RecordSoggetto *recordUno, RecordSoggetto *recordDue);
float confrontaImpronta(RecordSoggetto *recordUno, RecordSoggetto *recordDue);

#endif //PROGETTOC_OUTPUT_H
