#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NOME 50
#define MAX_DESC 100
#define MAX_COLECAO 100
#define MAX_CARRINHO 3

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
    unsigned int carrinho[MAX_CARRINHO];
    size_t contador_carrinho;
    unsigned int colecao[MAX_COLECAO];
    size_t contador_colecao;
} Usuario;

//OPERAÇÕES JOGOS
// Busca jogo e retorna 1 se encontra e 0 se não;
int busca_jogo(Jogo* base_jogo, unsigned int id_jogo, size_t contador){
    int resultado = 0;

    for(size_t i = 0; i < contador; i++){
        if(base_jogo[i].id == id_jogo){
            resultado = 1;
            goto end;

        }
    }

    end:
        return resultado;
}

//Retorna o id do jogo ao fazer uma busca pelo ID
Jogo* get_jogo(Jogo* base_jogo, unsigned int id_jogo, size_t contador_jogo){
    Jogo* jogo_buscado;
    for(size_t i = 0; i < contador_jogo; i++){
        if(base_jogo[i].id == id_jogo){
            jogo_buscado = &base_jogo[i];
            goto end;

        }
    }

    end:
        return jogo_buscado;
}

//Retorna o preco do jogo ao fazer uma besca pelo ID
float busca_preco(Jogo* base_jogo, unsigned int id_jogo, size_t contador){
    float preco = 0.0f;

    for(size_t i = 0; i < contador; i++){
        if(base_jogo[i].id == id_jogo){
            preco = base_jogo[i].preco;

        }
    }

    return preco;

}

//Adiciona um novo jogo a base de jogos
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

//OPERACOES USUARIOS
Usuario* get_usuario(Usuario* base_usuario, size_t contador, unsigned int id_ativo){
    Usuario* usuario;
    for(size_t i = 0; i < contador; i++){
        if(base_usuario[i].id == id_ativo){
            usuario = &base_usuario[i];
        }
    }

    return usuario;
}

// Busca o ID do usuario na base e retorna 1 se o encontra e 0 se não.
int login(Usuario* base_usuario, size_t contador, unsigned int id){
    int resultado = 0;

    for(size_t i = 0; i < contador; i++){
        if(base_usuario[i].id == id){
            resultado = 1;
            printf("Entrando como %s", base_usuario[i].nome);
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

    //Cadastro do Nome
    while(getchar() != '\n'); // Limpa o buffer;
    char *nome = malloc(MAX_NOME);
    printf("Digite o nome do usuario: ");
    fgets(nome, MAX_NOME * sizeof(nome), stdin);
    novo_usuario.nome = nome;

    //Cadastro do usuário na base
    novo_usuario.contador_carrinho = 0;
    novo_usuario.contador_colecao = 0;
    base_usuario[*contador] = novo_usuario;
    *contador += 1;
    resultado = 1;

    
    return resultado;

}

// 2 - Adicionar ao carrinho
int adicionar_ao_carrinho(Usuario* base_usuario, size_t contador_usuario, unsigned int id_ativo, unsigned int jogo){
    Usuario* usuario = get_usuario(base_usuario, contador_usuario, id_ativo);
    int resultado = 0;
    size_t contador = usuario->contador_carrinho;
    if(contador == MAX_CARRINHO){
        printf("CARRINHO CHEIO!\n");
        goto end;
    }

    usuario->carrinho[contador] = jogo;
    contador++;
    usuario->contador_carrinho = contador;
    resultado = 1;

    end:
        return resultado;
}

//Calcula o preco total dos itens presentes no carrinho
float preco_carrinho_final(Usuario* base_usuario, size_t contador_usuario, Jogo* base_jogo, size_t contador_jogo, unsigned int id_ativo){
    Usuario* usuario = get_usuario(base_usuario,contador_usuario, id_ativo);
    float soma_preco = 0.0f;
    size_t contador = usuario->contador_carrinho;

    for(size_t i = 0; i < contador; i++){
        unsigned int id = usuario->carrinho[i];

        soma_preco += busca_preco(base_jogo, id, contador_jogo);

    }

    return soma_preco;
}

//A funcao diminui o contador do carrinho, permitindo que os items sejam sobrescrevidos
void limpa_carrinho(Usuario* base_usuario, size_t contador_usuario, unsigned int id_ativo){
    Usuario* usuario = get_usuario(base_usuario, contador_usuario,id_ativo);
    memset(usuario->carrinho, 0, sizeof usuario->carrinho);
    usuario->contador_carrinho = 0;
}

//Adiciona jogos a colecao depois da compra. A funcao limpa o carrinho
int adicionar_a_colecao(Usuario* base_usuario,size_t contador_usuario, unsigned int id_ativo){
    int resultado = 0;
    Usuario* usuario = get_usuario(base_usuario, contador_usuario, id_ativo);
    size_t contador_carrinho = usuario->contador_carrinho;
    size_t contador_colecao = usuario->contador_colecao;

    if(contador_colecao == MAX_COLECAO) {
        printf("ERRO! O usuario possui o maximo de jogos possiveis %d\n", MAX_COLECAO);
        goto end;
    }

    for(size_t i = 0; i < contador_carrinho; i++){
        usuario->colecao[contador_colecao] = usuario->carrinho[i];
        contador_colecao++;
    }

    limpa_carrinho(base_usuario, contador_usuario, id_ativo);
    usuario->contador_colecao = contador_colecao;
    resultado = 1;

    end:
        return resultado;
}

// 3 - Comprar
int comprar_jogos(Usuario* base_usuario, size_t contador_usuario, Jogo* base_jogo, size_t contador_jogo, unsigned int id_ativo){
    int resultado = 0;

    
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
            scanf("%u", &id_jogo);
            if(!busca_jogo(base_jogo,id_jogo, contador_jogo)) {
                printf("Id nao existente...\n");
                goto adicao_compra;
            }
            adicionar_ao_carrinho(base_usuario, contador_usuario, id_ativo, id_jogo);
        }
    }

    compra:
        int confirm = 0;
        float preco_final = preco_carrinho_final(base_usuario, contador_usuario, base_jogo, contador_jogo,  id_ativo);
        printf("PRECO FINAL: %.2f\n", preco_final);
        printf("Digite 1 para confirmar a compra e 0 para negar: ");
        scanf("%d", &confirm);
        if(confirm == 0){
            limpa_carrinho(base_usuario,contador_usuario, id_ativo);
            printf("Compra negada...\n Voltando para o menu de usuario.\n");
            goto end;
        } else if(confirm == 1){
            adicionar_a_colecao(base_usuario, contador_usuario, id_ativo);
            printf("Compra aprovada! Items adicionados a colecao!\nVoltando para o menu de usuario.\n");
        } else {
            printf("ERRO. RESPOSTA INVALIDA\n. Tente novamente...");
            goto compra;
        }


    end:
        return resultado;
}

// 4 - Coleção
int ver_colecao(Usuario* base_usuario, size_t contador_usuario, Jogo* base_jogo, size_t contador_jogo, unsigned int id_ativo){
    int resultado = 0;
    Usuario* usuario = get_usuario(base_usuario, contador_usuario, id_ativo);
    size_t contador = usuario->contador_colecao;

    Jogo* jogo_colecao;
    printf("=========================\n");
    printf("COLECAO\n");
    printf("=========================\n");
    printf("\n");
    for(size_t i = 0; i < contador; i++){
        jogo_colecao = get_jogo(base_jogo, usuario->colecao[i], contador_jogo);

        if(jogo_colecao == NULL){
            goto end;
        }

        printf("=========================\n");
        printf("\tID: %u\n", jogo_colecao->id);
        printf("\tNOME: %s", jogo_colecao->nome);
        printf("\tDESC: %s", jogo_colecao->descricao);
        printf("\tPRECO: %.2f\n", jogo_colecao->preco);
        printf("=========================\n");
    }

    resultado = 1;

    end:
        return resultado;
}

// 5 - Atualizar Dados
void atualiza_dados(Usuario* base_usuario, size_t contador_usuario, unsigned int id_ativo){
    Usuario* usuario = get_usuario(base_usuario, contador_usuario, id_ativo);
    while(getchar() != '\n');
    printf("Atualizando os dados do usuario %s", usuario->nome);
    char* novo_nome = malloc(MAX_NOME * sizeof(char));
    printf("Digite o novo nome do usuario: ");
    fgets(novo_nome, MAX_NOME, stdin);
    usuario->nome = novo_nome;

}

// OPCIONAL - Manter salvo os valores


// OPERACOES GERAIS DO USUARIO
void usuario_ativo(Usuario* base_usuario, Jogo* base_jogo, unsigned int *id_ativo, size_t* contador_usuario, size_t* contador_jogo){
    int opt_usuario = 0;

    while(opt_usuario != 4){
        printf("MENU\n");
        printf("1. Comprar Jogo\n");
        printf("2. Ver colecao\n");
        printf("3. Atualizar os dados\n");
        printf("4. Sair\n");
        printf("Digite a opcao a ser esoclhida: ");
        scanf("%d", &opt_usuario);

        switch (opt_usuario)
        {
        case 1:
            comprar_jogos(base_usuario, *contador_usuario, base_jogo, *contador_jogo, *id_ativo);
            break;

        case 2:
            ver_colecao(base_usuario, *contador_usuario, base_jogo, *contador_jogo, *id_ativo);
            break;

        case 3:
            atualiza_dados(base_usuario,*contador_usuario, *id_ativo);
            break;

        case 4:
            *id_ativo = 0;
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
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
            unsigned int id = 0;
            printf("ID do Login: ");
            scanf("%u", &id);
            if(login(usuarios, contador_usuario, id)){
                usuario_ativo(usuarios, jogos, &id, &contador_usuario, &contador_jogos);
            } else {
                printf("ERRO: USUARIO NAO ENCONTRADO\n");
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
