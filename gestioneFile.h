#ifndef PROGETTOC_GESTIONEFILE_H
#define PROGETTOC_GESTIONEFILE_H

#define NOME_FILE_MAX 50

/*Procedure apertura e chiusura file*/
FILE * chiudiFile(FILE * fp);
void leggiDaFileBinario(VD *vettore, FILE *fp);

/*Gestione file binari, lettura, caricamento su vettore e salvataggio DB su file*/
void salvaDati(RecordSoggetto *elenco, char *nomeFile, int nElementi);
void caricaDati(VD *vettore, char *nomefile);
void accediDataBaseFile(VD *vettore);
void salvataggio(VD *vettore);

/*Gestione file binari criptati, caricamento su vettore e salvataggio DB criptato su file*/
void salvaDatiCriptati(RecordSoggetto *elenco, char *nomeFile, int nElementi);
void caricaDatiCriptati(VD *vettore, char *nomefile);
void accediDataBaseFileCriptato(VD *vettore);
void salvataggioCriptato(VD *vettore);

/*Decrypt & encrypt dei dati presenti nel file o nel vettore dinamico*/
void decryptData(RecordSoggetto *elenco, int nElementi);

#endif //PROGETTOC_GESTIONEFILE_H
