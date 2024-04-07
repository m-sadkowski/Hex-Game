#include <iostream>
#include <string>

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
		if (tab.get(i) == 'r') {
			pawns.red++;
		}
		else if (tab.get(i) == 'b') {
			pawns.blue++;
		}
	}
	return pawns;
}

bool IS_BOARD_CORRECT(const Dynamic_array& tab) {
	int blue = 0;
	int red = 0;
	for (int i = 0; i < tab.getSize(); i++) {
		if (tab.get(i) == 'r') {
			red++;
		}
		else if (tab.get(i) == 'b') {
			blue++;
		}
	}
	if (red - blue == 0 || red - blue == 1) {
		return true;
	}
	return false;
}

int BOARD_SIZE(const Dynamic_array& tab) {
	return int(sqrt(tab.getSize()));
}

void printArray(char** arr, int n) {
	for (int i = 0; i < n; i++) {
		cout << i << " ";
		for (int j = 0; j < n; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

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

		if (y + 1 < size) if (arr[x][y + 1] == c && !visited[x][y + 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x << " " << y + 1 << "\n";
			if (checkMap(x, y + 1, arr, size, visited, c)) return true;
		}
		// +1 +1
		if (y + 1 < size && x + 1 < size) if (arr[x + 1][y + 1] == c && !visited[x + 1][y + 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x + 1 << " " << y + 1 << "\n";
			if (checkMap(x + 1, y + 1, arr, size, visited, c)) return true;
		}
		// -1 0
		if (x > 0) if (arr[x - 1][y] == c && !visited[x - 1][y]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x - 1 << " " << y << "\n";
			if (checkMap(x - 1, y, arr, size, visited, c)) return true;
		}
		// + 1 0
		if (x + 1 < size) if (arr[x + 1][y] == c && !visited[x + 1][y]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x + 1 << " " << y << "\n";
			if (checkMap(x + 1, y, arr, size, visited, c)) return true;
		}
		// -1 -1
		if (x > 0 && y > 0) if (arr[x - 1][y - 1] == c && !visited[x - 1][y - 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x - 1 << " " << y - 1 << "\n";
			if (checkMap(x - 1, y - 1, arr, size, visited, c)) return true;
		}
		// 0 -1
		if (y > 0) if (arr[x][y - 1] == c && !visited[x][y - 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x << " " << y - 1 << "\n";
			if (checkMap(x, y - 1, arr, size, visited, c)) return true;
		}
	}
	return false;
}

int IS_GAME_OVER(const Dynamic_array& tab) {
	int size = BOARD_SIZE(tab);
	if (size == 1 && tab.get(0) == 'r') {
		return 1;
	}

	bool** visitedRed = new bool* [size];
	for (int i = 0; i < size; i++) {
		visitedRed[i] = new bool[size];
		for (int j = 0; j < size; j++) {
			visitedRed[i][j] = false;
		}
	}


	bool** visitedBlue = new bool* [size];
	for (int i = 0; i < size; i++) {
		visitedBlue[i] = new bool[size];
		for (int j = 0; j < size; j++) {
			visitedBlue[i][j] = false;
		}
	}

	char** arr = new char* [size];
	for (int i = 0; i < size; i++) {
		arr[i] = new char[size];
	}

	fillArray(arr, tab, size);

	for (int i = 0; i < size; i++) {
		if (checkMap(0, i, arr, size, visitedBlue, 'b')) {
			return 2;
		}
		if (checkMap(i, 0, arr, size, visitedRed, 'r')) {
			return 1;
		}
	}

	for (int i = 0; i < size; i++) {
		delete[] visitedRed[i];
		delete[] visitedBlue[i];
		delete[] arr[i];
	}
	delete[] visitedRed;
	delete[] visitedBlue;
	delete[] arr;

	return 0;
}

void IS_BOARD_POSSIBLE(Dynamic_array tab) {

	if (IS_GAME_OVER(tab) == 0 && IS_BOARD_CORRECT(tab)) {
		cout << "YES\n\n";
		return;
	}
	else if (!IS_BOARD_CORRECT(tab)) {
		cout << "NO\n\n";
		return;
	}

	int size = BOARD_SIZE(tab);
	Pair pawns = PAWNS_NUMBER(tab);

	if (IS_GAME_OVER(tab) == 1 && pawns.red - 1 == pawns.blue) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == 'r') {
				tab.set(i, '-');
				if (IS_GAME_OVER(tab) != 1) {
					cout << "YES\n\n";
					tab.set(i, 'r');
					return;
				}
				tab.set(i, 'r');
			}
		}
		cout << "NO\n\n";
		return;
	}
	else if (IS_GAME_OVER(tab) == 2 && pawns.blue == pawns.red) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == 'b') {
				tab.set(i, '-');
				if (IS_GAME_OVER(tab) != 2) {
					cout << "YES\n\n";
					tab.set(i, 'b');
					return;
				}
				tab.set(i, 'b');
			}
		}
		cout << "NO\n\n";
		return;
	}

	cout << "NO\n\n";
	return;
}

void CAN_WIN_NAIVE_OPPONENT(Dynamic_array tab)
{
	int size = BOARD_SIZE(tab);
	if (IS_GAME_OVER(tab) || !IS_BOARD_CORRECT(tab)) {
		cout << "NO\nNO\nNO\nNO\n";
		return;
	}

	char** arr = new char* [size];
	for (int i = 0; i < size; i++) {
		arr[i] = new char[size];
	}
	fillArray(arr, tab, size);

	bool win = false;
	Pair pawns = PAWNS_NUMBER(tab);

	int slots = size * size - pawns.red - pawns.blue;

	// CAN RED WIN IN 1 MOVE WITH NAIVE OPPONENT
	if ((pawns.red == pawns.blue && slots > 0) || (pawns.red > pawns.blue && slots > 1)) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == '-') {
				tab.set(i, 'r');
				if (IS_GAME_OVER(tab) == 1) {
					win = true;
					tab.set(i, '-');
					break;
				}
				tab.set(i, '-');
			}
		}
	}
	if (win) {
		cout << "YES\n";
		win = 0;
	}
	else {
		cout << "NO\n";
	}

	// CAN BLUE WIN IN 1 MOVE WITH NAIVE OPPONENT
	if ((pawns.red == pawns.blue && slots > 1) || (pawns.red > pawns.blue && slots > 0)) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == '-') {
				tab.set(i, 'b');
				if (IS_GAME_OVER(tab) == 2) {
					win = true;
					tab.set(i, '-');
					break;
				}
				tab.set(i, '-');
			}
		}
	}
	if (win) {
		cout << "YES\n";
		win = 0;
	}
	else {
		cout << "NO\n";
	}

	// CAN RED WIN IN 2 MOVES WITH NAIVE OPPONENT
	if ((pawns.red == pawns.blue && slots > 2) || (pawns.red > pawns.blue && slots > 3)) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == '-') {
				tab.set(i, 'r');
				if (!IS_GAME_OVER(tab)) {
					for (int j = 0; j < size * size; j++) {
						if (tab.get(j) == '-') {
							tab.set(j, 'r');
							if (IS_GAME_OVER(tab) == 1) {
								win = true;
								tab.set(j, '-');
								break;
							}
							tab.set(j, '-');
						}
					}
				}
				tab.set(i, '-');
			}
			if (win) break;
		}
	}
	if (win) {
		cout << "YES\n";
		win = 0;
	}
	else {
		cout << "NO\n";
	}

	// CAN BLUE WIN IN 2 MOVES WITH NAIVE OPPONENT
	if ((pawns.red == pawns.blue && slots > 3) || (pawns.red > pawns.blue && slots > 2)) {
		for (int i = 0; i < size * size; i++) {
			if (tab.get(i) == '-') {
				tab.set(i, 'b');
				if (!IS_GAME_OVER(tab)) {
					for (int j = 0; j < size * size; j++) {
						if (tab.get(j) == '-') {
							tab.set(j, 'b');
							if (IS_GAME_OVER(tab) == 2) {
								win = true;
								tab.set(j, '-');
								break;
							}
							tab.set(j, '-');
						}
					}
				}
				tab.set(i, '-');
			}
			if (win) break;
		}
	}
	if (win) {
		cout << "YES\n";
		win = 0;
	}
	else {
		cout << "NO\n";
	}

	for (int i = 0; i < size; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	return;
}

int main()
{
	std::string function = "";
	Dynamic_array tab;
	char c;
	std::cin >> c;
	while (!cin.eof()) {
		if (c == '-') {
			function = "";
			cin.putback(c);
			input(tab, c);
		}
		else {
			getline(cin, function);
		}

		if (function == "OARD_SIZE") { // READY
			// 8 %
			cout << BOARD_SIZE(tab) << "\n\n";
		}
		else if (function == "AWNS_NUMBER") { // READY
			// 8 %
			Pair pawns = PAWNS_NUMBER(tab);
			cout << pawns.red + pawns.blue << "\n\n";
		}
		else if (function == "S_BOARD_CORRECT") { // READY
			// 8 %
			if (IS_BOARD_CORRECT(tab)) {
				cout << "YES\n\n";
			}
			else {
				cout << "NO\n\n";
			}
		}
		else if (function == "S_GAME_OVER") { // READY
			// 20 %
			if (IS_BOARD_CORRECT(tab)) {
				int over = IS_GAME_OVER(tab);
				if (over == 0) cout << "NO\n\n";
				else if (over == 1) cout << "YES RED\n\n";
				else if (over == 2) cout << "YES BLUE\n\n";
			}
			else {
				cout << "NO\n\n";
			}
		}
		else if (function == "S_BOARD_POSSIBLE") { // READY
			// 20 %
			IS_BOARD_POSSIBLE(tab);
		}
		else if (function == "AN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") { // READY
			// 20 %
			getline(cin, function);
			getline(cin, function);
			getline(cin, function);
			CAN_WIN_NAIVE_OPPONENT(tab);
			cout << "\n\n";
		}
		else if (function == "AN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
			// 16 %
			getline(cin, function);
			getline(cin, function);
			getline(cin, function);
			break;
		}
		std::cin >> c;
	}
	return 0;
}