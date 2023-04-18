#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definicao Constantes */

#define VERDADE 1
#define FALSO 0
#define NAO_ENCONTRADO -1

#define TAMINVERSO 8

#define MAX_CARREIRAS 200

/* Definicao de Tipos de Dados */

typedef struct link1 {
    char *nome;
    double latitude, longitude;
    int idCarreiras[MAX_CARREIRAS];
    int numCarreiras;
    struct link1 *next;
} Paragem;

typedef struct link2 {
    int idOrigem, idDestino;
    double custo, duracao;
    struct link2 *previous, *next;
} Ligacao;

typedef struct link3 {
    char *nome;
    double custoTotal;
    double duracaoTotal;
    Ligacao *ligacoes;
    int numLigacoes;
    struct link3 *next;
} Carreira;

/* Variaveis Globais */

/* Variáveis para guardar paragens, ligações e carreiras. */

Paragem *_paragens=NULL;
Carreira *_carreiras=NULL;

/* Funções para parsing do input */

/* Le espaços. Devolve 0 se chegou ao final de linha ou 1 caso contrário. */

int leEspacos() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t');
    if (c == '\n') 
        return 0;
    ungetc(c, stdin);
    return 1;
}

/* Le um nome para a string que recebe como parametro. */

void leNome(char **s) {
    int i = 0, c;
    (*s) = (char*) malloc(sizeof(char));
    (*s)[0] = getchar();
    if ((*s)[0] != '"') {
        i = 1;
        while ((c = getchar()) != ' ' && c != '\t' && c != '\n') {
            (*s) = (char*) realloc((*s), (i+1)*sizeof(char));
            (*s)[i++] = c;
        }
        ungetc(c, stdin);
    }
    else {
        while((c = getchar()) != '"') {
            (*s) = (char*) realloc((*s), (i+1)*sizeof(char));
            (*s)[i++] = c;
        }
    }
    (*s) = (char*) realloc((*s), (i+1)*sizeof(char));
    (*s)[i++] = '\0';
}

/* Le todo o texto até ao final de linha. */
void leAteFimDeLinha() {
	char c = getchar();
	while (c != '\n')
		c = getchar();
}

/* Function that frees the whole system */
void freeSystem(int c){
    Paragem *tmp1;
    Carreira *tmp2;
    Ligacao *tmp3;
    leAteFimDeLinha();

    while (_paragens != NULL){
        tmp1 = _paragens;
        _paragens = _paragens->next;

        free(tmp1->nome);
        free(tmp1);
    }

    while (_carreiras != NULL){
        tmp2 = _carreiras;
        while(tmp2->ligacoes != NULL){
            tmp3 = tmp2->ligacoes;
            tmp2->ligacoes = tmp2->ligacoes->next;
            free(tmp3);
        }
        _carreiras = _carreiras->next;
        free(tmp2->nome);
        free(tmp2);
    }
    if (c == 'q'){
        exit(0);
    }
}

/* Function that verifies the last connection of the list*/
Ligacao* ultimaLigacao(Ligacao* head) {
    Ligacao* current = head;
    if (head == NULL) {
        return NULL;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    return current;
}

/*Length of linked list of Paragens*/
int tamanhoParagem() {
  int count = 0;
  Paragem *x = _paragens;
  while (x != NULL) {
    count++;
    x = x->next;
  }
  return count;
}

/* Function that discovers the stop connected to the index */
Paragem* encontraParagemPorIndex(int index) {
    Paragem* current = _paragens;
    int i = 0;
    if (index < 0) {
        return NULL;
    }
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    return current;
}

/* Fnções para tratar comandos */

/* Funções para tratar as carreiras */

/*Function that finds the Carreira through their index*/
Carreira* encontraCarreiraPorIndex(int index){
    Carreira* current = _carreiras;
    int i = 0;
    if (index < 0) {
        return NULL;
    }
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    return current;    
}


/* Mostra as ligações da carreira com indice i. */

void mostraLigacoesCarreira(int i, int inverso) {
    Carreira* c;
    int numLigacoes;
    Ligacao* ligacao;

    c = encontraCarreiraPorIndex(i);
    numLigacoes = c->numLigacoes;

    if (numLigacoes == 0) 
        return;
    if (inverso == FALSO) {
        ligacao = c->ligacoes;
        while(ligacao != NULL){
            printf("%s, ", encontraParagemPorIndex(ligacao->idOrigem)->nome);
            ligacao = ligacao->next;
        }
        ligacao = ultimaLigacao(c->ligacoes);
        printf("%s\n", encontraParagemPorIndex(ligacao->idDestino)->nome);
    }
    else {
        ligacao = ultimaLigacao(c->ligacoes);
        while(ligacao != NULL){
            printf("%s, ", encontraParagemPorIndex(ligacao->idDestino)->nome);
            ligacao = ligacao->previous;            
        }
        ligacao = c->ligacoes;
        printf("%s\n", encontraParagemPorIndex(ligacao->idOrigem)->nome);
    }
}

/* Mostra todas as carreiras. */

void listaCarreiras() {
    Carreira* current = _carreiras;
    while (current != NULL) {
        if(current->numLigacoes == 0){
            printf("%s %d %.2f %.2f\n",
            current->nome,
            current->numLigacoes,
            current->custoTotal,
            current->duracaoTotal);
            current = current->next;
        }
        else{
            Ligacao* primeira = 
                current->ligacoes;
            Ligacao* ultima = 
                ultimaLigacao(current->ligacoes);
            Paragem* origem = 
                encontraParagemPorIndex(primeira->idOrigem);
            Paragem* destino = 
                encontraParagemPorIndex(ultima->idDestino);
            printf("%s %s %s %d %.2f %.2f\n",
            current->nome,
            origem->nome,
            destino->nome,
            current->numLigacoes+1,
            current->custoTotal,
            current->duracaoTotal);
            current = current->next;
        }
    }
}

/* Procura uma carreira por nome.
   Devolve o indice da carreira ou NAO_ENCONTRADO se não existe. */

int encontraCarreira(char *nomeCarreira) {
    Carreira *current=_carreiras;
    int ind = 0;
    while (current != NULL) {
        if (strcmp(current->nome, nomeCarreira) == 0) {
            return ind;
        }
        current = current->next;
        ind++;
    }
    return NAO_ENCONTRADO;
}

/*Function that inserts the route into the linked list*/
void inserirCarreira(Carreira** head, Carreira* newCarreira) {
    Carreira* current = *head;
    if (*head == NULL) {
        *head = newCarreira;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCarreira;
    }
}

/* Procura se uma paragem existe numa carreira.
   Se existir, devolve o indice da primeira ligação que usa
   a paragem. Caso contrário, devolve NAO_ENCONTRADO. */

int encontraParagemCarreira(int idCarreira, int idParagem) {
    Carreira* c = encontraCarreiraPorIndex(idCarreira);
    Ligacao *l;
    int numLigacoes = c->numLigacoes;

    if(numLigacoes == 0){
        return NAO_ENCONTRADO;
    }

    l = c->ligacoes;
    while (l != NULL){
        if(l->idOrigem == idParagem){
            return VERDADE;
        }
        l = l->next;
    }
    l = ultimaLigacao(c->ligacoes);
    if (l->idDestino == idParagem)
        return VERDADE;
    return NAO_ENCONTRADO;
}

/* Cria uma carreira nova. */

void criaCarreira(char *nomeCarreira) {
    Carreira* newCarreira= (Carreira*)malloc(sizeof(Carreira));
    if (newCarreira == NULL) {
        printf("No memory.\n");
        freeSystem('q');
        return;
    }

    newCarreira->nome = (char*)malloc((strlen(nomeCarreira) + 1)*sizeof(char));
    if (newCarreira->nome == NULL) {
        printf("No memory.\n");
        free(newCarreira);
        freeSystem('q');
        return;
    }

    newCarreira->numLigacoes = 0;
    newCarreira->custoTotal = 0;
    newCarreira->duracaoTotal= 0;
    strcpy(newCarreira->nome, nomeCarreira);
    newCarreira->next = NULL;
    newCarreira->ligacoes = NULL;
    inserirCarreira(&_carreiras,newCarreira);
}

/* Verifica se a string é um prefixo de tamanho pelo menos 3 da
   palavra inverso. */

int verificaInversoOk(char *s) {
    char inv[] = "inverso";
    int size = strlen(s), i;

    if (size < 3 || size > 7)
        return FALSO;
    for (i = 0; i < size; i++)
        if (inv[i] != s[i])
            return FALSO;
    return VERDADE;
}

/* Função para tratar do comando 'c'. */

void carreiras() {
    char *s;
    char *inverso;
    int fimLinha = leEspacos();
    int index;
    
    if (!fimLinha) {
        listaCarreiras(_carreiras);
        return;
    }

    leNome(&s);
    index = encontraCarreira(s);
    fimLinha = leEspacos();
    if (!fimLinha) {
        if (index == NAO_ENCONTRADO){
            criaCarreira(s);
            free(s);
        }
        else{
            mostraLigacoesCarreira(index, FALSO);
            free(s); 
        }
    }
    else {
        leNome(&inverso);
        if (verificaInversoOk(inverso)){
            mostraLigacoesCarreira(index, VERDADE);
            free(s);
            free(inverso);
        }
        else{
            printf("incorrect sort option.\n");
            free(s);
            free(inverso);
        }
        leAteFimDeLinha();
    }
}

/* Funções para tratar as paragens */

/* Mostra todas as paragens. */

void listaParagens() {
    Paragem* current = _paragens;
    while (current != NULL){
        printf("%s: %16.12f %16.12f %d\n", 
        current->nome, 
        current->latitude, 
        current->longitude, 
        current->numCarreiras);
        current = current->next;
    }
}

/* Verifica se existe uma paragem com um determinado nome.
   Se existir devolve o indice. Caso contrário, devolve NAO_ENCONTRADO. */

int encontraParagem(char *nomeParagem) {
    Paragem* current = _paragens;
    int ind = 0;

    while (current != NULL) {
        if (strcmp(current->nome, nomeParagem) == 0) {
            return ind;
        }
        current = current->next;
        ind++;
    }
    return NAO_ENCONTRADO;
}

/*Function that inserts the stop into the linked list*/
void inserirParagem(Paragem** head, Paragem* newParagem) {
    Paragem *current = *head;
    if (*head == NULL) {
        *head = newParagem;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newParagem;
    }
}

/* Cria uma nova paragem. */

void criaParagem(char *nomeParagem, double latitude, double longitude) {
    Paragem* newParagem = (Paragem*)malloc(sizeof(Paragem));
    if (newParagem == NULL) {
        printf("No memory.\n");
        freeSystem('q');
        return;
    }

    newParagem->nome = (char*)malloc((strlen(nomeParagem) + 1) * sizeof(char));
    if (newParagem->nome == NULL) {
        printf("No memory.\n");
        free(newParagem);
        freeSystem('q');
        return;
    }

    newParagem->latitude = latitude;
    newParagem->longitude = longitude;
    newParagem->numCarreiras = 0;
    strcpy(newParagem->nome, nomeParagem);
    newParagem->next = NULL;
    inserirParagem(&_paragens,newParagem);
}

/* Função para tratar o comando 'p'. */

void paragens() {
    char *s;
    int fimLinha = leEspacos();
    int i;
    
    if (!fimLinha) {
        listaParagens(_paragens);
        return;
    }
    leNome(&s);
    fimLinha = leEspacos();
    if (!fimLinha) {
        if ((i = encontraParagem(s)) == NAO_ENCONTRADO){
            printf("%s: no such stop.\n", s);
            free(s);
        }
        else{   
            printf("%16.12f %16.12f\n", 
                   encontraParagemPorIndex(i)->latitude, 
                   encontraParagemPorIndex(i)->longitude);
            free(s);
        }
    }
    else {
        double latitude, longitude;
        if (scanf("%lf %lf", &latitude, &longitude) == 2){};
        if (encontraParagem(s) == NAO_ENCONTRADO){
            criaParagem(s, latitude, longitude);
            free(s);
        }
        else{
            printf("%s: stop already exists.\n", s);
            free(s);
        }
        leAteFimDeLinha();
    }
}

/* Funções para tratar as Ligações */

/* Function that inserts the connection at the beginning of the list */
void inserirLigacaoInicio(Ligacao** head, Ligacao* newLigacao) {
    if (*head == NULL) {
        *head = newLigacao;
    } else {
        newLigacao->next = *head;
        (*head)->previous = newLigacao;
        *head = newLigacao;
    }
}

/* Function that inserts the connection at the end of the list */
void inserirLigacaoFim(Ligacao** head, Ligacao* newLigacao) {
    Ligacao* current = *head;
    if (*head == NULL) {
        *head = newLigacao;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newLigacao;
        newLigacao->previous = current;
    }
}

/* Adiciona uma nova ligação. */

Ligacao* criaLigacao(int idParagemOrigem, int idParagemDestino,
                 double custo, double duracao) {
    Ligacao* l = (Ligacao *)malloc(sizeof(Ligacao));
    if (l == NULL) {
        printf("No memory.\n");
        freeSystem('q');
        return NULL;
    }

    l->idOrigem = idParagemOrigem;
    l->idDestino = idParagemDestino;
    l->custo = custo;
    l->duracao = duracao;
    l->next = NULL;
    l->previous = NULL;
    return l;
}

/* Acrescenta uma nova ligação no fim de uma carreira. */

void acrescentaLigacaoFim(int idCarreira, Ligacao* l) {
    Carreira* c = encontraCarreiraPorIndex(idCarreira);

    inserirLigacaoFim(&c->ligacoes,l);
    c->custoTotal += l->custo;
    c->duracaoTotal += l->duracao;
    c->numLigacoes++;
}

/* Acrescenta uma nova ligação no início de uma carreira. */

void acrescentaLigacaoInicio(int idCarreira, Ligacao* l) {
    Carreira* c = encontraCarreiraPorIndex(idCarreira);

    inserirLigacaoInicio(&c->ligacoes, l);
    c->custoTotal += l->custo;
    c->duracaoTotal += l->duracao;
    c->numLigacoes++;
}

/* Adiciona que existe uma nova carreira associada a uma paragem. */

void adicionaCarreiraParagem(int idParagem, int idCarreira) {
    Paragem* p = encontraParagemPorIndex(idParagem);
    p->idCarreiras[p->numCarreiras] = idCarreira;
    p->numCarreiras++;
}


/* Adiciona primeira ligacao da carreira. */

void adicionaPrimeiraLigacao(int idCarreira, int idParagemOrigem, int idParagemDestino,
                     double custo, double duracao) {
    Ligacao *l;
    if (idParagemOrigem == idParagemDestino){
        adicionaCarreiraParagem(idParagemOrigem, idCarreira);
    }
    else{
        adicionaCarreiraParagem(idParagemOrigem, idCarreira);
        adicionaCarreiraParagem(idParagemDestino, idCarreira);
    }
    l = criaLigacao(idParagemOrigem, idParagemDestino, custo, duracao);
    acrescentaLigacaoFim(idCarreira, l);  
}


/* Adiciona uma nova ligação a uma carreira. */

void adicionaLigacao(int idCarreira, int idParagemOrigem, int idParagemDestino,
                     double custo, double duracao) {
    Carreira* c = encontraCarreiraPorIndex(idCarreira);
    int numLigacoesCarreira = c->numLigacoes;
    Ligacao *l;
    
    if (numLigacoesCarreira == 0) 
        adicionaPrimeiraLigacao(idCarreira, idParagemOrigem, idParagemDestino,
				custo, duracao);
    else {
        Ligacao *origemLigacao = c->ligacoes;
        Ligacao *destinoLigacao = ultimaLigacao(c->ligacoes);
        if (idParagemOrigem == destinoLigacao->idDestino) {
            if (encontraParagemCarreira(idCarreira, idParagemDestino) == NAO_ENCONTRADO)
                adicionaCarreiraParagem(idParagemDestino, idCarreira);
            l = criaLigacao(idParagemOrigem, idParagemDestino, custo, duracao);
            acrescentaLigacaoFim(idCarreira, l);
        }
        else if (idParagemDestino == origemLigacao->idOrigem) {
            if (encontraParagemCarreira(idCarreira, idParagemOrigem) == NAO_ENCONTRADO)
                adicionaCarreiraParagem(idParagemOrigem, idCarreira);
            l = criaLigacao(idParagemOrigem, idParagemDestino, custo, duracao);
            acrescentaLigacaoInicio(idCarreira, l);
        }
        else 
            printf("link cannot be associated with bus line.\n");
    }
}

/* Le nome de carreira e paragens de uma ligacao. */

void leNomesComando(char **nomeCarreira, char **nomeOrigem, char **nomeDestino) {
    leEspacos();
    leNome(nomeCarreira);
    leEspacos();
    leNome(nomeOrigem);
    leEspacos();
    leNome(nomeDestino);
}

/* Função para tratar o comando 'l'. */

void ligacoes() {
    char *nomeCarreira;
    char *nomeOrigem;
    char *nomeDestino;
    double custo, duracao;
    int indexCarreira, indexOrigem, indexDestino;

    leNomesComando(&nomeCarreira, &nomeOrigem, &nomeDestino);
    if (scanf("%lf %lf", &custo, &duracao) == 2){};
    leAteFimDeLinha();

    indexCarreira = encontraCarreira(nomeCarreira);
    if (indexCarreira == NAO_ENCONTRADO){
        printf("%s: no such line.\n", nomeCarreira);
        free(nomeCarreira);
        free(nomeOrigem);
        free(nomeDestino);
    }
    else {
        indexOrigem = encontraParagem(nomeOrigem);
        if (indexOrigem == NAO_ENCONTRADO){
	        printf("%s: no such stop.\n", nomeOrigem);
            free(nomeCarreira);
            free(nomeOrigem);
            free(nomeDestino);
        }
        else {
            indexDestino = encontraParagem(nomeDestino);
            if (indexDestino == NAO_ENCONTRADO){
                printf("%s: no such stop.\n", nomeDestino);
                free(nomeCarreira);
                free(nomeOrigem);
                free(nomeDestino);
            }
            else if (custo < 0.0 || duracao < 0.0){
                printf("negative cost or duration.\n");
                free(nomeCarreira);
                free(nomeOrigem);
                free(nomeDestino);
            }
            else{
                adicionaLigacao(indexCarreira, indexOrigem, indexDestino, 
                custo, duracao);
                free(nomeCarreira);
                free(nomeOrigem);
                free(nomeDestino);                
            }
        }
    }
}

/* Funções para tratar as interseções */

/* Aplica Bubble Sort a um vector de identificadores de carreiras. */

void ordenaCarreiras(int *idCarreiras, int numCarreiras) {
    int i, j, houveTroca = VERDADE;
    for (i = 0; houveTroca && i < numCarreiras-1; i++) {
        houveTroca = FALSO;
        for (j = 0; j < numCarreiras-1-i; j++) {
            if (strcmp(encontraCarreiraPorIndex(idCarreiras[j])->nome,
                    encontraCarreiraPorIndex(idCarreiras[j+1])->nome) > 0) {
                int aux = idCarreiras[j];
                idCarreiras[j] = idCarreiras[j+1];
                idCarreiras[j+1] = aux;
                houveTroca = VERDADE;
            }
        }
    }
}

/* Função para tratar o comando 'i'. */

void intersecoes() {
    int i, c, idCarreira, numCarreiras;
    Paragem *p; 

    leAteFimDeLinha();

    for (i = 0; i < tamanhoParagem(); i++) {
        p = encontraParagemPorIndex(i);
        numCarreiras = p->numCarreiras;
        if (numCarreiras > 1) {
            printf("%s %d:", p->nome, numCarreiras);
            ordenaCarreiras(p->idCarreiras, numCarreiras);
            for (c = 0; c < numCarreiras; c++) {
                idCarreira = p->idCarreiras[c];
                printf(" %s", encontraCarreiraPorIndex(idCarreira)->nome);
            }
            printf("\n");
        }
    }
}

/* Function that eliminates a connection */

void eliminaLigacao(Ligacao** head, Ligacao* l){
    if (*head == NULL || l == NULL)
        return;

    if (*head == l)
        *head = l->next;
  
    if (l->next != NULL)
        l->next->previous = l->previous;
  
    if (l->previous != NULL)
        l->previous->next = l->next;
  
    free(l);
    l = NULL;
}

/*Function that removes a Carreira from the list*/

void retiraCarreira(Carreira** head,int index){
    Carreira *tmp;
    Carreira *prev = NULL;

    if (index == 0){
        tmp = *head;
        *head = tmp->next;
        free(tmp->nome);
        free(tmp);
        return;
    }

    tmp = encontraCarreiraPorIndex(index);
    prev = encontraCarreiraPorIndex(index-1);

    prev->next = tmp->next;
    free(tmp->nome);
    free(tmp);
}

/*Function that removes a Paragem from the list*/

void retiraParagem(Paragem **head,int index){
    Paragem *tmp;
    Paragem *prev = NULL;

    if (index == 0){
        tmp = *head;
        *head = tmp->next;
        free(tmp->nome);
        free(tmp);
        return;
    }

    tmp = encontraParagemPorIndex(index);
    prev = encontraParagemPorIndex(index-1);

    prev->next = tmp->next;
    free(tmp->nome);
    free(tmp);
}

/*'r' menu */

void eliminaCarreira(){
    char *nomeCarreira;
    int indexCar,i,j;
    Carreira *c;
    Paragem* currPar = _paragens;
    Ligacao* currLig;

    leEspacos();
    leNome(&nomeCarreira);
    leAteFimDeLinha();

    /* Checks if Carreira exists through the name*/
    indexCar = encontraCarreira(nomeCarreira);
    if (indexCar == NAO_ENCONTRADO){
        printf("%s: no such line.\n", nomeCarreira);
        free(nomeCarreira);
        return;
    }

    /*Eliminates every connection from Carreira*/
    c = encontraCarreiraPorIndex(indexCar);
    currLig = c->ligacoes;
    while(currLig != NULL){
        eliminaLigacao(&c->ligacoes,currLig);
        currLig = currLig->next;
    }

    /*Removes Carreira*/
    retiraCarreira(&_carreiras,indexCar);

    /*Go through every Paragem and if Paragem was associated with Carreira,
    eliminate the index of Carreira. If index bigger than the eliminated one,
    decrements. */
    while (currPar != NULL){
        for(i = 0; i < currPar->numCarreiras; i++){
            if(currPar->idCarreiras[i] == indexCar){
                for(j = i; j < currPar->numCarreiras; j++){
                    currPar->idCarreiras[j] = currPar->idCarreiras[j+1];
                    if (j == currPar->numCarreiras-1){
                        currPar->numCarreiras--;
                        break;
                    }
                }
            }
            if(currPar->idCarreiras[i] > indexCar){
                currPar->idCarreiras[i]--;
            }
        }
        currPar = currPar->next;
    }
    free(nomeCarreira);
}

/*'e' menu*/

void eliminaParagem(){
    char *nomeParagem;
    int indexPar;
    Carreira *currCar = _carreiras;
    Carreira *currCar2 = _carreiras;
    Ligacao *currLig, *currLig2;
    Ligacao *last;

    leEspacos();
    leNome(&nomeParagem);
    leAteFimDeLinha();

    /* Checks if Paragem exists through the name*/
    indexPar = encontraParagem(nomeParagem);
    if (indexPar == NAO_ENCONTRADO){
        printf("%s: no such stop.\n",nomeParagem);
        free(nomeParagem);
        return;
    }

    /*
    Check through every Carreira if there is connection related to the stop
    we want to eliminate
    */
    for (currCar=_carreiras;currCar != NULL;currCar = currCar->next){
        currLig = currCar->ligacoes;
        while(currLig != NULL){
            /* 
            If first connection, eliminates connection and next connection 
            will be the new head of list
            */
            if(currLig->idOrigem == indexPar){
                if(currLig == currCar->ligacoes){
                    currCar->custoTotal -= currLig->custo;
                    currCar->duracaoTotal -= currLig->duracao;
                    currCar->numLigacoes--;
                    eliminaLigacao(&currCar->ligacoes, currLig);
                    currLig = currCar->ligacoes;
                    continue;
                }
            }
            if(currLig->idDestino == indexPar){
                last = currLig->next;
                if(last == NULL){
                    /* 
                    If last connection, eliminates connection and next connection 
                    will be NULL
                    */
                    currCar->custoTotal -= currLig->custo;
                    currCar->duracaoTotal -= currLig->duracao;
                    currCar->numLigacoes--;
                    eliminaLigacao(&currCar->ligacoes,currLig);
                }
                else{
                    /*
                    If connection in the middle, passes the information from
                    the node after to currLIg node and eliminates the node after
                    currLig
                    */
                    currLig->custo += last->custo;
                    currLig->duracao += last->duracao;
                    currLig->idDestino = last->idDestino;
                    currCar->numLigacoes--;
                    eliminaLigacao(&currCar->ligacoes,last);
                }
            }
            else{
                currLig = currLig->next;
            }
        }
    }

    /*Eliminates Paragem*/
    retiraParagem(&_paragens,indexPar);

    /*
    Through every connection of every Carreira, if index of origin or destination
    is bigger than index of stop we want to eliminate, decrement
    */
    while(currCar2 != NULL){
        currLig2 = currCar2->ligacoes;
        while(currLig2 != NULL){
            if (currLig2->idOrigem > indexPar){
                currLig2->idOrigem--;
            }
            if (currLig2->idDestino > indexPar){
                currLig2->idDestino--;
            }
            currLig2 = currLig2->next;
        }
        currCar2 = currCar2->next;
    }

    free(nomeParagem);
}


/* Função MAIN */

int main() {
    int c;

    do {
        c = getchar();
        switch(c) {
            case 'c':
                carreiras();
                break;
            case 'p':
                paragens();
                break;
            case 'l':
                ligacoes();
                break;
            case 'i':
                intersecoes();
                break;
            case 'q':
                freeSystem(c);
                break;
            case 'a':
                freeSystem(c);
                break;
            case 'r':
                eliminaCarreira();
                break;
            case 'e':
                eliminaParagem();
                break;
            default:
	        /* Ignorar linhas em branco */
	        if (c == ' ' || c == '\t' || c == '\n') break;
        }
    } while (c != 'q');
    return 0;
}