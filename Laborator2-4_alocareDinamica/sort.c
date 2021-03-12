#include "sort.h"


void sort(MyList* l, FunctieComparare cmpF) {
	for (int i = 0; i < size(l) - 1; i++) {
		for (int j = i + 1; j < size(l); j++) {
			void* tr1 = get(l, i);
			void* tr2 = get(l, j);
			if (cmpF(tr1, tr2) > 0) {
				set(l, i, tr2);
				set(l, j, tr1);
			}
		}
	}
}
