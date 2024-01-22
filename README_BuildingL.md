# Instrukcje budowania

Szczegółowe instrukcje budowania projektu na systemie Linux.

## Potrzebne paczki

- cmake (zalecana wersja: 3.25)
- g++ / clang (zalecana wersja: g++ 12.2 / clang 14.0.5)
- ninja-build (zalecana wersja: 1.11.1)
- xorg-dev

## Budowanie projektu

### (1) 

W folderze głównym projektu należy wykonać polecenie:

    cmake . --preset <konfiguracja>

gdzie dostępnymi (na systemie Linux) konfiguracjami są:
- unixlike-gcc-release
- unixlike-clang-release
- unixlike-gcc-debug
- unixlike-clang-debug

### (2)

w folderze `build/<konfiguracja>/` wywołać polecenie:

    ninja


## Zbudowany projekt

Plik wykonywalny i cały folder assets w zbudowanym projekcie znajdować się będą w folderze `build/<konfiguracja>/mini_golf/`.
