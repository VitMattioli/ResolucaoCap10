#include <stdio.h>

int main() {
    float salarioFixo, vendasTotais, comissao, salarioFinal;

    printf("Digite o salario fixo do funcionario: R$ ");
    scanf("%f", &salarioFixo);
    printf("Digite o valor total das vendas do funcionario: R$ ");
    scanf("%f", &vendasTotais);

    comissao = vendasTotais * 0.06; 
    salarioFinal = salarioFixo + comissao;

    printf("\n===== Resultado =====\n");
    printf("Salario fixo: R$ %f\n", salarioFixo);
    printf("Comissão (6%% das vendas): R$ %f\n", comissao);
    printf("Salário final: R$ %f\n", salarioFinal);

    return 0;
}
