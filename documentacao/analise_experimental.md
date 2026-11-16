ANÁLISE EXPERIMENTAL

1. Introdução
Após a implementação e os testes de correção da tabela hash, foi realizada uma análise experimental para avaliar o desempenho do sistema de controle de estoque.
O objetivo foi observar o comportamento da estrutura conforme a quantidade de produtos cadastrados aumentava, analisando os tempos de execução, as colisões, as sondagens e o fator de carga da tabela.





2. Metodologia
Foram realizados experimentos com três quantidades diferentes de produtos: 100, 1.000 e 10.000 registros.
Cada cenário foi executado cinco vezes, e os resultados apresentados correspondem à média das cinco repetições válidas.
Durante os experimentos, foram avaliadas as seguintes operações e métricas:

- Inserção automática dos produtos na tabela.
- Busca de produtos existentes.
- Busca de produtos inexistentes.
- Quantidade de colisões durante as inserções.
- Quantidade de sondagens realizadas durante as inserções e buscas.
- Capacidade final da tabela.
- Fator de carga após a conclusão dos cadastros.

Os produtos foram cadastrados automaticamente, utilizando códigos numéricos sequenciais. Para as buscas bem-sucedidas, foram consultados todos os produtos cadastrados. Para as buscas malsucedidas, foram utilizados códigos que não estavam presentes na tabela.
O tempo de inserção considera também o trabalho realizado durante o redimensionamento da tabela e o rehashing dos produtos.
As sondagens de inserção incluem as posições examinadas tanto durante os novos cadastros quanto durante o rehashing.
A contagem de colisões considera quando a posição inicialmente calculada pela função hash já está ocupada por outro produto no momento de uma nova inserção.
Os tempos de busca representam a média do tempo necessário para executar o conjunto completo de buscas de cada cenário, considerando as cinco repetições.




3. Resultados dos experimentos


3.1. Cenário com 100 produtos

Quantidade de produtos: 100

Repetições válidas: 5

Tempo médio de inserção: 0,000032800 segundos

Tempo médio do conjunto de buscas bem-sucedidas: 0,000004600 segundos

Tempo médio do conjunto de buscas malsucedidas: 0,000007200 segundos

Média de colisões: 13

Média de sondagens na inserção: 250

Média de sondagens nas buscas bem-sucedidas: 100

Média de sondagens nas buscas malsucedidas: 164

Capacidade final da tabela: 200 posições

Fator de carga final: 0,50




3.2. Cenário com 1.000 produtos

Quantidade de produtos: 1.000

Repetições válidas: 5

Tempo médio de inserção: 0,000481600 segundos

Tempo médio do conjunto de buscas bem-sucedidas: 0,000045600 segundos

Tempo médio do conjunto de buscas malsucedidas: 0,000063800 segundos

Média de colisões: 224

Média de sondagens na inserção: 2.608

Média de sondagens nas buscas bem-sucedidas: 1.240

Média de sondagens nas buscas malsucedidas: 1.697

Capacidade final da tabela: 1.600 posições

Fator de carga final: 0,62




3.3. Cenário com 10.000 produtos

Quantidade de produtos: 10.000

Repetições válidas: 5

Tempo médio de inserção: 0,003015000 segundos

Tempo médio do conjunto de buscas bem-sucedidas: 0,000202400 segundos

Tempo médio do conjunto de buscas malsucedidas: 0,000239800 segundos

Média de colisões: 2.367

Média de sondagens na inserção: 65.190

Média de sondagens nas buscas bem-sucedidas: 27.536

Média de sondagens nas buscas malsucedidas: 30.787

Capacidade final da tabela: 25.600 posições

Fator de carga final: 0,39




4. Comparação dos resultados

A tabela abaixo reúne os principais resultados dos três cenários para facilitar a comparação.



Métrica                           |   100 produtos    |   1.000 produtos    |   10.000 produtos

Tempo de inserção                 |   0,000032800 s   |   0,000481600 s     |   0,003015000 s

Busca bem-sucedida                |   0,000004600 s   |   0,000045600 s     |   0,000202400 s

Busca malsucedida                 |   0,000007200 s   |   0,000063800 s     |   0,000239800 s

Colisões                          |   13              |   224               |   2.367

Sondagens na inserção             |   250             |   2.608             |   65.190

Sondagens na busca bem-sucedida   |   100             |   1.240             |   27.536

Sondagens na busca malsucedida    |   164             |   1.697             |   30.787

Capacidade final                  |   200             |   1.600             |   25.600

Fator de carga                    |   0,50            |   0,62              |   0,39



5. Análise dos resultados
Os resultados demonstram que o sistema conseguiu realizar as operações de inserção e busca nos três cenários testados, mantendo o funcionamento correto mesmo com o aumento da quantidade de produtos.
Como esperado, o tempo de inserção aumentou conforme o número de registros cresceu. Isso também ocorreu com a quantidade de colisões e sondagens, já que um número maior de produtos aumenta as possibilidades de ocupação das posições inicialmente calculadas pela função hash.
As buscas malsucedidas apresentaram mais sondagens do que as buscas bem-sucedidas nos três cenários. Isso acontece porque, ao procurar um produto inexistente, a tabela precisa continuar examinando posições até encontrar uma posição vazia ou atingir o limite de tentativas.
Também foi possível observar o funcionamento do redimensionamento dinâmico. A capacidade inicial da tabela era de 50 posições e foi duplicada sempre que o fator de carga ultrapassou 0,75.
Com isso, a tabela terminou os experimentos com 200, 1.600 e 25.600 posições, respectivamente.
O fator de carga final permaneceu abaixo do limite estabelecido nos três cenários, demonstrando que o mecanismo de crescimento da tabela funcionou conforme o planejado.

6. Conclusão
A análise experimental permitiu observar o comportamento da tabela hash em diferentes quantidades de registros.
Os testes demonstraram que a implementação conseguiu realizar inserções e buscas com tempos reduzidos, além de administrar as colisões por meio da sondagem linear.
O redimensionamento dinâmico também funcionou corretamente, aumentando a capacidade da tabela conforme a quantidade de produtos crescia e realizando o rehashing dos registros existentes.
Dessa forma, os resultados indicam que a implementação atende ao objetivo de controlar os produtos por meio de uma tabela hash com hashing universal, sondagem linear e alocação dinâmica de memória.
