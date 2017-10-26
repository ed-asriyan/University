#include "levenshtein.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MIN3(a, b, c) MIN(MIN(a, b), (c))

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

int _calc_levenshtien_recoursive(const char* src, int src_len, const char* dst, int dst_len) {
	// base case: empty strings
	if (src_len == 0) return dst_len;
	if (dst_len == 0) return src_len;

	const int cost = src[src_len - 1] != dst[dst_len - 1];

	// return minimum of delete char from src, delete char from dst, and delete char from both
	return MIN3(_calc_levenshtien_recoursive(src, src_len - 1, dst, dst_len) + 1,
	            _calc_levenshtien_recoursive(src, src_len, dst, dst_len - 1) + 1,
	            _calc_levenshtien_recoursive(src, src_len - 1, dst, dst_len - 1) + cost);

}

int calc_levenshtein_recoursive(const char* src, const char* dst) {
	return _calc_levenshtien_recoursive(src, (int) strlen(src), dst, (int) strlen(dst));
}

int calc_levenshtein_modified(const char* src, const char* dst) {
	const int src_len = strlen(src);
	const int dst_len = strlen(dst);

	int** const matrix = (int**) malloc((src_len) * sizeof(int*));

	for (int i = 0; i <= src_len; i++) {
		matrix[i] = (int*) malloc((dst_len + 1) * sizeof(int));
		matrix[i][0] = i;
	}
	for (int j = 0; j <= dst_len; j++) {
		matrix[0][j] = j;
	}
	for (int i = 1; i <= src_len; i++) {
		for (int j = 1; j <= dst_len; j++) {
			const int cost = src[i - 1] != dst[j - 1];

			matrix[i][j] = MIN3(
				matrix[i - 1][j] + 1,
				matrix[i][j - 1] + 1,
				matrix[i - 1][j - 1] + cost
			);
			if ((i > 1) &&
				(j > 1) &&
				(src[i - 1] == dst[j - 2]) &&
				(src[i - 2] == dst[j - 1])
				) {
				matrix[i][j] = MIN(
					matrix[i][j],
					matrix[i - 2][j - 2] + cost
				);
			}
		}
	}

	const int result = matrix[src_len][dst_len];
	for (int i = src_len; i >= 0; --i) {
		free(matrix[i]);
	}
	free(matrix);

	return result;
}
