
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <iostream>

using namespace std;

int cb[2], db[2], ce[2], de[2];
char msg[100];


// IDENTIFICA QUAL O MENOR VALOR DAS CHAVES
int identMenor(){
    int menor;
    if (de[0] < cb[0]){
        menor = de[0];
    } else {
        menor = cb[0];
    }
    return menor;
}

// CONVERTE UMA SEQ DE CONJUNTOS DE NUMEROS(INT) EM UMA SEQ DE CONJUNTO DE CHARS
int *numeroPraLetra(int aplicaChave[100]){
    int *chaveEmLetra = new int[100];
    int contConverteLetra = 0;
    for(int i=0; aplicaChave[i] != 0; i++){
        chaveEmLetra[contConverteLetra] = aplicaChave[i];
        // Caso a letra for M (retorne 0)
        if(aplicaChave[i] == -1){
            chaveEmLetra[contConverteLetra] = de[0];
        }
        // Caso precise separacao
        else if (aplicaChave[i] < 10){
            chaveEmLetra[contConverteLetra] *= 10;
            chaveEmLetra[contConverteLetra] += aplicaChave[i+1];
            i++;
        }
        chaveEmLetra[contConverteLetra] += 55;
        printf("%c\t", chaveEmLetra[contConverteLetra]);
        contConverteLetra++;
    }
    return chaveEmLetra;
}

int converteInt(char x){
    int c = x - 55;
    return c;
}

// CONVERTE UM NUMERO EM STRING PARA UM INT
int *letraPraNumero(char mensagem[] , int menor){
    printf("\nMsg em numero: ");
    int temp, cont = 0;
    int *conv = new int[100];
    for(int i=0; mensagem[i] != 0; i++){
        temp = converteInt(mensagem[i]);
        if (temp > menor){
            conv[cont] = temp/10;
            printf("%d\t",conv[cont]);
            cont++;
            conv[cont] = temp%10;
        } else  {
            conv[cont] = temp;
        }
        printf("%d\t",conv[cont]);
        cont++;
    }
    return conv;
}

// CONVERTE UM CONJ DE NUMEROS EM STRING, EM UM INT
int *charPraInt(char mensagem[]){
    int temp, xTemp = 0, mult=1;
    int *conv = new int[100];
    bool erro = false;
    for(int i=0; mensagem[i] != 0; i++){
        if(mensagem[i] == ' '){
            xTemp++;
            mult = 1;
        }
        else if (mensagem[i] == '0'){
            conv[xTemp] = -1;
        }
        else if (mensagem[i] >= 48 && mensagem[i] <= 57){
            conv[xTemp] = conv[xTemp] * mult + mensagem[i] - 48; 
            mult *= 10;
        }
        else{
            printf("\nErro: Insira numeros naturais apenas.\n");
            erro = true;
        }
    }
    
    // testa se valor esta entre 0 e 26 e converte valores '0' para '-1'
    for(int i=0; conv[i] != 0; i++){
        if (conv[i] > 26){
            printf("\nErro: Insira numeros entre 0 e 26.\n");
            erro = true;
        }
    }
    
    if (erro == true){
        conv = 0;
    }
    return conv;
}

char converteLetra(int x){
    char c = x + 55;
    return c;
}

// Aplica uma chave a um conjunto de numero
int aplicaChave(int i, int expo, int mod){
    
    int temp = expo;
    int mod1, cont;
    int aaa = 0;
    int valorFinal=1;
    
    while(temp != 0){
     
        for (int x=1; x<=temp; x*=2){
            // SE x for o maior valor 2^n possivel menor q temp
            if (temp/x == 1){
               
                mod1 = i;
                cont=2;
                //Vai elevando mod1 ao quadr e fznd mod ateh chegar no valor desejado
                while(cont <= x){
                    mod1 = mod1 * mod1;
                    mod1 %= mod;
                    cont = cont*2;
                }
                valorFinal *= mod1;
                temp %= x;
            }
        }
    }
    valorFinal = valorFinal % mod;

    if (valorFinal == 0){
        valorFinal = -1;
    }
    
    return valorFinal;
}

// Aplica uma chave a tds os conjuntos de numeros
int *aplicaArrayChaves(int a[100], int c[2]){
    int *r = new int[100];
    for(int i=0; a[i] != 0; i++){
        r[i] = aplicaChave(a[i], c[1], c[0]);
        if(r[i] == -1){
            printf("0\t");
        }
        else{
            printf("%d\t", r[i]);
        }
    }
    return r;
}

// VERIFICA SE O NUMERO EH OU N PRIMO
bool verificaPrimo(int x){
    bool R = true;
    int i=0, raiz = 0;
    
    // Pega a raiz quadrada inteira de X
    while(raiz == 0){
        if ((i*i < x ) && ((i+1)*(i+1) > x)){
            raiz = i;
        }
        else{
            i++;
        }
    }
    // Testa se eh primo ou n
    for (int j=2; j < raiz*raiz; j++){
        // Vai dividindo X por tds os valores menores q a raiz ao quadrado
        if (x % j == 0){
            R = false;
        }
    }
    return R;
}

// INTERFACE DO PROGRAMA
void interface(){
    int x;
    int a[2], b[2];
    printf("==== Programa de codificacao RSA =====\n");
    printf("[1]: Mandar msg pro banco, assinado\n");
    printf("[2]: Decodificar msg do banco\n");
    printf("Escolha uma das opcoes acima: ");

    bool loop;
    while(true){
        scanf("%d",&x);
    
        loop = false;
        switch(x){
            // CRIPTOGRAFA UMA PALAVRA
            case 1:{
                
                // SCANF DA MSG
                do{
                    printf("\nInsira a mensagem do banco, sem barras de espaco e tudo maiusculo: ");
                    scanf("%s",&msg);
                }while(msg[0] == 0);
                
                printf("\nInsira as duas chaves DE, com espaço entre elas. [Exemplo: '22 7']: ");
                scanf("%d %d", &de[0], &de[1]);
                
                printf("\nInsira as duas chaves CB, com espaço entre elas. [Exemplo: '35 5']: ");
                scanf("%d %d", &cb[0], &cb[1]);
                
                int menor = identMenor();
                char *point = msg;
                
                int *conv = letraPraNumero(point, menor);
                printf("\nChave De na msg: ");
                int *aplicaDe = aplicaArrayChaves(conv, de);
                printf("\nChave Cb na De: ");
                int *aplicaCb = aplicaArrayChaves(aplicaDe, cb);
                
                //IMPRIME MSG A SER ENVIADA PRO BANCO
                printf("\n\nMensagem original: %s",&msg);
                printf("\nMensagem a ser enviada pro banco: ");
                for(int i=0; aplicaCb[i] != 0; i++){
                    if(aplicaCb[i] == -1){
                        printf("0\t");
                    } else {
                        printf("%d\t",aplicaCb[i]);
                    }
                }
    
                break;
            }
            // DESCRIPTOGRAFA UMA SEQ NUMERICA
            case 2: {
                char chaveCodifStr[100];
                int *chaveCodif;
                int j = 0;
                bool erroAoInserir = false;
                
                // SCANF DA MSG
                do{
                    printf("\nInsira a mensagem a ser decodificada, separando os numeros por uma barra de espaco: ");
                    scanf (" %[^\n]s", &chaveCodifStr);
                    chaveCodif = charPraInt(chaveCodifStr);
                }while(chaveCodif == 0);
                
                printf("\nInsira as duas chaves DB, com espaço entre elas. [Exemplo: '35 5']: ");
                scanf("%d %d", &db[0], &db[1]);
                
                printf("\nInsira as duas chaves CE, com espaço entre elas. [Exemplo: '22 3']: ");
                scanf("%d %d", &ce[0], &ce[1]);
                
                printf("\nChave Db na Cb: ");
                int *aplicaDb = aplicaArrayChaves(chaveCodif, db);
                printf("\nChave Ce na Db: ");
                int *aplicaCe = aplicaArrayChaves(aplicaDb, ce);
                
                // IMPRIME DECODIFICACAO DA MSG
                printf("\nDecodificacao da mensagem: ");
                int *msgDecodif = numeroPraLetra(aplicaCe);
                
                break;
            }
            // SELECAO NAO VALIDA
            default: {
                printf("\nErro. Insira um numero valido: ");
                loop = true;
                break;
            }
                
        }
    }
    
}

int main(){
    
    printf("AAAAAA");

    //msg = "AMOR"; // ou 13 24 21 10 27
    de[0] = 22; de[1] = 7; // privada
    cb[0] = 35; cb[1] = 5; // publica
    db[0] = 35; db[1] = 5; // publica
    ce[0] = 22; ce[1] = 3; // privada

    // RODA O MENU
    interface();
    
    // VERIFICA SE EH PRIMO
    bool ehValida = verificaPrimo(19);
    if (ehValida == true){
        //printf("a chave eh valida");
    }
    
    // IDENTIFICA O MENOR VALOR DA ESQ DAS CHAVES
    int menor;
    if (de[0] < cb[0]){
        menor = de[0];
    } else {
        menor = cb[0];
    }
    
    printf("Msg original: %s",msg);
    
    // CONVERTE A MSG EM NUMEROS MENORES Q O MENOR INT
    printf("\nMsg em numero: ");
    int temp, cont = 0, conv[100];
    for(int i=0; msg[i] != 0; i++){
        temp = converteInt(msg[i]);
        if (temp > menor){
            conv[cont] = temp/10;
            printf("%d\t",conv[cont]);
            cont++;
            conv[cont] = temp%10;
            } else  {
            conv[cont] = temp;
        }
        printf("%d\t",conv[cont]);
        cont++;
    }
    
    //  APLICA AS CHAVES
    printf("\nChave De na msg: ");
    int *aplicaDe = aplicaArrayChaves(conv, de);

    printf("\nChave Cb na De: ");
    int *aplicaCb = aplicaArrayChaves(aplicaDe, cb);
    
    printf("\nChave Db na Cb: ");
    int *aplicaDb= aplicaArrayChaves(aplicaCb, db);
    
    printf("\nChave Ce na Db: ");
    int *aplicaCe = aplicaArrayChaves(aplicaDb, ce);


    // CONVERTE CHAVE ce EM LETRA
    int chaveCeEmLetra[100];
    int contConverteLetra = 0;
    printf("\nChave ce em msg: ");
    for(int i=0; aplicaCe[i] != 0; i++){
        chaveCeEmLetra[contConverteLetra] = aplicaCe[i];
        // Caso a letra for M (retorne 0)
        if(aplicaCe[i] == -1){
            chaveCeEmLetra[contConverteLetra] = de[0];
        }
        // Caso precise separacao
        else if (aplicaCe[i] < 10){
            chaveCeEmLetra[contConverteLetra] *= 10;
            chaveCeEmLetra[contConverteLetra] += aplicaCe[i+1];
            i++;
          }
        printf("%c\t", chaveCeEmLetra[contConverteLetra] + 55);
        contConverteLetra++;
    } 
    
    
    //IMPRIME MSG A SER ENVIADA PRO BANCO
    printf("\n\nMensagem original: %s",&msg);
    printf("\nMensagem a ser enviada pro banco: ");
    for(int i=0; aplicaCb[i] != 0; i++){
        if(aplicaCb[i] == -1){
            printf("0\t");
        } else {
            printf("%d\t",aplicaCb[i]);
        }
    }
    printf("\nSenha DE: [%d, %d]", de[0], de[1]);
    
    return 0;
}