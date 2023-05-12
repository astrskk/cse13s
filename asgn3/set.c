#include "set.h"

#include <stdio.h>

//looked up syntax for assignment operators (ie |= and %=)
Set set_empty(void) {
    Set set = 0;
    return set;
}

Set set_universal(void) {
    Set set = 255;
    return set;
}

Set set_insert(Set s, int x) {
    s |= (1 << x);
    return s;
}

Set set_remove(Set s, int x) {
    s &= ~(1 << x);
    return s;
}

bool set_member(Set s, int x) {
    if ((s & (1 << x)) != 0) {
        return 1;
    } else {
        return 0;
    }
}

Set set_union(Set s, Set t) {
    Set u = (s | t);
    return u;
}

Set set_intersect(Set s, Set t) {
    Set i = (s & t);
    return i;
}

Set set_difference(Set s, Set t) {
    Set d = (s & ~(t));
    return d;
}

Set set_complement(Set s) {
    return ~s;
}

//int main(void){
//	Set uni = set_universal();
//	Set set = 4;
//	int i = 2;
//	uint32_t x = 1 << i;
//	bool d = set_member(set, i);
//	printf("bool is %u\n set is:%u, i is %u, x is %u\n", d, set, i, x);
//	set = set_insert(set, 1);
//	Set a = set_difference(uni, set);
//	printf("%u, %u, %u\n", set, uni, a);
//	return 0;
//}
