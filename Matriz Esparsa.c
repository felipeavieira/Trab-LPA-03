#include <stdio.h>
#include <stdlib.h>

struct bloco
{
    int col;
    int lin;
    int dado;
    struct bloco * baixo;
    struct bloco * lado;
};

struct bloco **matrizlin;//Uma declaracao global dos vetores da matriz.

struct bloco **matrizcol;

int linha=0;//Sera responsavel por quardar o numero de linhas da matriz em uso.

int coluna=0;//Esse guardara as colunas

int busca (int l, int c)//funcao que realiza a busca de um valor e retorna ele.
{
    struct bloco * m = matrizlin[l-1];
    while (m!=NULL&&m->col<=c)
    {
        if (m->col==c)
        {
            return (m->dado);
        }
        m=m->lado;
    }
    return 0;//Se nao for encontrado o valor, entao ele eh zero.
}

void remover (int l, int c)//remove um bloco da lista.
{
    struct bloco *aux1, *aux2, *r;
    aux1=matrizlin[l-1];
    if (aux1->col!=c)
    {
    while (aux1->lado->col!=c)//encontra a posicao do bloco.
    {
        aux1=aux1->lado;
    }
    r=aux1->lado;//r eh o bloco a ser excluido
    aux1->lado=r->lado;//aux1 eh o anterior na linha
    }
    else
    {
        r=aux1;
        matrizlin[l-1]=r->lado;
    }
    aux2=matrizcol[c-1];
    if (aux2->lin!=l)
    {
    while (aux2->baixo->lin!=l)
    {
        aux2=aux2->baixo;//aux2 eh o anterior na coluna
    }
    aux2->baixo=r->baixo;
    }
    else
    {
        matrizcol[c-1]=r->baixo;
    }
    free(r);
}

void removerlista (struct bloco *aux)//remove e libera a memoria de uma lista encadeada.
{
    if (aux==NULL)
    {
        return;
    }
    if (aux->lado!=NULL)
    {
    removerlista(aux->lado);
    }
    free(aux);
}

void removematriz()//remove a matriz e libera a memoria.
{
    int i;
    for (i=0;i<linha;i++)
    {
        removerlista(matrizlin[i]);
    }
    free(matrizlin);
    free(matrizcol);
    linha=0;
}

void add ()
{
    int k,m,n,troca;
    struct bloco *novo, *busca1, *busca2;
    printf("Entre com o indice do valor, no formato (i j) sem os parenteses.\n");
    scanf("%d %d",&m,&n);
    while(m<1||n<1||m>linha||n>coluna)
    {
        printf("Valor invalido! Tente novamente:\n");
        scanf("%d %d",&m,&n);
    }
    printf("Entre com o valor: ");
    scanf("%d",&k);
    if (busca(m,n)!=0)
    {
        remover(m,n);//remove o bloco se ele ja exite
    }
    if (k==0)
    {
        return;//como o bloco foi removido acima, se o valor for zero a funcao acaba aqui.
    }
    novo=(struct bloco *)calloc(1,sizeof(struct bloco));//cria e preenche o bloco.
    novo->dado=k;
    novo->lin=m;
    novo->col=n;
    busca1 = matrizlin[m-1];//encontra a posicao do bloco na linha e o insere.
    busca2 = busca1;
    troca=0;
    if (busca1==NULL)
    {
        matrizlin[m-1]=novo;
        novo->lado=NULL;
        troca=1;
    }
    while(troca==0)
    {
        if(busca2==NULL)
        {
            busca1->lado=novo;
            novo->lado=NULL;
            troca=1;
        }
        else
        {
            if(busca2->col<n)
            {
                busca1=busca2;
                busca2=busca2->lado;
            }
            else
            {
                if (busca2->col>n)
                {
                    if(busca1!=busca2)
                    {
                        busca1->lado=novo;
                        novo->lado=busca2;
                        troca=1;
                    }
                    else
                    {
                        novo->lado= busca1;
                        matrizlin[m-1]=novo;
                        troca=1;
                    }
                }
            }
        }
    }
    busca1 = matrizcol[n-1];//encontra a posicao da coluna e o insere.
    busca2 = busca1;
    troca=0;
    if (busca1==NULL)
    {
        matrizcol[n-1]=novo;
        novo->baixo=NULL;
        troca=1;
    }
    while(troca==0)
    {
        if(busca2==NULL)
        {
            busca1->baixo=novo;
            novo->baixo=NULL;
            troca=1;
        }
        else
        {
            if(busca2->lin<m)
            {
                busca1=busca2;
                busca2=busca2->baixo;
            }
            else
            {
                if (busca2->lin>m)
                {
                    if(busca1!=busca2)
                    {
                        busca1->baixo=novo;
                        novo->baixo=busca2;
                        troca=1;
                    }
                    else
                    {
                        novo->baixo = busca1;
                        matrizcol[n-1]=novo;
                        troca=1;
                    }
                }
            }
        }
    }
}

void create ()//cria uma matriz, somente a estrutura, nao preenchendo-a
{
    printf("\nEntre com o numero de linhas: ");
    scanf("%d",&linha);
    while(linha<1)
    {
        printf("Insira um valor positivo. Tente novamente:\n");
        scanf("%d",&linha);
    }
    printf("\nEntre com o numero de colunas: ");
    scanf("%d",&coluna);
    while(coluna<1)
    {
        printf("Insira um valor positivo. Tente novamente:\n");
        scanf("%d",&coluna);
    }
    matrizlin=(struct bloco **)calloc(linha,sizeof(struct bloco *));
    matrizcol=(struct bloco **)calloc(coluna,sizeof(struct bloco *));
}

void somalinha (int l)//funcao que faz a soma de uma linha, percorrendo a lista
{
    struct bloco * m;
    int soma=0;
    m=matrizlin[l-1];
    while (m!=NULL)
    {
        soma=(soma+m->dado);
        m=m->lado;
    }
    printf("A soma da linha %d eh: %d\n",l,soma);
}

void somacoluna (int c)//funcao que faz a soma de uma coluna, percorrendo a lista
{
    struct bloco * m;
    int soma=0;
    m=matrizcol[c-1];
    while (m!=NULL)
    {
        soma=(soma+m->dado);
        m=m->baixo;
    }
    printf("A soma da coluna %d eh: %d\n",c,soma);
}

int menu ()//menu principal.
{
    int i,n;
    printf("\nO que deseja fazer agora?\n");
    printf("1. Remover matriz.\n2. Consultar posicao.\n3. Atribuir valor.\n4. Soma de linha.\n5. Soma de coluna.\n6. Sair.\nOpcao: ");
    scanf("%d",&i);
    printf("\n");
    switch (i)
    {
    case 1:
        {
            removematriz();
            return 0;
        }
    case 2:
        {
            int l,c;
            printf("Entre com a posicao a ser buscada, no formato (i j), sem os parenteses.\n");
            scanf("%d %d",&l,&c);
            while(l>linha||c>coluna)
            {
                printf("Valor invalido. Tente novamente:\n");
                scanf("%d %d",&l,&c);
            }
            printf("O valor desta posicao eh : %d\n", busca(l,c));
            return 0;
        }
    case 3:
        {
            printf("Com quantos valores voce deseja entrar?\n");
            scanf("%d",&n);
            while(n<1)
            {
                printf("Insira um valor positivo. Tente novamente:\n");
                scanf("%d",&n);
            }
            for(i=0;i<n;i++)
            {
                add();
            }
            return 0;
        }
    case 4:
        {
            printf("Qual linha deseja somar?\n");
            scanf("%d",&n);
            while(n<1||n>linha)
            {
                printf("Valor invalido! Tente novamente:\n");
                scanf("%d",&n);
            }
            somalinha(n);
            return 0;
        }
    case 5:
        {
            printf("Qual coluna deseja somar?\n");
            scanf("%d",&n);
            while(n<1||n>coluna)
            {
                printf("Valor invalido! Tente novamente:\n");
                scanf("%d",&n);
            }
            somacoluna(n);
            return 0;
        }
    case 6:
        {
            return 1;
        }
    default:
        {
            printf("Ocorreu um erro, tente novamente.");
            return 0;
        }
    }

}
int menucreate ()//Menu utilizado quando nao existe uma matriz criada.
{
    int i,n;
    printf("\nO que deseja fazer agora?\n");
    printf("1. Criar matriz.\n2. Sair.\nOpcao: ");
    scanf("%d",&i);
    printf("\n");
    switch(i)
    {
    case 1:
        {
            printf("\nInicializando matriz esparsa.\n");
            create();
            printf("Com quantos valores voce deseja entrar?\n");
            scanf("%d",&n);
            while(n<1)
            {
                printf("Insira um valor positivo. Tente novamente:\n");
                scanf("%d",&n);
            }
            for(i=0;i<n;i++)
            {
                add();
            }
            return 0;
        }
    case 2:
        {
            return 1;
        }
    default:
        {
            printf("Ocorreu um erro, tente novamente.");
            return 0;
        }
    }
}

int main ()
{
    int i,j,n;
    j=0;
    printf("Inicializando matriz esparsa.\n");
    create();//cria uma matriz inicial.
    printf("\nCom quantos valores voce deseja entrar?\n");
    scanf("%d",&n);
    while(n<1)
    {
        printf("Insira um valor positivo. Tente novamente:\n");
        scanf("%d",&n);
    }
    for(i=0;i<n;i++)
    {
        add();//preenche
    }
    while(j==0)//mantem o menu aberto ate que o usuario saia.
    {
        if (linha==0)
        {
            j=menucreate();
        }
        else
        {
        j=menu();
        }
    }
    if (linha!=0)
    {
    removematriz();
    }
    return 0;
}
