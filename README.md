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
- przyjmujący jako argument wartości odczytane z pliku json (typ argumentu: Json::Value)

Oraz metody:
- *get_name()*, zwracająca imię (string)
- *get_surname()*, zwracająca nazwisko (string)
- *get_employee_id()*, zwracająca identyfikator pracownika (unsigned int)
- *get_salary()*, zwracająca pensję pracownika (Money)
- *set_name()*, ustawiająca imię (void)
- *set_surname()*, ustawiająca nazwisko (void)
- *set_employee_id()*, ustawiająca identyfikator pracownika (unsigned int)
- *set_salary()*, ustawiająca pensję pracownika (Money)



