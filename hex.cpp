#include <iostream>

using namespace std;

struct Pair {
	int red;
	int blue;
	Pair() {
		red = 0;
		blue = 0;
	}
};

class Dynamic_array {
	char* arr;
	int size;
	int capacity;

public:
	Dynamic_array() {
		arr = new char[1];
		size = 0;
		capacity = 1;
	}

	Dynamic_array(const Dynamic_array& other) {
		size = other.size;
		capacity = other.capacity;
		arr = new char[capacity];
		for (int i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
	}

	Dynamic_array& operator=(const Dynamic_array& other) {
		if (this != &other) {
			delete[] arr;
			size = other.size;
			capacity = other.capacity;
			arr = new char[capacity];
			for (int i = 0; i < size; i++) {
				arr[i] = other.arr[i];
			}
		}
		return *this;
	}

	void push(char c) {
		if (size == capacity) {
			char* temp = new char[2 * capacity];
			for (int i = 0; i < capacity; i++) {
				temp[i] = arr[i];
			}
			delete[] arr;
			capacity *= 2;
			arr = temp;
		}
		arr[size] = c;
		size++;
	}

	char get(int index) const {
		return arr[index];
	}

	void set(int index, char c) {
		arr[index] = c;
	}

	int getSize() const {
		return size;
	}

	void print() const {
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void clear() {
		size = 0;
		capacity = 1;
		delete[] arr;
		arr = new char[1];
	}

	~Dynamic_array() {
		delete[] arr;
	}
};

void input(Dynamic_array& tab, char& c) {
	tab.clear();
	bool end = 0;
	cin >> c >> c >> c;
	while (1) {
		if (end) {
			break;
		}
		int num = 0;
		cin >> c;
		while (c == '-') {
			num++;
			if (num == 3) {
				cin >> c;
				if (c != '<' && c != '-') {
					cin.putback(c);
					end = 1;
					break;
				}
				cin.putback(c);
			}
			else if (num == 5) {
				end = 1;
				break;
			}
			cin >> c;
		}
		if (c == '<') {
			cin >> c;
			if (c == 'b' || c == 'r') {
				tab.push(c);
				cin >> c;
			}
			else if (c == '>') {
				tab.push('-');
			}
		}
	}
}

Pair PAWNS_NUMBER(const Dynamic_array& tab) {
	Pair pawns;
	for (int i = 0; i < tab.getSize(); i++) {
		tab.get(i) == 'r' ? pawns.red++ : (tab.get(i) == 'b' ? pawns.blue++ : 0);
	}
	return pawns;
}

bool IS_BOARD_CORRECT(const Dynamic_array& tab) {
	int blue = 0;
	int red = 0;
	for (int i = 0; i < tab.getSize(); i++) {
		tab.get(i) == 'r' ? red++ : (tab.get(i) == 'b' ? blue++ : 0);
	}
	if (red - blue == 0 || red - blue == 1) {
		return true;
	}
	return false;
}

int BOARD_SIZE(const Dynamic_array& tab) {
	return int(sqrt(tab.getSize()));
}

/*void printArray(char** arr, int n) {
	for (int i = 0; i < n; i++) {
		cout << i << " ";
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}*/

void fillArray(char** arr, const Dynamic_array& tab, int n) {
	int count = 0;
	for (int i = 0; i < n; ++i) {
		int row = i;
		int col = 0;
		while (row >= 0 && col < n) {
			arr[row][col] = tab.get(count++);
			--row;
			++col;
		}
	}
	for (int i = 1; i < n; ++i) {
		int row = n - 1;
		int col = i;
		while (row >= 0 && col < n) {
			arr[row][col] = tab.get(count++);
			--row;
			++col;
		}
	}
}

bool checkMap(int x, int y, char** arr, int size, bool** visited, char c) {
	// x to wiersz, y to kolumna
	visited[x][y] = true;
	if (arr[x][y] == c) {
		if (c == 'r' && y == size - 1) {
			return true;
		}
		else if (c == 'b' && x == size - 1) {
			return true;
		}

		const int dx[] = { 0, 1, -1, 1, -1, 0 };
		const int dy[] = { 1, 1, 0, 0, -1, -1 };

		for (int i = 0; i < 6; i++) {
			if (x + dx[i] >= 0 && x + dx[i] < size && y + dy[i] >= 0 && y + dy[i] < size) {
				if (arr[x + dx[i]][y + dy[i]] == c && !visited[x + dx[i]][y + dy[i]]) {
					if (checkMap(x + dx[i], y + dy[i], arr, size, visited, c)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

int IS_GAME_OVER(const Dynamic_array& tab) {
	int size = BOARD_SIZE(tab);
	if (size == 1 && tab.get(0) == 'r') {
		return 1;
	}

	bool** visited = new bool* [size];
	for (int i = 0; i < size; i++) {
		visited[i] = new bool[size];
		for (int j = 0; j < size; j++) {
			visited[i][j] = false;
		}
	}

	char** arr = new char* [size];
	for (int i = 0; i < size; i++) {
		arr[i] = new char[size];
	}

	fillArray(arr, tab, size);

	for (int i = 0; i < size; i++) {
		if (checkMap(0, i, arr, size, visited, 'b')) {
			for (int j = 0; j < size; j++) {
				delete[] visited[j];
				delete[] arr[j];
			}
			delete[] visited;
			delete[] arr;
			return 2;
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			visited[i][j] = false;
		}
	}

	for (int i = 0; i < size; i++) {
		if (checkMap(i, 0, arr, size, visited, 'r')) {
			for (int j = 0; j < size; j++) {
				delete[] visited[j];
				delete[] arr[j];
			}
			delete[] visited;
			delete[] arr;
			return 1;
		}
	}

	for (int j = 0; j < size; j++) {
		delete[] visited[j];
		delete[] arr[j];
	}
	delete[] visited;
	delete[] arr;
	return 0;
}

bool IS_BOARD_POSSIBLE(Dynamic_array tab) {

	if (IS_GAME_OVER(tab) == 0 && IS_BOARD_CORRECT(tab)) {
		return true;
	}
	else if (!IS_BOARD_CORRECT(tab)) {
		return false;
	}

	int size = BOARD_SIZE(tab);
	Pair pawns = PAWNS_NUMBER(tab);


	if (IS_GAME_OVER(tab) == 1 && pawns.red - 1 == pawns.blue) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == 'r') {
				tab.set(i, '-');
				if (IS_GAME_OVER(tab) != 1) {
					tab.set(i, 'r');
					return true;
				}
				tab.set(i, 'r');
			}
		}
		return false;
	}
	else if (IS_GAME_OVER(tab) == 2 && pawns.blue == pawns.red) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == 'b') {
				tab.set(i, '-');
				if (IS_GAME_OVER(tab) != 2) {
					tab.set(i, 'b');
					return true;
				}
				tab.set(i, 'b');
			}
		}
		return false;
	}

	return false;
}

void CAN_WIN_NAIVE_OPPONENT(Dynamic_array tab)
{
	int size = BOARD_SIZE(tab);
	if (IS_GAME_OVER(tab) || !IS_BOARD_CORRECT(tab)) {
		cout << "NO\nNO\nNO\nNO\n";
		return;
	}

	bool winRed1 = false;
	bool winBlue1 = false;
	bool winRed2 = false;
	bool winBlue2 = false;

	char** arr = new char* [size];
	for (int i = 0; i < size; i++) {
		arr[i] = new char[size];
	}
	fillArray(arr, tab, size);

	Pair pawns = PAWNS_NUMBER(tab);

	int slots = size * size - pawns.red - pawns.blue;

	if ((pawns.red == pawns.blue && slots > 0) || (pawns.red > pawns.blue && slots > 1)) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == '-') {
				tab.set(i, 'r');
				if (!winRed2 && !IS_GAME_OVER(tab) && ((pawns.red == pawns.blue && slots > 2) || (pawns.red > pawns.blue && slots > 3))) {
					for (int j = 0; j < size * size; j++) {
						if (tab.get(j) == '-') {
							tab.set(j, 'r');
							if (IS_GAME_OVER(tab) == 1) {
								winRed2 = true;
								tab.set(j, '-');
								break;
							}
							tab.set(j, '-');
						}
					}
				}
				if (!winRed1 && IS_GAME_OVER(tab) == 1) {
					winRed1 = true;
				}
				tab.set(i, '-');
			}
			if (winRed1 && winRed2) break;
		}
	}

	if ((pawns.red == pawns.blue && slots > 1) || (pawns.red > pawns.blue && slots > 0)) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == '-') {
				tab.set(i, 'b');
				if (!winBlue2 && !IS_GAME_OVER(tab) && ((pawns.red == pawns.blue && slots > 3) || (pawns.red > pawns.blue && slots > 2))) {
					for (int j = 0; j < size * size; j++) {
						if (tab.get(j) == '-') {
							tab.set(j, 'b');
							if (IS_GAME_OVER(tab) == 2) {
								winBlue2 = true;
								tab.set(j, '-');
								break;
							}
							tab.set(j, '-');
						}
					}
				}
				if (!winBlue1 && IS_GAME_OVER(tab) == 2) {
					winBlue1 = true;
				}
				tab.set(i, '-');
			}
			if (winBlue1 && winBlue2) break;
		}
	}

	winRed1 ? cout << "YES\n" : cout << "NO\n";

	winBlue1 ? cout << "YES\n" : cout << "NO\n";

	winRed2 ? cout << "YES\n" : cout << "NO\n";

	winBlue2 ? cout << "YES\n\n" : cout << "NO\n\n";

	for (int i = 0; i < size; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	return;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::string function = "";
	Dynamic_array tab;
	char buffer[256];
	char c;
	std::cin >> c;
	while (!cin.eof()) {
		if (c == '-') {
			function = "";
			cin.putback(c);
			input(tab, c);
		}
		else {
			if (fgets(buffer, sizeof(buffer), stdin)) {
				function = buffer;
			}
		}
		if (function == "OARD_SIZE\n") {
			// 8 %
			cout << BOARD_SIZE(tab) << "\n\n";
		}
		else if (function == "AWNS_NUMBER\n") {
			// 8 %
			Pair pawns = PAWNS_NUMBER(tab);
			cout << pawns.red + pawns.blue << "\n\n";
		}
		else if (function == "S_BOARD_CORRECT\n") {
			// 8 %
			IS_BOARD_CORRECT(tab) ? cout << "YES\n\n" : cout << "NO\n\n";
		}
		else if (function == "S_GAME_OVER\n") {
			// 20 %
			if (IS_BOARD_CORRECT(tab)) {
				int over = IS_GAME_OVER(tab);
				over == 0 ? cout << "NO\n\n" : cout << "YES "
					<< (over == 1 ? "RED" : "BLUE") << "\n\n";
			}
			else {
				cout << "NO\n\n";
			}
		}
		else if (function == "S_BOARD_POSSIBLE\n") {
			// 20 %
			IS_BOARD_POSSIBLE(tab) ? cout << "YES\n\n" : cout << "NO\n\n";
		}
		else if (function == "AN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT\n") {
			// 20 %
			for (int i = 0; i < 3; i++) {
				fgets(buffer, sizeof(buffer), stdin);
			}
			CAN_WIN_NAIVE_OPPONENT(tab);
		}
		else if (function == "AN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT\n") {
			// 16 %
			return 0;
		}
		else if (function == "PRINT") {
			tab.print();
		}
		std::cin >> c;
	}
	return 0;
}