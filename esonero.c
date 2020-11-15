/*
 * esonero.c
 * 
 * Copyright 2020 Gabriele <Gabriele@DESKTOP-6J9BB5F>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 128
char* messaggio;
char* chiave;
char* msg_criptato;
int criptaggio;

void inserisciStringa();
int controllaStringa();
void menu();
void inserimentoAutomaticoChiave();
void inserimentoManualeChiave();
void random_function(int);
void criptaMessaggio();
void decriptaMessaggio();

int main(int argc, char **argv)
{
	messaggio=(char*)malloc(sizeof(char)*N);
	chiave=(char*)malloc(sizeof(char)*N);
	msg_criptato=(char*)malloc(sizeof(char)*N);
	criptaggio=0;
	inserisciStringa();
	menu();
	return 0;
}

void inserisciStringa(){
	printf("Inserisci il messaggio da criptare: (Max 128 caratteri)\n");
	scanf("%s",messaggio);
	if(controllaStringa(messaggio)==0){
		printf("Inserimento non riuscito, messaggio più grande di 128 caratteri\n");
		inserisciStringa();
	}
}
	

int controllaStringa(char* stringa){
	if(strlen(stringa)>N){
		return 0;
	}
	else{
		printf("Inserito correttamente\n");
		return 1;
	}
}

void menu(){
	int scelta;
	do{
		printf("Inserire:\n 0 : Inserimento manuale chiave\n 1 : Creazione casuale chiave\n 2 : Riscrivi messaggio\n 3 : Cripta Messaggio\n 4 : Decripta messaggio\n 5 : Esci\n");
		scanf("%d",&scelta);
		switch(scelta){
			case 0:
				inserimentoManualeChiave();
				break;
			case 1:
				inserimentoAutomaticoChiave();
				break;
			case 2:
				inserisciStringa();
				break;
			case 3:
				criptaMessaggio();
				break;
			case 4:
				decriptaMessaggio();
				break;
			case 5:
				break;
			default:
				printf("Non hai selezionato una delle 4 opzioni, riprova\n");
				break;
		}
	}while(scelta!=5);
	printf("Messaggio: %s\n",messaggio);
	printf("Chiave: %s\n",chiave);
	printf("Messaggio Cifrato: %s\n",msg_criptato);
	printf("Uscita dal programma\n");
}

void inserimentoManualeChiave(){
	int len_messaggio=0;
	int len_chiave=0;
	FILE *fp;
	char nomefile[100]="chiave.txt";
	if ((fp=fopen(nomefile,"r"))==NULL) {
            printf("Errore nell'apertura del file");
	    exit(1);
   	}
   	len_messaggio=strlen(messaggio);
   	fgets(chiave,len_messaggio+1,fp);
	len_chiave=strlen(chiave);
	if(controllaStringa(chiave)==0 || len_chiave<len_messaggio){
		printf("Inserimento non riuscuto.\n Modifica chiave di lunghezza maggiore o uguale a %d e minore di 128 nel file di testo\n",len_messaggio);
	}
	fclose(fp);
	printf("Chiave: %s\n", chiave);
}

void inserimentoAutomaticoChiave(){
	int len_messaggio=0;
	len_messaggio=strlen(messaggio);
	random_function(len_messaggio);
	printf("Chiave: %s\n", chiave);
}

void random_function(int len_messaggio){
	time_t t;
	int a,i;
	for(i=0;i<len_messaggio;i++){
		srand((unsigned) time(&t)+i);
		a = rand() % N;
		chiave[i]=a;
	}
}

void criptaMessaggio(){
	int i=0;
	if(strlen(chiave)>=strlen(messaggio)){
		for(i=0;i<strlen(messaggio);i++){
			msg_criptato[i]=messaggio[i]^chiave[i];
		}
		printf("Criptaggio completato\n");
		printf("Messaggio criptato: %s\n",msg_criptato);
		criptaggio=1;
	}
	else{
		printf("Criptaggio non completato\n");
		printf("Lunghezza chiave minore lunghezza messaggio, riscrivere la chiave\n");
	}
}

void decriptaMessaggio(){
	if(criptaggio==1){
		char messaggio_orig[N];
		int i=0;
		for(i=0;i<strlen(messaggio);i++){
			messaggio_orig[i]=msg_criptato[i]^chiave[i];
		}
		printf("Messaggio originale: %s\n",messaggio_orig);
	}
	else{
		printf("Messaggio criptato non presente, prima criptare il messaggio\n");
	}
}
