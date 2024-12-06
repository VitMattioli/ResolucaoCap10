#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 50
#define MAX_RECEBIMENTOS 3

typedef struct {
    int num_doc;
    float valor_doc;
    char data_emissao[11];
    char data_vencimento[11];
    int cod_cli;
} Recebimento;

typedef struct {
    int cod_cli;
    char nome[50];
    char endereco[100];
    char fone[15];
    Recebimento recebimentos[MAX_RECEBIMENTOS];
    int qtd_recebimentos;
} Cliente;

void incluir_cliente(Cliente clientes[], int *qtdClientes) {
    if (*qtdClientes >= MAX_CLIENTES) {
        printf("Capacidade maxima de clientes atingida!\n");
        return;
    }

    Cliente novoCliente;
    printf("Codigo do cliente: ");
    scanf("%d", &novoCliente.cod_cli);

    for (int i = 0; i < *qtdClientes; i++) {
        if (clientes[i].cod_cli == novoCliente.cod_cli) {
            printf("Cliente ja cadastrado!\n");
            return;
        }
    }

    printf("Nome: ");
    scanf(" %[^\n]s", novoCliente.nome);
    printf("Endereco: ");
    scanf(" %[^\n]s", novoCliente.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]s", novoCliente.fone);
    novoCliente.qtd_recebimentos = 0;

    clientes[*qtdClientes] = novoCliente;
    (*qtdClientes)++;
    printf("Cliente cadastrado com sucesso!\n");
}

void alterar_cliente(Cliente clientes[], int qtdClientes) {
    int cod_cli;
    printf("Informe o codigo do cliente para alterar: ");
    scanf("%d", &cod_cli);

    for (int i = 0; i < qtdClientes; i++) {
        if (clientes[i].cod_cli == cod_cli) {
            printf("Alterando dados do cliente %s\n", clientes[i].nome);
            printf("Novo nome: ");
            scanf(" %[^\n]s", clientes[i].nome);
            printf("Novo endereco: ");
            scanf(" %[^\n]s", clientes[i].endereco);
            printf("Novo telefone: ");
            scanf(" %[^\n]s", clientes[i].fone);
            printf("Dados do cliente atualizados com sucesso!\n");
            return;
        }
    }
    printf("Cliente nao encontrado!\n");
}

void incluir_recebimento(Cliente clientes[], int qtdClientes) {
    int cod_cli;
    printf("Informe o codigo do cliente para adicionar um recebimento: ");
    scanf("%d", &cod_cli);

    for (int i = 0; i < qtdClientes; i++) {
        if (clientes[i].cod_cli == cod_cli) {
            if (clientes[i].qtd_recebimentos >= MAX_RECEBIMENTOS) {
                printf("Limite de recebimentos atingido para este cliente!\n");
                return;
            }

            Recebimento novoRecebimento;
            printf("Numero do documento: ");
            scanf("%d", &novoRecebimento.num_doc);
            printf("Valor do documento: ");
            scanf("%f", &novoRecebimento.valor_doc);
            printf("Data de emissao (dd/mm/aaaa): ");
            scanf(" %[^\n]s", novoRecebimento.data_emissao);
            printf("Data de vencimento (dd/mm/aaaa): ");
            scanf(" %[^\n]s", novoRecebimento.data_vencimento);
            novoRecebimento.cod_cli = cod_cli;

            clientes[i].recebimentos[clientes[i].qtd_recebimentos] = novoRecebimento;
            clientes[i].qtd_recebimentos++;
            printf("Recebimento cadastrado com sucesso!\n");
            return;
        }
    }
    printf("Cliente nao encontrado!\n");
}

int calcular_dias_atraso(char dataVencimento[]) {
    struct tm tmVenc = {0};
    time_t tVenc, tAtual;
    double diffDias;

    sscanf(dataVencimento, "%d/%d/%d", &tmVenc.tm_mday, &tmVenc.tm_mon, &tmVenc.tm_year);
    tmVenc.tm_mon -= 1; 
    tmVenc.tm_year -= 1900; 
    tVenc = mktime(&tmVenc);

    time(&tAtual);
    diffDias = difftime(tAtual, tVenc) / (60 * 60 * 24);
    return (int)(diffDias > 0 ? diffDias : 0);
}

void listar_recebimentos(Cliente clientes[], int qtdClientes, char dataInicio[], char dataFim[]) {
    printf("Recebimentos no periodo de %s a %s:\n", dataInicio, dataFim);

    for (int i = 0; i < qtdClientes; i++) {
        for (int j = 0; j < clientes[i].qtd_recebimentos; j++) {
            Recebimento r = clientes[i].recebimentos[j];
            int diasAtraso = calcular_dias_atraso(r.data_vencimento);
            printf("Cliente: %s\n", clientes[i].nome);
            printf("Numero do documento: %d\n", r.num_doc);
            printf("Valor: %.2f\n", r.valor_doc);
            printf("Data de vencimento: %s\n", r.data_vencimento);
            printf("Dias em atraso: %d\n", diasAtraso);
            printf("-----------------------------\n");
        }
    }
}

int main() {
    Cliente clientes[MAX_CLIENTES];
    int qtdClientes = 0;
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Incluir cliente\n");
        printf("2. Alterar cliente\n");
        printf("3. Incluir recebimento\n");
        printf("4. Listar recebimentos por periodo\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluir_cliente(clientes, &qtdClientes);
                break;
            case 2:
                alterar_cliente(clientes, qtdClientes);
                break;
            case 3:
                incluir_recebimento(clientes, qtdClientes);
                break;
            case 4: {
                char dataInicio[11], dataFim[11];
                printf("Informe a data inicial (dd/mm/aaaa): ");
                scanf(" %[^\n]s", dataInicio);
                printf("Informe a data final (dd/mm/aaaa): ");
                scanf(" %[^\n]s", dataFim);
                listar_recebimentos(clientes, qtdClientes, dataInicio, dataFim);
                break;
            }
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}
