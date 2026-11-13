/*
 * ===========================================================================
 *  PSE EM AÇÃO
 *  Sistema de Planejamento e Acompanhamento de Ações do
 *  Programa Saúde na Escola (PSE)
 *
 *  Atividade Extensionista Prática (AEP) - 2ª Entrega
 *  UNICESUMAR - Engenharia de Software / Análise e Desenvolvimento de Sistemas
 *
 *  Integrantes:
 *    Luiz Augusto da Rocha Bedendo - RA 26007445-2
 *    Italo Fernandes Santos        - RA 26003073-2
 *
 *  Compilação: gcc pse_em_acao.c -o pse_em_acao -Wall
 *  Execução  : ./pse_em_acao
 * ===========================================================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ACOES 100
#define TAM_ESCOLA 50
#define TAM_TEMA 50
#define TAM_DATA 11
#define TAM_PUBLICO 50
#define TAM_RESPONSAVEL 50

/* Situações possíveis de uma ação, conforme dicionário de dados (5.7) */
#define PLANEJADA 1
#define REALIZADA 2
#define CANCELADA 3

#define NAO_ENCONTRADO -1

/* ---------------------------------------------------------------------
 * Estrutura de dados (struct) — baseada no dicionário de dados (5.7)
 * --------------------------------------------------------------------- */
typedef struct {
    int  codigo;
    char escola[TAM_ESCOLA];
    char tema[TAM_TEMA];
    char data_prevista[TAM_DATA];
    char publico_alvo[TAM_PUBLICO];
    char responsavel[TAM_RESPONSAVEL];
    int  qtd_prevista;
    int  qtd_efetiva;
    int  situacao; /* 1-planejada 2-realizada 3-cancelada */
} AcaoPSE;

/* Vetor em memória + contador global de ações cadastradas (RN06) */
static AcaoPSE acoes[MAX_ACOES];
static int quantidade_de_acoes = 0;

/* ---------------------------------------------------------------------
 * Protótipos
 * --------------------------------------------------------------------- */
void limparBufferEntrada(void);
int  lerOpcaoMenu(void);
int  lerInteiro(const char *mensagem);
void lerString(const char *mensagem, char *destino, int tamanho);
int  campoVazio(const char *texto);
int  existeCodigo(int codigo);
int  localizarPorCodigo(int codigo);
const char *nomeSituacao(int situacao);

void cadastrarAcao(void);
void listarAcoes(void);
void pesquisarAcoes(void);
void atualizarSituacao(void);
void gerarResumo(void);
void exibirAcao(const AcaoPSE *a);
void exibirMenu(void);

/* ---------------------------------------------------------------------
 * main — Menu principal (ESCOLA/CASO conforme pseudocódigo da seção 6.4)
 * --------------------------------------------------------------------- */
int main(void) {
    int opcao;

    printf("=============================================================\n");
    printf("        PSE EM ACAO - Planejamento e Acompanhamento\n");
    printf("        Programa Saude na Escola (fins academicos)\n");
    printf("=============================================================\n");

    do {
        exibirMenu();
        opcao = lerOpcaoMenu();

        switch (opcao) {
            case 1: cadastrarAcao();     break;
            case 2: listarAcoes();       break;
            case 3: pesquisarAcoes();    break;
            case 4: atualizarSituacao(); break;
            case 5: gerarResumo();       break;
            case 0: printf("\nEncerrando o sistema. Ate a proxima!\n"); break;
            default:
                printf("\n[ERRO] Opcao invalida. Escolha um numero entre 0 e 5.\n");
        }
    } while (opcao != 0);

    return 0;
}

/* ---------------------------------------------------------------------
 * Funções utilitárias de entrada/validação
 * --------------------------------------------------------------------- */

/* Descarta o restante da linha do buffer de entrada (inclusive '\n') */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* descarta */ }
}

/*
 * Lê a opção do menu de forma robusta: se o usuário digitar texto não
 * numérico, retorna um valor fora do intervalo (99) para cair no
 * "CASO CONTRARIO" do switch, em vez de travar o programa (RNF03).
 */
int lerOpcaoMenu(void) {
    int opcao;
    printf("\nOpcao: ");
    if (scanf("%d", &opcao) != 1) {
        limparBufferEntrada();
        return 99;
    }
    limparBufferEntrada();
    return opcao;
}

/* Lê um inteiro validando que a entrada é numérica (RNF03) */
int lerInteiro(const char *mensagem) {
    int valor;
    int ok;
    do {
        printf("%s", mensagem);
        ok = (scanf("%d", &valor) == 1);
        limparBufferEntrada();
        if (!ok) {
            printf("[ERRO] Entrada invalida. Digite um numero inteiro.\n");
        }
    } while (!ok);
    return valor;
}

/* Lê uma string com fgets (evita overflow) e remove o '\n' final */
void lerString(const char *mensagem, char *destino, int tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        } else {
            /* linha maior que o buffer: descarta o restante */
            limparBufferEntrada();
        }
    } else {
        destino[0] = '\0';
    }
}

/* RN05/RF06 (parcial): considera vazio também string só com espacos */
int campoVazio(const char *texto) {
    int i;
    int tamanho = (int) strlen(texto);
    if (tamanho == 0) return 1;
    for (i = 0; i < tamanho; i++) {
        if (!isspace((unsigned char) texto[i])) {
            return 0;
        }
    }
    return 1;
}

/* RN01 — verifica se já existe uma ação com o código informado */
int existeCodigo(int codigo) {
    int i;
    for (i = 0; i < quantidade_de_acoes; i++) {
        if (acoes[i].codigo == codigo) {
            return 1;
        }
    }
    return 0;
}

/* Retorna o índice da ação com o código informado, ou NAO_ENCONTRADO */
int localizarPorCodigo(int codigo) {
    int i;
    for (i = 0; i < quantidade_de_acoes; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return NAO_ENCONTRADO;
}

const char *nomeSituacao(int situacao) {
    switch (situacao) {
        case PLANEJADA: return "Planejada";
        case REALIZADA: return "Realizada";
        case CANCELADA: return "Cancelada";
        default:        return "Desconhecida";
    }
}

void exibirMenu(void) {
    printf("\n-------------------------------------------------------------\n");
    printf("1 - Cadastrar acao\n");
    printf("2 - Listar acoes\n");
    printf("3 - Pesquisar acao\n");
    printf("4 - Atualizar situacao\n");
    printf("5 - Gerar resumo\n");
    printf("0 - Encerrar\n");
    printf("-------------------------------------------------------------\n");
}

/* ---------------------------------------------------------------------
 * RF01 / RN01 / RN02 / RN03 / RN06 — Cadastro de ação
 * --------------------------------------------------------------------- */
void cadastrarAcao(void) {
    AcaoPSE nova;
    int codigo;

    printf("\n=== CADASTRAR ACAO ===\n");

    /* RN06 — limite de armazenamento do vetor */
    if (quantidade_de_acoes >= MAX_ACOES) {
        printf("[ERRO] Limite maximo de acoes atingido (%d). "
               "Nao e possivel cadastrar novas acoes.\n", MAX_ACOES);
        return;
    }

    /* RN01 — código único */
    do {
        codigo = lerInteiro("Codigo da acao: ");
        if (existeCodigo(codigo)) {
            printf("[ERRO] Codigo ja cadastrado. Informe outro codigo.\n");
        }
    } while (existeCodigo(codigo));
    nova.codigo = codigo;

    /* RF06 — campos obrigatórios não podem ficar vazios */
    do {
        lerString("Escola: ", nova.escola, TAM_ESCOLA);
        if (campoVazio(nova.escola)) {
            printf("[ERRO] Campo obrigatorio nao preenchido.\n");
        }
    } while (campoVazio(nova.escola));

    do {
        lerString("Tema: ", nova.tema, TAM_TEMA);
        if (campoVazio(nova.tema)) {
            printf("[ERRO] Campo obrigatorio nao preenchido.\n");
        }
    } while (campoVazio(nova.tema));

    do {
        lerString("Data prevista (DD/MM/AAAA): ", nova.data_prevista, TAM_DATA);
        if (campoVazio(nova.data_prevista)) {
            printf("[ERRO] Campo obrigatorio nao preenchido.\n");
        }
    } while (campoVazio(nova.data_prevista));

    do {
        lerString("Publico-alvo (ex.: turmas do 6 ano): ", nova.publico_alvo, TAM_PUBLICO);
        if (campoVazio(nova.publico_alvo)) {
            printf("[ERRO] Campo obrigatorio nao preenchido.\n");
        }
    } while (campoVazio(nova.publico_alvo));

    do {
        lerString("Responsavel: ", nova.responsavel, TAM_RESPONSAVEL);
        if (campoVazio(nova.responsavel)) {
            printf("[ERRO] Campo obrigatorio nao preenchido.\n");
        }
    } while (campoVazio(nova.responsavel));

    /* RN02 — quantidade prevista não pode ser negativa */
    do {
        nova.qtd_prevista = lerInteiro("Quantidade prevista de participantes: ");
        if (nova.qtd_prevista < 0) {
            printf("[ERRO] Quantidade invalida. Informe um valor >= 0.\n");
        }
    } while (nova.qtd_prevista < 0);

    /* RN03 — toda ação nasce como "planejada"; qtd_efetiva só é usada depois */
    nova.qtd_efetiva = 0;
    nova.situacao = PLANEJADA;

    acoes[quantidade_de_acoes] = nova;
    quantidade_de_acoes++;

    printf("\n[OK] Acao cadastrada com sucesso! (codigo %d)\n", nova.codigo);
}

/* ---------------------------------------------------------------------
 * RF02 — Listagem de ações
 * --------------------------------------------------------------------- */
void exibirAcao(const AcaoPSE *a) {
    printf("Codigo......: %d\n", a->codigo);
    printf("Escola......: %s\n", a->escola);
    printf("Tema........: %s\n", a->tema);
    printf("Data prevista: %s\n", a->data_prevista);
    printf("Publico-alvo.: %s\n", a->publico_alvo);
    printf("Responsavel..: %s\n", a->responsavel);
    printf("Qtd prevista.: %d\n", a->qtd_prevista);
    if (a->situacao == REALIZADA) {
        printf("Qtd efetiva..: %d\n", a->qtd_efetiva);
    }
    printf("Situacao.....: %s\n", nomeSituacao(a->situacao));
    printf("-------------------------------------------------------------\n");
}

void listarAcoes(void) {
    int i;
    printf("\n=== LISTAGEM DE ACOES ===\n");

    if (quantidade_de_acoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("-------------------------------------------------------------\n");
    for (i = 0; i < quantidade_de_acoes; i++) {
        exibirAcao(&acoes[i]);
    }
    printf("Total de acoes cadastradas: %d\n", quantidade_de_acoes);
}

/* ---------------------------------------------------------------------
 * RF03 — Pesquisa por código, escola ou tema
 * --------------------------------------------------------------------- */

/* Compara ignorando maiusculas/minusculas (torna a busca por texto mais amigavel) */
static int contemSemCaseSensitive(const char *texto, const char *termo) {
    char textoLower[TAM_ESCOLA > TAM_TEMA ? TAM_ESCOLA : TAM_TEMA];
    char termoLower[256];
    size_t i;

    for (i = 0; texto[i] != '\0' && i < sizeof(textoLower) - 1; i++) {
        textoLower[i] = (char) tolower((unsigned char) texto[i]);
    }
    textoLower[i] = '\0';

    for (i = 0; termo[i] != '\0' && i < sizeof(termoLower) - 1; i++) {
        termoLower[i] = (char) tolower((unsigned char) termo[i]);
    }
    termoLower[i] = '\0';

    return strstr(textoLower, termoLower) != NULL;
}

void pesquisarAcoes(void) {
    int criterio;
    int codigoBusca;
    char termoBusca[TAM_ESCOLA];
    int encontrou = 0;
    int i;

    printf("\n=== PESQUISAR ACAO ===\n");

    if (quantidade_de_acoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("Pesquisar por: 1-Codigo  2-Escola  3-Tema\n");
    do {
        criterio = lerInteiro("Criterio: ");
        if (criterio < 1 || criterio > 3) {
            printf("[ERRO] Opcao invalida. Escolha 1, 2 ou 3.\n");
        }
    } while (criterio < 1 || criterio > 3);

    if (criterio == 1) {
        codigoBusca = lerInteiro("Codigo a pesquisar: ");
    } else {
        lerString("Termo a pesquisar: ", termoBusca, TAM_ESCOLA);
    }

    printf("\n--- Resultado da pesquisa ---\n");
    for (i = 0; i < quantidade_de_acoes; i++) {
        int corresponde = 0;

        if (criterio == 1 && acoes[i].codigo == codigoBusca) {
            corresponde = 1;
        } else if (criterio == 2 && contemSemCaseSensitive(acoes[i].escola, termoBusca)) {
            corresponde = 1;
        } else if (criterio == 3 && contemSemCaseSensitive(acoes[i].tema, termoBusca)) {
            corresponde = 1;
        }

        if (corresponde) {
            exibirAcao(&acoes[i]);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum registro encontrado.\n");
    }
}

/* ---------------------------------------------------------------------
 * RF04 / RN04 — Atualização de situação
 * --------------------------------------------------------------------- */
void atualizarSituacao(void) {
    int codigo;
    int indice;
    int novaSituacao;

    printf("\n=== ATUALIZAR SITUACAO ===\n");

    if (quantidade_de_acoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    codigo = lerInteiro("Codigo da acao: ");
    indice = localizarPorCodigo(codigo);

    if (indice == NAO_ENCONTRADO) {
        printf("[ERRO] Registro inexistente.\n");
        return;
    }

    printf("Acao encontrada:\n");
    exibirAcao(&acoes[indice]);

    printf("Nova situacao -> 1-Planejada  2-Realizada  3-Cancelada\n");
    do {
        novaSituacao = lerInteiro("Situacao: ");
        if (novaSituacao < 1 || novaSituacao > 3) {
            printf("[ERRO] Opcao invalida. Escolha 1, 2 ou 3.\n");
        }
    } while (novaSituacao < 1 || novaSituacao > 3);

    acoes[indice].situacao = novaSituacao;

    /* RN04 — quantidade efetiva só é solicitada quando a ação é realizada */
    if (novaSituacao == REALIZADA) {
        int qtdEfetiva;
        do {
            qtdEfetiva = lerInteiro("Quantidade efetiva de participantes: ");
            if (qtdEfetiva < 0) {
                printf("[ERRO] Quantidade invalida. Informe um valor >= 0.\n");
            }
        } while (qtdEfetiva < 0);
        acoes[indice].qtd_efetiva = qtdEfetiva;
    }

    printf("\n[OK] Situacao atualizada com sucesso!\n");
}

/* ---------------------------------------------------------------------
 * RF05 — Geração do resumo geral
 * --------------------------------------------------------------------- */
void gerarResumo(void) {
    int i;
    int totalPlanejadas = 0;
    int totalRealizadas = 0;
    int totalCanceladas = 0;
    int totalParticipantes = 0;
    int totalPrevisto = 0;
    double percentual;

    printf("\n=== RESUMO GERAL DO PROGRAMA ===\n");

    if (quantidade_de_acoes == 0) {
        printf("Nenhuma acao cadastrada ainda. Nao ha dados para resumir.\n");
        return;
    }

    for (i = 0; i < quantidade_de_acoes; i++) {
        totalPrevisto += acoes[i].qtd_prevista;

        switch (acoes[i].situacao) {
            case PLANEJADA:
                totalPlanejadas++;
                break;
            case REALIZADA:
                totalRealizadas++;
                totalParticipantes += acoes[i].qtd_efetiva;
                break;
            case CANCELADA:
                totalCanceladas++;
                break;
            default:
                break;
        }
    }

    /* Evita divisao por zero quando nenhuma acao tem quantidade prevista */
    if (totalPrevisto > 0) {
        percentual = ((double) totalParticipantes / (double) totalPrevisto) * 100.0;
    } else {
        percentual = 0.0;
    }

    printf("-------------------------------------------------------------\n");
    printf("Total de acoes cadastradas ..: %d\n", quantidade_de_acoes);
    printf("  Planejadas .................: %d\n", totalPlanejadas);
    printf("  Realizadas .................: %d\n", totalRealizadas);
    printf("  Canceladas .................: %d\n", totalCanceladas);
    printf("Total previsto de participantes: %d\n", totalPrevisto);
    printf("Total efetivo de participantes .: %d\n", totalParticipantes);
    printf("Percentual de participacao ......: %.2f%%\n", percentual);
    printf("-------------------------------------------------------------\n");
}
