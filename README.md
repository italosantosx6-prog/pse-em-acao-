# PSE em Ação

Sistema de terminal, em linguagem C, para planejamento e acompanhamento de
ações do **Programa Saúde na Escola (PSE)**.

> Atividade Extensionista Prática (AEP) — UNICESUMAR
> Engenharia de Software / Análise e Desenvolvimento de Sistemas
> Integrantes: Luiz Augusto da Rocha Bedendo (RA 26007445-2) e
> Italo Fernandes Santos (RA 26003073-2)

🎥 **Vídeo de apresentação:** https://youtu.be/hbg_6XFngG4

## Sobre o projeto

O sistema permite cadastrar, listar, pesquisar e acompanhar ações
**coletivas** do PSE (ex.: campanhas de alimentação saudável, atividade
física, saúde bucal), sem armazenar qualquer dado individual de
estudantes. Os dados são mantidos apenas em memória durante a execução do
programa (não há banco de dados, arquivo em disco ou interface gráfica).

## Funcionalidades (escopo mínimo obrigatório)

| Opção | Funcionalidade |
|-------|-----------------------------------------------------------|
| 1 | Cadastrar ação |
| 2 | Listar ações |
| 3 | Pesquisar ação (por código, escola ou tema) |
| 4 | Atualizar situação (planejada / realizada / cancelada) |
| 5 | Gerar resumo geral do programa |
| 0 | Encerrar o sistema |

## Compilação

Requer apenas um compilador C padrão (GCC ou equivalente). Não há
dependências externas.

```bash
gcc pse_em_acao.c -o pse_em_acao -Wall
```

## Execução

```bash
./pse_em_acao        # Linux / macOS
pse_em_acao.exe      # Windows (após compilar com MinGW, por exemplo)
```

## Estrutura de dados

```c
#define MAX_ACOES 100

typedef struct {
    int  codigo;
    char escola[50];
    char tema[50];
    char data_prevista[11];
    char publico_alvo[50];
    char responsavel[50];
    int  qtd_prevista;
    int  qtd_efetiva;
    int  situacao; /* 1-planejada 2-realizada 3-cancelada */
} AcaoPSE;
```

## Validações implementadas

- Código de ação único (não permite duplicados).
- Quantidade prevista/efetiva de participantes não pode ser negativa.
- Campos obrigatórios (escola, tema, data, público-alvo, responsável) não
  podem ficar vazios.
- Limite máximo de armazenamento (100 ações em memória).
- Opções de menu fora do intervalo 0–5 são rejeitadas, sem encerrar o
  programa.
- Atualização de situação para código inexistente é tratada e informada
  ao usuário.

## Limitações conhecidas

- Os dados são armazenados **apenas em memória**: ao encerrar o programa,
  todos os cadastros são perdidos (não há persistência em arquivo ou
  banco de dados nesta versão).
- O sistema não armazena, em nenhuma hipótese, dados individuais de
  estudantes (nome, CPF, diagnóstico etc.), por definição de escopo e de
  ética do projeto.

## Documentação adicional

- `casos_de_uso.md` — descrição detalhada dos 6 casos de uso do sistema.
- `diagrama_casos_uso.svg` — diagrama UML de casos de uso.
- `resultados_testes.md` — registro de execução dos 14 casos de teste
  planejados na 1ª entrega.
- `manual_do_usuario.md` — manual do usuário final, com instruções de uso
  e exemplos.

## Licença / finalidade

Projeto com finalidade estritamente acadêmica e introdutória. Todos os
dados utilizados para demonstração são fictícios.
