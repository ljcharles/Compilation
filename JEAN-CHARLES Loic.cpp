/*
 * 09/10/17
 * JEAN-CHARLES Loic
 * M1 INFORMATIQUE RP
 * Ce programme permet d'implementer un automate avec sorties en C. On entre un mot contenant les lettres de l'aphabet de l'automate,
 * puis il nous renvoit le mot correspondant.Enfin, le programme affiche si le mot entré au début est reconnu par l'automate.
*/
#include <stdio.h>

const int N = 50;

bool automate(char alphabet[N], char mot[N], int nbAlphabet, int nbEtat, int tr[N][N], bool eF[N], char tS[N][N]){
	int i, indiceMotfinal = 0, j, k, etat = 0;
	char mfinal[N];
	
	for(i = 0; mot[i] != '\0'; i++){ 
		printf("Nous sommes a l'etat %d, on lit la lettre %c.\n", etat+1,mot[i]);
		for(j=0;j<nbAlphabet;j++){
			if(mot[i] == alphabet[j]){
				for(k=0;tS[etat][k] != '\n';k++){ 
					mfinal[indiceMotfinal] = tS[etat][k];
					indiceMotfinal++;
				}
				etat = tr[etat][j];
			}
		}
	}

	mfinal[indiceMotfinal] = '\0';
	printf("Le mot obtenu a la sortie de l'automate est : %s.\n", mfinal);
	return eF[etat];
}

void constructionAutomate(int *nbAlpha, int *nbEtat, char alphabet[N], bool etatFinal[N], int transitions[N][N], char tableSortie[N][N]){
	int NbEtat, NbAlpha, i, j, k, numTransition, chiffreEtatFinal;
	char value;

	printf("Veuiller entrer le nombre de lettres de l'alphabet de l'automate :\n");
	scanf("%d",&NbAlpha);
	*nbAlpha = NbAlpha;
		
	printf("Veuiller entrer le nombre d'etats de l'automate :\n");
	scanf("%d",&NbEtat);
	*nbEtat = NbEtat;
		
	for(i=0; i<NbEtat; i++) etatFinal[i] = false;
		
	printf("Veuiller entrer les lettres de l'alphabet(une par une) de l'automate :\n");
	for(i = 0; i < NbAlpha; i++){
		while(getchar() != '\n');
		scanf("%c",&alphabet[i]);
	}
	alphabet[i] = '\0';
		
	printf("Alphabet de l'automate : %s.\n",alphabet);
		
	printf("Veuiller entrer les transitions de l'automate :\n");

	for(i=0; i<NbEtat; i++){
		for(j=0; j<NbAlpha; j++) {
			printf("Pour l'etat %d si on lit la lettre %c on arrive a l'etat ? :\n",i+1,alphabet[j]);
			scanf("%d",&numTransition);
			transitions[i][j] = numTransition - 1;
		}
	}
		
	printf("table de Transition\n");
		
	for(i=0; i<NbEtat; i++) 
		for(j=0; j<NbAlpha; j++) 
			printf("Etat %d  - Lettre %c - Etat transitoire : %d \n",i+1,alphabet[j], transitions[i][j]+1);
		
	printf("Veuiller entrer les mots de l'alphabet de sortie de l'automate, appuyer espace si mot vide !\n");
		
	while(getchar() != '\n');
	for(i = 0;i<NbEtat;i++){
		for (j=0, k=0;j<NbAlpha;j++){
			printf("Pour l'etat %d si on lit la lettre %c on obtient le mot ? :\n",i+1,alphabet[j]);
			do{
				scanf("%c",&value);
				tableSortie[i][k] = value;
				k++;
			}while(value != '\n');
		}
	}
		
	printf("table de Sortie\n");
		
	for(i=0; i<NbEtat; i++) {
		for(j=0, k = 0; j<NbAlpha; j++) {
			printf("Etat %d  - Lettre %c - Mot :",i+1,alphabet[j]);
			while(tableSortie[i][k] != '\n')
			{
				printf("%c", tableSortie[i][k]);
				k++;
			}
			k++;
			printf("\n");
		}
	}
		
	printf("Veuiller entrer les etats finaux (1 ou 2 etc...) un par un et entrer 0 si vous avez fini :\n");
	do{
		scanf("%d",&chiffreEtatFinal);
		if(chiffreEtatFinal != 0) etatFinal[chiffreEtatFinal-1] = true;
	}while(chiffreEtatFinal != 0);
		
	printf("table des Etats Finaux\n");
		
	for(i=0; i<NbEtat; i++) printf("Etat %d  - Final %s \n",i+1,etatFinal[i]?"true":"false");
}

int main(){
	int chiffreEtatFinal = 0,numTransition = 0,NbAlpha = 0,NbEtat = 0;
	char motTeste[N], alphabet[N];
	bool reconnu;
	int transitions[N][N], quitter;
	char tableSortie[N][N];
	bool etatFinal[N];
	
	
	do{
		constructionAutomate(&NbAlpha,&NbEtat,alphabet,etatFinal,transitions,tableSortie);

		printf("Veuiller entrer le mot a tester: ");
		while(getchar() != '\n');
		scanf("%s",motTeste);
		
		printf("Mot teste : %s.\n", motTeste);
		reconnu = automate(alphabet,motTeste, NbAlpha, NbEtat, transitions, etatFinal,tableSortie);
		
		if(reconnu) printf("Le mot est reconnu par l'automate !\n");
		else printf("Le mot n'est pas reconnu par l'automate !\n");
		printf("\n------------------------------------------------------\n");

		printf("Veuiller entrer 0 pour sortir du programme ou 1 pour continuer : ");
		scanf("%d",&quitter);
    }while(quitter!=0);

	return 0;
}
