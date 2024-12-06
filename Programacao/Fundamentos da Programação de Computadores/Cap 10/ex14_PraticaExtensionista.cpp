#include <stdio.h>
#include <string.h>

#define MAX_MEDICOS 3
#define MAX_PACIENTES 5
#define MAX_CONSULTAS 10

typedef struct {
    int cod_pac;
    char nome[50];
    char endereco[100];
    char fone[20];
} Paciente;

typedef struct {
    int cod_med;
    char nome[50];
    char endereco[100];
    char fone[20];
} Medico;

typedef struct {
    int num_consulta;
    char dia_semana[10]; 
    char hora[6]; 
    int cod_med;
    int cod_pac;
} Consulta;

Paciente pacientes[MAX_PACIENTES];
Medico medicos[MAX_MEDICOS];
Consulta consultas[MAX_CONSULTAS];

int qtd_pacientes = 0;
int qtd_medicos = 0;
int qtd_consultas = 0;

void cadastrar_paciente() {
    if (qtd_pacientes >= MAX_PACIENTES) {
        printf("Limite de pacientes atingido.\n");
        return;
    }

    Paciente novo;
    printf("Codigo do paciente: ");
    scanf("%d", &novo.cod_pac);

    for (int i = 0; i < qtd_pacientes; i++) {
        if (pacientes[i].cod_pac == novo.cod_pac) {
            printf("Codigo ja cadastrado para outro paciente.\n");
            return;
        }
    }

    printf("Nome do paciente: ");
    scanf(" %[^\n]", novo.nome);
    printf("Endereco: ");
    scanf(" %[^\n]", novo.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]", novo.fone);

    pacientes[qtd_pacientes++] = novo;
    printf("Paciente cadastrado com sucesso.\n");
}

void cadastrar_medico() {
    if (qtd_medicos >= MAX_MEDICOS) {
        printf("Limite de medicos atingido.\n");
        return;
    }

    Medico novo;
    printf("Codigo do medico: ");
    scanf("%d", &novo.cod_med);

    for (int i = 0; i < qtd_medicos; i++) {
        if (medicos[i].cod_med == novo.cod_med) {
            printf("Codigo ja cadastrado para outro medico.\n");
            return;
        }
    }

    printf("Nome do medico: ");
    scanf(" %[^\n]", novo.nome);
    printf("Endereco: ");
    scanf(" %[^\n]", novo.endereco);
    printf("Telefone: ");
    scanf(" %[^\n]", novo.fone);

    medicos[qtd_medicos++] = novo;
    printf("Medico cadastrado com sucesso.\n");
}

void cadastrar_consulta() {
    if (qtd_consultas >= MAX_CONSULTAS) {
        printf("Limite de consultas atingido.\n");
        return;
    }

    Consulta nova;
    printf("Numero da consulta: ");
    scanf("%d", &nova.num_consulta);
    printf("Dia da semana (ex: Segunda): ");
    scanf(" %[^\n]", nova.dia_semana);
    printf("Hora (ex: 08:30): ");
    scanf(" %[^\n]", nova.hora);

    printf("Codigo do medico: ");
    scanf("%d", &nova.cod_med);

    int medico_encontrado = 0;
    for (int i = 0; i < qtd_medicos; i++) {
        if (medicos[i].cod_med == nova.cod_med) {
            medico_encontrado = 1;
            break;
        }
    }
    if (!medico_encontrado) {
        printf("Medico nao encontrado.\n");
        return;
    }

    printf("Codigo do paciente: ");
    scanf("%d", &nova.cod_pac);

    int paciente_encontrado = 0;
    for (int i = 0; i < qtd_pacientes; i++) {
        if (pacientes[i].cod_pac == nova.cod_pac) {
            paciente_encontrado = 1;
            break;
        }
    }
    if (!paciente_encontrado) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    int consultas_do_dia = 0;
    for (int i = 0; i < qtd_consultas; i++) {
        if (strcmp(consultas[i].dia_semana, nova.dia_semana) == 0 && consultas[i].cod_med == nova.cod_med) {
            consultas_do_dia++;
        }
    }
    if (consultas_do_dia >= 2) {
        printf("O medico ja atingiu o limite de consultas para este dia.\n");
        return;
    }

    consultas[qtd_consultas++] = nova;
    printf("Consulta cadastrada com sucesso.\n");
}

void pesquisar_consultas() {
    int cod_med;
    char dia[10];
    printf("Codigo do medico: ");
    scanf("%d", &cod_med);
    printf("Dia da semana (ex: Segunda): ");
    scanf(" %[^\n]", dia);

    printf("Consultas do medico %d no dia %s:\n", cod_med, dia);
    for (int i = 0; i < qtd_consultas; i++) {
        if (consultas[i].cod_med == cod_med && strcmp(consultas[i].dia_semana, dia) == 0) {
            printf("Consulta %d - Hora: %s - Paciente: %d\n", consultas[i].num_consulta, consultas[i].hora, consultas[i].cod_pac);
        }
    }
}

void listar_consultas() {
    char dia[10];
    printf("Dia da semana (ex: Segunda): ");
    scanf(" %[^\n]", dia);

    printf("Consultas no dia %s:\n", dia);
    for (int i = 0; i < qtd_consultas; i++) {
        if (strcmp(consultas[i].dia_semana, dia) == 0) {
            printf("Consulta %d - Hora: %s - Medico: %d - Paciente: %d\n", consultas[i].num_consulta, consultas[i].hora, consultas[i].cod_med, consultas[i].cod_pac);
        }
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu Principal\n");
        printf("1. Cadastrar paciente\n");
        printf("2. Cadastrar medico\n");
        printf("3. Cadastrar consulta\n");
        printf("4. Pesquisar consultas de medico\n");
        printf("5. Listar consultas de um dia\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_paciente();
                break;
            case 2:
                cadastrar_medico();
                break;
            case 3:
                cadastrar_consulta();
                break;
            case 4:
                pesquisar_consultas();
                break;
            case 5:
                listar_consultas();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida!\n");
        }
    } while (opcao != 6);

    return 0;
}
