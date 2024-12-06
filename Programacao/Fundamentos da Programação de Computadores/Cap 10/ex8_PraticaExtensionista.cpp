#include <stdio.h>
#include <string.h>

#define NUM_ESTADOS 15

typedef struct {
    char nome[50];
    int numVeiculos;
    int numAcidentes;
} Estado;

int main() {
    Estado estados[NUM_ESTADOS];
    int i, totalVeiculos = 0;
    int maiorIndiceAcidentes = 0, menorIndiceAcidentes = 0;
    float percentualVeiculos[NUM_ESTADOS], mediaAcidentes = 0.0;

    for (i = 0; i < NUM_ESTADOS; i++) {
        printf("Estado %d:\n", i + 1);
        printf("Nome: ");
        fgets(estados[i].nome, 50, stdin);
        estados[i].nome[strcspn(estados[i].nome, "\n")] = '\0'; 
        printf("Numero de veiculos: ");
        scanf("%d", &estados[i].numVeiculos);
        printf("Numero de acidentes: ");
        scanf("%d", &estados[i].numAcidentes);
        getchar(); 

        totalVeiculos += estados[i].numVeiculos;

        if (i == 0 || estados[i].numAcidentes > estados[maiorIndiceAcidentes].numAcidentes) 
		{
            maiorIndiceAcidentes = i;
        }
        if (i == 0 || estados[i].numAcidentes < estados[menorIndiceAcidentes].numAcidentes) 
		{
            menorIndiceAcidentes = i;
        }

        mediaAcidentes += estados[i].numAcidentes;
    }

    for (i = 0; i < NUM_ESTADOS; i++) {
        percentualVeiculos[i] = (float)estados[i].numVeiculos / totalVeiculos * 100;
    }

    mediaAcidentes /= NUM_ESTADOS;

    printf("\n===== Resultados =====\n");
    printf("Maior indice de acidentes: %s (%d acidentes)\n",
           estados[maiorIndiceAcidentes].nome, estados[maiorIndiceAcidentes].numAcidentes);
    printf("Menor indice de acidentes: %s (%d acidentes)\n",
           estados[menorIndiceAcidentes].nome, estados[menorIndiceAcidentes].numAcidentes);

    printf("\nPercentual de veiculos por estado:\n");
    for (i = 0; i < NUM_ESTADOS; i++) {
        printf("%s: %.2f%%\n", estados[i].nome, percentualVeiculos[i]);
    }

    printf("\nMedia de acidentes entre os estados: %.2f\n", mediaAcidentes);

    return 0;
}
