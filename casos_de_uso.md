# Descrição dos Casos de Uso — PSE em Ação

**Ator:** Operador do Sistema (coordenador(a) pedagógico(a), profissional da
Atenção Primária à Saúde ou gestor(a) municipal do PSE — perfil único, sem
diferenciação de permissões).

---

## UC01 — Cadastrar Ação

**Objetivo:** Registrar uma nova ação do PSE no sistema.
**Ator:** Operador do Sistema.
**Pré-condições:** O número de ações cadastradas é menor que `MAX_ACOES` (100).

**Fluxo principal:**
1. O operador seleciona a opção "1 - Cadastrar ação" no menu.
2. O sistema solicita o código da ação.
3. O operador informa o código.
4. O sistema solicita escola, tema, data prevista, público-alvo, responsável
   e quantidade prevista de participantes.
5. O operador informa os dados solicitados.
6. O sistema registra a ação com situação inicial "planejada" e exibe a
   mensagem "Ação cadastrada com sucesso!".

**Fluxos alternativos:**
- **FA01 — Limite de armazenamento atingido:** se o vetor já contém 100
  ações, o sistema exibe "Limite máximo de ações atingido" e retorna ao
  menu sem solicitar dados (passo 2 não ocorre).
- **FA02 — Código duplicado:** se o código informado no passo 3 já existe,
  o sistema exibe "Código já cadastrado" e solicita novamente o código
  (RN01).
- **FA03 — Campo obrigatório vazio:** se qualquer campo textual do passo 5
  for deixado em branco, o sistema exibe "Campo obrigatório não
  preenchido" e solicita novamente aquele campo.
- **FA04 — Quantidade negativa:** se a quantidade prevista informada for
  menor que zero, o sistema exibe "Quantidade inválida" e solicita
  novamente o valor (RN02).

**Pós-condições:** A ação é armazenada no vetor em memória com situação
"planejada" (RN03) e o contador de ações é incrementado.

---

## UC02 — Listar Ações

**Objetivo:** Exibir todas as ações cadastradas no sistema.
**Ator:** Operador do Sistema.
**Pré-condições:** Nenhuma.

**Fluxo principal:**
1. O operador seleciona a opção "2 - Listar ações".
2. O sistema percorre o vetor de ações e exibe, para cada registro, código,
   escola, tema, data prevista, público-alvo, responsável, quantidade
   prevista e situação.
3. O sistema exibe o total de ações cadastradas.

**Fluxo alternativo:**
- **FA01 — Nenhuma ação cadastrada:** se o vetor estiver vazio, o sistema
  exibe "Nenhuma ação cadastrada" e retorna ao menu.

**Pós-condições:** Nenhuma alteração de dados; apenas leitura e exibição.

---

## UC03 — Pesquisar Ação

**Objetivo:** Localizar rapidamente uma ou mais ações cadastradas.
**Ator:** Operador do Sistema.
**Pré-condições:** Existe ao menos uma ação cadastrada.

**Fluxo principal:**
1. O operador seleciona a opção "3 - Pesquisar ação".
2. O sistema exibe os critérios disponíveis: 1-Código, 2-Escola, 3-Tema.
3. O operador escolhe o critério e informa o termo de busca.
4. O sistema percorre o vetor de ações, compara cada registro com o termo
   informado (busca exata para código; busca por ocorrência de texto,
   sem diferenciar maiúsculas/minúsculas, para escola e tema) e exibe os
   registros correspondentes.

**Fluxos alternativos:**
- **FA01 — Vetor vazio:** se não houver ações cadastradas, o sistema exibe
  "Nenhuma ação cadastrada" e retorna ao menu sem solicitar critério.
- **FA02 — Critério inválido:** se o número do critério não estiver entre
  1 e 3, o sistema exibe "Opção inválida" e solicita novamente.
- **FA03 — Nenhum resultado:** se nenhuma ação corresponder ao termo
  buscado, o sistema exibe "Nenhum registro encontrado".

**Pós-condições:** Nenhuma alteração de dados; apenas leitura e exibição.

---

## UC04 — Atualizar Situação

**Objetivo:** Alterar a situação de uma ação cadastrada (planejada,
realizada ou cancelada) e, quando aplicável, registrar a quantidade
efetiva de participantes.
**Ator:** Operador do Sistema.
**Pré-condições:** Existe ao menos uma ação cadastrada.

**Fluxo principal:**
1. O operador seleciona a opção "4 - Atualizar situação".
2. O sistema solicita o código da ação.
3. O operador informa o código.
4. O sistema localiza a ação e exibe seus dados atuais.
5. O sistema solicita a nova situação (1-Planejada, 2-Realizada,
   3-Cancelada).
6. O operador informa a nova situação.
7. O sistema atualiza o campo `situacao` da ação.
8. Caso a nova situação seja "realizada", o sistema solicita a quantidade
   efetiva de participantes (RN04) e a armazena.
9. O sistema exibe "Situação atualizada com sucesso!".

**Fluxos alternativos:**
- **FA01 — Vetor vazio:** se não houver ações cadastradas, o sistema exibe
  "Nenhuma ação cadastrada" e retorna ao menu.
- **FA02 — Código inexistente:** se o código informado no passo 3 não
  corresponder a nenhuma ação, o sistema exibe "Registro inexistente" e
  retorna ao menu.
- **FA03 — Situação inválida:** se o valor informado no passo 6 não
  estiver entre 1 e 3, o sistema exibe "Opção inválida" e solicita
  novamente.
- **FA04 — Quantidade efetiva negativa:** se o valor informado no passo 8
  for negativo, o sistema exibe "Quantidade inválida" e solicita
  novamente.

**Pós-condições:** A ação correspondente ao código informado passa a ter a
nova situação registrada; se a situação for "realizada", o campo
`qtd_efetiva` é atualizado.

---

## UC05 — Gerar Resumo Geral

**Objetivo:** Apresentar uma visão consolidada do programa: quantidade de
ações por situação, total de participantes atendidos e percentual de
participação em relação ao previsto.
**Ator:** Operador do Sistema.
**Pré-condições:** Nenhuma.

**Fluxo principal:**
1. O operador seleciona a opção "5 - Gerar resumo".
2. O sistema percorre o vetor de ações, somando o total previsto de
   participantes e contabilizando quantas ações estão planejadas,
   realizadas e canceladas, além do total efetivo de participantes das
   ações realizadas.
3. O sistema calcula o percentual de participação
   (`total_participantes / total_previsto * 100`).
4. O sistema exibe os totais por situação, o total previsto, o total
   efetivo e o percentual calculado.

**Fluxo alternativo:**
- **FA01 — Nenhuma ação cadastrada:** se o vetor estiver vazio, o sistema
  exibe "Nenhuma ação cadastrada ainda" e não calcula o resumo.
- **FA02 — Total previsto igual a zero:** se a soma das quantidades
  previstas for zero (nenhuma ação com participantes previstos), o
  sistema define o percentual como 0%, evitando divisão por zero.

**Pós-condições:** Nenhuma alteração de dados; apenas leitura, cálculo e
exibição.

---

## UC06 — Encerrar Sistema

**Objetivo:** Finalizar a execução do programa.
**Ator:** Operador do Sistema.
**Pré-condições:** Nenhuma.

**Fluxo principal:**
1. O operador seleciona a opção "0 - Encerrar".
2. O sistema exibe "Encerrando o sistema. Até a próxima!" e finaliza a
   execução.

**Fluxo alternativo:**
- **FA01 — Opção de menu inválida:** em qualquer caso de uso, se o
  operador digitar uma opção fora do intervalo 0–5 (ou um valor não
  numérico), o sistema exibe "Opção inválida" e reexibe o menu principal
  (RN07), sem encerrar o programa.

**Pós-condições:** O programa é finalizado; como os dados são mantidos
apenas em memória (RN06/risco R02), todas as ações cadastradas na sessão
são perdidas ao encerrar — limitação registrada explicitamente no manual
do usuário e nas considerações finais.
