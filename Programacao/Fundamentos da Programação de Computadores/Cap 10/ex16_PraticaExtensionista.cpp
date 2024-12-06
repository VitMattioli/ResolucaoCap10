#include <stdio.h>
#include <string.h>

#define MAX_TOMBOS 20
#define MAX_EXEMPLARES 3

typedef struct {
    int numero_tombo;
    char nome_obra[50];
    char nome_autor[50];
    char nome_editora[50];
    int codigo_area;
} Tombo;

typedef struct {
    int numero_tombo;
    int numero_exemplar;
    char data_compra[11];
} Obra;

Tombo tombos[MAX_TOMBOS];
Obra obras[MAX_TOMBOS * MAX_EXEMPLARES];

int qtd_tombos = 0;
int qtd_obras = 0;

void cadastrar_tombo() {
    if (qtd_tombos >= MAX_TOMBOS) {
        printf("Limite de tombos atingido.\n");
        return;
    }

    Tombo novo;
    printf("Numero do tombo: ");
    scanf("%d", &novo.numero_tombo);

    for (int i = 0; i < qtd_tombos; i++) {
        if (tombos[i].numero_tombo == novo.numero_tombo) {
            printf("Este tombo ja esta cadastrado.\n");
            return;
        }
    }

    printf("Nome da obra: ");
    scanf(" %[^\n]", novo.nome_obra);
    printf("Nome do autor: ");
    scanf(" %[^\n]", novo.nome_autor);
    printf("Nome da editora: ");
    scanf(" %[^\n]", novo.nome_editora);
    printf("Codigo da area (1 - Exatas, 2 - Humanas e Sociais, 3 - Biomedicas): ");
    scanf("%d", &novo.codigo_area);

    if (novo.codigo_area < 1 || novo.codigo_area > 3) {
        printf("Codigo da area invalido.\n");
        return;
    }

    tombos[qtd_tombos++] = novo;
    printf("Tombo cadastrado com sucesso.\n");
}

void cadastrar_obra() {
    if (qtd_obras >= MAX_TOMBOS * MAX_EXEMPLARES) {
        printf("Limite de exemplares atingido.\n");
        return;
    }

    Obra nova;
    printf("Numero do tombo: ");
    scanf("%d", &nova.numero_tombo);

    int tombo_encontrado = 0, qtd_exemplares = 0;
    for (int i = 0; i < qtd_tombos; i++) {
        if (tombos[i].numero_tombo == nova.numero_tombo) {
            tombo_encontrado = 1;
        }
    }
    if (!tombo_encontrado) {
        printf("Tombo nao encontrado.\n");
        return;
    }

    for (int i = 0; i < qtd_obras; i++) {
        if (obras[i].numero_tombo == nova.numero_tombo) {
            qtd_exemplares++;
        }
    }

    if (qtd_exemplares >= MAX_EXEMPLARES) {
        printf("Limite de exemplares para este tombo atingido.\n");
        return;
    }

    printf("Numero do exemplar: ");
    scanf("%d", &nova.numero_exemplar);
    printf("Data de compra (DD/MM/AAAA): ");
    scanf(" %[^\n]", nova.data_compra);

    obras[qtd_obras++] = nova;
    printf("Obra cadastrada com sucesso.\n");
}

void obras_por_area() {
    int area;
    printf("Codigo da area (1 - Exatas, 2 - Humanas e Sociais, 3 - Biomedicas): ");
    scanf("%d", &area);

    if (area < 1 || area > 3) {
        printf("Codigo da area invalido.\n");
        return;
    }

    printf("Obras na area %d:\n", area);
    for (int i = 0; i < qtd_tombos; i++) {
        if (tombos[i].codigo_area == area) {
            printf("- %s (Autor: %s, Editora: %s, Tombo: %d)\n", tombos[i].nome_obra, tombos[i].nome_autor, tombos[i].nome_editora, tombos[i].numero_tombo);
        }
    }
}

void obras_por_autor() {
    char autor[50];
    printf("Nome do autor: ");
    scanf(" %[^\n]", autor);

    printf("Obras do autor %s:\n", autor);
    for (int i = 0; i < qtd_tombos; i++) {
        if (strcmp(tombos[i].nome_autor, autor) == 0) {
            printf("- %s (Editora: %s, Tombo: %d)\n", tombos[i].nome_obra, tombos[i].nome_editora, tombos[i].numero_tombo);
        }
    }
}

void obras_por_editora() {
    char editora[50];
    printf("Nome da editora: ");
    scanf(" %[^\n]", editora);

    printf("Obras da editora %s:\n", editora);
    for (int i = 0; i < qtd_tombos; i++) {
        if (strcmp(tombos[i].nome_editora, editora) == 0) {
            printf("- %s (Autor: %s, Tombo: %d)\n", tombos[i].nome_obra, tombos[i].nome_autor, tombos[i].numero_tombo);
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Cadastrar tombos\n");
        printf("2. Cadastrar obras\n");
        printf("3. Mostrar obras por area\n");
        printf("4. Mostrar obras por autor\n");
        printf("5. Mostrar obras por editora\n");
        printf("6. Encerrar o programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_tombo();
                break;
            case 2:
                cadastrar_obra();
                break;
            case 3:
                obras_por_area();
                break;
            case 4:
                obras_por_autor();
                break;
            case 5:
                obras_por_editora();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}
