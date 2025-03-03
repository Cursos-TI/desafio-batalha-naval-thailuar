#include <stdio.h>

#define TAMANHO 10  // Tamanho do tabuleiro
#define TAM_NAVIO 3 // Tamanho fixo dos navios
#define TAM_HABILIDADE 5 // Tamanho das matrizes de habilidades
#define MARC_NAVIO 3 // Valor para navios
#define MARC_HABILIDADE 5 // Valor para áreas afetadas por habilidades

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    // Preenche o tabuleiro com 0 (água)
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

int validarPosicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int deltaLinha, int deltaColuna) {
    // Verifica se a posição do navio está dentro do tabuleiro e não sobrepõe outro navio
    for (int i = 0; i < TAM_NAVIO; i++) {
        int novaLinha = linha + (i * deltaLinha);
        int novaColuna = coluna + (i * deltaColuna);

        if (novaLinha < 0 || novaLinha >= TAMANHO || novaColuna < 0 || novaColuna >= TAMANHO) {
            return 0; // Fora do tabuleiro
        }
        if (tabuleiro[novaLinha][novaColuna] == MARC_NAVIO) {
            return 0; // Sobreposição
        }
    }
    return 1; // Válido
}

void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int deltaLinha, int deltaColuna) {
    // Posiciona o navio no tabuleiro
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha + (i * deltaLinha)][coluna + (i * deltaColuna)] = MARC_NAVIO;
    }
}

// Função para aplicar habilidades no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], int origemLinha, int origemColuna, int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int offset = TAM_HABILIDADE / 2; // Ponto central da matriz de habilidade

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int novaLinha = origemLinha + (i - offset);
                int novaColuna = origemColuna + (j - offset);

                if (novaLinha >= 0 && novaLinha < TAMANHO && novaColuna >= 0 && novaColuna < TAMANHO) {
                    if (tabuleiro[novaLinha][novaColuna] != MARC_NAVIO) {
                        tabuleiro[novaLinha][novaColuna] = MARC_HABILIDADE;
                    }
                }
            }
        }
    }
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTabuleiro de Batalha Naval:\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 0) {
                printf("~ "); // Água
            } else if (tabuleiro[i][j] == MARC_NAVIO) {
                printf("N "); // Navio
            } else if (tabuleiro[i][j] == MARC_HABILIDADE) {
                printf("* "); // Área afetada por habilidade
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];

    inicializarTabuleiro(tabuleiro);

    // Posicionando navios (definição direta)
    int navios[4][4] = {
        {2, 4, 0, 1},  // Navio horizontal
        {5, 7, 1, 0},  // Navio vertical
        {1, 1, 1, 1},  // Navio diagonal principal (\)
        {8, 2, -1, 1}  // Navio diagonal secundária (/)
    };

    // Posiciona os navios no tabuleiro
    for (int i = 0; i < 4; i++) {
        if (validarPosicao(tabuleiro, navios[i][0], navios[i][1], navios[i][2], navios[i][3])) {
            posicionarNavio(tabuleiro, navios[i][0], navios[i][1], navios[i][2], navios[i][3]);
        }
    }

    // Definição das matrizes de habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0}
    };

    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    // Aplicando habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, 3, 3, cone);
    aplicarHabilidade(tabuleiro, 6, 6, cruz);
    aplicarHabilidade(tabuleiro, 5, 2, octaedro);

    // Exibir tabuleiro atualizado
    exibirTabuleiro(tabuleiro);

    return 0;
}
