#include <stdio.h>
#include <string.h>

#define NUM_HABITANTES 50

typedef struct {
    char sexo;        
    float altura;     
    int idade;        
    char corOlhos;    
} Habitante;

void ler_dados(Habitante habitantes[]) 
{
    for (int i = 0; i < NUM_HABITANTES; i++) {
        printf("\nHabitante %d:\n", i + 1);

        printf("Sexo (M/F): ");
        scanf(" %c", &habitantes[i].sexo);

        printf("Altura: ");
        scanf(" %f", &habitantes[i].altura);

        printf("Idade: ");
        scanf(" %d", &habitantes[i].idade);

		printf("Cor dos Olhos: A= Azul; V= Verde; C= Castanho\n");
        printf("Cor dos olhos (A/V/C): ");
        scanf(" %c", &habitantes[i].corOlhos);
    }
}

void calculos(Habitante habitantes[], float *mediaIdadeCastanhos, int *maiorIdade, int *quantidadeMulheres, float *percentualHomens) 
{
    int somaIdadeCastanhos = 0, contadorCastanhos = 0;
    int totalHomens = 0, totalMulheres = 0;
    *maiorIdade = 0;
    *quantidadeMulheres = 0;

    for (int i = 0; i < NUM_HABITANTES; i++) {
        Habitante h = habitantes[i];

        if (h.idade > *maiorIdade) {
            *maiorIdade = h.idade;
        }

        if (h.corOlhos == 'C' && h.altura > 1.60) {
            somaIdadeCastanhos += h.idade;
            contadorCastanhos++;
        }

        if (h.sexo == 'F' || h.sexo == 'f') {
            totalMulheres++;
            if ((h.idade >= 20 && h.idade <= 45) || (h.corOlhos == 'V' && h.altura < 1.70)) {
                (*quantidadeMulheres)++;
            }
        }

        if (h.sexo == 'M' || h.sexo == 'm') {
            totalHomens++;
        }
    }

    *mediaIdadeCastanhos = contadorCastanhos > 0 
                           ? (float)somaIdadeCastanhos / contadorCastanhos 
                           : 0.0;

    *percentualHomens = (float)totalHomens / NUM_HABITANTES * 100;
}

int main() {
    Habitante habitantes[NUM_HABITANTES];

    ler_dados(habitantes);

    float mediaIdadeCastanhos, percentualHomens;
    int maiorIdade, quantidadeMulheres;

    calculos(habitantes, &mediaIdadeCastanhos, &maiorIdade, &quantidadeMulheres, &percentualHomens);

    printf("\nResultados da pesquisa:\n");
    printf("Media de idade das pessoas com olhos castanhos e altura superior a 1,60 m: %.2f anos\n", mediaIdadeCastanhos);
    printf("Maior idade entre os habitantes: %d anos\n", maiorIdade);
    printf("Quantidade de mulheres com idade entre 20 e 45 anos ou olhos verdes e altura < 1,70 m: %d\n", quantidadeMulheres);
    printf("Percentual de homens: %.2f%%\n", percentualHomens);

    return 0;
}
