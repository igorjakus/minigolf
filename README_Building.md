# Instrukcje buodwania

Szczegółowe instrukcje budowania projektu.

## Instrukcje budowania dla:

<details>
<summary>Visual Studio</summary>

Budowanie przy pomocy VS jest banalne. Wystarczy otworzyć projekt. VS sam znajdzie pliki CMake. 
Należy u góry wybrać jedynie rodzaj konfiguracji i plik wykonywalny. 
Następnie można zbudować projekt kombinacją klawiszy ctrl + shift + B, lub zbudować i uruchomić przyciskiem F5. 
W razie problemów z kompilacją pomocne może być przejście z kompilatora MSVC na Clang lub usunięcie projektu, a następnie ponowne jego sklonowanie.

</details>

<details>
<summary>Terminal</summary>

Budowanie projektu odbywa się w dwóch prostych krokach:
1) Utworzenie konfiguracji przy pomocy CMake
2) Zbudowanie programu przy pomocy generatora Ninja

Krok 1 nie jest wymagany jeżeli od ostatniego zbudowania projektu wprowadzono wyłącznie zmiany do plików źródłowych (tzn. program zbuduje się poprawnie tak długo jak nie dodasz nowego pliku).

### (1) 

W folderze głównym projektu wydaj polecenie:

    cmake . --preset <konfiguracja>

gdzie dostępnymi (na systemach Linux i MacOS) konfiguracjami są:
- unixlike-gcc-debug
- unixlike-gcc-release
- unixlike-clang-debug
- unixlike-clang-release

### (2)

przejdź do folderu `build/<konfiguracja>/` i wywołaj polecenie:

    ninja

</details>

## Ustawienia konfiguracji

Konfiguracja zostanie utworzona z ustawieniami znajdującymi się w pliku `ProjectSettings.cmake`. Aby je zmienić należy wartości odpowiednich ustawień zmienić na `ON` lub `OFF`.

Budując w terminalu polecenie `cmake` należy po zmianie ustawień wywoływać z dodatkową flagą na końcu `--fresh`.

## Zbudowany projekt

Plik wykonywalny i cały folder assets w zbudowanym projekcie znajdować się będą w folderze `build/<konfiguracja>/mini_golf/`.

