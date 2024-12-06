#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 12
#define MAX_CONTAS 48
#define MAX_CONTAS_POR_CLIENTE 15

typedef struct {
    char nome[50];
    int idade;
    char endereco[100];
    char cpf_cnpj[20];
    int numero_contas;
    int contas[MAX_CONTAS_POR_CLIENTE]; 
} Cliente;

typedef struct {
    int numero_conta;
    char cpf_cnpj[20];
    float saldo;
} Conta;

Cliente clientes[MAX_CLIENTES];
Conta contas[MAX_CONTAS];
int qtd_clientes = 0;
int qtd_contas = 0;

void cadastrar_cliente() {
    if (qtd_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Cliente novo;
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Idade: ");
    scanf("%d", &novo.idade);
    printf("Endereco: ");
    scanf(" %[^\n]", novo.endereco);
    printf("CPF/CNPJ: ");
    scanf(" %[^\n]", novo.cpf_cnpj);
    novo.numero_contas = 0;

    for (int i = 0; i < qtd_clientes; i++) {
        if (strcmp(clientes[i].cpf_cnpj, novo.cpf_cnpj) == 0) {
            printf("Este CPF/CNPJ ja esta cadastrado.\n");
            return;
        }
    }

    clientes[qtd_clientes++] = novo;
    printf("Cliente cadastrado com sucesso.\n");
}

void cadastrar_conta() {
    if (qtd_contas >= MAX_CONTAS) {
        printf("Limite de contas atingido.\n");
        return;
    }

    Conta nova;
    printf("Numero da conta: ");
    scanf("%d", &nova.numero_conta);

    for (int i = 0; i < qtd_contas; i++) {
        if (contas[i].numero_conta == nova.numero_conta) {
            printf("Este numero de conta ja esta cadastrado.\n");
            return;
        }
    }

    printf("CPF/CNPJ do cliente: ");
    scanf(" %[^\n]", nova.cpf_cnpj);
    printf("Saldo inicial: ");
    scanf("%f", &nova.saldo);

    int cliente_encontrado = 0;
    for (int i = 0; i < qtd_clientes; i++) {
        if (strcmp(clientes[i].cpf_cnpj, nova.cpf_cnpj) == 0) {
            cliente_encontrado = 1;
            if (clientes[i].numero_contas >= MAX_CONTAS_POR_CLIENTE) {
                printf("Este cliente ja atingiu o limite de contas.\n");
                return;
            }
            clientes[i].contas[clientes[i].numero_contas++] = nova.numero_conta;
            break;
        }
    }

    if (!cliente_encontrado) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    contas[qtd_contas++] = nova;
    printf("Conta cadastrada com sucesso.\n");
}

void mostrar_todas_contas() {
    printf("Contas cadastradas:\n");
    for (int i = 0; i < qtd_contas; i++) {
        printf("Numero da conta: %d, CPF/CNPJ: %s, Saldo: %.2f\n",
               contas[i].numero_conta, contas[i].cpf_cnpj, contas[i].saldo);
    }
}

void contas_por_cliente() {
    char cpf_cnpj[20];
    printf("Informe o CPF/CNPJ do cliente: ");
    scanf(" %[^\n]", cpf_cnpj);

    printf("Contas do cliente %s:\n", cpf_cnpj);
    for (int i = 0; i < qtd_contas; i++) {
        if (strcmp(contas[i].cpf_cnpj, cpf_cnpj) == 0) {
            printf("Numero da conta: %d, Saldo: %.2f\n", contas[i].numero_conta, contas[i].saldo);
        }
    }
}

void somatorio_contas_por_cliente() {
    char cpf_cnpj[20];
    printf("Informe o CPF/CNPJ do cliente: ");
    scanf(" %[^\n]", cpf_cnpj);

    float soma = 0;
    for (int i = 0; i < qtd_contas; i++) {
        if (strcmp(contas[i].cpf_cnpj, cpf_cnpj) == 0) {
            soma += contas[i].saldo;
        }
    }

    printf("Somatorio das contas do cliente %s: %.2f\n", cpf_cnpj, soma);
}

void contas_com_saldo_negativo() {
    printf("Contas com saldo negativo:\n");
    for (int i = 0; i < qtd_contas; i++) {
        if (contas[i].saldo < 0) {
            printf("Numero da conta: %d, CPF/CNPJ: %s, Saldo: %.2f\n",
                   contas[i].numero_conta, contas[i].cpf_cnpj, contas[i].saldo);
        }
    }
}

void mostrar_ativo_bancario() {
    float soma = 0;
    for (int i = 0; i < qtd_contas; i++) {
        soma += contas[i].saldo;
    }

    printf("Ativo bancario total: %.2f\n", soma);
}

int main() {
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar conta\n");
        printf("3. Mostrar todas as contas\n");
        printf("4. Mostrar contas de um cliente\n");
        printf("5. Mostrar somatorio das contas de um cliente\n");
        printf("6. Mostrar contas com saldo negativo\n");
        printf("7. Mostrar ativo bancario\n");
        printf("8. Encerrar programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_cliente();
                break;
            case 2:
                cadastrar_conta();
                break;
            case 3:
                mostrar_todas_contas();
                break;
            case 4:
                contas_por_cliente();
                break;
            case 5:
                somatorio_contas_por_cliente();
                break;
            case 6:
                contas_com_saldo_negativo();
                break;
            case 7:
                mostrar_ativo_bancario();
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 8);

    return 0;
}
