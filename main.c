#include <stdio.h>
#include <stdlib.h>

int main() {
    char nome[50];
    int horaInicio, minutoInicio, horarioTotal, tempoConectado, tempoNecessario = 0, minutosExtras = 0, tempoEstimado = 0, avisoDesaceleracao = 0;
    float bateriaInicial, bateriaAtual, ganhoPorMinuto, bateriaTemp, kwhConsumido = 0.0, tarifaKwh = 4.0, taxaFixa = 2.50, valorEnergia, multaOciosidade = 0.0, valorTotal;

    printf("========================================\n");
    printf(" SISTEMA DE RECARGA VEICULAR ELETRICA\n");
    printf("========================================\n\n");

    printf("Digite o nome do usuario: ");
    scanf(" %[^\n]", nome);

    do {
    printf("Digite a porcentagem inicial da bateria (0 a 99): ");

    if (scanf("%f", &bateriaInicial) != 1) {
        printf("Valor invalido! Digite novamente.\n\n");

        while (getchar() != '\n');

        bateriaInicial = -1;

    } else {
        while (getchar() != '\n');

        if (bateriaInicial < 0 || bateriaInicial > 99) {
        printf("Valor invalido! Digite novamente.\n\n");
        }
    }

    } while (bateriaInicial < 0 || bateriaInicial > 99);

    bateriaAtual = bateriaInicial;
    bateriaTemp = bateriaInicial;

    while (bateriaTemp < 100) {
    if (bateriaTemp < 80) {
        bateriaTemp += 1.5;
    } else {
        bateriaTemp += 0.7;
    }
    tempoEstimado++;
    }

    printf("\nTempo estimado para atingir 100%%: %d minutos\n\n",
       tempoEstimado);

    do {
    printf("Digite a hora de inicio da sessao (ex: 14 ou 14:30): ");

    minutoInicio = 0;

    int resultado = scanf("%d:%d", &horaInicio, &minutoInicio);

    if (resultado < 1) {
        printf("Horario invalido! Digite novamente.\n\n");

        while (getchar() != '\n');

        horaInicio = -1;
    } else if (horaInicio < 0 || horaInicio > 23 ||
        minutoInicio < 0 || minutoInicio > 59) {
        printf("Horario invalido! Digite novamente.\n\n");
    }

    } while (horaInicio < 0 || horaInicio > 23 ||
         minutoInicio < 0 || minutoInicio > 59);

    horarioTotal = (horaInicio * 60) + minutoInicio;

    do{
        printf("Digite por quantos minutos o carro ficara conectado: ");
        if (scanf("%d", &tempoConectado) != 1) {
        printf("Tempo invalido! Digite novamente.\n\n");

     while (getchar() != '\n');

    tempoConectado = 0;

    } else if (tempoConectado <= 0) {
        printf("Tempo invalido! Digite novamente.\n\n");
    }

    } while (tempoConectado <= 0);

    if (horarioTotal >= 1020 && horarioTotal < 1320) {
        tarifaKwh = tarifaKwh * 1.15;

        printf("\nHorario de pico detectado!\n");
        printf("Acrescimo de 15%% aplicado na tarifa do kWh.\n");
    }

    printf("\n========================================\n");
    printf(" INICIANDO SESSAO DE RECARGA...\n");
    printf("========================================\n\n");

    for (tempoNecessario = 1; tempoNecessario <= tempoConectado; tempoNecessario++) {
    if (bateriaAtual < 100) {
        if (bateriaAtual < 80) {
            ganhoPorMinuto = 1.5;
            kwhConsumido += 0.8;
        } else {
            if (avisoDesaceleracao == 0) {
            printf("\nCarregamento desacelerado apos 80%% para protecao da bateria.\n");
            avisoDesaceleracao = 1;
        }
            ganhoPorMinuto = 0.7;
            kwhConsumido += 0.4;
        }

        bateriaAtual += ganhoPorMinuto;

        if (bateriaAtual > 100)
            bateriaAtual = 100;
    }

    printf("Minuto %d -> Bateria: %.1f%%\n",
           tempoNecessario,
           bateriaAtual);
}

    if (tempoConectado > tempoEstimado) {
    minutosExtras = tempoConectado - tempoEstimado;
    multaOciosidade = minutosExtras * 5.0;
} else {
    multaOciosidade = 0;
}
    valorEnergia = kwhConsumido * tarifaKwh;
    valorTotal = valorEnergia + taxaFixa + multaOciosidade;

    printf("\n========================================\n");
    printf(" RELATORIO FINAL DA SESSAO\n");
    printf("========================================\n\n");

    printf("Usuario: %s\n", nome);

    printf("\n--- DADOS DA RECARGA ---\n");
    printf("Bateria inicial: %.1f%%\n", bateriaInicial);
    printf("Bateria final: %.1f%%\n", bateriaAtual);
    printf("Tempo estimado para recarga total: %d minutos\n",
           tempoEstimado);
    printf("Tempo conectado: %d minutos\n",
           tempoConectado);
    printf("Energia consumida: %.1f kWh\n",
           kwhConsumido);

    printf("\n--- TARIFACAO ---\n");
    printf("Valor do kWh: R$ %.2f\n",
           tarifaKwh);
    printf("Custo da energia: R$ %.2f\n",
           valorEnergia);
    printf("Taxa fixa de conectividade: R$ %.2f\n",
           taxaFixa);
    if (multaOciosidade > 0) {
    printf("Multa de ociosidade: R$ %.2f\n",
           multaOciosidade);
    } else {
    printf("Nao houve multa de ociosidade.\n");
    }
    printf("\nVALOR TOTAL: R$ %.2f\n",
           valorTotal);

    printf("\n========================================\n");
    printf(" SESSAO ENCERRADA\n");
    printf("========================================\n");

    return 0;
}