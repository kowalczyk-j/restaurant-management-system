# projekt_PROI_restauracja

Plik wykonywalny app2 został wyjątkowo dodany w celu prezentacji działania GUI.
Zbudowanie tego pliku może nie być możliwe ze względu na wymagane biblioteki

## Nasz cuowny projekt
A tutaj zostanie dodana dokumantcja

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
    - *set_name(string name)*, ustawiająca imię (void)
    - *set_surname(string surname)*, ustawiająca nazwisko (void)
    - *set_employee_id(unsigned int id)*, ustawiająca identyfikator pracownika (unsigned int)
    - *set_salary(Money salary)*, ustawiająca pensję pracownika (Money)
    - *set_address(Addres address)*, ustawiająca adres pracownika (Addres)
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
- *parse_staff_from_json(string path)*, odczytująca pliki JSON i zwracająca obiekt typu Json::Value
- *save_staff_to_json(Json::Value staff, string path), zapisująca dane do pliku JSON (void).

