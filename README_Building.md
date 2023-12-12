# Instrukcje buodwania

Szczegółowe instrukcje budowania projektu.

<details>
<summary>Visual Studio</summary>

## Budowanie przy pomocy Visual Studio

Budowanie przy pomocy VS jest banalne. Wystarczy otworzyć projekt. VS sam znajdzie pliki CMake. Należy u góry wybrać jedynie rodzaj konfiguracji i plik wykonywalny. Następnie można zbudować projekt kombinacją klawiszy ctrl + shift + B, lub zbudować i uruchomić przyciskiem F5.

</details>

<details>
<summary>Terminal</summary>

## Budowanie ręczne w terminalu

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

przejdź do folderu build/
    

</details>
