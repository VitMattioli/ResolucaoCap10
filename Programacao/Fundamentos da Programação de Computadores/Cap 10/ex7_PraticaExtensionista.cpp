#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_CONTAS 100

typedef struct {
    int codigoCliente;
    char nomeCliente[100];
} Cliente;

typedef struct {
    int numeroConta;
    float valorCompra;
    int codigoCliente;
} Conta;

Cliente clientes[MAX_CLIENTES];
Conta contas[MAX_CONTAS];
int totalClientes = 0;
int totalContas = 0;

int buscarCliente(int codigo) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].codigoCliente == codigo) {
            return i;
        }
    }
    return -1;
}

int clientePossuiConta(int codigoCliente) {
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].codigoCliente == codigoCliente) {
            return 1;
        }
    }
    return 0;

void adicionarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Erro: Limite maximo de clientes atingido.\n");
        return;
    }

    int codigo;
    char nome[100];
    printf("Código do cliente: ");
    scanf("%d", &codigo);
    getchar(); 

    if (buscarCliente(codigo) != -1) {
        printf("Erro: Cliente com o mesmo codigo ja cadastrado.\n");
        return;
    }

    printf("Nome do cliente: ");
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = '\0'; 

    clientes[totalClientes].codigoCliente = codigo;
    strcpy(clientes[totalClientes].nomeCliente, nome);
    totalClientes++;

    printf("Cliente cadastrado com sucesso!\n");
}

void adicionar_conta() {
    if (totalContas >= MAX_CONTAS) {
        printf("Erro: Limite maximo de contas atingido.\n");
        return;
    }

    int codigoCliente;
    printf("Codigo do cliente: ");
    scanf("%d", &codigoCliente);

    if (buscarCliente(codigoCliente) == -1) {
        printf("Erro: Cliente nao cadastrado.\n");
        return;
    }

    printf("Numero da conta: ");
    scanf("%d", &contas[totalContas].numeroConta);
    printf("Valor da compra: R$ ");
    scanf("%f", &contas[totalContas].valorCompra);

    contas[totalContas].codigoCliente = codigoCliente;
    totalContas++;

    printf("Conta cadastrada com sucesso!\n");
}

void remover_cliente() {
    int codigoCliente;
    printf("Codigo do cliente a ser removido: ");
    scanf("%d", &codigoCliente);

    int indiceCliente = buscarCliente(codigoCliente);
    if (indiceCliente == -1) {
        printf("Erro: Cliente nao encontrado.\n");
        return;
    }

    if (clientePossuiConta(codigoCliente)) {
        printf("Exclusao nao permitida: Cliente possui contas vinculadas.\n");
        return;
    }

    for (int i = indiceCliente; i < totalClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    totalClientes--;

    printf("Cliente removido com sucesso!\n");
}

void listar_clientes() {
    printf("\nClientes cadastrados:\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("Codigo: %d, Nome: %s\n", clientes[i].codigoCliente, clientes[i].nomeCliente);
    }
}

void listar_contas() {
    printf("\nContas cadastradas:\n");
    for (int i = 0; i < totalContas; i++) {
        printf("Numero da Conta: %d, Codigo do Cliente: %d, Valor da Compra: R$ %.2f\n",
               contas[i].numeroConta, contas[i].codigoCliente, contas[i].valorCompra);
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar cliente\n");
        printf("2. Adicionar conta\n");
        printf("3. Remover cliente\n");
        printf("4. Listar clientes\n");
        printf("5. Listar contas\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_cliente();
                break;
            case 2:
                adicionar_conta();
                break;
            case 3:
                remover_cliente();
                break;
            case 4:
                listar_clientes();
                break;
            case 5:
                listar_contas();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida.\n");
        }
    } while (opcao != 6);

    return 0;
}
