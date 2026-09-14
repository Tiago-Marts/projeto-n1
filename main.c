#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    unsigned int colecao[100];
} Usuario;

#define MAX_USERS 100
#define MAX_NOME 50

// Busca o ID do usuario na base e retorna 1 se o encontra e 0 se não.
int login(Usuario* base_usuario, unsigned int id){
    int resultado = 0;

    for(int i = 0; i < MAX_USERS; i++){
        if(base_usuario[i].id == id){
            resultado = 1;
            goto end;
        }
    }

    end:
        return resultado;
}

int cadastrar_usuario(Usuario* base_usuario, size_t* contador){
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
        char nome[MAX_NOME];
        printf("Digite o nome do usuario: ");
        fgets(nome, MAX_NOME, stdin);
        printf("NOME: %s", nome);



}
// OPERACOES GERAIS DO USUARIO
// 2 - Adicionar ao carrinho
// 3 - Comprar
// 4 - Coleção
// 5 - Sair 
// OPCIONAL - Manter salvo os valores

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
            break;
        
        case 2:
            int id = 0;
            printf("ID do Login: ");
            scanf("%d", &id);
            if(login(usuarios, id)){

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