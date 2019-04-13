#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAXRETSTRING 1050
#define MAXRET 70

int main() {
	int i = 0;
	int j, k;
	char *dados = NULL;
	char nome[30];
	char arqNome[30] = {""};
	char opcao[10];
	char todosRet[MAXRETSTRING];
	char retPintado[MAXRET][10];
	int index;
	char umRet[10];
	
	for(i = 0; i < 70; i++){
		strcpy(retPintado[i], "");
	}
	
	FILE *arqPiet;
	
	dados = getenv("QUERY_STRING");
	
	if (sscanf(dados, "nome=%[^&]&opcao=%[^&]&%s", nome, opcao, todosRet) == 3) {
		strcat(arqNome, "jogo-Piet-");
		strcat(arqNome, nome);
		strcat(arqNome, ".txt");
		
		arqPiet = fopen(arqNome, "r");
		fscanf(arqPiet, "Name=%[^\n]\n", nome);
		
		while (!feof(arqPiet)) {
			fscanf(arqPiet, "%i=%[^\n]\n", &index, umRet);
			strcpy(retPintado[index], umRet);
		}
		i = 0;
		char *pch = strtok(todosRet, "=on&ret");
		char retPint[MAXRET][10];
		while (pch != NULL) {
			strcpy(retPint[i], pch);
			i++;
			pch = strtok(NULL, "=on&ret");
		}
		
		for (j = 0; j < i; j++) {
			k = atoi(retPint[j]);
			strcpy(retPintado[k], opcao);
		}
		
		arqPiet = freopen(arqNome, "w", arqPiet);	
		fprintf(arqPiet, "Name=%s\n", nome);
		for (i = 0; i < MAXRET; i++) {
			if (strcmp(retPintado[i], ""))
				fprintf(arqPiet, "%i=%s\n", i, retPintado[i]);
		}
		
		fclose(arqPiet);
		
	} else if (sscanf(dados, "nome=%s", nome) == 1) {
		strcat(arqNome, "jogo-Piet-");
		strcat(arqNome, nome);
		strcat(arqNome, ".txt");
		
		arqPiet = fopen(arqNome, "w");
		fprintf(arqPiet, "Name=%s\n", nome);
		
		fclose(arqPiet);
	}
	
	printf("%s%c%c\n","Content-Type:text/html;charset=UTF-8",13,10);
	printf("<html>");
		printf("<head>");
			printf("<meta charset=\"utf-8\">");
			printf("<title>Jogando...</title>");
			printf("<link rel=\"stylesheet\" href=\"../style.css\">");
		printf("</head>");
		printf("<body>");
			printf("<h1>Jogo de Pintar - Piet Mondrian</h1>");
			perror("Nada");
			printf("<form action=\"mondrian.cgi\" method=\"get\">");
				printf("<input type=\"hidden\" name=\"nome\" value=\"%s\">", nome);
				printf("<select name=\"opcao\">");
				printf("<option class=\"s1\" value=\"black\">Preto</option>");
				printf("<option class=\"s2\" value=\"red\">Vermelho</option>");
				printf("<option class=\"s3\" value=\"yellow\">Amarelo</option>");
				printf("<option class=\"s4\" value=\"blue\">Azul</option>>");
				printf("<option class=\"s5\" value=\"white\">Branco</option>");
				printf("</select>");
				printf("<input type=\"submit\" value=\"Pintar!\"> </input>");
				printf("<div id=\"desenho\">");
					for (i = 0; i < 70; i++) {
						printf("<input type=\"checkbox\" id=\"%d\" name=\"ret%d\">", i, i);
						printf("<label for=\"%d\"", i);
						if (strcmp(retPintado[i], ""))
							printf(" style=\"background-color: %s\"", retPintado[i]);
						printf("></label>");
					}
				printf("</div>");
			printf("</form>");
		printf("</body>");
	printf("</html>");
	
	return 0;
}
