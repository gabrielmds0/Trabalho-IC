#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int icliente=0, iconta=0, itransacao=0;

FILE* fconta;

struct cliente{
        int codigo;
        char nome[200];
        char CPF[20];
        char telefone[20];
        char endereco[200];
    };
    
struct conta{
         char agencia[10];
         char numconta[12];
         char cliente[200];
         float saldo;
     };

     
     struct transacoes{
         char tipo[10];
         float valor;
         int data;
         char conta[12];
         char descricao[100];
     };
     
    struct cliente clientes[100];
    struct conta contas[200];
    struct transacoes transacao[1000];
    struct conta contasec[200];
     
void menu1(){
    char comando1;
    printf("=============== Bem vindo! =================\n");
    printf("Digite um comando para prosseguir:\nC – Gerenciar Clientes\nT – Gerenciar Contas\nS – Sair\n");
    
}
void menu2(){
    printf("============ Gerenciar Clientes ============\nDigite um comando para prosseguir:\n");
    printf("C – Cadastrar um cliente\nL – Listar todos os clientes cadastrados\nB - Buscar cliente já cadastrado\n");
    printf("A - Atualizar um cliente cadastrado\nE – Excluir um cliente cadastrado\nS – Sair\n");
}

void menu3(){
    printf("Digite um comando para prosseguir:\nR – Listagem de todas as contas cadastradas.\n");
    printf("C – Cadastrar uma conta para um cliente.\nL – Listar todas as contas de um cliente.\n");
    printf("W – Realizar um saque em uma conta.\nD – Realizar um depósito em uma conta.\nT – Realizar transferência entre contas.\n");
    printf("E – Exibir extrato de uma conta.\nS – Sair\n");
}

void Cadastrar(FILE* fp){
    system("clear");
    fseek(fp, 0, SEEK_END);
    char cpf_teste[20];
    int codigo_teste;
    int j = 0;
    
    char a;
    
    
    printf("Insira seu código\n");
    scanf("%d", &codigo_teste);
    
    for(j = 0; j<icliente; j++){
        if(clientes[j].codigo == codigo_teste){
            printf("Cliente já cadastrado\n");
            return;
        }
    }
        clientes[icliente].codigo = codigo_teste;
    

    
    scanf("%c", &a);
    printf("Insira seu nome:\n");
    scanf("%[^\n]", clientes[icliente].nome);
    
    
    printf("Insira seu CPF/CNPJ\n");
    scanf("%s", cpf_teste);
    for(j = 0; j<icliente; j++){
        if((strcmp(clientes[j].CPF, cpf_teste)) == 0){
            printf("Cliente já cadastrado\n");
            return;
        }
    }
    
    strcpy(clientes[icliente].CPF, cpf_teste);

    
   
    
    
    printf("Insira seu telefone\n");
    scanf("%s", clientes[icliente].telefone);
    
    scanf("%c", &a);
    printf("Insira seu endereço\n");
    scanf("%[^\n]", clientes[icliente].endereco);
    
    fprintf(fp,"%d\n%s\n%s\n%s\n%s\n",clientes[icliente].codigo, clientes[icliente].nome, clientes[icliente].CPF, clientes[icliente].telefone, clientes[icliente].endereco);
    icliente++;
    menu1();

    
}



void Listar(){
    FILE* fp =fopen("Cadastro.txt", "r");
    int j = 0;
    
    system("clear");
    for(j = 0; j<icliente; j++){
        printf("%s\n", clientes[j].nome);
    }
    menu1();
    
}

void Excluir(){
    char auxNome[200];
    char auxEnd[200];
    int auxcodigo;
    char auxtelefone[20];
    char auxCPF[20];
    int codigo_teste;
    int k = 0;
    int j = 0;
    FILE* fp = fopen("Cadastro.txt", "r+");
    
    
    system("clear");
    
        printf("Insira o codigo do cliente que deseja excluir:\n");
        scanf("%d", &codigo_teste);
        for(j = 0; j<icliente; j++) {
            if(clientes[j].codigo == codigo_teste){
                for(k = j; k<(icliente-1); k++){
                    auxcodigo = clientes[k+1].codigo;
                    clientes[k].codigo = auxcodigo;
                    
                    strcpy(auxNome, clientes[k+1].nome);
                    strcpy(clientes[k].nome, auxNome);
                    
                    strcpy(auxCPF, clientes[k+1].CPF);
                    strcpy(clientes[k].CPF, auxCPF);  

                    
                    strcpy(auxtelefone, clientes[k+1].telefone);
                    strcpy(clientes[k].telefone, auxtelefone);
                    

                    strcpy(auxEnd, clientes[k+1].endereco);
                    strcpy(clientes[k].endereco, auxEnd);
                   

                    
                }
                icliente--;
                break;
            }
            
        }
        fclose(fp);
        remove("Cadastro.txt");
        fp = fopen("Cadastro.txt", "w");
        for(j=0; j<icliente; j++){
            
            fprintf(fp,"%d\n%s\n%s\n%s\n%s\n",clientes[j].codigo, clientes[j].nome, clientes[j].CPF, clientes[j].telefone, clientes[j].endereco);
        }
    printf("O cliente com seguinte código foi excluido:%d\n", codigo_teste);
    menu1();
}

    
        


void Atualizar(){
    
    int a;
    int codigo_teste;
    char cpf_teste[20];
    int j = 0;
    
    
    
    FILE* fp = fopen("Cadastro.txt", "w");
    system("clear");
    printf("Digite 1 para inserir código ou 2 para inserir CPF\n");
    scanf("%d", &a);
    if(a == 1){
        printf(" Digite seu código:\n");
        scanf("%d", &codigo_teste);
        for(j = 0; j<icliente; j++){
            if(clientes[j].codigo == codigo_teste){
                printf("Insira os novos dados:\n");
                printf("Insira seu nome:\n");
                scanf("%*c");
                scanf("%[^\n]", clientes[j].nome);
    
    
                printf("Insira seu CPF/CNPJ\n");
                scanf("%s", cpf_teste);
            
             
    
                strcpy(clientes[j].CPF, cpf_teste);

                printf("Insira seu telefone\n");
                scanf("%s", clientes[j].telefone);
    
                scanf("%*c");
                printf("Insira seu endereço\n");
                scanf("%[^\n]", clientes[j].endereco);
    
                fprintf(fp,"%s\n%s\n%s\n%s\n",clientes[j].nome, clientes[j].CPF, clientes[j].telefone, clientes[j].endereco);
                system("clear");
                menu1();
                
            
            
            }
        }
        printf("Cliente não encontrado");
        menu1();
        }
    if(a == 2){
        printf(" Digite seu CPF/CNPJ:\n");
        scanf("%s", cpf_teste);
        for(j = 0; j<icliente; j++){
            if(clientes[j].CPF == cpf_teste){
                printf("Insira os novos dados:\n");
                printf("Insira seu nome:\n");
                scanf("%[^\n]", clientes[j].nome);
    
    
                printf("Insira seu CPF/CNPJ\n");
                scanf("%s", cpf_teste);
            
                strcpy(clientes[j].CPF, cpf_teste);

                printf("Insira seu telefone\n");
                scanf("%s", clientes[j].telefone);
    
                scanf("%*c");
                printf("Insira seu endereço\n");
                scanf("%[^\n]", clientes[j].endereco);
    
                fprintf(fp,"%s\n%s\n%s\n%s\n",clientes[j].nome, clientes[j].CPF, clientes[j].telefone, clientes[j].endereco);
                
               menu1();
                return;
            
            
            }
        
    }
        printf("Cliente não encontrado");
        menu1();
        return;
        
    }
    
}



void Buscar(){
    int a;
    char cliente_teste[200];
    char cpf_teste[20];
    int codigo_teste;
    int j = 0;
    int teste = 0;
    
    system("clear");
    
    printf("Digite 1 para inserir nome, 2 para CPF e 3 para código.\n");
    scanf("%d", &a);
    if(a == 1){
        printf("Insira seu nome:\n");
        scanf("%s", cliente_teste);
        for(j = 0; j<icliente; j++){
            if((strcmp(clientes[j].nome, cliente_teste)) == 0){
                printf("%s\n", clientes[j].nome);
                printf("%d\n", clientes[j].codigo);
                printf("%s\n", clientes[j].CPF);
                printf("%s\n", clientes[j].telefone);
                printf("%s\n", clientes[j].endereco);
                teste++;
            
            }  
            
            
        }
        if(teste == 0){
        printf("Cliente não encontrado\n");
        
        }

        menu1();
        return;
    }
    
    if(a == 2){
        printf("Insira seu CPF/CNPJ:\n");
        scanf("%s", cpf_teste);
        for(j = 0; j<icliente; j++){
            if((strcmp(clientes[j].CPF, cpf_teste)) == 0){
                printf("%s\n", clientes[j].nome);
                printf("%d\n", clientes[j].codigo);
                printf("%s\n", clientes[j].CPF);
                printf("%s\n", clientes[j].telefone);
                printf("%s\n", clientes[j].endereco);
                teste++;
            }
        
        
        }
        if(teste == 0){
    printf("Cliente não encontrado\n");
        }
        
        menu1();
        return;
    }
    if(a == 3){
        printf("Insira seu código:\n");
        scanf("%d", &codigo_teste);
        for(j = 0; j<icliente; j++){
            if(clientes[j].codigo == codigo_teste){
                printf("%s\n", clientes[j].nome);
                printf("%d\n", clientes[j].codigo);
                printf("%s\n", clientes[j].CPF);
                printf("%s\n", clientes[j].telefone);
                printf("%s\n", clientes[j].endereco);
                teste++;
                }
        }
        if(teste == 0){
        printf("Cliente não encontrado\n");
    
        }
        
        menu1();
        return;
    }
}




void Cadastrar_conta(){
    
    char a;
    int j = 0; int k = 0;
    char cliente_teste[200];
    char agencia_teste[10];
    char numconta_teste[12];
    
    system("clear");
    
    printf("Insira sua agencia:\n");
    scanf("%*c");
    scanf("%[^\n]", agencia_teste);
    printf("Insira seu numero de conta:\n");
    scanf("%*c");
    scanf("%[^\n]", numconta_teste);
     for(j = 0; j<iconta; j++){
        if(((strcmp(contas[j].agencia, agencia_teste)) == 0) && ((strcmp(contas[j].numconta, numconta_teste)) == 0 )){
            printf("Cliente já cadastrado\n");
            return;
        }
        
    }
     strcpy(contas[iconta].agencia, agencia_teste);
     strcpy(contas[iconta].numconta, numconta_teste);
     strcpy(transacao[k].conta, contas[iconta].numconta);
  
    
    
    printf("Insira seu nome:\n");
    scanf("%*c");
    scanf("%[^\n]", cliente_teste);
    strcpy(contas[iconta].cliente, cliente_teste);
         
    

    scanf("%*c");
    contas[iconta].saldo = 0;
    
    fprintf(fconta,"%s\n%s\n%s\n%f\n",contas[iconta].cliente, contas[iconta].agencia, contas[iconta].numconta, contas[iconta].saldo);
    iconta++;
    menu1();  
    
}

void ListarConta(){
    FILE* fp =fopen("CadastroConta.txt", "r");
    int j = 0;
    
    system("clear");
    
    for(j = 0; j<iconta; j++){
        fscanf(fp, "%[^\n]", contas[j].cliente);
        fscanf(fp, "%*c");
        fscanf(fp, "%[^\n]", contas[j].agencia);
        fscanf(fp, "%*c");
        fscanf(fp, "%[^\n]", contas[j].numconta);
        fscanf(fp, "%*c");
        fscanf(fp, "%f", &contas[j].saldo);
        fscanf(fp, "%*c");
      
        }
    for(j = 0; j<iconta; j++){
        printf("%.2f - %s, Agencia%s, Numero de Conta:%s ",contas[j].saldo, contas[j].cliente, contas[j].agencia, contas[j].numconta);
    }
    //system("clear");
    menu1();
    
}

void Deposito(FILE* fp){
    int j = 0;
    char numconta_teste[12];
    char agencia_teste[10];
    float deposito_teste;
    int dia, mes;
    char tipo[10];
    
    system("clear");
    
    
    printf("Insira a data do depóito, sua agencia e numero de conta\n");
    scanf("%d/%d\n%s\n%s",&dia, &mes, agencia_teste, numconta_teste);
    scanf("%*c");
    for(j = 0; j<iconta; j++){
        if((strcmp(contas[j].agencia, agencia_teste)) == 0 && (strcmp(contas[j].numconta, numconta_teste)) == 0){
            strcpy(transacao[itransacao].tipo, "CREDITO");
            strcpy(transacao[itransacao].conta,numconta_teste);
            printf("Insira uma descricao da transação:\n");
            fflush(stdin);
            scanf("%[^\n]", transacao[itransacao].descricao);
            printf("Insira o valor a ser depositado:\n");
            scanf("%f", &deposito_teste);
            contas[j].saldo += deposito_teste;
            transacao[itransacao].valor = deposito_teste;
            printf("Seu saldo atual é:\n");
            printf("%.2f\n", contas[j].saldo);
            fprintf(fp,"%s %s\n", contas[j].agencia, contas[j].numconta);
            fprintf(fp, "Agencia:%s; Numero de Conta:%s; Cliente:%s; Tipo:DEBITO; Movimentação:+%.2f; Data: %d/%d; %d; Descrição:%s\n", contas[j].agencia, contas[j].numconta, contas[j].cliente, transacao[itransacao].valor, dia, mes, j, transacao[itransacao].descricao );

        }
    }
    itransacao++;
    menu1();
    
}

void ListagemConta(){
    FILE* fp = fopen("CadastroConta.txt", "r");
    char cliente[200];
    int a;
    int j = 0;
    char CPF[20];
    char cpf_teste[20];
    int codigo_teste;
    int k;
    int teste = 0;
    
    system("clear");
    
    printf("Digite 1 para inserir código ou 2 para inserir CPF/CNPJ\n");
    scanf("%d", &a);
    if(a == 1){
        printf("Insira seu código:\n");
        scanf("%d", &codigo_teste);
        for(j = 0; j<icliente; j++){
            if(codigo_teste == clientes[j].codigo){
                strcpy(cliente, clientes[j].nome);
                for(k = 0; k<iconta; k++){
                    if((strcmp(cliente, contas[k].cliente)) == 0){
                        printf("%f - %s, Agencia:%s, Numero de Conta:%s \n",contas[k].saldo, contas[k].cliente, contas[k].agencia, contas[k].numconta);
                    }
                }
                teste ++;
                
            }   
        }
        if(teste == 0)
        	printf("Cliente não encontrado\n");
    }
    if(a == 2){
         printf("Insira seu CPF:\n");
        scanf("%s", cpf_teste);
        for(j = 0; j<icliente; j++){
            if((strcmp(cpf_teste, clientes[j].CPF)) == 0){
                strcpy(cliente, clientes[j].nome);
                for(k = 0; k<iconta; k++){
                    if((strcmp(cliente, contas[k].cliente)) == 0){
                        printf("%f - %s, Agencia%s, Numero de Conta:%s \n",contas[k].saldo, contas[k].cliente, contas[k].agencia, contas[k].numconta);
                    }
                }
                teste ++;
                
            }
            else{
                printf("Cliente não encontrado\n");
            }
            
        }
        
    }
    
    if(teste == 0){
        printf("Cliente não encontrado\n");
        
    }
    menu1();
}

void Saque(FILE* fp){
    int j = 0;
    char numconta_teste[12];
    char agencia_teste[10];
    int deposito_teste;
    int dia, mes;
    char tipo[10];
    int notas200, notas100, notas50, notas20, notas10, notas5, notas2;
    
    system("clear");
    
    printf("Insira a data do saque, sua agencia e numero de conta\n");
    scanf("%d/%d\n%s\n%s",&dia, &mes, agencia_teste, numconta_teste);
    scanf("%*c");
    for(j = 0; j<iconta; j++){
        if((strcmp(contas[j].agencia, agencia_teste)) == 0 && (strcmp(contas[j].numconta, numconta_teste)) == 0){
            printf("R$%f - %s, Agencia%s, Numero de Conta:%s\n",contas[j].saldo, contas[j].cliente, contas[j].agencia, contas[j].numconta);
            printf("Insira uma descricao da transação:\n");
            scanf("%[^\n]", transacao[itransacao].descricao);
            strcpy(transacao[itransacao].conta,numconta_teste);
            scanf("%*c");
            printf("Insira o valor a ser sacado:\n");
            scanf("%d", &deposito_teste);
            if(deposito_teste <= contas[j].saldo){
            contas[j].saldo -= deposito_teste;
            transacao[itransacao].valor = deposito_teste;
            strcpy(transacao[itransacao].tipo , "DEBITO");
            notas200 = deposito_teste/200;
            notas100 = (deposito_teste%200)/100;
            notas50 = ((deposito_teste%200)%100)/50;
            notas20 = (((deposito_teste%200)%100)%50)/20;
            notas10 = ((((deposito_teste%200)%100)%50)%20)/10;
            notas5 = (((((deposito_teste%200)%100)%50)%20)%10)/5;
            notas2 = ((((((deposito_teste%200)%100)%50)%20)%10)%5)/2;
            if(notas200 != 0){
                printf("Foram entregues %d nota(s) de 200 reais\n", notas200);
                
                }
            if(notas100 != 0){
                printf("Foram entregues %d nota(s) de 100 reais\n", notas100);
                
                }
            if(notas50 != 0){
                printf("Foram entregues %d nota(s) de 50 reais\n", notas50);
                
                }
            if(notas20 != 0){
                printf("Foram entregues %d nota(s) de 20 reais\n", notas20);
                
                }
            if(notas10 != 0){
                printf("Foram entregues %d nota(s) de 10 reais\n", notas10);
                
                }
            if(notas5 != 0){
                printf("Foram entregues %d nota(s) de 5 reais\n", notas5);
                
                }
            if(notas2 != 0){
                printf("Foram entregues %d nota(s) de 2 reais\n", notas2);
                
                }
            printf("Seu saldo atual é:\n");
            printf("%.2f\n", contas[j].saldo);
            fprintf(fp,"%s %s\n", contas[j].agencia, contas[j].numconta);
            fprintf(fp, "Agencia:%s; Numero de Conta:%s; Cliente:%s; Tipo:DEBITO; Movimentação:-%.2f; Data: %d/%d; %d; Descrição:%s\n",contas[j].agencia, contas[j].numconta, contas[j].cliente, transacao[itransacao].valor, dia, mes, j, transacao[itransacao].descricao );
            
            }
            else{
                printf("Saldo insuficiente\n");
            }
        }
        
    }
    itransacao++;
    menu1();
    
}

void Transferencia(FILE* fp, FILE* fconta){
    char numconta_teste[12];
    char agencia_teste[10];
    char numconta_teste2[12];
    char agencia_teste2[10];
    int deposito_teste;
    char tipo[10];
    int k = 0;
    int j = 0;
    int dia;
    int mes;
    
    system("clear");
    
    printf("Insira agencia da conta que enviará o dinheiro:\n");
    scanf("%s", agencia_teste);
    scanf("%*c");
    printf("Insira o numero de conta da conta que enciará o dinheiro:\n");
    scanf("%s", numconta_teste);
    scanf("%*c");
    for(j = 0; j<iconta; j++){
        if((strcmp(contas[j].agencia, agencia_teste)) == 0 && (strcmp(contas[j].numconta, numconta_teste)) == 0){
            printf("R$%f - %s, Agencia:%s, Numero de Conta:%s\n",contas[j].saldo, contas[j].cliente, contas[j].agencia, contas[j].numconta);
            printf("Insira agencia da conta que recebera o dinheiro:\n");
            scanf("%s", agencia_teste2);
            scanf("%*c");
            printf("Insira o numero de conta da conta que receberá o dinheiro:\n");
            scanf("%s", numconta_teste2);
            scanf("%*c");
            for(k = 0; k<iconta; k++){
              
                if((strcmp(contas[k].agencia, agencia_teste2)) == 0 && (strcmp(contas[k].numconta, numconta_teste2)) == 0){
                    printf("Insira a data da transferência:\n");
                    scanf("%d/%d", &dia, &mes);
                    printf("Insira o tipo da transferência(CREDITO OU DEBITO):\n");
                    scanf("%*c");
                    scanf("%[^\n]", transacao[itransacao].tipo);
                    printf("Insira uma descricao da transação:\n");
            	    scanf("%*c");
            	    scanf("%[^\n]", transacao[itransacao].descricao);
                    strcpy(transacao[itransacao].conta, numconta_teste);
                    printf("Insira o valor a ser transferido:\n");
                    scanf("%d", &deposito_teste);
                    if(deposito_teste <= contas[j].saldo){
                        contas[j].saldo -= deposito_teste;
                        contas[k].saldo += deposito_teste;
                        transacao[itransacao].valor = deposito_teste;
                            fprintf(fp,"%s %s\n", contas[j].agencia, contas[j].numconta);
                            fprintf(fp, "Transferencia da conta %s-%s; %d/%d\n", contas[j].agencia, contas[j].numconta, dia, mes);
                        
                        for(j = 0; j<iconta;j++){ 
                            fscanf(fconta, "%[^\n]", contas[j].cliente);
                            fscanf(fconta, "%*c");
                            fscanf(fconta, "%[^\n]", contas[j].agencia);
                            fscanf(fconta, "%*c");
                            fscanf(fconta, "%[^\n]", contas[j].numconta);
                            fscanf(fconta, "%*c");
                            fscanf(fconta, "%f", &contas[j].saldo);
                            fscanf(fconta, "%*c");
                            
                        }
                        remove("CadastroConta.txt");
                        fconta = fopen("CadastroConta.txt", "w");
                        for(j = 0; j<iconta; j++){
                            fprintf(fconta,"%s\n%s\n%s\n%f\n",contas[j].cliente, contas[j].agencia, contas[j].numconta, contas[j].saldo);
                        }
                    }
                }
            }
        }
    }
    itransacao++;
    menu1();
}


void Extrato2()
{
   system("clear"); 
   fflush(stdin); 
    int j = 0, k = 0;
    char agencia[10], numconta[12]; 

    printf("Digite a agencia: \n"); 
    scanf("%s", agencia); 
    printf("Digite o numero da conta: \n"); 
    fflush(stdin); 
    scanf("%s", numconta);
    scanf("%*c");
    for (j = 0; j<iconta; j++){ 
         if(((strcmp(contas[j].agencia, agencia)) == 0) && ((strcmp(contas[j].numconta, numconta)) == 0 )){ 
            printf("\n==============Dados da Conta==============\n"); 
            printf("Nome: %s\n", contas[j].cliente); 
            printf("Numero da Conta: %s\n", contas[j].numconta); 
            printf("Saldo da conta: %.2lf\n", contas[j].saldo); 
           
 
            for ( k = 0; k<itransacao; k++ ) { 
                if((strcmp(contas[j].numconta, transacao[k].conta)) == 0) { 
                    printf("=============================================\n"); 
                    printf("Tipo: %s\n", transacao[k].tipo); 
                    printf("Descricao: %s\n", transacao[k].descricao); 
                    printf("Valor: %.2f\n", transacao[k].valor); 
                    printf("=============================================\n");
                 } 
            } 
        }
    }
    menu1();
}





int main()
{
    char comando1;
    char comando2;
    char comando3;
    char comando4;
    
    
    menu1();
    fconta = fopen("CadastroConta.txt", "w");
    FILE* fcads = fopen("Cadastro.txt", "w");
    FILE* fp = fopen("Transações.txt", "w+");
    
    while((scanf("%c", &comando1)) && comando1!='s'){
        
    if(comando1 == 'C' || comando1 =='c'){
        menu2();
        scanf("\n%c", &comando3);
        if(comando3 == 'C' || comando3 == 'c'){
            Cadastrar(fcads);
        }
        else if(comando3 == 'L' || comando3 == 'l'){
            Listar();
        }
        else if(comando3 == 'A' || comando3 == 'a'){
            Atualizar();
            
        }
        else if(comando3 == 'B' || comando3 == 'b'){
            Buscar();
            
        }
        else if(comando3 == 'E' || comando3 == 'e'){
            Excluir();
        } 
        else if(comando3 == 'S' || comando3 == 's'){
            return 0;
        }
    }
    
    else if(comando1 == 'T' || comando1 == 't'){
        menu3();
        scanf("\n%c", &comando4);
        if(comando4 == 'C' || comando4 == 'c'){
            Cadastrar_conta();
        }
        else if(comando4 == 'r' || comando4 == 'R'){
            ListarConta();
            
        }
        else if(comando4 == 'D' || comando4 == 'd'){
            Deposito(fp);
        }
         else if(comando4 == 'W' || comando4 == 'w'){
            Saque(fp);
        }
         else if(comando4 == 'L' || comando4 == 'l'){
            ListagemConta();
        }
        else if(comando4 == 'T' || comando4 == 't'){
            Transferencia(fp, fconta);
        }
        else if(comando4 == 'E' || comando4 == 'e'){
            Extrato2();
        }
            
    }
    
    }
}
    
