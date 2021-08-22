#ifndef PROGETTOC_GESTIONE_H
#define PROGETTOC_GESTIONE_H

/*Subroutine per l'eliminazione, la ricerca e il recupero di elementi all'interno del vettore passato*/
void eliminaSoggetti(VD *vettore);
RecordSoggetto *eliminaCriminale(RecordSoggetto *elenco, int indice, int nElementi);
RecordSoggetto recuperaElemento(VD *vettore, int posizione);
int dimensioneVettore(VD *vettore);
void rimuoviElementoInCoda(VD *vettore);
void cercaSoggetto(VD *vettore);

/*Procedure di ordinamento del database - alfabeticamente(per cognome) o per confronto (dal minore al maggiore)*/
void ordinaPerNome(RecordSoggetto *elenco, int nElementi);
void ordinaPerCognome(RecordSoggetto *elenco, int nElementi);
void ordinaAlfabeticamente(RecordSoggetto *elenco, int nElementi);
void ordinaPerConfronto(RecordSoggetto *elenco, RecordSoggetto *criminale, int nElementi);
void ordinaConfronti(RecordSoggetto *elenco, int *vett, int nElementi);

#endif //PROGETTOC_GESTIONE_H
