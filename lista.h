#define TAMANHO 15

// so o que temos: a musica e a lista 
struct musica
{
    char    Faixa[TAMANHO];
    char    Artista[TAMANHO];
    int     min;
    int     seg;
};  // musica
typedef struct musica Musica;

struct no
{
    void*       dados;
    struct no*  proxima;
};  // no
typedef struct no Lista;

// as funcoes que escrevemos

Lista*  apagar(Lista*);
Musica* fabrica(int);
Lista*  inserir(void*, Lista*);
int     listar(Lista*);

// fase 2 :)

Lista*  apagar_da_playlist(int, Lista*);
int     gravar_no_arquivo(char*, Lista*);
Lista*  inserir_do_arquivo(char*, Lista*);
Lista*  inserir_na_playlist(Musica*, Lista*);
void    mostra_musica(Musica*, char*);
