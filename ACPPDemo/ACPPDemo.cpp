#include <stdio.h>
#include <vector>

using namespace std;

struct mystruct {
	int x;
};

int main(int argc, char **argv) {
	vector<mystruct *> thing;

	for (auto i = thing.begin(); i != thing.end(); i++) {
		(*i)->x = 5;
	}

	for (auto i : thing) {
		i->x = 5;
	}

	return 0;
}
