## Magazyn firmy

Przygotuj program, który pozwala na spis produktów z magazynu.

    Zaprojektuj strukturę dla produktu, która będzie zawierać nazwę przedmiotu, cenę jednostkową i jego ilość.
    Wykorzystaj std::vector do przechowywania wszystkich produktów.
    Napisz tekstowy interfejs użytkownika, który może:
    - wyświetlić spis (raport) (możesz użyć \t),
    - dodać produkt,
    - usunąć produkt,
    - zmienić ilość produktu,
    - Wyszukać produkt po nazwie,
    - zoptymalizować magazyn (połączyć produkty o tej samej nazwie w jeden),
    - zakończyć program.
    Program przy starcie wczytuje spis produktów z pliku (przekazany jako argv[1] lub domyślnie “magazyn.txt”) i zapisuje go do niego przy wyjściu:
        Strumienie std::ifstream i std::ofstream, analogicznie do std::cin, std::cout.

Przygotuj program, tak aby był odporny na dziwne pomysły użytkowników (np. nie pozwalaj na ujemny stan ilości przedmiotu, ujemną cenę, itd).