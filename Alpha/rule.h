#ifndef ruleH
#define ruleH
struct rule
{
	char symbol;
	int shift;
	int new_state;
	int is_breakpoint;
	rule(char sy = ' ', int sh = -1, int n_s = -1, bool i_b = -1){

	}
};
#endif

