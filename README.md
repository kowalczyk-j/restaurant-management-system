# projekt_PROI_restauracja (Z05)
*Kajetan Rożej, Kinga Świderek, Magdalena Dudek, Jakub Kowalczyk*

## Tematyka projektu oraz krótki opis
Stworzyliśmy program, który pomoże menadżerowi sieci restauracji w zarządzaniu lokalami i personelem. Całość została przedstawiona w przyjaznym dla użytkownika GUI. Za jego pomocą można wprowadzać do systemu nowe zamówienia, modyfikować menu danej restauracji, ustalać nowe pensje pracowników, zmieniać skład kadry czy chociażby kontrolować stan spiżarni.

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


## Struktura
W skład naszego projektu wchodzą następujące foldery:
- *gui*, w którym składowane są pliki wykorzystywane przez interfejs graficzny
- *rsc*, zawierający grafiki wykorzystywane przez GUI
- *lib*, zawierający zestaw bibiotek zewnętrznych niezbędnych do uruchomienia GUI
- *src*
    - *dish_menu*: klasa Dish
    - *employees*: klasy Employee oraz dziedziczące: Cook, Deliverer, Manager, Waiter
    - *order*: klasa bazowa Order oraz dziedziczące: DeliveryOrder oraz OnSiteOrder
    - *pantry*: klasa Product
    - *restaurant*: klasa Restaurant
    - *utils*: klasy Money oraz Addres, wykorzystywane w definicji powyższych klas
- klasa szablonowa *Database.h*, służąca jako baza danych do obiektów konkretnego typu


### Employee
Abstrakcyjna klasa pracownika. Zawiera pola:
- (unsigned int) *employee_id*;
- (string) *name*;
- (string) *surname*;
- (string) *position_name*;
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
    - *get_position()*, zwracająca stanowisko, na którym pracuje
- ***settery***
    - *set_name(string name)*, ustawiająca imię
    - *set_surname(string surname)*, ustawiająca nazwisko
    - *set_id(unsigned int id)*, ustawiająca identyfikator pracownika
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
    - zawierają dodatkowe pola: *tips* oraz metodę *new_tip(double tip)*, dodającą wartość tip do pola tips.
- ***Manager***

### Dish
Klasa przechowująca informacje o daniu, a konkretnie:
- *id dania* służące do identyfikacji go w menu;
- *nazwa dania*;
- *typ dania* wybierany z klasy enum jako przystawka, zupa, danie główne, deser lub napój;
- *informacja vege* służy do oznaczania dań dla wegetarian;
- *składniki* jako wektor struktury Ingredient która przechowuje id produktu i jego potrzebną ilość do wykonania dania;
- *alergeny* jako set, aby uniknąć powtarzania się tych samych pozycji;

Klasa posiada konstuktor domyślny, przyjmujący także wskazanie na danę bazych produktów, aby umożliwić automatyczne pobranie listy alergenów ze składników.
Wsród metod dostępne jest także dodanie i usunięcie składniku do listy, a także wyprintowanie składników czy alergenów.
Zdefiniowany został operator wyprowadzający do strumienia cout w postaci pozycji dania do widoku w Menu.
Za współpracę z plikami odpowiadają metody parsujące do formatu Json:Value oraz tworzące obiekt z wartości tego typu.

### Product
Zawiera klasę bazową Product, na którą składają się pola:
- unsigned int product_id=0 – id produktu, o domyślnej wartości 0;
-    string name – nazwa produktu
-    units unit – jednostka, w  której ma być przechowany produkt
-    string alergen –  alergeny
-    int quantity – ilość produktu aktualnie znajdującego się w spiżarni
-    int available_quantity – dostępna ilość uwzględniająca przyjęte zamówienia


Klasę tworzą metody: 
    -	Gettery:
    -	 Get_name();
    -	Get_unit() – zwraca jednostkę w postaci stringa, po odnalezieniu jej w units_map;
    -	Get_enum_unit() – zwraca jednostkę w postaci enuma;
    -	Get_allrgen();
    -	Get_id();
    -	Get_quantity();
    -	Get_avaliable_qunatity();
-	Setery:
    -	Set_name()
    -	Set_allergen()
    -	Set_id()
-	operator+=(int quantity_to_add) – jako argument przyjmuje quantity_to_add, dodaje pewną ilość produktu(quantity to add) na stan zwiększając jednocześnie ilość dostępnego produktu;
-	operator-=(int quantity_to_sub) – jako argument przyjmuje ilość produktu do usunięcia ze spiżarni; redukuje jednocześnie ilość dostępnego produktu(avaliable_quantity);
-	reserve(int quantity) – jako argument przyjmuje ilość produktu do zarezerwowania na poczet zamówienia; rezerwacja produktu objawia się obniżeniem available_qunatity danego produktu;
-	release(int quantity) – jako argument przyjmuje quantity, ilość produktu, który należy zwolnić, czyt. dodać do quantity; produkt zostaje zwolniony po usunięciu zamówienia;
-	use_product(int quantity_to_take) – jako argument przyjmuje quantity_to_take, czyt. wykorzystana ilość produktu; metoda odejmuje wykorzystaną ilość produktu po faktycznym zrealizowaniu zamówienia
-	print_product() – wypisuje informacje o produkcie;
-	parse_to_json() – konwertuje informacje o produkcie do formatu json;


### Orders
Klasa bazowa odpowiadająca zamówieniu w restauracji. Dwie dziedziczące klasy DeliveryOrders i OnSiteOrders reprezentują odpowiednio zamówienia z dostawą i zamówienia
obsługiwane na miejscu. Opis atrybutów każdej z klas znajduje się przy jej definicji.

### Restaurant
Klasa reprezentująca całą restaurację wraz z:
- spiżarnią
- menu
- pracownikami(kucharzami, dostawcami, managerami, kelnerami)
- aktywnymi zamówieniami i ich historią

Jest to główna klasa programu, która reprentuje całą restaurację i zarządza wszystkimi procesami. Jako pośrednik między użytkownikiem a "bazami danych" dba o intgralność trzymnaych danych
(np. nie pozwala na usunięcie ze spiżarni składnika będącego aktualnie w daniu) i stale monitoruje ilość zapsów, pomagając przyjmować tylko te zamówienia, które faktycznie mogą zostać zrealizowane.

### Database
Klasa szablonowa o funkcjonalności bazy danych, umożlwia łatwe i uporządkowane przechowywanie obiektów klas z polem przeznaczonym na unikalne id. Dzięki funkcjoalności takiej jak autmatyczny dobór wolnego id, możliwość łatwego pobierania konkretnego obiektu jak i wszytskich danych idelnie nadaje się do implementacji restauracyjnej spiżarni, listy dań, czy zamówień.

### GUI
Graficzny interfejs uzytkownika został wykonany z wykorzystaniem bibilioteki Qt w wersji 5.15. Katalog gui zawiera 14 folderów z których każdy reprezentuje jedno okno
programu z plikami .ui, .h (w tym okno główne). Ponadto w folderze znajduje się plik main.cpp uruchamiający GUI.

### Testy jednostkowe
Testy jednostkowe klas (w pliku *test.cpp*) przeprowadzone zostały we frameworku Google test. Staraliśmy się testować zarówno przypadki skrajne, jak i typowe. Ważnym elementem testów jest sprawdzenie zdefiniowanych wyjątków - czy są prawiłowo obsłużone. W przypadku testowania zapisu i odczytu plików json, skupiliśmy się na przetestowaniu ich za pomocą pisania kodu w main.cpp. Zwracanie wartości Json::Value i jej prawidłowe formatowanie umieśliśmy również w Google testach. Sprawne testowanie podstawowych akcji umożliwiło nam także GUI, w którym można było wygodnie obserwować zmiany wprowadzanych wartości.


### Podsumowanie
Oczywiście pomimo wielu naszych wysiłków i starań przezntowany program dalej nie jest kompletny i mógłby podlegać dalszemu rozwojowi. Z pomysłów, które przyszły nam do głowy warto wspomnieć
chociażby o rozróżnianiu poszczególnych partii produktów "wchodzących" na magazyn, dodanie weryfikacji poszczególnych pól klasy adresownej, czy, bardzo potrzebne, wczytywnaie restauacji z pliku JSON. Graficzny interfejs użytkownika również w wielu aspektach powinien zostać dopracowany, aby korzytanie z aplikacji było łatwe i przyjemne. Mamy jednak nadzieję, że pomimo tak licznych możliwości rozwoju nasz program spełnia podstawowe postawione przed nim cele
