/* Exercise 4-14. Define a macro swap(t, x, y) that interchanges two arguments of type t. */

#define swap(t, x, y) {\
			t c = x;\
			x = y;\
			y = c;}