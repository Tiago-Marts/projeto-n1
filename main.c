#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NOME 50
#define MAX_DESC 100

//Jogos
typedef struct {
    unsigned int id;
    char* nome;
    char* descricao;
    float preco;
} Jogo;

//Usuario
typedef struct {
    unsigned int id;
    char* nome;
    unsigned int carrinho[3];
    size_t contador_carrinho;
    unsigned int colecao[100];
    size_t contador_colecao;
} Usuario;

//OPERAÇÕES JOGOS
// Busca jogo e retorna 1 se encontra e 0 se não;
int busca_jogo(Jogo* base_jogo, unsigned int id_jogo, size_t contador){
    int resultado = 0;

    for(size_t i = 0; i < contador; i++){
        if(base_jogo[i].id == id_jogo){
            resultado = 1;
            printf("preco jogo: %.2f\n", base_jogo[i].preco);
            goto end;

        }
    }

    end:
        return resultado;
}

float busca_preco(Jogo* base_jogo, unsigned int id_jogo, size_t contador){
    float preco = 0.0f;

    for(size_t i = 0; i < contador; i++){
        if(base_jogo[i].id == id_jogo){
            preco = base_jogo[i].preco;

        }
    }

    return preco;

}


int adiciona_jogo(Jogo* base_jogo, size_t* contador_jogo){
    int resultado = 0;
    Jogo novo_jogo;

    unsigned int id = 0;
    printf("Digite o ID do jogo: ");
    scanf("%u", &id);
    novo_jogo.id = id;

    while(getchar() != '\n');
    char* nome = malloc(MAX_NOME * sizeof(char));
    printf("Digite o nome do jogo: ");
    fgets(nome, MAX_NOME, stdin);
    novo_jogo.nome = nome;


    char* descricao = malloc(MAX_DESC * sizeof(char*));
    printf("Digite uma descricao para o jogo (MAX 100 palavras): \n");
    fgets(descricao, MAX_DESC, stdin);
    novo_jogo.descricao = descricao;


    float preco = 0.0f;
    printf("Digite o preco do jogo: ");
    scanf("%f", &preco);
    novo_jogo.preco = preco;


    base_jogo[*contador_jogo] = novo_jogo;
    resultado = 1;


    *contador_jogo += 1;

    return resultado;

}



// Busca o ID do usuario na base e retorna 1 se o encontra e 0 se não.
int login(Usuario* base_usuario, size_t contador, int id){
    int resultado = 0;

    for(int i = 0; i < contador; i++){
        printf("%d\n",base_usuario[i].id);
        printf("%s\n",base_usuario[i].nome);
        if(base_usuario[i].id == id){
            resultado = 1;

            goto end;
        }
    }

    end:
        return resultado;
}



// Realiza as etapas de cadastro de usuario. Retorna 1 para sucesso e 0 para falha.
int cadastrar_usuario(Usuario* base_usuario, size_t* contador){
    int resultado = 0;
    Usuario novo_usuario;


    cadastro_id:
        unsigned int id = 0;
        int eh_unico = 0;
        printf("-----AVISO-----\n");
        printf("\t 1. O ID precisa ser unico \n");
        printf("\t 2. O ID deve ser diferente de 0 \n");
        printf("Digite um ID para seu usuario: ");
        scanf("%d", &id);

        //Verifica se o ID é unico
        for(size_t i = 0; i < *contador; i++){
            if(base_usuario[i].id == id){
                printf("ERRO: ID ja criado...\n");
                goto cadastro_id;
            }
        }

        if(id == 0){
            printf("ERRO: ID igual 0...\n");
            goto cadastro_id;
        }
        novo_usuario.id = id;

    cadastro_nome:
        while(getchar() != '\n'); // Limpa o buffer;
        char *nome = malloc(MAX_NOME);
        printf("Digite o nome do usuario: ");
        fgets(nome, MAX_NOME * sizeof(nome), stdin);
        novo_usuario.nome = nome;

    cadastro:
        novo_usuario.contador_carrinho = 0;
        novo_usuario.contador_colecao = 0;
        base_usuario[*contador] = novo_usuario;
        *contador += 1;
        resultado = 1;

    end:
        return resultado;

}


// 2 - Adicionar ao carrinho
int adicionar_ao_carrinho(Usuario* base_usuario, unsigned int id_ativo, unsigned int jogo){
    size_t contador = base_usuario[id_ativo].contador_carrinho;
    base_usuario[id_ativo].carrinho[contador] = jogo;
    contador++;
    base_usuario[id_ativo].contador_carrinho = contador;
}

float preco_carrinho_final(Usuario* base_usuario, Jogo* base_jogo, size_t contador_jogo, unsigned int id_ativo){
    float soma_preco = 0.0f;
    size_t contador = base_usuario[id_ativo].contador_carrinho;

    for(int i = 0; i < contador; i++){
        unsigned int id = base_usuario[id_ativo].carrinho[i];

        soma_preco += busca_preco(base_jogo, id, contador_jogo);

    }

    return soma_preco;
}


// 3 - Comprar
int comprar_jogos(Usuario* base_usuario, Jogo* base_jogo, size_t contador_jogo, unsigned int id_ativo){
    int resultado = 0;

    carrinho:
        int quantidade;
        printf("Digite 0 para sair.\n");
        printf("Digite quantos jogos deseja comprar (max. 3 por vez): ");
        scanf("%d", &quantidade);

        if(quantidade > 3){
            printf("Limite excedido!\n");
            goto compra;
        } else if(quantidade == 0){
            printf("Saindo da compra...\n");
        } else {
            for(int i = 0; i < quantidade; i++){
                adicao_compra:

                    unsigned int id_jogo = 0;
                    printf("Digite o ID do jogo que deseja comprar: ");
                    scanf("%d", &id_jogo);
                    if(!busca_jogo(base_jogo,id_jogo, contador_jogo)) {
                        printf("Id nao existente...\n");
                        goto adicao_compra;
                    }
                    printf("Passou\n");
                    adicionar_ao_carrinho(base_usuario, id_ativo, id_jogo);
            }
        }

    compra:
        int confirm = 0;
        float preco_final = preco_carrinho_final(base_usuario, base_jogo, contador_jogo,  id_ativo);
        printf("PRECO FINAL: ")
        printf("Digite 1 para confirmar a compra e 0 para negar: ");


    end:
        return resultado;
}


// 4 - Coleção
// 5 - Sair
// OPCIONAL - Manter salvo os valores


// OPERACOES GERAIS DO USUARIO
void usuario_ativo(Usuario* base_usuario, Jogo* base_jogo, unsigned int id_ativo, size_t* contador_usuario, size_t* contador_jogo){
    int opt_usuario = 0;

    while(opt_usuario != 4){
        printf("MENU\n");
        printf("1. Comprar Jogo\n");
        printf("2. Ver coleção\n");
        printf("3. Atualizar os dados\n");
        printf("4. Sair\n");
        printf("Digite a opcao a ser esoclhida: ");
        scanf("%d", &opt_usuario);

        switch (opt_usuario)
        {
        case 1:
            comprar_jogos(base_usuario, base_jogo, *contador_jogo, id_ativo);
            break;
        case 2:
            break;
        case 3:
            break;

        case 4:
            break;

        default:
            break;
        }
    }
}

//MAIN
int main(void){
    Jogo jogos[50];
    Usuario usuarios[MAX_USERS];
    size_t contador_usuario = 0;
    size_t contador_jogos = 0;

    int opt_menu = 0;

    while(opt_menu != 4){
        printf("MENU\n");
        printf("1. Cadastrar Jogo\n");
        printf("2. Entrar como usuario\n");
        printf("3. Cadastrar usuario\n");
        printf("4. Sair\n");
        printf("Digite a opcao a ser esoclhida: ");
        scanf("%d", &opt_menu);

        switch (opt_menu)
        {
        case 1:
            adiciona_jogo(jogos, &contador_jogos);
            break;

        case 2:
            int id = 0;
            printf("ID do Login: ");
            scanf("%d", &id);
            if(login(usuarios, contador_usuario, id)){
                usuario_ativo(usuarios, jogos, id, &contador_usuario, &contador_jogos);
            } else {

            }
            break;

        case 3:
            cadastrar_usuario(usuarios, &contador_usuario);
            break;
        default:
            break;
        }
    }


    return 0;
}
