#include "levenshtein.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int calc_levenshtein_general(const char* src, const char* dst) {
	/*
	mathematically, levenshtein distance is:
	i = len(a); j = len(b);
					{ max(i,j)								if min(i,j)==0,
					{					else
	lev_ab (i,j) =	{		{ lev_ab(i-1,j) + 1				(Del)
					{	 min{ lev_ab(i,j-1) + 1				(Ins)
							{ lev_ab(i-1,j-1) + ind(i,j)	(Match(+0), Replace(+1))
	ind(i,j) = (a[i]==b[j]) ? 0 : 1
	in ^ we suppose that strings are in [1..n] format: a="abc", a[1]='a'
	*/

	// distance between str and "" is always len(str)
	const int m = (int) strlen(src);
	const int n = (int) strlen(dst);
	if (!m) return n;
	if (!n) return m;

	// for all i and j, matrix[i,j] will hold the Levenshtein distance between
	// the first i characters of src and the first j characters of dst;
	// note that matrix has (m+1)*(n+1) values
	int** const matrix = (int**) malloc((m + 1) * sizeof(int*));
	for (int i = 0; i <= m; ++i) {
		matrix[i] = (int*) malloc((n + 1) * sizeof(int));
		matrix[i][0] = i;
	}
	for (int i = 0; i <= n; ++i) {
		matrix[0][i] = i;
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			const int cost = src[i - 1] != dst[j - 1];

			const int above = matrix[i - 1][j];
			const int left = matrix[i][j - 1];
			const int diag = matrix[i - 1][j - 1];
			matrix[i][j] = MIN(MIN(above + 1, left + 1), diag + cost);
		}
	}

	const int result = matrix[m][n];
	for (int i = m; i >= 0; --i) {
		free(matrix[i]);
	}
	free(matrix);

	return result;
}
