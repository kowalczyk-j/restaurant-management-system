# projekt_PROI_restauracja (Z05)
*Kajetan Rożej, Kinga Świderek, Magdalena Dudek, Jakub Kowalczyk*

## Tematyka projektu oraz krótki opis
Stworzyliśmy program, który pomoże menadżerowi sieci restauracji w zarządzaniu lokalami i personelem. Całość została przedstawiona w przyjaznym dla użytkownika GUI. Za jego pomocą można wprowadzać do systemu nowe zamówienia, modyfikować menu danej restauracji, ustalać nowe pensje pracowników, zmieniać skład kadry czy chociażby kontrolować stan spiżarni.

## Struktura
W skład naszego projektu wchodzą następujące foldery:
- *gui*, w którym składowane są pliki wykorzystywane przez interfejs graficzny
- *rsc*, zawierający grafiki wykorzystywane przez GUI
- *lib*, zawierający zestaw bibiotek zewnętrznych niezbędnych do uruchoeminia GUI
- *src*
    - *dish_menu*: klasy Dish oraz Menu
    - *employees*: klasy Employee oraz dziedziczące: Cook, Deliverer, Manager, Waiter, oraz klasa szablonowa Staff
    - *order*: klasa bazowa Order oraz dziedziczące: DeliveryOrder oraz OnSiteOrder
    - *pantry*: klasy Pantry oraz Product
    - *restaurant*: klasa Restaurant
    - *utils*: klasy Money oraz Addres, wykorzystywane w definicji powyższych klas

## Uruchaminie

UWAGA Plik wykonywalny guiApp został wyjątkowo dodany w celu prezentacji działania GUI.
Zbudowanie tego pliku może nie być możliwe, umieszczono jednak CMakeList użyty do tego celu - jest on dostępny pod nazwą CMakeListGUI.txt .

Komilacja programu dokonywana jest poprzez program CMake. W folderze projektu z konsoli należy wywołać
cmake --build {ścieżka_do_projektu}/build --config Debug --target app -j 6 --
(przykładowy program, wypiszę kilka rzeczy na ekranie)
lub
cmake --build {ścieżka_do_projektu}/build --config Debug --target tests -j 6 --
(testy jednostkowe do wybranych klas).

Aby uruchomić aplikację w trybie z interfejsem graficznym należy wywołać następującą komende:
export LD_LIBRARY_PATH={ścieżka_do_projeku}/lib/lib/ && ./guiApp

W każdym z powyższych przypadków {ścieżka_do_projektu} powinno zostać zastąpione pełną ścieżką do projektu.



### Employee
Klasa bazowa pracownika. Zawiera pola:
- (unsigned int) *employee_id*;
- (string) *name*;
- (string) *surname*;
- (Addres) *address*;
- (Money) *salary*;

Zdefiniowane są dwa konstruktory:
- przyjmujący jako argumenty employee_id, name, surname, address, salary
- przyjmujący jako argument wartości odczytane z pliku JSON (typ argumentu: Json::Value)

Oraz metody:
- ***gettery***
    - *get_name()*, zwracająca imię (string)
    - *get_surname()*, zwracająca nazwisko (string)
    - *get_employee_id()*, zwracająca identyfikator pracownika (unsigned int)
    - *get_salary()*, zwracająca pensję pracownika (Money)
    - *get_address()*, zwracająca adres pracownika (Addres)
- ***settery***
    - *set_name(string name)*, ustawiająca imię
    - *set_surname(string surname)*, ustawiająca nazwisko
    - *set_employee_id(unsigned int id)*, ustawiająca identyfikator pracownika
    - *set_salary(Money salary)*, ustawiająca pensję pracownika
    - *set_address(Addres address)*, ustawiająca adres pracownika
- *parse_to_json()*, wirtualna funkcja zwracająca dane pracownika przekonwertowane do formatu JSON (Json::Value)
- *save_to_json(string path)*, zapisująca dane pracownika do pliku JSON (void)
- *print(ostream& os)* wirtualna funkcja wysyłająca do strumienia dane o pracowniku

Ponadto, w pliku Employee.h zdefiniowana jest funkcja *parse_employee_from_json(string path)*, odczytująca dane o pracowniku z pliku JSON (zwracany typ: Json::Value)

#### Klasy dziedziczące po Employee
Każda z klas dziedziczących po Employee ma zdefiniowany operator << oraz metodę *parse_to_json()*. Obie dodają informację na temat stanowiska.
- ***Cook***
    - zawiera dodatkowe pole: *is_chef*, wskazujące czy dany kucharz jest również szefem kuchni.
    - dodatkowe gettery i settery: *get_ischef()*, *set_ischef()*, zmieniająca wartość *is_chef* na *true* oraz *remove_ischef()*, zmieniająca wartość *is_chef* na *false*
- ***Deliverer*** i ***Waiter***
    - zawierają dodatkowe pola: *tips* oraz *orders_to_serve* oraz metodę *new_tip(double tip)*, dodającą wartość tip do pola tips.
- ***Manager***

### Staff
Klasa szablonowa Staff przechowuje dane na temat jednego typu pracowników w wektorze *staff*.
Zawiera dwa konstruktory:
- przyjmujący jako argument wektor staff
- przyjmujący jako argument dane z pliku JSON (typ argumentu: Json::Value)

Oraz metody:
- ***gettery***:
    - *get_staff()*, zwracająca wektor staff
    - *size()*, zwracająca ilość zatrudnionych pracowników
- *operator[]*, zwracający pracownika na danej pozycji (size_t) w wektorze staff
- *fire(size_t position)*, usuwająca z wektora staff pracownika o danym indeksie. Wyrzuca wyjątek *PositionOutOfBounds*, gdy indeks jest większy niż ilość elementów w wektorze staff
- *employ(const T& employee)*, dodaje pracownika do staff. Rzuca wyjątek *AlreadyStaffMember*, jeśli pracownik *employee* znajduje się już w kolekcji staff
- *parse_to_json()*, zwracająca dane o każdym pracowniku (Json::Value)

Zdefiniowane są również funkcje:
- *parse_staff_from_json(string path)*, odczytująca plik JSON i zwracająca obiekt typu Json::Value
- *save_staff_to_json(Json::Value staff, string path)*, zapisująca dane do pliku JSON.


### GUI
Graficzny interfejs uzytkownika został wykonany z wykorzystaniem bibilioteki Qt w wersji 5.15. Katalog gui zawiera 14 folderów z których każdy reprezentuje jedno okno
programu z plikami .ui, .cpp i .h (w tym okno główne). Ponadto w folderze znajduje się plik main.cpp uruchamiający GUI.

UWAGA! Ze względu na brak czasu obsługa wyjątków z poziozmu GUI nie została zaimplamentowana. W związku z tym operacje takie jak:
- dodanie zamówienia o takim samym id jak zamówienie istniejące
- dodanie pracownika o takim samym id jak zamówienie istniejące
- usunięcie ilości produktu do wartości mniejszej niż 0
spowodują zamknięcie okna programu

### Orders
Klasa bazowa odpowiadająca zamówieniu w restauracji. Dwie dziedziczące klasy DeliveryOrders i OnSiteOrders reprezentują odpowiednio zamówienia z dostawą i zamówienia
obsługiwane na miejscu. Opis atrybutów każdej z klas znajduje się przy jej definicji.

### Restaurant
Klasa reprexentująca całą restaurację wraz z:
- spiżarnią
- menu
- pracownikami(kucharzami, dostawcami, managerami, kelnerami)
- aktywnymi zamówieniami(na miejscu i z dostawą)

Poszczególne atrybuty i metody klasy zostały opisane w jej definicji. Jest to główna klasa programu.

### Testy jednostkowe
Testy jednostkowe klas (w pliku *test.cpp*) przeprowadzone zostały w frameworku Google test. Staraliśmy się testować zarówno przypadki skrajne, jak i typowe. Ważnym elementem testów jest sprawdzenie zdefiniowanych wyjątków - czy są prawiłowo obsłużone. W przypadku testowania zapisu i odczytu plików json, skupiliśmy się na przetestowaniu ich za pomocą pisania kodu w main.cpp. Zwracanie wartości Json::Value i jej prawidłowe formatowanie umieśliśmy również w Google testach.
