#include <stdio.h>
#include <string.h>

#define MAX_MEDICOS 50
#define MAX_PACIENTES 100
#define MAX_CONSULTAS 200

typedef struct {
    int codMedico;
    char nome[50];
    char endereco[100];
    float salario;
} Medico;

typedef struct {
    int codPaciente;
    char nome[50];
    char endereco[100];
    int idade;
} Paciente;

typedef struct {
    int numProntuario;
    char dataConsulta[11]; 
    char diagnostico[100];
    int codMedico;
    int codPaciente;
} Consulta;

int buscarMedicoPorCodigo(Medico medicos[], int qtd, int codMedico) {
    for (int i = 0; i < qtd; i++) {
        if (medicos[i].codMedico == codMedico)
            return i;
    }
    return -1;
}

int buscarPacientePorCodigo(Paciente pacientes[], int qtd, int codPaciente) {
    for (int i = 0; i < qtd; i++) {
        if (pacientes[i].codPaciente == codPaciente)
            return i;
    }
    return -1;
}

int medicoTemConsultas(Consulta consultas[], int qtdConsultas, int codMedico) {
    for (int i = 0; i < qtdConsultas; i++) {
        if (consultas[i].codMedico == codMedico)
            return 1;
    }
    return 0;
}

void incluir_medico(Medico medicos[], int *qtdMedicos) {
    int codMedico;
    printf("Codigo do medico: ");
    scanf("%d", &codMedico);

    int pos = buscarMedicoPorCodigo(medicos, *qtdMedicos, codMedico);
    if (pos == -1) {
        pos = (*qtdMedicos)++;
    }

    medicos[pos].codMedico = codMedico;
    printf("Nome do medico: ");
    getchar(); 
    fgets(medicos[pos].nome, 50, stdin);
    medicos[pos].nome[strcspn(medicos[pos].nome, "\n")] = '\0';
    printf("Endereço do medico: ");
    fgets(medicos[pos].endereco, 100, stdin);
    medicos[pos].endereco[strcspn(medicos[pos].endereco, "\n")] = '\0';
    printf("Salario do medico: ");
    scanf("%f", &medicos[pos].salario);
}

void incluir_paciente(Paciente pacientes[], int *qtdPacientes) {
    int codPaciente;
    printf("Codigo do paciente: ");
    scanf("%d", &codPaciente);

    int pos = buscarPacientePorCodigo(pacientes, *qtdPacientes, codPaciente);
    if (pos == -1) {
        pos = (*qtdPacientes)++;
    }

    pacientes[pos].codPaciente = codPaciente;
    printf("Nome do paciente: ");
    getchar(); 
    fgets(pacientes[pos].nome, 50, stdin);
    pacientes[pos].nome[strcspn(pacientes[pos].nome, "\n")] = '\0';
    printf("Endereço do paciente: ");
    fgets(pacientes[pos].endereco, 100, stdin);
    pacientes[pos].endereco[strcspn(pacientes[pos].endereco, "\n")] = '\0';
    printf("Idade do paciente: ");
    scanf("%d", &pacientes[pos].idade);
}

void incluir_consulta(Consulta consultas[], int *qtdConsultas, Medico medicos[], int qtdMedicos, Paciente pacientes[], int qtdPacientes) {
    if (*qtdConsultas >= MAX_CONSULTAS) {
        printf("Limite de consultas atingido.\n");
        return;
    }

    int codMedico, codPaciente;
    printf("Codigo do medico: ");
    scanf("%d", &codMedico);

    if (buscarMedicoPorCodigo(medicos, qtdMedicos, codMedico) == -1) {
        printf("Medico não encontrado.\n");
        return;
    }

    printf("Codigo do paciente: ");
    scanf("%d", &codPaciente);

    if (buscarPacientePorCodigo(pacientes, qtdPacientes, codPaciente) == -1) {
        printf("Paciente nao encontrado.\n");
        return;
    }

    Consulta novaConsulta;
    novaConsulta.numProntuario = *qtdConsultas + 1;
    novaConsulta.codMedico = codMedico;
    novaConsulta.codPaciente = codPaciente;

    printf("Data da consulta (DD/MM/AAAA): ");
    getchar(); 
    fgets(novaConsulta.dataConsulta, 11, stdin);
    novaConsulta.dataConsulta[strcspn(novaConsulta.dataConsulta, "\n")] = '\0';

    printf("Diagnostico: ");
    fgets(novaConsulta.diagnostico, 100, stdin);
    novaConsulta.diagnostico[strcspn(novaConsulta.diagnostico, "\n")] = '\0';

    consultas[(*qtdConsultas)++] = novaConsulta;
}

void excluir_medico(Medico medicos[], int *qtdMedicos, Consulta consultas[], int qtdConsultas) {
    int codMedico;
    printf("Codigo do medico a ser excluido: ");
    scanf("%d", &codMedico);

    int pos = buscarMedicoPorCodigo(medicos, *qtdMedicos, codMedico);
    if (pos == -1) {
        printf("Medico nao encontrado.\n");
        return;
    }

    if (medicoTemConsultas(consultas, qtdConsultas, codMedico)) {
        printf("Exclusao nao permitida. Medico possui consultas associadas.\n");
        return;
    }

    for (int i = pos; i < (*qtdMedicos) - 1; i++) {
        medicos[i] = medicos[i + 1];
    }
    (*qtdMedicos)--;
    printf("Medico excluido com sucesso.\n");
}

void data_consultas(Consulta consultas[], int qtdConsultas, Medico medicos[], int qtdMedicos, Paciente pacientes[], int qtdPacientes) {
    char data[11];
    printf("Informe a data (DD/MM/AAAA): ");
    getchar(); 
    fgets(data, 11, stdin);
    data[strcspn(data, "\n")] = '\0';

    printf("\nConsultas realizadas na data %s:\n", data);
    for (int i = 0; i < qtdConsultas; i++) {
        if (strcmp(consultas[i].dataConsulta, data) == 0) {
            int posMedico = buscarMedicoPorCodigo(medicos, qtdMedicos, consultas[i].codMedico);
            int posPaciente = buscarPacientePorCodigo(pacientes, qtdPacientes, consultas[i].codPaciente);

            printf("Prontuario: %d\n", consultas[i].numProntuario);
            printf("Medico: %s\n", posMedico != -1 ? medicos[posMedico].nome : "Desconhecido");
            printf("Paciente: %s\n", posPaciente != -1 ? pacientes[posPaciente].nome : "Desconhecido");
            printf("Diagnostico: %s\n\n", consultas[i].diagnostico);
        }
    }
}

int main() {
    Medico medicos[MAX_MEDICOS];
    Paciente pacientes[MAX_PACIENTES];
    Consulta consultas[MAX_CONSULTAS];
    int qtdMedicos = 0, qtdPacientes = 0, qtdConsultas = 0;
    int opcao;

    do {
    	printf("\nMenu Principal\n");
    	printf("1. Incluir/Alterar Medicos\n");
    	printf("2. Incluir/Alterar Pacientes\n");
    	printf("3. Incluir Consultas\n");
    	printf("4. Excluir Medico\n");
    	printf("5. Exibir Consultas por Data\n");
    	printf("6. Sair\n");
    	printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                incluir_medico(medicos, &qtdMedicos);
                break;
            case 2:
                incluir_paciente(pacientes, &qtdPacientes);
                break;
            case 3:
                incluir_consulta(consultas, &qtdConsultas, medicos, qtdMedicos, pacientes, qtdPacientes);
                break;
            case 4:
                excluir_medico(medicos, &qtdMedicos, consultas, qtdConsultas);
                break;
            case 5:
                data_consultas(consultas, qtdConsultas, medicos, qtdMedicos, pacientes, qtdPacientes);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }   
	} while (opcao != 6);

    return 0;
}
   
