#include"GameLife.h"
//additional funcs
int checkPositive(int num, int module) {
    if (num < 0) return num + module;
    return num;
}

//class
void GameLife::createGrid() {
    if (!iscreated) return;
	actionlist.resize(cellnum);
	for (int x = 0; x < actionlist.size(); x++) {
		for (int y = 0; y < actionlist[x].size(); y++) {
			actionlist[x][y]=rand() % 2;
		}
	}
}
int GameLife::getNeighbour(int Cx, int Cy) {
    int counter = 0;
    int cellnum = actionlist.size();
    for (int y = Cy - 1; y < Cy + 2; y++) {
        for (int x = Cx - 1; x < Cx + 2; x++) {
            int ym = checkPositive(y % cellnum, cellnum);
            int xm = checkPositive(x % cellnum, cellnum);
            //std::cout << "x:" << xm << "  y:" << ym <<" ";
            //std::cout << "cell:" << actionlist[xm][ym] << std::endl;
            counter += actionlist[xm][ym];
        }
    }
    counter -= actionlist[Cx][Cy];
    return counter;
}
std::vector<std::vector<int>> GameLife::nextStep() {
    std::vector<std::vector<int>> newactionlist;
    int cellnum = actionlist.size();
    newactionlist.resize(cellnum);
    for (int i = 0; i < cellnum; i++) newactionlist[i].resize(cellnum);
    for (int y = 0; y < cellnum; y++) {
        for (int x = 0; x < cellnum; x++) {

            int currentcell = actionlist[x][y];
            int neighcount = getNeighbour(x, y);

            if (currentcell == 0) {
                if (neighcount == 3)
                    newactionlist[x][y] = 1;
                else { newactionlist[x][y] = 0; }
            }
            else if (currentcell == 1) {

                if (neighcount == 2 || neighcount == 3) { newactionlist[x][y] = 1; }
                else newactionlist[x][y] = 0;
            }

        }
    }
    actionlist = newactionlist;
    return actionlist;
}
