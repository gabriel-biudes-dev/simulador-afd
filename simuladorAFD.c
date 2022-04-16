#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simuladorAFD.h"
#define MAX 1000

Lista* criar_lista_vazia(){
  Lista *aux = (Lista*) malloc(sizeof(Lista));
  aux->info = NULL;
  aux->prox = NULL;
  return aux;
}

Lista* inserir(Lista *l, char* valor){
  Lista *aux = (Lista*) malloc(sizeof(Lista));
  aux->info = valor;
  if(l->info){
    aux->prox = l;
  }else{
    aux->prox = NULL;
  }
  return aux;
}

char* pegar_primeiro(char *str){
  char *aux = (char*) malloc(sizeof(char));
  strcpy(aux, str);
  *(aux + 1) = 0;
  return aux;
}

int buscar(Lista *l, char* item){
  if(l->info != NULL){
    if(strcmp(item, l->info) == 0){
      return 1;
    }
    if(l->prox != NULL){
      buscar(l->prox, item);
    }
  }
}

char* remove_espacos(char* s) {
    int i = 0;
    char *temp = (char*) malloc(sizeof(char) * MAX);
    while(*s){
        if(*s != ' '){
          *(temp + i) = *s;
          i++;
        }
        s++;
    }
    *(temp + i) = 0;
    temp = (char *) realloc(temp, strlen(temp) + 1);
    return temp;
}

char* proximoEstado(char* c, char* estado_atual, Lista* transicoes){
  char *temp;
  int contagem = 1;
  if(transicoes->info != NULL){
    temp = (char*) malloc(sizeof(strlen(transicoes->info) + 1));
    strcpy(temp, transicoes->info);
    temp = strtok(temp, " ");
    while(temp){
      if(contagem == 1 && strcmp(temp, estado_atual) == 0){
        temp = strtok(NULL, " ");
        if(strcmp(temp, c) == 0){
          temp = strtok(NULL, " ");
          return temp;
        }
      }
      temp = strtok(NULL, " ");
      contagem++;
    }
    if(transicoes->prox != NULL){
      proximoEstado(c, estado_atual, transicoes->prox);
    }
  }
}

void remove_ultimo(char *str, int x){
  *(str + strlen(str) - x) = 0;
}

void remove_primeiro(char *str){
  int i;
  for(i = 0; i < strlen(str); i++){
    *(str + i) = *(str + i + 1);
  }
}

void validar(char *cadeia, Lista* alfabeto, Lista *estados, Lista *finais, Lista* transicoes){
  int val = 1;
  int comeca_nula = 0;
  char* estado_atual = "q0";
  char* primeiro_char;
  if(strcmp(pegar_primeiro(cadeia), "@") == 0){
    comeca_nula = 1;
  }
  //Repete o processo até que a cadeia termine
  while(strlen(cadeia) > 0){
    printf("[%s]%s\n", estado_atual, cadeia);
    primeiro_char = pegar_primeiro(cadeia);
    //Verifica se o simbolo pertence ao alfabeto
    if(buscar(alfabeto, primeiro_char)){
      //Verifica se existe algum possível estado próximo quando se lê tal simbolo no estado atual
      if(proximoEstado(primeiro_char, estado_atual, transicoes) != NULL){
        estado_atual = proximoEstado(primeiro_char, estado_atual, transicoes);
        remove_ultimo(estado_atual, 1);
      }else{
        val = 0;
      }
    }else{
      val = 0;
    }
    cadeia++;
  }
  //Verifica se o algoritmo parou em um estado final
  if(!buscar(finais, estado_atual)){
    val = 0;
  }
  if(!comeca_nula){
    printf("[%s]%s\n", estado_atual, cadeia);
  }
  if(val){
    printf("ACEITA\n");
  }else{
    printf("REJEITA\n");
  }
}

Lista* guardarDados(Lista *l, char *str){
  char *aux = (char*) malloc(sizeof(char) * MAX);
  strcpy(aux, str);
  aux = strtok(aux, "{");
  aux = strtok(NULL, "{");
  remove_ultimo(aux, 2);
  aux = strtok(aux, ",");
  while(aux){
    aux = remove_espacos(aux);
    l = inserir(l, aux);
    aux = strtok(NULL, ",");
  }
  free(aux);
  return l;
}

Lista* guardarTransicao(Lista *l, char *str){
  char *aux = (char*) malloc(sizeof(char) * MAX);
  char *aux2 = (char*) malloc(sizeof(char) * MAX);
  char *str_final = (char*) malloc(sizeof(char) * MAX);
  strcpy(aux, str);
  aux = strtok(aux, "=");
  aux2 = aux;
  aux = strtok(NULL, "=");
  aux2 = strtok(aux2, ",");
  remove_primeiro(aux2);
  aux2 = remove_espacos(aux2);
  strcpy(str_final, aux2);
  strcat(str_final, " ");
  aux2 = strtok(NULL, ",");
  aux2 = remove_espacos(aux2);
  remove_ultimo(aux2, 1);
  strcat(str_final, aux2);
  strcat(str_final, " ");
  aux = remove_espacos(aux);
  strcat(str_final, aux);
  aux = NULL;
  aux2 = NULL;
  free(aux);
  free(aux2);
  l = inserir(l, str_final);
  return l;
}

int main()
{
  //DeclaraÃo de variáveis e estruturas
  Lista *alfabeto = criar_lista_vazia();
  Lista *estados = criar_lista_vazia();
  Lista *finais = criar_lista_vazia();
  Lista *transicoes = criar_lista_vazia();
  char *cadeia = (char*) malloc(sizeof(char) * 50);
  FILE *f;
  int i;
  char linha[100];

  //Armazenamento dos dados em listas, a partir de um arquivo txt
  alfabeto = inserir(alfabeto, "@");
  f = fopen("arquivo.txt", "r");
  for(i = 0; fgets(linha, MAX, f); i++){
    if(i == 0){
      alfabeto = guardarDados(alfabeto, linha);
    }else if(i == 1){
      estados = guardarDados(estados, linha);
    }else if(i == 2){
      finais = guardarDados(finais, linha);
    }else{
      transicoes = guardarTransicao(transicoes, linha);
    }
  }

  //Loop de entrada de dados
  printf("Insira uma palavra a ser testada: ");
  while(scanf("%[^\n]%*c", cadeia)){
    validar(cadeia, alfabeto, estados, finais, transicoes);
    printf("\nInsira uma nova palavra a ser testada: ");
  }
  free(cadeia);
  return 0;
}
