#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 15000

typedef struct {
    char nome[50];
    char cpf[15];
    char rg[12];
    char endereco[100];
    int dia_primeira_compra, mes_primeira_compra, ano_primeira_compra;
    float total_gasto;
    int vip; 
} Cliente;

Cliente clientes[MAX_CLIENTES];
int qtd_clientes = 0;

int diferencaMeses(int dia, int mes, int ano, int dia_atual, int mes_atual, int ano_atual) {
    int diferenca = (ano_atual - ano) * 12 + (mes_atual - mes);
    if (diferenca > 6 || (diferenca == 6 && dia_atual > dia)) {
        return 1; 
    }
    return 0; 
}

void cadastrar_cliente() {
    if (qtd_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Cliente novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("CPF: ");
    scanf(" %[^\n]", novo.cpf);
    printf("RG: ");
    scanf(" %[^\n]", novo.rg);
    printf("Endereco: ");
    scanf(" %[^\n]", novo.endereco);
    printf("Data da primeira compra (dd/mm/aaaa): ");
    scanf(" %d/%d/%d", &novo.dia_primeira_compra, &novo.mes_primeira_compra, &novo.ano_primeira_compra);
    novo.total_gasto = 0;
    novo.vip = 0;

    clientes[qtd_clientes++] = novo;
    printf("Cliente cadastrado com sucesso!\n");
}

void atualizar_gasto() {
    char rg[12];
    printf("Informe o RG do cliente: ");
    scanf(" %[^\n]", rg);

    for (int i = 0; i < qtd_clientes; i++) {
        if (strcmp(clientes[i].rg, rg) == 0) {
            float novo_gasto;
            printf("Digite o novo valor gasto pelo cliente: ");
            scanf("%f", &novo_gasto);
            clientes[i].total_gasto += novo_gasto;

            if (!clientes[i].vip && clientes[i].total_gasto >= 5000) {
                clientes[i].vip = 1;
                printf("Parabens! O cliente agora eh VIP.\n");
            } else {
                printf("Total atualizado com sucesso!\n");
            }
            return;
        }
    }

    printf("Cliente com RG %s nao encontrado.\n", rg);
}

void verificar_6meses() {
    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);
    int dia_atual = data_atual->tm_mday;
    int mes_atual = data_atual->tm_mon + 1; 
    int ano_atual = data_atual->tm_year + 1900;

    for (int i = 0; i < qtd_clientes; i++) {
        if (!clientes[i].vip && diferencaMeses(clientes[i].dia_primeira_compra, clientes[i].mes_primeira_compra, clientes[i].ano_primeira_compra, dia_atual, mes_atual, ano_atual)) {
            clientes[i].total_gasto = 0;
            printf("Total gasto do cliente %s (RG: %s) foi zerado por exceder 6 meses.\n", clientes[i].nome, clientes[i].rg);
        }
    }
}

void listar_clientes() {
    printf("Lista de clientes:\n");
    for (int i = 0; i < qtd_clientes; i++) {
        printf("Nome: %s, CPF: %s, RG: %s, Total Gasto: %.2f, VIP: %s\n",
               clientes[i].nome, clientes[i].cpf, clientes[i].rg, clientes[i].total_gasto,
               clientes[i].vip ? "Sim" : "Nao");
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Atualizar gasto de cliente\n");
        printf("3. Verificar e zerar total gasto (nao VIP)\n");
        printf("4. Listar clientes\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_cliente();
                break;
            case 2:
                atualizar_gasto();
                break;
            case 3:
                verificar_6meses();
                break;
            case 4:
                listar_clientes();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
