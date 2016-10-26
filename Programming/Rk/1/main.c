#include <stdlib.h>
#include <stdio.h>

#include "Hall.h"

int main() {
	int n = 0;
	int m = 0;
	int k = 0;

	scanf("%d %d %d", &n, &m, &k);

	Hall* hall = create_hall(n);

	for (int i = 0; i < m; i++) {
		int x = 0;
		int y = 0;
		scanf("%d %d", &y, &x);
		set_reserved_place(hall, x - 1, y - 1);
	}

	int favorite_x = 0;
	int favorite_y = 0;
	scanf("%d %d", &favorite_y, &favorite_x);
	set_favorite_place(hall, favorite_x - 1, favorite_y - 1);
	
	int the_best_place = calc_lucky_sum(hall, k);
	printf("%d", the_best_place);

	free_hall(hall);

	return 0;
}