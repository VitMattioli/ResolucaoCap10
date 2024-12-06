#include <stdio.h>
#include <string.h>

#define MAX_ESTILISTAS 3
#define MAX_ESTACOES 2
#define MAX_ROUPAS_POR_ESTACAO 10

typedef struct {
    int codigo;
    char nome[50];
    float salario;
} Estilista;

typedef struct {
    int codigo;
    char nome[30];
} Estacao;

typedef struct {
    int codigo;
    char descricao[100];
    int cod_estilista;
    int cod_estacao;
    int ano;
} Roupa;

typedef struct {
    Roupa roupas[MAX_ROUPAS_POR_ESTACAO];
    int qtd_roupas;
} RoupasPorEstacao;

void cadastrar_estilistas(Estilista estilistas[]) {
    for (int i = 0; i < MAX_ESTILISTAS; i++) {
        printf("Cadastro do estilista %d\n", i + 1);
        printf("Codigo do estilista: ");
        scanf("%d", &estilistas[i].codigo);
        printf("Nome do estilista: ");
        scanf(" %[^\n]s", estilistas[i].nome);
        printf("Salario: ");
        scanf("%f", &estilistas[i].salario);
        printf("--------------------------\n");
    }
}

void cadastrar_estacoes(Estacao estacoes[]) {
    for (int i = 0; i < MAX_ESTACOES; i++) {
        printf("Cadastro da estacao %d\n", i + 1);
        printf("Codigo da estacao: ");
        scanf("%d", &estacoes[i].codigo);
        printf("Nome da estacao: ");
        scanf(" %[^\n]s", estacoes[i].nome);
        printf("--------------------------\n");
    }
}

void cadastrar_roupa(RoupasPorEstacao roupasPorEstacao[], Estilista estilistas[], int qtdEstilistas, Estacao estacoes[], int qtdEstacoes) {
    int cod_estacao;
    printf("Informe o codigo da estacao para cadastrar uma roupa: ");
    scanf("%d", &cod_estacao);

    int indexEstacao = -1;
    for (int i = 0; i < qtdEstacoes; i++) {
        if (estacoes[i].codigo == cod_estacao) {
            indexEstacao = i;
            break;
        }
    }

    if (indexEstacao == -1) {
        printf("Estacao nao encontrada!\n");
        return;
    }

    if (roupasPorEstacao[indexEstacao].qtd_roupas >= MAX_ROUPAS_POR_ESTACAO) {
        printf("Limite maximo de roupas para esta estacao atingido!\n");
        return;
    }

    Roupa novaRoupa;
    printf("Codigo da roupa: ");
    scanf("%d", &novaRoupa.codigo);
    printf("Descricao da roupa: ");
    scanf(" %[^\n]s", novaRoupa.descricao);

    printf("Informe o codigo do estilista responsavel: ");
    scanf("%d", &novaRoupa.cod_estilista);

    int estilistaEncontrado = 0;
    for (int i = 0; i < qtdEstilistas; i++) {
        if (estilistas[i].codigo == novaRoupa.cod_estilista) {
            estilistaEncontrado = 1;
            break;
        }
    }

    if (!estilistaEncontrado) {
        printf("Estilista nao encontrado!\n");
        return;
    }

    novaRoupa.cod_estacao = cod_estacao;
    printf("Ano da colecao: ");
    scanf("%d", &novaRoupa.ano);

    roupasPorEstacao[indexEstacao].roupas[roupasPorEstacao[indexEstacao].qtd_roupas] = novaRoupa;
    roupasPorEstacao[indexEstacao].qtd_roupas++;
    printf("Roupa cadastrada com sucesso!\n");
}

void roupas_por_estacao(RoupasPorEstacao roupasPorEstacao[], Estacao estacoes[], int qtdEstacoes, Estilista estilistas[], int qtdEstilistas) {
    int cod_estacao;
    printf("Informe o codigo da estacao para listar as roupas: ");
    scanf("%d", &cod_estacao);

    int indexEstacao = -1;
    for (int i = 0; i < qtdEstacoes; i++) {
        if (estacoes[i].codigo == cod_estacao) {
            indexEstacao = i;
            break;
        }
    }

    if (indexEstacao == -1) {
        printf("Estacao nao encontrada!\n");
        return;
    }

    printf("Roupas da estacao %s:\n", estacoes[indexEstacao].nome);

    for (int i = 0; i < roupasPorEstacao[indexEstacao].qtd_roupas; i++) {
        Roupa r = roupasPorEstacao[indexEstacao].roupas[i];
        printf("Codigo da roupa: %d\n", r.codigo);
        printf("Descricao: %s\n", r.descricao);
        printf("Ano: %d\n", r.ano);

        for (int j = 0; j < qtdEstilistas; j++) {
            if (estilistas[j].codigo == r.cod_estilista) {
                printf("Estilista: %s\n", estilistas[j].nome);
                break;
            }
        }
        printf("--------------------------\n");
    }
}

int main() {
    Estilista estilistas[MAX_ESTILISTAS];
    Estacao estacoes[MAX_ESTACOES];
    RoupasPorEstacao roupasPorEstacao[MAX_ESTACOES] = {0};

    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Cadastrar estilistas\n");
        printf("2. Cadastrar estacoes\n");
        printf("3. Cadastrar roupa\n");
        printf("4. Listar roupas por estacao\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_estilistas(estilistas);
                break;
            case 2:
                cadastrar_estacoes(estacoes);
                break;
            case 3:
                cadastrar_roupa(roupasPorEstacao, estilistas, MAX_ESTILISTAS, estacoes, MAX_ESTACOES);
                break;
            case 4:
                roupas_por_estacao(roupasPorEstacao, estacoes, MAX_ESTACOES, estilistas, MAX_ESTILISTAS);
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
