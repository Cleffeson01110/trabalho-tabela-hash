E1.2 — Vetor dinâmico com crescimento e rehashing

A tabela utiliza um vetor alocado dinamicamente, com capacidade inicial de 50 posições.

Quando uma nova inserção ultrapassaria o fator de carga de 0,75, a capacidade da tabela é duplicada. Uma nova área de memória é alocada e os produtos existentes são inseridos novamente, utilizando a função hash e a nova capacidade.

Esse processo é chamado de rehashing e permite que os registros sejam reorganizados de acordo com o novo tamanho da tabela.




H7 — Função hash universal

A função hash utilizada segue o método de hashing universal, com a seguinte expressão:

h(k) = ((a × k + b) mod p) mod m

Onde:

- k representa o código do produto.
- a e b são parâmetros escolhidos aleatoriamente no início da execução.
- p é um número primo definido como 1.000.003.
- m representa a capacidade atual da tabela.

O parâmetro a é escolhido entre 1 e p - 1, enquanto b é escolhido entre 0 e p - 1.

Os parâmetros permanecem os mesmos durante toda a execução do programa, mas podem mudar quando o programa é iniciado novamente.




C2 — Sondagem linear

Para tratar as colisões, foi implementada a sondagem linear.

Quando a posição inicial calculada pela função hash já está ocupada, o programa verifica as posições seguintes até encontrar uma posição disponível.

A posição examinada é calculada pela expressão:

(h(k) + i) mod m

Onde i representa o número da tentativa de sondagem.

O método permite que diferentes produtos sejam armazenados na tabela mesmo quando suas chaves geram o mesmo índice inicial.





A2 — Controle de estoque

A aplicação permite realizar as seguintes operações:

- Cadastrar produtos, verificando se o código já está registrado.
- Buscar produtos pelo código.
- Atualizar nome, quantidade e preço sem modificar o código.
- Remover produtos da tabela.
- Listar os produtos cadastrados.

Para controlar as posições da tabela, são utilizados três estados:

- 0: posição vazia.
- 1: posição ocupada.
- 2: posição removida.

Quando um produto é removido, sua posição recebe o estado 2. Essa marcação permite que as buscas continuem funcionando corretamente mesmo quando existem colisões, evitando interromper a sondagem antes de encontrar outros produtos.
