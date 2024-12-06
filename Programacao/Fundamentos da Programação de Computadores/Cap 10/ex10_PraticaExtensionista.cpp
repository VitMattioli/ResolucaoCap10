#include <stdio.h>
#include <string.h>

#define NUM_DOCUMENTOS 15


typedef struct {
    int numeroDocumento;
    int codigoCliente;
    char dataVencimento[11]; 
    char dataPagamento[11];  
    float valorConta;
    float juros;
} Documento;

int diferenca_dias(char dataVencimento[], char dataPagamento[]) {
    int diaV, mesV, anoV;
    int diaP, mesP, anoP;

    sscanf(dataVencimento, "%d/%d/%d", &diaV, &mesV, &anoV);
    sscanf(dataPagamento, "%d/%d/%d", &diaP, &mesP, &anoP);

    int totalDiasV = anoV * 365 + mesV * 30 + diaV;
    int totalDiasP = anoP * 365 + mesP * 30 + diaP;

    return totalDiasP - totalDiasV;
}

int main() {
    Documento documentos[NUM_DOCUMENTOS];
    float totalReceber = 0.0, somaJuros = 0.0;
    int i;

    for (i = 0; i < NUM_DOCUMENTOS; i++) {
        printf("Documento %d:\n", i + 1);
        printf("Numero do documento: ");
        scanf("%d", &documentos[i].numeroDocumento);
        printf("Codigo do cliente: ");
        scanf("%d", &documentos[i].codigoCliente);
        getchar(); 
        printf("Data de vencimento (DD/MM/AAAA): ");
        fgets(documentos[i].dataVencimento, 11, stdin);
        documentos[i].dataVencimento[strcspn(documentos[i].dataVencimento, "\n")] = '\0';
        getchar(); 
        printf("Data de pagamento (DD/MM/AAAA): ");
        fgets(documentos[i].dataPagamento, 11, stdin);
        documentos[i].dataPagamento[strcspn(documentos[i].dataPagamento, "\n")] = '\0';
        printf("Valor da conta: R$ ");
        scanf("%f", &documentos[i].valorConta);

        int diasAtraso = diferenca_dias(documentos[i].dataVencimento, documentos[i].dataPagamento);
        if (diasAtraso > 0) {
            documentos[i].juros = documentos[i].valorConta * 0.0002 * diasAtraso;
        } else {
            documentos[i].juros = 0.0;
        }

        totalReceber += documentos[i].valorConta + documentos[i].juros;
        somaJuros += documentos[i].juros;
    }

    printf("\n===== Documentos Cadastrados =====\n");
    for (i = 0; i < NUM_DOCUMENTOS; i++) {
        printf("Documento %d:\n", i + 1);
        printf("Numero do documento: %d\n", documentos[i].numeroDocumento);
        printf("Codigo do cliente: %d\n", documentos[i].codigoCliente);
        printf("Data de vencimento: %s\n", documentos[i].dataVencimento);
        printf("Data de pagamento: %s\n", documentos[i].dataPagamento);
        printf("Valor da conta: R$ %f\n", documentos[i].valorConta);
        printf("Juros: R$ %f\n", documentos[i].juros);
        printf("Total: R$ %f\n\n", documentos[i].valorConta + documentos[i].juros);
    }

    printf("===== Resumo =====\n");
    printf("Total geral a receber: R$ %.2f\n", totalReceber);
    printf("Media dos juros: R$ %.2f\n", somaJuros / NUM_DOCUMENTOS);

    return 0;
}
