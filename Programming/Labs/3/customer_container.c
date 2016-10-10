//
// Created by ed on 10.10.16.
//

#include "customer_container.h"

int ReadWholeCustomerList(XmlObject* root, Customer*** result) {
	Customer** array = NULL;
	int count = 0;
	int array_len = 0;

	char* root_body = get_xml_object_body(root);
	Customer* curr_customer = NULL;
	while (*root_body && (curr_customer = CreateCustomerFromXml(root_body, &root_body))) {
		if (count >= array_len || array == NULL) {
			array = (Customer**) realloc(array, sizeof(Customer*) * (array_len = (array_len + 1) * 3));
		}

		array[count++] = curr_customer;
	}

	if (result != NULL) {
		*result = array;
	} else {
		free(result);
	}
	return count;
}

void FreeCustomerList(Customer** c, int count) {
	for (int i = 0; i < count; ++i) {
		FreeCustomer(c[i]);
	}
	free(c);
}

int defaultCustomerCmp(Customer* a, Customer* b) {
	int a_id = get_customer_id(a);
	int b_id = get_customer_id(b);

	if (a_id == b_id) {
		return 0;
	} else if (a_id < b_id) {
		return 1;
	} else {
		return -1;
	}
}

void merging(Customer** a, Customer** b, int low, int mid, int high, int (* cmp)(Customer*, Customer*)) {
	int l1, l2, i;

	for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
		if (cmp(a[l1], a[l2]) <= 0) {
			b[i] = a[l1++];
		} else {
			b[i] = a[l2++];
		}
	}

	while (l1 <= mid) {
		b[i++] = a[l1++];
	}

	while (l2 <= high) {
		b[i++] = a[l2++];
	}

	for (i = low; i <= high; i++) {
		a[i] = b[i];
	}
}

void sort(Customer** a, Customer** b, int low, int high, int (* cmp)(Customer*, Customer*)) {
	int mid;

	if (low < high) {
		mid = (low + high) / 2;
		sort(a, b, low, mid, cmp);
		sort(a, b, mid + 1, high, cmp);
		merging(a, b, low, mid, high, cmp);
	} else {
		return;
	}
}

void MergeSort(Customer** array, int count, int (* cmp)(Customer*, Customer*)) {
	if (cmp == NULL) {
		cmp = &defaultCustomerCmp;
	}

	Customer** b = (Customer**) malloc(sizeof(Customer*) * count);
	sort(array, b, 0, count - 1, cmp);

	memcpy(array, b, sizeof(Customer*) * count);
	free(b);
}
