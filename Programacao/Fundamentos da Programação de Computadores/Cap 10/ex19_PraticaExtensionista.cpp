#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 9999

typedef struct {
    int registro;
    char nome[50];
    char data_nascimento[11]; 
    char cpf[15];
    char rg[12];
    char cidade[50];
    char endereco[100];
    int quantidade_eletro; 
} Cliente;

Cliente clientes[MAX_CLIENTES];
int qtd_clientes = 0;

void cadastrar_clientes() {
    if (qtd_clientes >= MAX_CLIENTES) {
        printf("Limite maximo de clientes atingido.\n");
        return;
    }

    Cliente novo;
    novo.registro = qtd_clientes + 1;

    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);
    printf("Data de nascimento (dd/mm/aaaa): ");
    scanf(" %[^\n]", novo.data_nascimento);
    printf("CPF: ");
    scanf(" %[^\n]", novo.cpf);
    printf("RG: ");
    scanf(" %[^\n]", novo.rg);
    printf("Cidade: ");
    scanf(" %[^\n]", novo.cidade);
    printf("Endereço: ");
    scanf(" %[^\n]", novo.endereco);
    printf("Quantidade de eletrodomesticos adquiridos: ");
    scanf("%d", &novo.quantidade_eletro);

    clientes[qtd_clientes++] = novo;
    printf("Cliente cadastrado com sucesso! Registro: %d\n", novo.registro);
}

void listar_participantes() {
    printf("\nClientes Participantes do Sorteio:\n");
    int participantes = 0;
    for (int i = 0; i < qtd_clientes; i++) {
        if (clientes[i].quantidade_eletro >= 5) {
            printf("Registro: %d, Nome: %s, Quantidade Comprada: %d\n",
                   clientes[i].registro, clientes[i].nome, clientes[i].quantidade_eletro);
            participantes++;
        }
    }
    if (participantes == 0) {
        printf("Nenhum cliente participante do sorteio.\n");
    }
}

void realizar_sorteio() {
    int participantes = 0;
    int registros[MAX_CLIENTES];
    
    for (int i = 0; i < qtd_clientes; i++) {
        if (clientes[i].quantidade_eletro >= 5) {
            registros[participantes++] = clientes[i].registro;
        }
    }

    if (participantes == 0) {
        printf("Nenhum cliente qualificado para o sorteio.\n");
        return;
    }

    srand(time(NULL));
    int vencedor_index = rand() % participantes;
    int registro_vencedor = registros[vencedor_index];

    for (int i = 0; i < qtd_clientes; i++) {
        if (clientes[i].registro == registro_vencedor) {
            printf("\n=== Resultado do Sorteio ===\n");
            printf("Registro Vencedor: %d\n", clientes[i].registro);
            printf("Nome: %s\n", clientes[i].nome);
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Parabens! Voce ganhou a Ferrari F-50!\n");
            return;
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Participantes do Sorteio\n");
        printf("3. Realizar Sorteio\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_clientes();
                break;
            case 2:
                listar_participantes();
                break;
            case 3:
                realizar_sorteio();
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida!.\n");
        }
    } while (opcao != 4);

    return 0;
}
