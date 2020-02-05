#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct line {
	int id;
	string Name;
	int id_father;
};
class table {
	private:
		void Show_children(int id) {
			cout << T[id - 1].id << " " << T[id - 1].Name << " " << T[id - 1].id_father << " (";
			for (int i = 0; i < amount; i++) {
				if (T[i].id_father == id) {
					cout << T[i].id << " " << T[i].Name << " " << T[i].id_father << "; ";
				}
			}
			cout << " )" << endl;
		}
	public:
		line* T;
		int  amount;
		void Show_table() {
			for (int i = 0; i < amount; i++) {
				cout << T[i].id << " " << T[i].Name << " " << T[i].id_father << endl;
			}
		}
		table() {
			ifstream IFdocument("document.txt");
			IFdocument  >> amount;
			T = new line[amount];
			for (int i = 0; i < amount; i++) {
				IFdocument >> T[i].id >> T[i].Name >> T[i].id_father;
			}
			IFdocument.close();
		}
		void Show_parents(int id) {
			int i = id;
			while (1) {
				cout << T[i - 1].id << " " << T[i - 1].Name << " " << T[i - 1].id_father << " -> ";
				i = T[i - 1].id_father;
				if (T[i - 1].id_father == 0) {
					cout << T[i - 1].id << " " << T[i - 1].Name << " " << T[i - 1].id_father << endl;
					break;
				}
			}
		}
		void Show_tree() {
			for (int i = 1; i < amount; i++) {
				Show_children(i);
			}
		}
		void Show_all_children(int id) {
			Show_children(id);
			for (int i = 0; i < amount; i++) {
				if (T[i].id_father == id) {
					Show_all_children(i + 1);
				}
			}
		}
		void Way(int id_start, int id_finish) {
			int** Search = new int* [amount];
			for (int i = 0; i < amount; i++) {
				Search[i] = new int[3];
				Search[i][0] = INT_MAX; // Растояние
				Search[i][1] = 0;       // Путь
				Search[i][2] = 0;       // Обработано ли
			}
			Search[id_start - 1][0] = 0;
			int min_distance, id_min;
			while (1) {
				min_distance = INT_MAX;
				id_min = 0;
				for (int i = 0; i < amount; i++) {
					if (Search[i][0] < min_distance && Search[i][2] == 0) {
						min_distance = Search[i][0];
						id_min = i + 1;
					}
				}
				if (id_min == 0) {
					break;
				}
				if (id_min != 1) {
					if (Search[T[id_min - 1].id_father - 1][0] > Search[id_min - 1][0] + 1) {
						Search[T[id_min - 1].id_father - 1][0] = Search[id_min - 1][0] + 1;
						Search[T[id_min - 1].id_father - 1][1] = id_min;
					}
				}
				for (int i = 0; i < amount; i++) {
					if (T[i].id_father == id_min) {
						if (Search[i][0] > Search[id_min - 1][0] + 1) {
							Search[i][0] = Search[id_min - 1][0] + 1;
							Search[i][1] = id_min;
						}
					}
				}
				Search[id_min - 1][2] = 1;
			}
			for (int i = id_finish; i != 0; i = Search[i - 1][1]) {
				cout << T[i - 1].id << " " << T[i - 1].Name << " " << T[i - 1].id_father;
				if (i != id_start) {
					cout << " <- ";
				}
			}
		}
};
int main() {
	table Table;
	//Table.Show_table();
	//Table.Show_parents(31);
	//Table.Show_tree();
	//Table.Show_all_children(5);
	Table.Way(24, 29);
}