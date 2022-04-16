typedef struct no{
  char *info;
  struct no *prox;
} Lista;

//Cria uma lista vazia
//Pré-condição: nenhuma
//Pós-condição: retorna uma lista vazia
Lista* criar_lista_vazia();

//Insere um dado na lista
//Pré-condição: nenhuma
//Pós-condição: retorna a nova cabeça da lista com o dado inserido
Lista* inserir(Lista *l, char* valor);

//Acessar o primeiro caractere de uma string
//Pré-condição: nenhuma
//Pós-condição: retorna uma string formada apenas pelo primeiro caractere da string fornecida, caso exista
char* pegar_primeiro(char *str);

//Verifica se o item está presente na lista
//Pré-condição: nenhuma
//Pós-condição: retorna 1 caso o item esteja presente, 0 caso não esteja
int buscar(Lista *l, char* item);

//Definir qual é o próximo estado do autômato
//Pré-condição: nenhuma
//Pós-condição: retorna uma string representando o próximo estado do autômato após uma transição
char* proximoEstado(char* c, char* estado_atual, Lista* transicoes);

//Remover caracteres no final da string
//Pré-condição: nenhuma
//Pós-condição: remove os x últimos caracteres da string
void remove_ultimo(char *str, int x);

//Remover caracteres no início da string
//Pré-condição: nenhuma
//Pós-condição: remove o primeiro caractere da string
void remove_primeiro(char *str);

//Armazenar informações do autômato
//Pré-condição: no arquivo texto, deve estar definido com o formato específico "lista={x,y,z,...}"
//Pós-condição: retorna uma lista com a informação informada armazenada
Lista* guardarDados(Lista *l, char *str);

//Armazenar transições do autômato
//Pré-condição: no arquivo texto, deve estar definido com o formato específico "(qx,a)= qy"
//Pós-condição: retorna uma lista com a informação informada armazenada
Lista* guardarTransicao(Lista *l, char *str);

//Remove espaços em branco na string
//Pré-condição: nenhuma
//Pós-condição: retorna a string sem os espaços em branco
char* remove_espacos(char* s);

//Valida o autômato
//Pré-condição: nenhuma
//Pós-condição: imprime na tela se o processamento foi aceito ou rejeitado
void validar(char *cadeia, Lista* alfabeto, Lista *estados, Lista *finais, Lista* transicoes);
