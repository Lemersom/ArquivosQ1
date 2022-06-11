/*
Aluno: Lemersom Fernandes Filho     RA: 2410176

UTFPR - CP
AS32F - Tecnicas de Programacao - N12A
P3 - Arquivos - Questao 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
------------------------------
RA.........: 123456
Acertos....: 10
Nota.......: 5,0
Resultado..: Reprovado
------------------------------
*/

struct aluno{
	char ra[10];
	char escolhas[31];
	int acertos;
	float nota;
	char resultado[20];
}typedef aluno;

void ler_aluno(aluno*, FILE*); //le o arquivo e guarda no vetor as informacoes do ra e escolhas dos alunos
void qtd_acertos(aluno*, FILE*); //ve a quantidade de acertos de cada aluno comparando com o gabarito
void ver_resultado(aluno*); //ve se o aluno foi aprovado ou reprovado    >=7.5 aprovado, else reprovado
void gravar_saida(aluno*, FILE*); //gravar dados em um txt resultado
void mostrar_saida(aluno*, FILE*); //exibir os dados gravados no txt resultado


int main(){
	
	FILE *prova;
	FILE *gabarito;
	FILE *resultado;
	
	aluno al[20];
	
	
	ler_aluno(al, prova);
	
	qtd_acertos(al, gabarito);
	
	ver_resultado(al);
	
	gravar_saida(al, resultado);
	
	mostrar_saida(al, resultado);
	
	
	return 0;
}

void ler_aluno(aluno *al, FILE *prova){
	int i = 0, j = 0, e = 0; // i:controlar letras do RA  j: controlar qual aluno é   n: controlar escolhas do aluno
	char c; //letras
	
	prova = fopen("prova.txt", "r");
	if(prova == NULL){
		printf("Erro, nao foi possivel abrir o arquivo: prova.txt\n");
	}
	else{
		while(1){
			c = fgetc(prova);
			if(feof(prova)){    //fim de arquivo
				break;
			}
			if(c == '\n'){   //caso pular de linha, aumenta o j e reseta n e i para 0
				j++;
				e = 0;
				i = 0;
			}else{
				if(c != ';'){
					if(i < 6){        //guardar o RA
						al[j].ra[i] = c;
					}else{            //guardar as escolhas
						al[j].escolhas[e] = c;
						e++;
					}
					i++;
				}
			}
			
		}
	}
		
	fclose(prova);
}

void qtd_acertos(aluno *al, FILE *gabarito){
	int j = 0, e = 0;  // j: controlar qual aluno é    e: controlar escolhas
	char c;  //letras, ou seja, alternativa correta da questao
	
	gabarito = fopen("gabarito.txt", "r");
	if(gabarito == NULL){
		printf("Erro, nao foi possivel abrir o arquivo: gabarito.txt\n");
	}
	else{
		while(j < 10){
			c = fgetc(gabarito);
			if(feof(gabarito)){  //fim de arquivo, pula de aluno e volta a analisar a primeira questao
				al[j].nota = al[j].acertos * 0.5; //calculo da nota
				j++;
				e = 0;
				rewind(gabarito); //volta para o inicio do arquivo
			}
			if(c == '\n'){  //pulou de linha, passou pra proxima questao
				e++;
			}else{
				if(e == 0){
					al[j].acertos = 0;
				}
				if(al[j].escolhas[e] == c){
					al[j].acertos = al[j].acertos + 1;
				}
			}
		}
	}
	fclose(gabarito);
}

void ver_resultado(aluno *al){
	int j = 0;
	
	for(j = 0; j < 10; j++){
		if(al[j].nota >= 7.5){
			strcpy(al[j].resultado, "Aprovado");
		}else{
			strcpy(al[j].resultado, "Reprovado");
		}
	}	
}

void gravar_saida(aluno *al, FILE *resultado){
	int j = 0;
	
	resultado = fopen("resultado.txt", "w");
	if(resultado == NULL){
		printf("Erro, nao foi possivel abrir/criar o arquivo: resultado.txt");
	}
	else{
		for(j = 0; j < 10; j++){
			fprintf(resultado, "------------------------------\nRA.........: %s\nAcertos....: %d\nNota.......: %.1f\nResultado..: %s\n------------------------------\n",
			al[j].ra, al[j].acertos, al[j].nota, al[j].resultado);
		}
	}
	fclose(resultado);
}

void mostrar_saida(aluno *al, FILE *resultado){
	int j = 0;
	char ra[10], result[10], acertos[10], nota[10];
	
	resultado = fopen("resultado.txt", "r");
	if(resultado == NULL){
		printf("Erro, nao foi possivel abrir/criar o arquivo: resultado.txt");
	}
	else{
		for(j = 0; j < 10; j++){
			fscanf(resultado, "------------------------------\nRA.........: %s\nAcertos....: %s\nNota.......: %s\nResultado..: %s\n------------------------------\n",
			ra, acertos, nota, result);
			
			printf("------------------------------\nRA.........: %s\nAcertos....: %s\nNota.......: %s\nResultado..: %s\n------------------------------\n",
			ra, acertos, nota, result);
		}
	}
	fclose(resultado);
}
