#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rep(i,a,b) for(int i=a;i<b;i++)

#define max(a,b) a > b ? a : b

#define LIN 10 
#define COL 6

void get_start(int mat[][COL], int* n) {

	int aux, start;

	aux = start = -1;

	rep(i, 0, LIN) {
		aux = start;
		start = max(start, mat[i][0]);
		if (aux != start) {
			*n = i;
		}
	}

	return;
}

void get_matrix(int m[][COL]) {

	rep(i, 0, LIN) {
		rep(j, 0, COL) {
			if (m[i][j] != -1) printf("%2d ", m[i][j]);
			else printf("%2c ", 'x');
		}
		printf("\n");
	}
	printf("\n");

	return;
}

void get_path(int* path) {

	printf("Inicio: (%d, 0)\nCaminho: ", path[0]);
	rep(i, 1, COL) {
		if (path[i] == -1) printf("%c ", '^');
		else if (path[i] == 1) printf("%c ", 'v');
		else printf("%c ", '>');
	}
	printf("\n");

	return;
}

int solve(int mat[][COL], int result[][COL], int* path) {

	int a, b, c;
	int n, m;

	m = 0;

	get_start(mat, &n);

	int ret = mat[n][m];

	result[n][m] = mat[n][m];

	//linha inicial
	path[0] = n;

	while (++m < COL) {

		//direita e cima
		a = (n - 1 > -1) ? mat[n - 1][m] : -1;
		//direita
		b = mat[n][m];
		//direita e baixo
		c = (n + 1 < LIN) ? mat[n + 1][m] : -1;

		//direita e cima é a "melhor opção"
		if (a >= b && a >= c) {
			ret += a;
			n--;
			path[m] = -1;
		}
		else if (b >= a && b >= c) {
			ret += b;
			path[m] = 0;
		}
		else {
			ret += c;
			n++;
			path[m] = 1;
		}

		result[n][m] = mat[n][m];
	}

	get_matrix(mat);
	get_path(path);
	get_matrix(result);

	return ret;
}

int main() {

	int mat[][COL] = {
		{1, 3, 2, 7, 7, 1} ,
		{3, 1, 1, 0, 0, 3} ,
		{3, 1, 1, 0, 0, 3} ,
		{3, 4, 1, 0, 0, 3} ,
		{9, 4, 2, 0, 0, 3} ,
		{3, 1, 1, 0, 0, 3} ,
		{3, 1, 1, 0, 0, 3} ,
		{3, 1, 1, 0, 0, 3} ,
		{2, 7, 4, 5, 2, 4} ,
		{4, 6, 0, 2, 9, 6}
	};

	int result[LIN][COL];
	int path[COL] = { 0 };
	memset(result, -1, LIN * COL * sizeof(int));

	printf("Resultado: %d\n", solve(mat, result, path));

	return 0;
}
