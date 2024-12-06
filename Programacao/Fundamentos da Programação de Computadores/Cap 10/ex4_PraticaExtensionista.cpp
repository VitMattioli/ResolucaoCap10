#include <stdio.h>

#define NUM_HABITANTES 20

typedef struct {
    int idade;           
    char sexo;          
    float rendaFamiliar; 
    int numFilhos;       
} Habitante;

void ler_dados(Habitante habitantes[]) {
    for (int i = 0; i < NUM_HABITANTES; i++) {
        printf("\nHabitante %d:\n", i + 1);

        printf("Idade: ");
        scanf("%d", &habitantes[i].idade);

        printf("Sexo (M/F): ");
        scanf(" %c", &habitantes[i].sexo);

        printf("Renda Familiar: R$ ");
        scanf("%f", &habitantes[i].rendaFamiliar);

        printf("Numero de filhos: ");
        scanf("%d", &habitantes[i].numFilhos);
    }
}

void calculos(Habitante habitantes[], float *mediaRenda, int *menorIdade, int *maiorIdade, int *mulheresCriticas) {
    float somaRenda = 0.0;
    int totalMulheresCriticas = 0;
    *menorIdade = habitantes[0].idade;
    *maiorIdade = habitantes[0].idade;

    for (int i = 0; i < NUM_HABITANTES; i++) {
        Habitante h = habitantes[i];

        somaRenda += h.rendaFamiliar;

        if (h.idade < *menorIdade) {
            *menorIdade = h.idade;
        }
        if (h.idade > *maiorIdade) {
            *maiorIdade = h.idade;
        }

        if (h.sexo == 'F' || h.sexo == 'f') {
            if (h.numFilhos > 2 && h.rendaFamiliar < 600.0) {
                totalMulheresCriticas++;
            }
        }
    }

    *mediaRenda = somaRenda / NUM_HABITANTES;

    *mulheresCriticas = totalMulheresCriticas;
}

int main() {
    Habitante habitantes[NUM_HABITANTES];

    ler_dados(habitantes);

    float mediaRenda;
    int menorIdade, maiorIdade, mulheresCriticas;

    calculos(habitantes, &mediaRenda, &menorIdade, &maiorIdade, &mulheresCriticas);

    printf("\nResultados da pesquisa:\n");
    printf("Media de renda familiar: R$ %.2f\n", mediaRenda);
    printf("Menor idade: %d anos\n", menorIdade);
    printf("Maior idade: %d anos\n", maiorIdade);
    printf("Quantidade de mulheres com mais de dois filhos e renda inferior a R$ 600,00: %d\n", mulheresCriticas);

    return 0;
}
