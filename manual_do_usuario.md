# Manual do Usuário — PSE em Ação

## 1. Objetivo do sistema

O sistema "PSE em Ação" tem como objetivo auxiliar equipes escolares e de
saúde a planejar, registrar e acompanhar, de forma organizada, as ações
coletivas do Programa Saúde na Escola (PSE), **sem armazenar dados
individuais dos estudantes atendidos**. Trata-se de uma aplicação de
terminal, escrita em linguagem C, com finalidade acadêmica e introdutória.

## 2. Instruções de compilação e execução

O código-fonte é compilado com qualquer compilador C padrão (ex.: GCC),
sem dependências externas.

**Compilação:**
```bash
gcc pse_em_acao.c -o pse_em_acao -Wall
```

**Execução:**
```bash
./pse_em_acao          # Linux / macOS
pse_em_acao.exe        # Windows
```

Ao iniciar, o sistema exibe uma mensagem de boas-vindas seguida do menu
principal.

## 3. Opções do menu principal

```
1 - Cadastrar ação
2 - Listar ações
3 - Pesquisar ação
4 - Atualizar situação
5 - Gerar resumo
0 - Encerrar
```

- **1 – Cadastrar ação:** registra uma nova ação do PSE, solicitando
  código, escola, tema, data prevista, público-alvo, responsável e
  quantidade prevista de participantes. Toda ação nasce com situação
  "planejada".
- **2 – Listar ações:** exibe todas as ações cadastradas até o momento,
  com código, escola, tema, data, público-alvo, responsável, quantidade
  prevista e situação atual.
- **3 – Pesquisar ação:** localiza ações por código (busca exata), por
  escola ou por tema (busca por trecho de texto, sem diferenciar
  maiúsculas/minúsculas), exibindo todos os registros correspondentes.
- **4 – Atualizar situação:** altera a situação de uma ação cadastrada
  para planejada, realizada ou cancelada. Quando a situação é alterada
  para "realizada", o sistema solicita a quantidade efetiva de
  participantes.
- **5 – Gerar resumo geral:** exibe a quantidade de ações planejadas,
  realizadas e canceladas, o total de participantes efetivamente
  atendidos e o percentual de participação em relação ao total previsto.
- **0 – Encerrar:** finaliza a execução do programa. **Atenção:** como os
  dados ficam apenas em memória, todos os cadastros são perdidos ao
  encerrar.

## 4. Mensagens de validação

O sistema não encerra abruptamente diante de entradas inválidas. Em vez
disso, exibe uma mensagem explicativa e solicita a informação novamente:

| Situação | Mensagem exibida |
|---|---|
| Código já cadastrado | `[ERRO] Codigo ja cadastrado. Informe outro codigo.` |
| Campo obrigatório vazio | `[ERRO] Campo obrigatorio nao preenchido.` |
| Quantidade negativa | `[ERRO] Quantidade invalida. Informe um valor >= 0.` |
| Entrada não numérica onde se espera número | `[ERRO] Entrada invalida. Digite um numero inteiro.` |
| Opção de menu fora do intervalo 0–5 | `[ERRO] Opcao invalida. Escolha um numero entre 0 e 5.` |
| Código inexistente (ao atualizar situação) | `[ERRO] Registro inexistente.` |
| Nenhuma ação cadastrada (listar/pesquisar/atualizar/resumir) | `Nenhuma acao cadastrada.` |
| Limite de 100 ações atingido (ao cadastrar) | `[ERRO] Limite maximo de acoes atingido (100).` |

## 5. Exemplo de uso passo a passo

1. **Cadastrar uma ação:** no menu, digite `1` e informe:
   - Código: `1`
   - Escola: `Escola Municipal Alvorada`
   - Tema: `Alimentação Saudável`
   - Data prevista: `10/03/2026`
   - Público-alvo: `Turmas do 6º ano`
   - Responsável: `Maria Silva`
   - Quantidade prevista: `30`

   O sistema exibirá: `[OK] Acao cadastrada com sucesso! (codigo 1)`

2. **Listar as ações:** digite `2` para conferir o cadastro. A ação
   aparecerá com situação "Planejada".

3. **Atualizar a situação após a realização da ação:** digite `4`,
   informe o código `1`, escolha a opção `2` (Realizada) e informe a
   quantidade efetiva de participantes, por exemplo `28`.

4. **Gerar o resumo geral:** digite `5` para verificar o percentual de
   participação alcançado em relação ao previsto (no exemplo,
   28/30 × 100 = 93,33%).

5. **Pesquisar uma ação:** digite `3`, escolha o critério `2` (Escola) e
   informe `Alvorada` para localizar a ação cadastrada.

6. **Encerrar o sistema:** digite `0`.

## 6. Capturas de tela

> [Espaço reservado para as capturas de tela do sistema em execução,
> a serem inseridas no documento final da 2ª entrega, demonstrando as
> seis funcionalidades descritas acima.]

## 7. Considerações finais

### Resultados obtidos
O sistema implementa, de forma funcional e validada, as seis
funcionalidades mínimas exigidas (cadastro, listagem, pesquisa,
atualização de situação, resumo geral e validação de entradas), conforme
descrito nos requisitos funcionais RF01–RF06 da 1ª entrega. Os 14 casos
de teste planejados foram executados manualmente e todos foram aprovados
(ver `resultados_testes.md`), cobrindo tanto os fluxos principais quanto
os fluxos de exceção previstos nos fluxogramas e pseudocódigos.

### Limitações
A principal limitação do sistema, já prevista na matriz de riscos da 1ª
entrega (risco R02), é o armazenamento exclusivamente em memória: todos
os dados cadastrados são perdidos ao encerrar o programa, não havendo
persistência em arquivo ou banco de dados nesta versão. Além disso, o
sistema trata apenas um perfil de usuário, sem controle de acesso, e a
busca textual (por escola/tema) localiza qualquer trecho correspondente,
podendo retornar mais resultados do que o esperado em bases com nomes
semelhantes.

### Aprendizados
A elaboração de fluxogramas e pseudocódigos antes da implementação (1ª
entrega) facilitou significativamente a etapa de codificação, reduzindo
retrabalho e tornando mais clara a divisão de tarefas entre os
integrantes do grupo. A experiência também reforçou a importância de
validar continuamente as entradas do usuário para atender ao requisito
de confiabilidade (RNF03), evitando o encerramento abrupto do programa.

### Possibilidades de melhoria
Como evolução natural do projeto — fora do escopo desta atividade —
destacam-se: (1) persistência dos dados em arquivo de texto, permitindo
retomar o cadastro entre execuções; (2) ordenação e filtros adicionais na
listagem; (3) ampliação dinâmica da capacidade de armazenamento, hoje
limitada pela constante `MAX_ACOES`; e (4) controle de perfis de acesso,
caso o sistema venha a ser utilizado por múltiplas equipes
simultaneamente.
