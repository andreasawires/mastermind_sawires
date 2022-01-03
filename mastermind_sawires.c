#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// creazione di un codice random
void creazioneCodice(char codiceSegreto[4][10])
{
  int coloreRandom;
  for (int i=0; i<4; i++)
  {
    coloreRandom = 1 + (rand() % 7);
    printf("\nquesto e' il colore random %i", coloreRandom);
    switch(coloreRandom)
    {
      case 1: strcpy(codiceSegreto[i], "bianco");       break;
      case 2: strcpy(codiceSegreto[i], "nero");         break;
      case 3: strcpy(codiceSegreto[i], "rosso");        break;
      case 4: strcpy(codiceSegreto[i], "blu");          break;
      case 5: strcpy(codiceSegreto[i], "verde");        break;
      case 6: strcpy(codiceSegreto[i], "arancione");    break;
      case 7: strcpy(codiceSegreto[i], "viola");        break;
    }
  }
}

// funzione per prendere il tentativo dello user
void inserimentoColori(char tentativo[4][10])
{
  printf("\nInserisci i colori\n");
  for(int i=0; i<4; i++)
    scanf("%s", tentativo[i]);
}

// calcolo dello punteggio
void calcolaPunteggio(char codiceSegreto[4][10], char tentativo[4][10], int *neri, int *bianchi)
{
  int controlloCodiceSegreto[4] = {1,1,1,1}, controlloTentativo[4] = {1,1,1,1};
  *neri = *bianchi = 0;

  // controllo la lista per assegnare i neri
  for (int i=0; i<4; i++)
  {
    if (strcmp(codiceSegreto[i], tentativo[i]) == 0)
    {
      ++*neri;
      controlloCodiceSegreto[i] = controlloTentativo[i] = 0;
    }
  }

  // controllo la lista per assegnare i bianchi
  for (int i=0; i<4; i++)
  {
    for (int j=0; j<4; j++)
    {     
      if (strcmp(codiceSegreto[i], tentativo[j]) == 0  &&  controlloTentativo[i]  &&  controlloCodiceSegreto[j]  &&  i != j)        
      {
        ++*bianchi;
        controlloCodiceSegreto[j] = controlloTentativo[i] = 0;
      }
    }
  }
}

void mostraPunteggio(char tentativo[4][10], int neri, int bianchi) 
{
  printf("\nTetativo\t\t\t\tPunteggio\n");   
  for (int i=0; i<4; i++) 
    printf("%s ", tentativo[i]);


  printf("\t\t");

  for (int i=0; i<neri; i++) 
    printf("Nero ");

  for (int i=0; i<bianchi; i++)
    printf("Bianco ");

  printf("\n\n");
}

int main()
{
  // funzione utilizzata per fare in modo che i numeri generati randomicamente non siano sempre gli stessi
  srand ( time(NULL) );

  printf("----------------------------------------------------------------------------------------------------------------\n");
  printf("Benvenuto in Mastermind by Andrea Sawires\n");
  printf("Le regole del gioco sono semplici:\n");
  printf("All'inizio di ogni partita viene generato un codice segreto che dovrai indovinare\n");
  printf("Il codice e' una serie di 4 colori e il tuo compito e' quello di indovinare i colori nell'ordine corretto\n\n");
  printf("Ogni volta che fai un tentativo ricevi un punteggio:\n");
  printf("Ricevi un pallino nero per ogni volta che indovini sia il colore sia la posizione\n");
  printf("Ricevi un pallino bianco per ogni volta che indovini solo il colore ma non la posizione\n");
  printf("I colori accettati sono: bianco, nero, rosso, blu, verde, arancione, viola\n");
  printf("Hai 12 tentativi per vincere, buona fortuna!!\n");

  int numeroTentativi, continuare=0, neri, bianchi;
  char codiceSegreto[4][10], tentativo[4][10];

  while (1)
  {
    printf("\nPremi 1 per iniziare, premi qualsiasi altro tasto per uscire\n");
    scanf("%d", &continuare);

    if (continuare == 1)
    {
      // creazione di un codice random
      creazioneCodice(codiceSegreto);

      for (numeroTentativi=1; numeroTentativi<=12; numeroTentativi++)
      {
        // prendere il tentativo dello user
        inserimentoColori(tentativo);

        // calcola punteggio
        calcolaPunteggio(codiceSegreto, tentativo, &neri, &bianchi);

        // mostrare punteggio
        mostraPunteggio(tentativo, neri, bianchi);

        // se il punteggio è 4 neri allora lo user ha vinto
        if (neri == 4)
        {
          printf("Congratulazioni, hai vinto!\n\n");
          break;
        }
      }

      // se il numero di tentativi è >12 allora printa game over
      if (numeroTentativi > 12)
      {
        printf("\nMi dispiace hai perso, questo era il codice segreto: %s, %s, %s, %s\n\n\n\n", codiceSegreto[0], codiceSegreto[1], codiceSegreto[2], codiceSegreto[3]);
        return 0;
      }

    } else {
      printf("Alla prossima!!\n");
      return 0;
    }
  }

  return 0;
}