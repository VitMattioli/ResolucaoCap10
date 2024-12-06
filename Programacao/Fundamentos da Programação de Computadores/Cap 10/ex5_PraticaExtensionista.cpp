#include <stdio.h>
#include <string.h>

#define NUM_PRODUTOS 50

typedef struct {
    int codigo;          
    char descricao[100]; 
    float valorUnitario; 
    int quantidade;      
} Produto;

void lerProdutos(Produto produtos[]) {
    for (int i = 0; i < NUM_PRODUTOS; i++) {
        printf("\nProduto %d:\n", i + 1);

        printf("Codigo: ");
        scanf("%d", &produtos[i].codigo);

        printf("Descricao: ");
        getchar(); 
        fgets(produtos[i].descricao, 100, stdin);
        produtos[i].descricao[strcspn(produtos[i].descricao, "\n")] = '\0';

        printf("Valor unitario: R$ ");
        scanf("%f", &produtos[i].valorUnitario);

        printf("Quantidade em estoque: ");
        scanf("%d", &produtos[i].quantidade);
    }
}

void alterarProduto(Produto produtos[], int codigo) {
    for (int i = 0; i < NUM_PRODUTOS; i++) {
        if (produtos[i].codigo == codigo) {
            printf("\nProduto encontrado:\n");
            printf("Descricao atual: %s\n", produtos[i].descricao);
            printf("Valor unitario atual: R$ %.2f\n", produtos[i].valorUnitario);
            printf("Quantidade atual: %d\n", produtos[i].quantidade);

            printf("\nNova descricao: ");
            getchar();
            fgets(produtos[i].descricao, 100, stdin);
            produtos[i].descricao[strcspn(produtos[i].descricao, "\n")] = '\0';

            printf("Novo valor unitario: R$ ");
            scanf("%f", &produtos[i].valorUnitario);

            printf("Nova quantidade em estoque: ");
            scanf("%d", &produtos[i].quantidade);

            printf("\nProduto atualizado com sucesso!\n");
            return;
        }
    }
    printf("\nCodigo do produto nao encontrado.\n");
}

void listarProdutosPorLetra(Produto produtos[], char letra) {
    int encontrados = 0;
    printf("\nProdutos que começam com a letra '%c':\n", letra);
    for (int i = 0; i < NUM_PRODUTOS; i++) {
        char primeiraLetra = produtos[i].descricao[0];
        if (primeiraLetra == letra || primeiraLetra == letra + ('a' - 'A') || primeiraLetra == letra - ('a' - 'A')) {
            printf("Código: %d | Descrição: %s | Valor unitário: R$ %.2f | Estoque: %d\n",
                   produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidade);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum produto encontrado.\n");
    }
}

void listarProdutosComEstoqueBaixo(Produto produtos[]) {
    int encontrados = 0;
    printf("\nProdutos com estoque inferior a 5 unidades:\n");
    for (int i = 0; i < NUM_PRODUTOS; i++) {
        if (produtos[i].quantidade < 5) {
            printf("Código: %d | Descrição: %s | Valor unitário: R$ %.2f | Estoque: %d\n",
                   produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidade);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhum produto encontrado com estoque baixo.\n");
    }
}

int main() {
    Produto produtos[NUM_PRODUTOS];
    int opcao, codigo;
    char letra;

    printf("Cadastro inicial dos produtos:\n");
    lerProdutos(produtos);

    do {
        printf("\nMenu de opcoes:\n");
        printf("1. Alterar dados de um produto\n");
        printf("2. Listar produtos cuja descrição começa com uma letra\n");
        printf("3. Listar produtos com estoque inferior a 5 unidades\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInforme o codigo do produto a ser alterado: ");
                scanf("%d", &codigo);
                alterarProduto(produtos, codigo);
                break;

            case 2:
                printf("\nInforme a letra inicial da descrição: ");
                scanf(" %c", &letra);
                listarProdutosPorLetra(produtos, letra);
                break;

            case 3:
                listarProdutosComEstoqueBaixo(produtos);
                break;

            case 4:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}
