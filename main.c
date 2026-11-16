#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>






typedef struct {
    int codigo;
    char nome[100];
    int quantidade;
    float preco;
    int estado;
}produto;



int funcao_hash(int codigo, int a, int b, int p, int m);

int sondagem_linear(int indice_inicial, int tentativa, int capacidade);




int aumentar_capacidade(produto **produtos, int *capacidade,
                        int a, int b, int p) {

    int novaCapacidade = *capacidade * 2;

    produto *novaTabela = malloc(novaCapacidade * sizeof(produto));

    if (novaTabela == NULL) {
        printf("Erro ao aumentar capacidade!\n");
        return 0;
    }

    for (int i = 0; i < novaCapacidade; i++) {
        novaTabela[i].estado = 0;
    }

    for (int i = 0; i < *capacidade; i++) {

        if ((*produtos)[i].estado == 1) {

            int indice_inicial = funcao_hash(
                (*produtos)[i].codigo, a, b, p, novaCapacidade
            );

            int tentativa = 0;
            int indice;

            while (tentativa < novaCapacidade) {

                indice = sondagem_linear(
                    indice_inicial, tentativa, novaCapacidade
                );


            if (novaTabela[indice].estado == 0) {
                break;
            }

            tentativa++;
            }

            if (tentativa == novaCapacidade) {
                free(novaTabela);
                printf("Erro ao realocar os produtos!\n");
                return 0;
            }

            novaTabela[indice] = (*produtos)[i];
        }
    }

    free(*produtos);

    *produtos = novaTabela;
    *capacidade = novaCapacidade;


    return 1;
}



int funcao_hash(int codigo, int a, int b, int p, int m){
    long long resultado;

    resultado = ((long long)a * codigo +b) % p;
    resultado = resultado % m;

    return (int)resultado;
}



int sondagem_linear(int indice_inicial, int tentativa, int capacidade) {
    return (indice_inicial + tentativa) % capacidade;
}



void adicionar_produto(produto **produtos, int *quantidade, int *capacidade, int a, int b, int p){
    produto novo;

    printf ("\nDigite o codigo do produto: ");
    scanf("%d", &novo.codigo);

    if(novo.codigo < 0 || novo.codigo > 999999) {
        printf ("codigo invalido! use valores entre 0 e 999999.\n");
        return;
    }

    printf("Digite o nome do produto: ");
    scanf (" %99[^\n]", novo.nome);

    printf ("Digite a quantidade em estoque: ");
    scanf ("%d", &novo.quantidade);

    printf ("Digite o preco do produto: ");
    scanf ("%f", &novo.preco);

    float fator_carga = (float)(*quantidade + 1) / *capacidade;

    if (fator_carga > 0.75) {

        if (!aumentar_capacidade(produtos, capacidade, a, b, p)) {
            return;
        }
    }

    int indice_inicial = funcao_hash(novo.codigo, a, b, p, *capacidade);


    int indice;
    int tentativa = 0;
    int primeira_removida = -1;

    while (tentativa < *capacidade) {

    indice = sondagem_linear(indice_inicial, tentativa, *capacidade);



    if ((*produtos)[indice].estado == 1) {
            if ((*produtos)[indice].codigo == novo.codigo) {
                printf("Ja existe um produto com esse codigo!\n");
                return;
            }

        }
        else if ((*produtos)[indice].estado == 2) {

            if (primeira_removida == -1) {
                primeira_removida = indice;
            }

        }
        else {

            if (primeira_removida != -1) {
                indice = primeira_removida;
            }

            break;
        }

        tentativa++;
    }

    if (tentativa == *capacidade) {

        if (primeira_removida != -1) {
            indice = primeira_removida;
        }
        else {
            printf("Tabela cheia!\n");
            return;
        }
    }

    (*produtos)[indice] = novo;
    (*produtos)[indice].estado = 1;

    (*quantidade)++;

    printf("Produto cadastrado com sucesso!\n");
}



void buscar_produto(produto *produtos, int capacidade, int a, int b, int p) {

    int codigo_busca;

    printf("\nDigite o codigo do produto que deseja buscar: ");
    scanf("%d", &codigo_busca);

    int indice_inicial = funcao_hash(codigo_busca, a, b, p, capacidade);

    int indice;
    int tentativa = 0;

    while (tentativa < capacidade) {

    indice = sondagem_linear(indice_inicial, tentativa, capacidade);



    if (produtos[indice].estado == 0) {
            break;
        }

        if (produtos[indice].estado == 1 && produtos[indice].codigo == codigo_busca) {

            printf("\nProduto encontrado!\n");
            printf("Codigo: %d\n", produtos[indice].codigo);
            printf("Nome: %s\n", produtos[indice].nome);
            printf("Quantidade: %d\n", produtos[indice].quantidade);
            printf("Preco: R$ %.2f\n", produtos[indice].preco);

            return;
        }

        tentativa++;
    }

    printf("\nProduto nao encontrado!\n");
}



void atualizar_produto(produto *produtos, int capacidade, int a, int b, int p) {

    int codigo_busca;

    printf("\nDigite o codigo do produto que deseja atualizar: ");
    scanf("%d", &codigo_busca);

    int indice_inicial = funcao_hash(codigo_busca, a, b, p, capacidade);

    int indice;
    int tentativa = 0;

    while (tentativa < capacidade) {

        indice = sondagem_linear(indice_inicial, tentativa, capacidade);

        if (produtos[indice].estado == 0) {
            break;
        }

        if (produtos[indice].estado == 1 && produtos[indice].codigo == codigo_busca) {

            printf("\nProduto encontrado! Digite os novos dados.\n");

            printf("Novo nome: ");
            scanf(" %99[^\n]", produtos[indice].nome);

            printf("Nova quantidade: ");
            scanf("%d", &produtos[indice].quantidade);

            printf("Novo preco: ");
            scanf("%f", &produtos[indice].preco);

            printf("\nProduto atualizado com sucesso!\n");

            return;
        }

        tentativa++;
    }

    printf("\nProduto nao encontrado!\n");
}



void remover_produto(produto *produtos, int *quantidade,
                     int capacidade, int a, int b, int p) {

    int codigo_busca;

    printf("\nDigite o codigo do produto que deseja remover: ");
    scanf("%d", &codigo_busca);

    int indice_inicial = funcao_hash(codigo_busca, a, b, p, capacidade);

    int indice;
    int tentativa = 0;

    while (tentativa < capacidade) {

        indice = sondagem_linear(indice_inicial, tentativa, capacidade);

        if (produtos[indice].estado == 0) {
            break;
        }

        if (produtos[indice].estado == 1 &&
            produtos[indice].codigo == codigo_busca) {

            produtos[indice].estado = 2;

            (*quantidade)--;

            printf("\nProduto removido com sucesso!\n");

            return;
        }

        tentativa++;
    }

    printf("\nProduto nao encontrado!\n");
}



void listar_produtos(produto *produtos, int capacidade) {

    int encontrou = 0;

    printf("\n========== PRODUTOS CADASTRADOS ==========\n");

    for (int i = 0; i < capacidade; i++) {

        if (produtos[i].estado == 1) {

            printf("\nCodigo: %d\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Preco: R$ %.2f\n", produtos[i].preco);

            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("\nNenhum produto cadastrado!\n");
    }
}




int main() {

    produto *produtos;

    int capacidade = 50;
    int quantidade = 0;

    int multiplicador_a;
    int incremento_b;
    int primo_p = 1000003;

    int opcao;

    srand(time(NULL));

    long long numero_aleatorio =
        (long long)rand() * (RAND_MAX + 1LL) + rand();

    multiplicador_a = (numero_aleatorio % (primo_p - 1)) + 1;

    numero_aleatorio =
        (long long)rand() * (RAND_MAX + 1LL) + rand();

    incremento_b = numero_aleatorio % primo_p;

    produtos = malloc(capacidade * sizeof(produto));

    if (produtos == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    for (int i = 0; i < capacidade; i++) {
        produtos[i].estado = 0;
    }


    do {

        printf("\n========== SISTEMA DE ESTOQUE ==========\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Buscar produto\n");
        printf("3 - Atualizar produto\n");
        printf("4 - Remover produto\n");
        printf("5 - Listar produtos\n");
        printf("6 - Sair\n");
        printf("========================================\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                adicionar_produto(
                    &produtos, &quantidade, &capacidade,
                    multiplicador_a, incremento_b, primo_p
                );
                break;

            case 2:
                buscar_produto(
                    produtos, capacidade,
                    multiplicador_a, incremento_b, primo_p
                );
                break;

            case 3:
                atualizar_produto(
                    produtos, capacidade,
                    multiplicador_a, incremento_b, primo_p
                );
                break;

            case 4:
                remover_produto(
                    produtos, &quantidade, capacidade,
                    multiplicador_a, incremento_b, primo_p
                );
                break;

            case 5:
                listar_produtos(produtos, capacidade);
                break;

            
            case 6:
                printf("\nEncerrando o programa...\n");
            break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

     } while (opcao != 6);

    free(produtos);

    return 0;
}




