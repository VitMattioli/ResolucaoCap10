#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDENS 100

typedef struct {
    int numero_os;
    char data[11];
    float valor;
    char servico[100];
    char cliente[50];
} OrdemServico;

OrdemServico ordens[MAX_ORDENS];
int qtd_ordens = 0;

void cadastrar_ordem() {
    if (qtd_ordens >= MAX_ORDENS) {
        printf("Limite maximo de ordens de servico atingido.\n");
        return;
    }

    OrdemServico nova;
    printf("\nNumero da OS: ");
    scanf("%d", &nova.numero_os);
    printf("Data (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.data);
    printf("Valor: R$ ");
    scanf("%f", &nova.valor);
    printf("Servico realizado: ");
    scanf(" %[^\n]", nova.servico);
    printf("Nome do cliente: ");
    scanf(" %[^\n]", nova.cliente);

    ordens[qtd_ordens++] = nova;
    printf("Ordem de servico cadastrada com sucesso!\n");
}

void calcular_media() {
    if (qtd_ordens == 0) {
        printf("\nNenhuma ordem de servico cadastrada.\n");
        return;
    }

    float soma = 0.0;
    for (int i = 0; i < qtd_ordens; i++) {
        soma += ordens[i].valor;
    }

    printf("\nMedia dos valores das ordens de servico: R$ %.2f\n", soma / qtd_ordens);
}

void servico_mais_caro() {
    if (qtd_ordens == 0) {
        printf("\nNenhuma ordem de servico cadastrada.\n");
        return;
    }

    float maior_valor = ordens[0].valor;
    int indice_maior = 0;

    for (int i = 1; i < qtd_ordens; i++) {
        if (ordens[i].valor > maior_valor) {
            maior_valor = ordens[i].valor;
            indice_maior = i;
        }
    }

    OrdemServico mais_caro = ordens[indice_maior];
    printf("\n=== Servico mais caro ===\n");
    printf("Cliente: %s\n", mais_caro.cliente);
    printf("Servico realizado: %s\n", mais_caro.servico);
    printf("Data: %s\n", mais_caro.data);
    printf("Valor: R$ %.2f\n", mais_caro.valor);
}

int main() {
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Cadastrar Ordem de Servico\n");
        printf("2. Calcular Media dos Valores\n");
        printf("3. Mostrar Servico Mais Caro\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_ordem();
                break;
            case 2:
                calcular_media();
                break;
            case 3:
                servico_mais_caro();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 4);

    return 0;
}
