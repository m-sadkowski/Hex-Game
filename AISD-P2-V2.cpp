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

void input(Dynamic_array& tab, char &c) {
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
			} else if (num == 5) {
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
			} else if (c == '>') {
				tab.push('-');
			}
		}
	}
} 

Pair PAWNS_NUMBER(Dynamic_array tab) {
	Pair pawns;
	for (int i = 0; i < tab.getSize(); i++) {
		if (tab.get(i) == 'r') {
			pawns.red++;
		} else if (tab.get(i) == 'b') {
			pawns.blue++;
		}
	}
	return pawns;
}

bool IS_BOARD_CORRECT(Dynamic_array tab) {
	int blue = 0;
	int red = 0;
	for (int i = 0; i < tab.getSize(); i++) {
		if (tab.get(i) == 'r') {
			red++;
		} else if (tab.get(i) == 'b') {
			blue++;
		}
	}
	if (red - blue == 0 || red - blue == 1) {
		return true;
	} 
	return false;
}

int BOARD_SIZE(Dynamic_array tab) {
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

void fillArray(char** arr, Dynamic_array tab, int n) {
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

bool goDown(int x, int y, char** arr, int size, bool** visited) {
	// x to wiersz, y to kolumna
	visited[x][y] = true;
	if (arr[x][y] == 'b') {
		if (x == size - 1) {
			return true;
		}
		// 0 -1
		if (y > 0) if(arr[x][y - 1] == 'b' && !visited[x][y - 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x << " " << y - 1 << "\n";
			if (goDown(x, y - 1, arr, size, visited)) return true;
		}
		// 0 +1
		if (y + 1 < size) if(arr[x][y + 1] == 'b' && !visited[x][y + 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x << " " << y + 1 << "\n";
			if (goDown(x, y + 1, arr, size, visited)) return true;
		}
		// +1 0
		if (x + 1 < size) if(arr[x + 1][y] == 'b' && !visited[x + 1][y]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x + 1 << " " << y << "\n";
			if (goDown(x + 1, y, arr, size, visited)) return true;
		}
		// +1 +1
		if (x + 1 < size && y + 1 < size) if(arr[x + 1][y + 1] == 'b' && !visited[x + 1][y + 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x + 1 << " " << y + 1 << "\n";
			if (goDown(x + 1, y + 1, arr, size, visited)) return true;
		}
		// -1 -1
		if (x > 0 && y > 0) if (arr[x - 1][y - 1] == 'b' && !visited[x - 1][y - 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x - 1 << " " << y - 1 << "\n";
			if (goDown(x - 1, y - 1, arr, size, visited)) return true;
		}
		// -1 0
		if (x > 0) if (arr[x - 1][y] == 'b' && !visited[x - 1][y]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x - 1 << " " << y << "\n";
			if (goDown(x - 1, y, arr, size, visited)) return true;
		}
	}
	return false;
}

bool goRight(int x, int y, char** arr, int size, bool** visited) {
	// x to wiersz, y to kolumna
	visited[x][y] = true;
	if (arr[x][y] == 'r') {
		if (y == size - 1) {
			return true;
		}
		if (y + 1 < size) if (arr[x][y + 1] == 'r' && !visited[x][y + 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x << " " << y + 1 << "\n";
			if (goRight(x, y + 1, arr, size, visited)) return true;
		}
		// +1 +1
		if (y + 1 < size && x + 1 < size) if(arr[x + 1][y + 1] == 'r' && !visited[x + 1][y + 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x + 1 << " " << y + 1 << "\n";
			if (goRight(x + 1, y + 1, arr, size, visited)) return true;
		}
		// -1 0
		if (x > 0) if(arr[x - 1][y] == 'r' && !visited[x - 1][y]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x - 1 << " " << y << "\n";
			if (goRight(x - 1, y, arr, size, visited)) return true;
		}
		// + 1 0
		if (x + 1 < size) if(arr[x + 1][y] == 'r' && !visited[x + 1][y]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x + 1 << " " << y << "\n";
			if (goRight(x + 1, y, arr, size, visited)) return true;
		}
		// -1 -1
		if (x > 0 && y > 0) if (arr[x - 1][y - 1] == 'r' && !visited[x - 1][y - 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x - 1 << " " << y - 1 << "\n";
			if (goRight(x - 1, y - 1, arr, size, visited)) return true;
		}
		// 0 -1
		if (y > 0) if (arr[x][y - 1] == 'r' && !visited[x][y - 1]) {
			//cout << "z pola " << x << " " << y << " idziemy na " << x << " " << y - 1 << "\n";
			if (goRight(x, y - 1, arr, size, visited)) return true;
		}
	}
	return false;
}

void IS_GAME_OVER(Dynamic_array tab) {
	int size = BOARD_SIZE(tab);
	if (size == 1 && tab.get(0) == 'r') {
		cout << "YES RED\n\n";
		return;
	}

	bool** visitedBlue = new bool*[size];
	for (int i = 0; i < size; i++) {
		visitedBlue[i] = new bool[size];
		for (int j = 0; j < size; j++) {
			visitedBlue[i][j] = false;
		}
	}

	bool** visitedRed = new bool* [size];
	for (int i = 0; i < size; i++) {
		visitedRed[i] = new bool[size];
		for (int j = 0; j < size; j++) {
			visitedRed[i][j] = false;
		}
	}

	char** arr = new char*[size];
	for (int i = 0; i < size; i++) {
		arr[i] = new char[size];
	}

	fillArray(arr, tab, size);
	//printArray(arr, size);

	for (int i = 0; i < size; i++) {
		if (goDown(0, i, arr, size, visitedBlue)) {
			cout << "YES BLUE\n\n";
			return;
		}
		if (goRight(i, 0, arr, size, visitedRed)) {
			cout << "YES RED\n\n";
			return;
		}
	}
	cout << "NO\n\n";
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
		} else {
			getline(cin, function);
		} 
		if (function == "OARD_SIZE") {
			// 8 %
			cout << BOARD_SIZE(tab) << "\n\n";
		} else if (function == "AWNS_NUMBER") {
			// 8 %
			Pair pawns = PAWNS_NUMBER(tab);
			cout << pawns.red + pawns.blue << "\n\n";
		} else if (function == "S_BOARD_CORRECT") {
			// 8 %
			if (IS_BOARD_CORRECT(tab)) {
				cout << "YES\n\n";
			} else {
				cout << "NO\n\n";
			}
		} else if (function == "S_GAME_OVER") {
			// 20 %
			if (IS_BOARD_CORRECT(tab)) {
				IS_GAME_OVER(tab);
			} else {
				cout << "NO\n\n";
			}
		} else if (function == "S_BOARD_POSSIBLE") {
			// 20 %
			break;
		} else if (function == "AN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
			// 20 %
			getline(cin, function);
			getline(cin, function);
			getline(cin, function);
			break;
		} else if (function == "AN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
			// 20 %
			getline(cin, function);
			getline(cin, function);
			getline(cin, function);
			break;
		}
		std::cin >> c;
	}
	return 0;
}