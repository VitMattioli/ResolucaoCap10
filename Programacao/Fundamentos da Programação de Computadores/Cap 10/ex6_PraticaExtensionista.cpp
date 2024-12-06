#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_CONTAS 100

typedef struct {
    int numeroCliente;
    char nome[100];
    char telefone[15];
    char endereco[200];
} Cliente;

typedef struct {
    int numeroConta;
    int numeroCliente;
    float saldo;
} ContaBancaria;

Cliente clientes[MAX_CLIENTES];
ContaBancaria contas[MAX_CONTAS];
int totalClientes = 0;
int totalContas = 0;

void cadastrar_cliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Erro: Limite maximo de clientes atingido.\n");
        return;
    }

    printf("\nCadastro de cliente:\n");
    printf("Numero do cliente: ");
    scanf("%d", &clientes[totalClientes].numeroCliente);
    getchar(); 
    printf("Nome: ");
    fgets(clientes[totalClientes].nome, 100, stdin);
    clientes[totalClientes].nome[strcspn(clientes[totalClientes].nome, "\n")] = '\0'; 
    printf("Telefone: ");
    fgets(clientes[totalClientes].telefone, 15, stdin);
    clientes[totalClientes].telefone[strcspn(clientes[totalClientes].telefone, "\n")] = '\0'; 
    printf("Endereco: ");
    fgets(clientes[totalClientes].endereco, 200, stdin);
    clientes[totalClientes].endereco[strcspn(clientes[totalClientes].endereco, "\n")] = '\0'; 

    totalClientes++;
    printf("Cliente cadastrado com sucesso!\n");
}

int buscarCliente(int numeroCliente) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].numeroCliente == numeroCliente) {
            return i;
        }
    }
    return -1;
}

void cadastrar_conta() {
    if (totalContas >= MAX_CONTAS) {
        printf("Erro: Limite maximo de contas atingido.\n");
        return;
    }

    int numeroCliente;
    printf("\nCadastro de conta bancaria:\n");
    printf("Numero do cliente titular: ");
    scanf("%d", &numeroCliente);

    int indiceCliente = buscarCliente(numeroCliente);
    if (indiceCliente == -1) {
        printf("Cliente nao cadastrado.\n");
        printf("Deseja cadastrar o cliente? (1 - Sim, 0 - Não): ");
        int opcao;
        scanf("%d", &opcao);
        if (opcao == 1) {
            cadastrar_cliente();
        } else {
            printf("Cadastro de conta cancelado.\n");
            return;
        }
    }

    printf("Numero da conta: ");
    scanf("%d", &contas[totalContas].numeroConta);
    contas[totalContas].numeroCliente = numeroCliente;
    printf("Saldo inicial: R$ ");
    scanf("%f", &contas[totalContas].saldo);

    totalContas++;
    printf("Conta bancaria cadastrada com sucesso!\n");
}

void exibir_contas() {
    printf("\nContas cadastradas:\n");
    for (int i = 0; i < totalContas; i++) {
        printf("Conta: %d\n", contas[i].numeroConta);
        printf("Titular (Numero do Cliente): %d\n", contas[i].numeroCliente);
        printf("Saldo: R$ %.2f\n", contas[i].saldo);

        int indiceCliente = buscarCliente(contas[i].numeroCliente);
        if (indiceCliente != -1) {
            printf("Nome do Cliente: %s\n", clientes[indiceCliente].nome);
            printf("Telefone: %s\n", clientes[indiceCliente].telefone);
            printf("Endereco: %s\n", clientes[indiceCliente].endereco);
        }
        printf("---------------------------\n");
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Cadastrar conta bancaria\n");
        printf("3. Exibir contas cadastradas\n");
        printf("4. Sair\n");
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
                exibir_contas();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}
