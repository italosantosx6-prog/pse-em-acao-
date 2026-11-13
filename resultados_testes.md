# Registro de Execução do Plano de Testes — PSE em Ação

Compilação utilizada: `gcc -Wall -Wextra -std=c99 pse_em_acao.c -o pse_em_acao`
Resultado da compilação: **sem erros e sem warnings**.

| ID | Caso de teste | Resultado observado | Status |
|----|----------------------------------------|---------------------------------------------------------------------|--------|
| TC01 | Cadastro com todos os dados válidos | Ação armazenada; exibida mensagem "Ação cadastrada com sucesso!" | ✅ Aprovado |
| TC02 | Cadastro com código já existente | Mensagem "Código já cadastrado"; sistema solicitou novo código | ✅ Aprovado |
| TC03 | Cadastro com quantidade prevista negativa (-5) | Mensagem "Quantidade inválida"; sistema solicitou novo valor | ✅ Aprovado |
| TC04 | Cadastro com campo obrigatório vazio (escola) | Mensagem "Campo obrigatório não preenchido"; sistema solicitou novamente | ✅ Aprovado |
| TC05 | Listagem com o vetor vazio | Mensagem "Nenhuma ação cadastrada" | ✅ Aprovado |
| TC06 | Listagem com registros cadastrados (3 ações) | Exibição organizada de todas as ações, com código, escola, tema, data e situação | ✅ Aprovado |
| TC07 | Pesquisa com resultado encontrado (por escola) | Exibição da ação correspondente à escola pesquisada | ✅ Aprovado |
| TC08 | Pesquisa sem resultado encontrado | Mensagem "Nenhum registro encontrado" | ✅ Aprovado |
| TC09 | Atualização de situação para "realizada" | Situação e quantidade efetiva atualizadas; mensagem de sucesso | ✅ Aprovado |
| TC10 | Atualização de situação para "cancelada" | Situação atualizada para cancelada; mensagem de sucesso | ✅ Aprovado |
| TC11 | Atualização com código inexistente | Mensagem "Registro inexistente" | ✅ Aprovado |
| TC12 | Geração de resumo com ações mistas (1 planejada, 1 realizada, 1 cancelada) | Totais corretos por situação (1/1/1) e percentual calculado corretamente (13,33%), sem divisão por zero | ✅ Aprovado |
| TC13 | Seleção de opção inexistente no menu (9) | Mensagem "Opção inválida"; menu reexibido | ✅ Aprovado |
| TC14 | Cadastro além do limite de armazenamento (101ª ação, MAX_ACOES=100) | Mensagem "Limite máximo de ações atingido"; cadastro não realizado | ✅ Aprovado |

**Resultado geral:** 14 de 14 casos de teste aprovados (100%).

## Ajuste em relação ao planejamento da 1ª entrega

Durante a implementação, foi adicionada uma validação extra, não detalhada no
pseudocódigo original: as operações de **listar**, **pesquisar**, **atualizar
situação** e **gerar resumo** verificam se `quantidade_de_acoes == 0` antes de
prosseguir, exibindo "Nenhuma ação cadastrada" e retornando ao menu. Essa
mudança foi incorporada porque, sem ela, a pesquisa e a atualização
tentariam ler um código mesmo sem nenhum registro em memória, gerando uma
experiência confusa para o usuário. A regra de negócio RN07 (opção de menu
fora do intervalo 0–5) e as demais regras (RN01 a RN06) permanecem
implementadas exatamente como especificado na 1ª entrega.
