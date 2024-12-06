#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_VENDEDORES 4
#define MESES 12

typedef struct {
    int codigo;
    char nome[50];
    float vendas[MESES];
} Vendedor;

void inicializar_vendedores(Vendedor vendedores[]) {
    for (int i = 0; i < NUM_VENDEDORES; i++) {
        vendedores[i].codigo = -1; 
        for (int j = 0; j < MESES; j++) {
            vendedores[i].vendas[j] = 0.0;
        }
    }
}

int codigo_vendedor(Vendedor vendedores[], int codigo) {
    for (int i = 0; i < NUM_VENDEDORES; i++) {
        if (vendedores[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void cadastrar_vendedor(Vendedor vendedores[]) {
    int codigo;
    printf("Digite o codigo do vendedor: ");
    scanf("%d", &codigo);

    if (codigo_vendedor(vendedores, codigo) != -1) {
        printf("Erro: Ja existe um vendedor com este codigo.\n");
        return;
    }

    for (int i = 0; i < NUM_VENDEDORES; i++) {
        if (vendedores[i].codigo == -1) {
            vendedores[i].codigo = codigo;
            printf("Digite o nome do vendedor: ");
            scanf(" %[^\n]", vendedores[i].nome);
            printf("Vendedor cadastrado com sucesso!\n");
            return;
        }
    }
    printf("Erro: Numero maximo de vendedores atingido.\n");
}

void cadastrar_venda(Vendedor vendedores[]) {
    int codigo, mes;
    float valor;

    printf("Digite o codigo do vendedor: ");
    scanf("%d", &codigo);
    int indice = codigo_vendedor(vendedores, codigo);
    if (indice == -1) {
        printf("Erro: Vendedor nao encontrado.\n");
        return;
    }

    printf("Digite o numero do mes (1-12): ");
    scanf("%d", &mes);
    if (mes < 1 || mes > 12) {
        printf("Erro: Mes invalido.\n");
        return;
    }

    if (vendedores[indice].vendas[mes - 1] > 0) {
        printf("Erro: Venda ja cadastrada para este vendedor neste mes.\n");
        return;
    }

    printf("Digite o valor da venda: ");
    scanf("%f", &valor);
    vendedores[indice].vendas[mes - 1] = valor;
    printf("Venda cadastrada com sucesso!\n");
}

void consultar_vendas_mes(Vendedor vendedores[]) {
    int codigo, mes;

    printf("Digite o codigo do vendedor: ");
    scanf("%d", &codigo);
    int indice = codigo_vendedor(vendedores, codigo);
    if (indice == -1) {
        printf("Erro: Vendedor nao encontrado.\n");
        return;
    }

    printf("Digite o numero do mes (1-12): ");
    scanf("%d", &mes);
    if (mes < 1 || mes > 12) {
        printf("Erro: Mes invalido.\n");
        return;
    }

    printf("Vendas do vendedor %s no mes %d: R$ %.2f\n", 
           vendedores[indice].nome, mes, vendedores[indice].vendas[mes - 1]);
}

void consultar_total_vendas(Vendedor vendedores[]) {
    int codigo;

    printf("Digite o codigo do vendedor: ");
    scanf("%d", &codigo);
    int indice = codigo_vendedor(vendedores, codigo);
    if (indice == -1) {
        printf("Erro: Vendedor nao encontrado.\n");
        return;
    }

    float total = 0.0;
    for (int i = 0; i < MESES; i++) {
        total += vendedores[indice].vendas[i];
    }

    printf("Total de vendas do vendedor %s: R$ %.2f\n", 
           vendedores[indice].nome, total);
}

void vendedor_com_mais_vendas(Vendedor vendedores[]) {
    int mes;

    printf("Digite o numero do mes (1-12): ");
    scanf("%d", &mes);
    if (mes < 1 || mes > 12) {
        printf("Erro: Mes invalido.\n");
        return;
    }

    int maiorVendedor = -1;
    float maiorVenda = 0.0;
    for (int i = 0; i < NUM_VENDEDORES; i++) {
        if (vendedores[i].vendas[mes - 1] > maiorVenda) {
            maiorVenda = vendedores[i].vendas[mes - 1];
            maiorVendedor = i;
        }
    }

    if (maiorVendedor != -1) {
        printf("Vendedor com maior venda no mes %d: %s (R$ %.2f)\n", 
               mes, vendedores[maiorVendedor].nome, maiorVenda);
    } else {
        printf("Nenhuma venda registrada no mes %d.\n", mes);
    }
}

void mes_com_mais_vendas(Vendedor vendedores[]) {
    float totalMes[MESES] = {0.0};
    for (int i = 0; i < NUM_VENDEDORES; i++) {
        for (int j = 0; j < MESES; j++) {
            totalMes[j] += vendedores[i].vendas[j];
        }
    }

    int mesMaior = 0;
    for (int j = 1; j < MESES; j++) {
        if (totalMes[j] > totalMes[mesMaior]) {
            mesMaior = j;
        }
    }

    printf("Mes com maior venda: %d (Total: R$ %.2f)\n", 
           mesMaior + 1, totalMes[mesMaior]);
}

int main() {
    Vendedor vendedores[NUM_VENDEDORES];
    inicializar_vendedores(vendedores);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar vendedor\n");
        printf("2. Cadastrar venda\n");
        printf("3. Consultar vendas de um vendedor em um mes\n");
        printf("4. Consultar total de vendas de um vendedor\n");
        printf("5. Vendedor que mais vendeu em um mes\n");
        printf("6. Mes com mais vendas\n");
        printf("7. Finalizar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrar_vendedor(vendedores); 
				break;
            case 2: cadastrar_venda(vendedores); 
				break;
            case 3: consultar_vendas_mes(vendedores); 
				break;
            case 4: consultar_total_vendas(vendedores); 
				break;
            case 5: vendedor_com_mais_vendas(vendedores); 
				break;
            case 6: mes_com_mais_vendas(vendedores); 
				break;
            case 7: printf("Saindo...\n"); 
				break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 7);

    return 0;
}
