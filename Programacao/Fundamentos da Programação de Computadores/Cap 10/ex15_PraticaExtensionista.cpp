#include <stdio.h>
#include <string.h>

#define MAX_COZINHEIROS 3
#define MAX_INGREDIENTES 15
#define MAX_RECEITAS 20
#define MAX_ING_RECEITA 3

typedef struct {
    int codigo;
    char nome[50];
} Cozinheiro;

typedef struct {
    int codigo;
    char descricao[50];
} Ingrediente;

typedef struct {
    int codigo;
    char nome[50];
    float calorias; 
    int cod_cozinheiro;
    int ingredientes[MAX_ING_RECEITA];
    float quantidade[MAX_ING_RECEITA];
    char unidade[MAX_ING_RECEITA][10];
    int qtd_ingredientes;
} Receita;

Cozinheiro cozinheiros[MAX_COZINHEIROS];
Ingrediente ingredientes[MAX_INGREDIENTES];
Receita receitas[MAX_RECEITAS];

int qtd_cozinheiros = 0;
int qtd_ingredientes = 0;
int qtd_receitas = 0;

void cadastrar_cozinheiro() {
    if (qtd_cozinheiros >= MAX_COZINHEIROS) {
        printf("Limite de cozinheiros atingido.\n");
        return;
    }

    Cozinheiro novo;
    printf("Codigo do cozinheiro: ");
    scanf("%d", &novo.codigo);
    printf("Nome do cozinheiro: ");
    scanf(" %[^\n]", novo.nome);

    cozinheiros[qtd_cozinheiros++] = novo;
    printf("Cozinheiro cadastrado com sucesso.\n");
}

void cadastrar_ingrediente() {
    if (qtd_ingredientes >= MAX_INGREDIENTES) {
        printf("Limite de ingredientes atingido.\n");
        return;
    }

    Ingrediente novo;
    printf("Codigo do ingrediente: ");
    scanf("%d", &novo.codigo);
    printf("Descricao do ingrediente: ");
    scanf(" %[^\n]", novo.descricao);

    ingredientes[qtd_ingredientes++] = novo;
    printf("Ingrediente cadastrado com sucesso.\n");
}

void cadastrar_receita() {
    if (qtd_receitas >= MAX_RECEITAS) {
        printf("Limite de receitas atingido.\n");
        return;
    }

    Receita nova;
    printf("Codigo da receita: ");
    scanf("%d", &nova.codigo);
    printf("Nome da receita: ");
    scanf(" %[^\n]", nova.nome);
    printf("Calorias a cada 100g: ");
    scanf("%f", &nova.calorias);

    printf("Codigo do cozinheiro: ");
    scanf("%d", &nova.cod_cozinheiro);

    int cozinheiro_encontrado = 0;
    for (int i = 0; i < qtd_cozinheiros; i++) {
        if (cozinheiros[i].codigo == nova.cod_cozinheiro) {
            cozinheiro_encontrado = 1;
            break;
        }
    }
    if (!cozinheiro_encontrado) {
        printf("Cozinheiro nao encontrado.\n");
        return;
    }

    printf("Quantos ingredientes (maximo %d): ", MAX_ING_RECEITA);
    scanf("%d", &nova.qtd_ingredientes);

    if (nova.qtd_ingredientes > MAX_ING_RECEITA) {
        printf("Numero de ingredientes excede o maximo permitido.\n");
        return;
    }

    for (int i = 0; i < nova.qtd_ingredientes; i++) {
        printf("Codigo do ingrediente %d: ", i + 1);
        scanf("%d", &nova.ingredientes[i]);

        int ingrediente_encontrado = 0;
        for (int j = 0; j < qtd_ingredientes; j++) {
            if (ingredientes[j].codigo == nova.ingredientes[i]) {
                ingrediente_encontrado = 1;
                break;
            }
        }
        if (!ingrediente_encontrado) {
            printf("Ingrediente nao encontrado.\n");
            return;
        }

        printf("Quantidade: ");
        scanf("%f", &nova.quantidade[i]);
        printf("Unidade de medida (ex: g, ml): ");
        scanf(" %[^\n]", nova.unidade[i]);
    }

    receitas[qtd_receitas++] = nova;
    printf("Receita cadastrada com sucesso.\n");
}

void receitas_cozinheiro() {
    int cod_cozinheiro;
    printf("Codigo do cozinheiro: ");
    scanf("%d", &cod_cozinheiro);

    printf("Receitas do cozinheiro %d:\n", cod_cozinheiro);
    for (int i = 0; i < qtd_receitas; i++) {
        if (receitas[i].cod_cozinheiro == cod_cozinheiro) {
            printf("- %s (Codigo: %d, Calorias: %.2f)\n", receitas[i].nome, receitas[i].codigo, receitas[i].calorias);
        }
    }
}

void receitas_por_calorias() {
    float min_calorias, max_calorias;
    printf("Intervalo de calorias (minimo e maximo): ");
    scanf("%f %f", &min_calorias, &max_calorias);

    printf("Receitas com calorias entre %.2f e %.2f:\n", min_calorias, max_calorias);
    for (int i = 0; i < qtd_receitas; i++) {
        if (receitas[i].calorias >= min_calorias && receitas[i].calorias <= max_calorias) {
            printf("- %s (Codigo: %d, Calorias: %.2f)\n", receitas[i].nome, receitas[i].codigo, receitas[i].calorias);
        }
    }
}

void receitas_por_cozinheiro() {
    int total_receitas[MAX_COZINHEIROS] = {0};

    for (int i = 0; i < qtd_receitas; i++) {
        for (int j = 0; j < qtd_cozinheiros; j++) {
            if (receitas[i].cod_cozinheiro == cozinheiros[j].codigo) {
                total_receitas[j]++;
            }
        }
    }

    for (int i = 0; i < qtd_cozinheiros; i++) {
        printf("Cozinheiro %s elaborou %d receitas.\n", cozinheiros[i].nome, total_receitas[i]);
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Cadastrar cozinheiro\n");
        printf("2. Cadastrar ingrediente\n");
        printf("3. Cadastrar receita\n");
        printf("4. Mostrar receitas de um cozinheiro\n");
        printf("5. Mostrar receitas por calorias\n");
        printf("6. Mostrar total de receitas por cozinheiro\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_cozinheiro();
                break;
            case 2:
                cadastrar_ingrediente();
                break;
            case 3:
                cadastrar_receita();
                break;
            case 4:
                receitas_cozinheiro();
                break;
            case 5:
                receitas_por_calorias();
                break;
            case 6:
                receitas_por_cozinheiro();
                break;
            case 7:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}
