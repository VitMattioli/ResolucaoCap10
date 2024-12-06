#include <stdio.h>

#define NUM_PESSOAS 20

typedef struct {
    float salario;
    int idade;
    int filhos;
    char sexo;
} Pessoa;

void ler_dados(Pessoa pessoas[]) {
    for (int i = 0; i < NUM_PESSOAS; i++) {
        printf("\nPessoa %d:\n", i + 1);

        printf("Digite o salario: R$ ");
        scanf("%f", &pessoas[i].salario);

        printf("Digite a idade: ");
        scanf("%d", &pessoas[i].idade);

        printf("Digite o numero de filhos: ");
        scanf("%d", &pessoas[i].filhos);

        printf("Digite o sexo (M/F): ");
        scanf(" %c", &pessoas[i].sexo);
    }
}

void calculos(Pessoa pessoas[], float *mediaSalario, float *mediaFilhos, float *maiorSalario, float *percentualMulheres) {
    float somaSalario = 0.0;
    int somaFilhos = 0;
    float maior = 0.0;
    int mulheresComSalarioAlto = 0;
    int totalMulheres = 0;

    for (int i = 0; i < NUM_PESSOAS; i++) {
        somaSalario += pessoas[i].salario;
        somaFilhos += pessoas[i].filhos;

        if (pessoas[i].salario > maior) {
            maior = pessoas[i].salario;
        }

        if (pessoas[i].sexo == 'F' || pessoas[i].sexo == 'f') {
            totalMulheres++;
            if (pessoas[i].salario > 1000.0) {
                mulheresComSalarioAlto++;
            }
        }
    }

    *mediaSalario = somaSalario / NUM_PESSOAS;
    *mediaFilhos = (float)somaFilhos / NUM_PESSOAS;
    *maiorSalario = maior;
    *percentualMulheres = totalMulheres > 0 
                          ? (float)mulheresComSalarioAlto / totalMulheres * 100 
                          : 0.0;
}

int main() {
    Pessoa pessoas[NUM_PESSOAS];

    ler_dados(pessoas);

    float mediaSalario, mediaFilhos, maiorSalario, percentualMulheres;

    calculos(pessoas, &mediaSalario, &mediaFilhos, &maiorSalario, &percentualMulheres);

    printf("\nResultados da pesquisa:\n");
    printf("Media de salario da populacao: R$ %.2f\n", mediaSalario);
    printf("Media do numero de filhos: %.2f\n", mediaFilhos);
    printf("Maior salario: R$ %.2f\n", maiorSalario);
    printf("Percentual de mulheres com salario superior a R$ 1.000,00: %.2f%%\n", percentualMulheres);

    return 0;
}
