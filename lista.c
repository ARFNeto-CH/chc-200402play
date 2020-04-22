#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>                               
#include <stdlib.h>
#include <string.h>

#include "lista.h"

Lista*  apagar(Lista* l)
{   // apagar e como listar()
    if (l == NULL)
    {
        printf("Lista nao iniciada\n");
        return NULL;
    }
    if (l->dados == NULL)
    {
        printf("Lista vazia\n");
        return NULL;
    }
    // nao esta vazia entao varre a lista e apaga 
    // os caras todos
    Lista* aux = l;
    Lista* temp = NULL;
    do
    {
        temp = aux->proxima; // salva o endereco da proxima
        free(aux->dados); // apaga essa musica
        free(aux); // apaga o no da lista
        aux = temp;
    } while (aux != NULL); // do-while()
    return NULL;
};  // apagar()

Musica* fabrica(int parm)
{
    // a cada chamada retorna uma musica novinha
    static int n = 0;
    if (parm == 0)
    {
        srand(200401);
        n = 1;
        return NULL;
    }
    Musica* m = (Musica*)malloc(sizeof(Musica));
    sprintf(m->Faixa, "Musica 1234 %03d", n);
    sprintf(m->Artista, "Artista ABC %03d", n);
    m->min = rand() % 10;
    m->seg = rand() % 60;
    n = n + 1;
    return m;
};  // fabrica()

Lista*  inserir(void* valor, Lista* l)
{   // insere dados: musica nesse caso
    //printf("***** inserir() *****\n");
    // cria um elemento
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->proxima = l;
    novo->dados = valor;
    return novo;
};  // inserir()

int     listar(Lista* l)
{
    int total = 0;
    Lista* aux = l;
    if (l == NULL)
    {
        printf("Lista nao iniciada\n");
        return -1;
    }
    if (l->dados == NULL)
    {
        printf("Lista vazia\n");
        return 0;
    }
    // nao esta vazia entao cria um ponteiro para
    // o tipo de dados que estamos usando

    printf(
        "              #            faixa            artista    HH:MM\n\n"
    );
    do
    {
        total = total + 1;
        char pos[TAMANHO];
        sprintf(pos,"%14d", total);
        mostra_musica(aux->dados, pos);
        aux = aux->proxima;
    } while (aux != NULL); // do-while()
    printf("\n");
    return total;
};  // listar()

// fase 2 :)
Lista*  apagar_da_playlist(int n, Lista* playlist)
{   // baseado em listar()
    int pos = 0;
    Lista* pL = playlist;
    Lista* pAnt = NULL; // vai apontar para a faixa anterior
    if (pL == NULL) return pL; // vazio
    if (pL->dados == NULL) return pL; // vai que...
    // agora sim vamos procurar
    do
    {   // procura a faixa por posicao
        if (pos == n)
        {   // vai apagar essa
            if (pAnt != NULL)
            {   // tinha uma musica antes dessa
                pAnt->proxima = pL->proxima;
                free(pL->dados);
                free(pL);
                return playlist;
            }
            else
            {   // vai apagar a primeira
                playlist = pL->proxima;
                free(pL->dados);
                free(pL);
                return playlist;
            };  // if()
        };  // if()
        pos = pos + 1; // pos atual
        pAnt = pL;
        pL = pL->proxima;
    } while (pL != NULL); // do-while()
    return playlist; // nao achou tal faixa
};  // apagar_da_playlist()

int     gravar_no_arquivo(char* arquivo, Lista* playlist)
{
    // vai gravar em 'arquivo' a playlist em 'playlist'
    int n = 0;
    FILE* saida;
    saida = fopen(arquivo, "w");
    if (saida == NULL)
    {
        printf("Erro tentando criar '%s'\n", arquivo);
        return -1;
    };  // if()
    // se a playlist esta vazia faz o simples
    if (playlist == NULL)
    {
        fclose(saida);
        return 0; // sim, normal. So esta vazia
    };  // if()
    if (playlist->dados == NULL)
    {
        fclose(saida);
        return 0; // sim, normal. So esta vazia
    };  // if()
    // tem musicas, e o arquivo esta aberto
    // e como listar() so que ao inves de mostrar na tela grava no disco
    // entao cou copiar o codigo de listar() que ja esta ok
    int total = 0;
    Lista* aux = playlist;
    Musica* m = NULL;
    // faixa e artista nao sao strings...
    char musica[TAMANHO+1];
    char artista[TAMANHO+1];
    memset(musica, 0, TAMANHO + 1);
    memset(artista, 0, TAMANHO + 1);
    do
    {
        total = total + 1;
        m = (Musica*)aux->dados;
        memcpy(musica, m->Faixa, TAMANHO); // ja tem o 0 no fim
        memcpy(artista, m->Artista, TAMANHO);
        n = fprintf(saida, "%15s %15s %02d %02d\n",
            musica, artista, m->min, m->seg); // 15 + 15 + 2 + 2 + 3 espacos e o \n = 38
        aux = aux->proxima;
    } while (aux != NULL); // do-while()
    fclose(saida);
    return total;
};

Lista*  inserir_do_arquivo(char* arquivo, Lista* playlist_inicial)
{
    const char* mascara = "%15c%*1c%15c%*1c%2d%*1c%2d%*1c";
    const char* arq_entrada = arquivo;
    int n = 0;
    Lista* pL = playlist_inicial; // a playlist no comeco
    FILE* entrada;
    // o que vai ler de cada linha
    char musica[TAMANHO+1];
    char artista[TAMANHO+1];
    int min = 0;
    int seg = 0;
    // zera os campos de musica e artista
    memset(musica, 0, TAMANHO+1);
    memset(artista, 0, TAMANHO+1);
    entrada = fopen(arq_entrada, "r");
    if (entrada == NULL)
    {
        printf("Erro tentando abrir '%s'\n", arq_entrada);
        return pL;
    };  // if()
    // agora le os caras e poe na lista
    while (!feof(entrada))
    {
        n = fscanf(entrada, mascara, musica, artista, &min, &seg);
        if (n != 4) break;
        // leu ok entao cria a musica e poe na lista
        // atencao: nome e artista nao sao strings
        Musica* nova = (Musica*)malloc(sizeof(Musica)); // cria a faixa
        memcpy(nova->Faixa, musica, TAMANHO);
        memcpy(nova->Artista, artista, TAMANHO);
        nova->min = min; 
        nova->seg = seg;
        pL = inserir((void*)(nova), pL); // insere a musica
    }   // while()
    fclose(entrada);
    return pL;
};  // inserir_do_arquivo()

Lista*  inserir_na_playlist(Musica* musica, Lista* playlist)
{
    // inserir na playlist eh algo besta. Como nao tem qualquer restricao
    // tipo duplicar musicas ou inserir em certa posicao, e igual a inserir()
    if (musica == NULL) return playlist; // nao tinha musica
    Lista* pL = (Lista*)malloc(sizeof(Lista)); // cria o registro na lista
    Musica* nova = (Musica*)malloc(sizeof(Musica)); // cria a faixa
    memcpy(nova->Artista, musica->Artista, TAMANHO);
    memcpy(nova->Faixa, musica->Faixa, TAMANHO);
    nova->min = musica->min;
    nova->seg = musica->seg;
    // em *nova esta a musica nova. grava em *pL
    pL->proxima = playlist; // insere no inicio
    pL->dados = (void*)nova;
    return pL; // novo inicio
    return NULL;
};  // inserir_na_playlist()

void    mostra_musica(Musica* m, char* titulo)
{
    char    t_musica[TAMANHO + 1];
    char    t_artista[TAMANHO + 1];
    t_musica[TAMANHO] = 0;
    t_artista[TAMANHO] = 0;
    memcpy(t_musica, m->Faixa, TAMANHO);
    memcpy(t_artista, m->Artista, TAMANHO);

    printf(
        "%15s: %15s    %15s    %02d:%02d\n",
        titulo,
        t_musica,
        t_artista,
        m->min,
        m->seg
    );
    return;
};  // mostra_musica()