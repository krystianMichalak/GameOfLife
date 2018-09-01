Gliwice 2018.01

Programowanie komputerów
Temat: Gra o przeżycie

Autor: Krystian Michalak

1.	Treść zdania

Gra o przeżycie jest zmodyfikowana wersja gry o życie Conway’a. Gra toczy się na prostokątnej płaszczyźnie podzielonej na kwadratowe komórki. Każda komórka ma ośmiu “sąsiadów”, czyli komórki przylegające do niej bokami i rogami. Każda komórka może znajdować się w jednym z dwóch stanów: może być albo “żywa” (włączona), albo “martwa” (wyłączona).
Stany komórek zmieniają się w pewnych jednostkach czasu. Stan wszystkich komórek w pewnej jednostce czasu jest używany do obliczenia stanu wszystkich komórek w następnej jednostce. Po obliczeniu wszystkie komórki zmieniają swój stan dokładnie w tym samym momencie. Stan komórki zależy tylko od liczby jej żywych sąsiadów.
Reguły gry według Conwaya:
Martwa komórka, która ma dokładnie 3 żywych sąsiadów, staje się żywa w następnej jednostce czasu (rodzi się).
 Żywa komórka z 2 albo 3 żywymi sąsiadami pozostaje nadal żywa; przy innej liczbie sąsiadów umiera (z “samotności” albo “zatłoczenia”).
W zmodyfikowanej wersji gry wyróżniamy dodatkowo typ komórki, która w momencie niebezpieczeństwa śmierci ulega hibernacji na losowa (z przedziału 1-10) liczbę iteracji. W czasie hibernacji jest ona widziana jako martwa przez sąsiednie komórki. Po zakończeniu procesu hibernacji jeżeli nadal grozi jej śmierć zmienia swój stan. Inny wyróżniony typ komórki uwzględnia tylko 4 sąsiednie komórki w celu sprawdzenia reguł. Ostatnim typem jest komórka trudno odradzalna, która potrzebuje aż trzech kolejnych iteracji spełniających warunek odrodzenia, żeby sama się odrodziła.
Program uruchamiany jest z linii poleceń z wykorzystaniem następujących przełączników (kolejność przełączników jest dowolna):
-i plik wejściowy
-p liczba iteracji
-o plik wyjściowy
Plik wejściowy i wyjściowy zawiera odpowiednio macierz odzwierciedlająca początkowy i końcowy stan płaszczyzny. Każda komórka określana jest przez swój typ: N – normalna, H – hibernująca, O – ograniczona do 4 sąsiadów, T – trudno odradzalna, oraz wartość 1 jeżeli jest żywa lub 0 w przeciwnym wypadku. Przykładowy plik może wyglądać następująco:
N 0 N 1 N 0 N 1 N 1 N 1
H 1 N 1 H 1 T 1 N 1 N 0
O 1 O 1 O 0 T 0 N 1 N 1

2.	Analiza rozwiązania
Dane na których będą wykonywane operacje stanowią dwuwymiarową tablicę dlatego jako strukturę danych wybrano vector vectorów. Szablon vector jest to struktura danych reprezentująca tablicę. Tablica jest zbudowana z elementów o typie przekazanym poprzez parametr szablonu Type, w naszym przypadku jest to obiekt typu Cell. Niniejszy kontener umożliwia modyfikację rozmiaru tablicy w trakcie życia obiektu. Jest to ważne ponieważ przed odczytaniem tablicy jej rozmiar nie jest znany.
Bazową klasę w niniejszym programie stanowi klasa Cell. Klasy pochodne dziedziczące po klasie bazowe to: NormalCell, HibernatedCell, RestrictedCell, HardToReviveCell. Osobną klasą jest klasa CellGroup przechowująca vector vectorów oraz dodatkowo klasy FileReadWriteException i UserInputException dziedziczące po klasie std::exception. Ostatnią klasę stanowi klasa CommandLine, która gromadzi operacje przeprowadzane na danych wprowadzanych jako argumenty wywołania programu z linii poleceń.

Program po rozpoczęciu otworzy plik wejściowy i dla każdego typu komórki utworzy odpowiedni obiekt przypisując mu stan początkowy. Następnie wskaźnik na ten obiekt zostanie przekazany do tablicy – vectora vectorów. Na podstawie przekazanej z linii poleceń liczby iteracji tablica zostanie przekształcona taką ilość razy uwzględniając zasady zmiany stanów komórki oraz zdolności specjalne komórek. Po zakończeniu tablica zostanie zapisana do wskazanego pliku.

3.	Specyfikacja zewnętrzna
Program należy uruchomić z linii poleceń (cmd.exe) w następujący sposób:
<GameOfLife.exe > -i <plik do przetworzenia> -p <liczba iteracji> -o <plik do zapisu>
Jeżeli program nie jest uruchamiany z katalogu, w którym się znajduje należy podać do niego pełną ścieżkę, tak samo należy postępować z plikiem do przetworzenia.
Plik do przetworzenia powinien być plikiem tekstowym zawierającym - odzwierciedlającym początkowy rozkład komórek. Czyli:
<typ komórki> <spacja> <stan komórki> <typ komórki> <spacja> <stan komórki> …
<typ komórki> <spacja> <stan komórki> <typ komórki> <spacja> <stan komórki> …
…

Typy komórki:
N – normalna, H – hibernująca, O – ograniczona do 4 sąsiadów, T – trudno odradzalna
Stany komórki:
1 – żywa, 0 – martwa.

W przypadku podania nieprawidłowych argumentów wywołania programu np. ujemna liczba iteracji program wyświetli komunikat:
"Bad command line arguments!"
i zakończy pracę.

W przypadku braku możliwości odczytu pliku program wyświetli komunikat:
"Could not open the file to read!"
i zakończy pracę.


W przypadku gdy w pliku do przetworzenia zostaną użyte symbole inne niż dopuszczone program wyświetli komunikat:
"Invalid Characters Type in file! Only Allowed : \"0\", \"1\", \"N\", \"O\", \"H\" !"
i zakończy pracę.

W przypadku gdy w pliku do przetworzenia zostaną użyte symbole w innej kolejności niż jest to dozwolone program wyświetli komunikat:
"Invalid Characters Sequence in file!
After: character there should be a space and then \"0\" or \"1\" !"
i zakończy pracę.

W przypadku braku możliwości zapisu pliku program wyświetli komunikat:
" Could not open the file to write!"
i zakończy pracę.

4.	Specyfikacja wewnętrzna
Klasa Cell:
Pola chronione:
state (typu wyliczeniowego cellState (dead lub alive)) - aktualny stan komórki
newState (typu wyliczeniowego cellState (dead lub alive)) – stan następny czyli taki  jaki przyjmie komórka w następnej iteracji
Metody publiczne:
	void NewState() – ustawia stan następny jako stan aktualny
	virtual string GetTypeState() – zwraca typ i stan komórki
	virtual bool IsRestricted() – sprawdź czy komórka jest ograniczona
	void SetState(cellState state) – ustawia aktualny stan komórki
	cellState GetState() – zwraca aktualny stan komórki
virtual void Evolve(int aliveCells) – wyznacza nowy stan komórki na podstawie stanu sąsiadujących komórek 
Klasa CellGroup:
Pola prywatne:
	Vector< vector<Cell *> > cellGroup – tablica komórek
Metody prywatne:
void ConvertStrToVect(string line) – zmienia wiersz pobrany z pliku tekstowego na wektor z komórkami
int GetAliveNeigbor(Cell * current, int i, int j) – wyznacza ilość żywych komórek względem aktualnie rozpatrywanej komórki
	Metody publiczne:
void LoadFromFile(string path) – odczyt tablicy znaków z pliku i utworzenie struktury danych - wektora wektorów
void Calculate NewStates() – wyznaczenie nowych stanów dla wszystkich komórek
void SetNewStates() – ustawienie nowych stanów dla wszystkich komórek
void Display() – wyświetlenie tablicy na ekranie
void SaveToFile(string pathName) – zapis danych do pliku
	Klasa CommandLine:
	Pola prywatne:
		string sourcePath – ścieżka pliku z danymi
		string resultPath – ścieżka pliku z wynikiem
		int iterations – liczba iteracji
	Metody publiczne:
void SetData(char * tab[], int length) – pobranie danych z wiersza poleceń i przypisanie wartości odpowiednim polom
string GetSourcePath() – zwraca ścieżkę odczytu
string GetResultPath() – zwraca ścieżkę zapisu
int GetIterations() – zwraca liczbę iteracji
Klasa FileReadWriteException
Pola prywatne:
	int type – typ błędu
	char * exceptionType – komunikat o błędzie
Metody publiczne:
const char * what() const throw() – zwraca komunikat identyfikujący typ błędu
	Klasa UserInputException:
	Metody publiczne:
const char * what() const throw() – zwraca komunikat identyfikujący typ błędu
	Klasa HardToReviveCell dziedzicząca po klasie Cell
	Pola prywatne:
		unsigned int cycles – licznik cykli potrzebnych do odrodzenia komórki (3)
		bool isReborning – czy komórka jest w fazie odradzania
Metody publiczne:
void Evolve(int aliveCells) – ustal stan komórki w następnym cyklu na podstawie stanów sąsiednich komórek
string GetTypeState() – zwraca typ i stan komórki
bool IsRestricted() – sprawdź czy komórka jest ograniczona
	Klasa HibernatedCell dziedzicząca po klasie Cell
	Pola prywatne:
		unsigned int cycles – licznik cykli hibernacji komórki 1-9
bool isHibernated – czy komórka jest w fazie hibernacji
	Metoda prywatna:
		void Hibernate() – komórka zostaje zahibernowana
	Metoda publiczna:
	void Evolve(int aliveCells) – ustal stan komórki w następnym cyklu na podstawie stanów sąsiednich komórek
string GetTypeState() – zwraca typ i stan komórki
bool IsRestricted() – sprawdź czy komórka jest ograniczona
	Klasa NormalCell dziedzicząca po klasie Cell
	Metoda publiczna:
	void Evolve(int aliveCells) – ustal stan komórki w następnym cyklu na podstawie stanów sąsiednich komórek
string GetTypeState() – zwraca typ i stan komórki
bool IsRestricted() – sprawdź czy komórka jest ograniczona
	Klasa RestrictedCell dziedzicząca po klasie Cell
	Metoda publiczna:
	void Evolve(int aliveCells) – ustal stan komórki w następnym cyklu na podstawie stanów sąsiednich komórek
string GetTypeState() – zwraca typ i stan komórki
bool IsRestricted() – sprawdź czy komórka jest ograniczona







