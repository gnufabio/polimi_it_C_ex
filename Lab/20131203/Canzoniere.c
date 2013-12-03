#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BRANI 200
#define MAX_RIGA  100

#define FILENAME "canzoniere.txt"
#define INDICE "indice.txt"

typedef struct { char titolo[MAX_RIGA];
                 int linea_inizio;
				 int lunghezza_testo_in_righe;
				 long int inizio;
				 long int fine;  } Brano ;

typedef struct { char filename[50];
                 int num_brani;
                 Brano brani[MAX_BRANI];  } Canzoniere;
                 

/* Prototipi di funzione */
int load_data(Canzoniere *);
int menu(void);
long int get_offset(FILE *, int);

int conta_canzoni(Canzoniere *);
void stampa_titoli(Canzoniere *);
void stampa_ricerca(Canzoniere *, char*);
void genera_indice(Canzoniere *);

int main() {
	Canzoniere canzoniere;
	int scelta;
	char ricerca[MAX_RIGA];
	
	strcpy(canzoniere.filename, FILENAME);
	load_data(&canzoniere);
	
	while((scelta = menu()) != 5) {
		switch(scelta) {
			case 1:
				printf("\nCanzoni: %d\n", conta_canzoni(&canzoniere));
				break;
			case 2:
				stampa_titoli(&canzoniere);
				break;
			case 3:
				printf("\nInserisci un criterio di ricerca: ");
				scanf("%s", ricerca);
				stampa_ricerca(&canzoniere, ricerca);
				break;
			case 4:
				genera_indice(&canzoniere);
				break;
			case 5:
				exit(0);
		}
	}
	
	return 0;
}

/*
 * Cerca prima di tutto nei titoli.
 * Successivamente, cerca l'accorrenza della parola *ricerca nei byte del file
 * compresi tra inizio e fine.
 */
void stampa_ricerca(Canzoniere *canzoniere, char *ricerca) {
	FILE *fpin;
	char riga[MAX_RIGA];
	int i, j;
	
	printf("\nRisultati della ricerca nei titoli:\n");
	for(i = 0; i < canzoniere->num_brani; i++) {
		if(pif(canzoniere->brani[i].titolo, ricerca)) {
			printf("%d) %s\n", i + 1, canzoniere->brani[i].titolo);
		}
	}
	
	fpin = fopen(canzoniere->filename, "r");
	if(fpin == NULL) return;
	printf("\nRisultati della ricerca nelle canzoni:\n");
	
	for(i = 0; i < canzoniere->num_brani; i++) {
		fseek(fpin, canzoniere->brani[i].inizio, SEEK_SET);
		
		/* Continua finché si può leggere e non abbiamo superato ancora il byte di fine */
		while((fgets(riga, MAX_RIGA, fpin) != NULL) && (ftell(fpin) <= canzoniere->brani[i].fine)) {
			if(strstr(riga, ricerca) != NULL ) {
				printf("%d) %s\n", i + 1, canzoniere->brani[i].titolo);
				break;
			}
		}
	}
	
	fclose(fpin);
}

/* Restituisce l'offset della linea n° linea.*/
long int get_offset(FILE *fpin, int linea) {
	char c = ' ';
	long int originalpos = ftell(fpin);
	long int result;
	
	if(linea == 0) return 0;
	
	for(;linea > 0 && c != EOF;) {
		c = fgetc(fpin);
		if(c == '\n') {
			linea--;
		}
		 
	}
	
	result = ftell(fpin);
	fseek(fpin, originalpos, SEEK_SET);
	return result;
}

/* Restituisce il conto delle canzoni */
int conta_canzoni(Canzoniere *canzoniere) {
	return canzoniere->num_brani;
}       
  
/* Stampa i titoli delle canzoni */
void stampa_titoli(Canzoniere *canzoniere) {
	int i;
	for(i = 0; i < canzoniere->num_brani; i++) {
		printf("%d) %s\n", i + 1, canzoniere->brani[i].titolo);
	}
}
  
void genera_indice(Canzoniere *canzoniere) {
	FILE *fpin;
	int i;
	
	fpin = fopen(INDICE, "w");
	if(fpin == NULL) return;
	
	for(i = 0; i < canzoniere->num_brani; i++) {
		fprintf(fpin, "%d) %s [ll %d-%d]\n", i + 1, canzoniere->brani[i].titolo, canzoniere->brani[i].linea_inizio + 1, canzoniere->brani[i].linea_inizio + 1 + canzoniere->brani[i].lunghezza_testo_in_righe);
	}
	printf("Indice generato!\n");
	fclose(fpin);
}  


/* Carica nella struttura Canzoniere alcuni dati dal file, tra cui:
 * - Titoli delle canzoni
 * - Linea di inizio/fine delle canzoni
 * - Byte di inizio e di fine delle canzoni
 */
int load_data(Canzoniere *canzoniere) {
	FILE *fpin;
	int linea, brano, ricerca_titolo;
	char buff[MAX_RIGA];
	
	fpin = fopen(canzoniere ->filename, "r");
	if(fpin == NULL) return 0;
	
	canzoniere->brani[0].inizio = 0L;
	
	for(linea = 0, brano = -1, ricerca_titolo = 0; fgets(buff, MAX_RIGA, fpin) != NULL; linea++) {
		/* L'ultimo carattere è un accapo, noi non lo vogliamo! */
		buff[strlen(buff) - 1] = '\0';
		
		/* Siamo all'inizio di un testo */
		if(strcmp(buff, "**********") == 0) {
			brano++;
			
			if(brano > 0) {
				/* Aggiorna i dati dell'ultimo brano */
				canzoniere->brani[brano - 1].lunghezza_testo_in_righe = linea - canzoniere->brani[brano - 1].linea_inizio - 1;
				canzoniere->brani[brano - 1].fine = ftell(fpin) - (strlen(buff) + 1);
			}
			/* E quelli del brano corrente */
			canzoniere->brani[brano].inizio = ftell(fpin);
			canzoniere->brani[brano].linea_inizio = linea + 1;
			ricerca_titolo = 1;
			continue;
		}
		
		/* Stiamo ricercando il titolo del brano corrente */
		if(ricerca_titolo) {
			strcpy(canzoniere->brani[brano].titolo, buff);
			ricerca_titolo = 0;
			continue;
		}
		 
	}
	
	/* Infine aggiorna i dati dell'ultimissimo brano che non possono essere aggiunti dal while */
	if(brano > 0) {
		canzoniere->brani[brano].lunghezza_testo_in_righe = linea - canzoniere->brani[brano - 1].linea_inizio;
		canzoniere->brani[brano].fine = ftell(fpin);
	}
	
	canzoniere->num_brani = brano + 1;
	fclose(fpin);
}

/* Stampa un menu e restituisci la scelta */
int menu(void) {
	int choice = 0;
			
	while(choice < 1 || choice > 5) {
		printf(	"\n\nScegli che fare:\n"
			"1) Conta le canzoni contenute nel file\n"
			"2) Visualizza i titoli delle canzoni\n"
			"3) Trova le accorrenze di una parola in titoli e testi\n"
			"4) Genera indice\n"
			"5) Uscire\n\n"
			"Scelta: ");
		scanf("%d", &choice);
		fflush(stdin);
	}
	return choice;
}
