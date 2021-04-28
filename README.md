# Studentų pažymių apskaitos programa

Programa, kuri yra skirta studento galutinio pažymio skaičiavimui. Programa išveda studentų pasiekimų ataskaita pagal namų darbų, egzamino pažymius bei pasirinktą skaičiavimo būdą.

## Naudojimosi instrukcija

Paleidus programą, komandinėje eilutėje reikės:

* Pasirinkti, kad būtų duomenys nuskaitomi iš failo\
  ----------- Arba -----------
* Įvesti vardą ir pavardę
* Įvesti namų darbų bei egzamino pažymius

> Programoje galima pasirinkti, kad pažymiai būtų generuojami automatiškai (RANDOM).

* Pasirinkti skaičiavimo būdą
* Pasirinkti duomenų išvedimo vietą

Programa paskaičiuoja visų pažymių vidurkį ar medianą ir išveda galutinį balą.

### Programos vykdymo eiga

1. Pateikiama užklausa failo nuskaitymui.
```shell
>> Ar noretumete duomenis nuskaityti is failo? (y/n): n
```
2. Prašoma įvesti studento vardą ir pavardę.
```shell
>> Iveskite studento varda: Vardenis
>> Iveskite studento pavarde: Pavardenis
```
3. Pateikiama galimybė įvesti pažymių kiekį iš anksto.
```shell
>> Ar zinote pazymiu kieki? (y/n): y
>> Iveskite ne neigiama pazymiu kieki: 5
```
4. Pateikiama galimybė atsitiktinai sugeneruoti pažymius.
```shell
>> Ar norite atsitiktinai sugeneruoti pazymius? (y/n): y
```
5. Pagal pasirenkimus išvedami įvesti ar sugeneruoti pažymiai.
```shell
>> Sugeneruoti 5 pazymiai: 5 1 4 10 2
>> Sugeneruotas galutinis pazymys: 10
```
6. Pateikiama užklausa kito studento pridėjimui.
```shell
>> Ivesti dar viena studenta? (y/n): n
```
7. Leidžiama pasirinkti vidurkį ar/ir medianą galutinio balo skaičiavimui.
> Galutinis balas = 0.4 * pažymių (vidurkis / mediana) + 0.6 * egzamino pažymys.
```shell
>> Skaiciuoti naudojant (1) Vidurki, (2) Mediana, (3) Abu.
>> Pasirinkite (1-3): 1
```
8. Pateikiama užklausa duomenų išvedimui į failą.
```shell
>> Rezultatus pateikti faile? (y/n): n
```
9. Išvedamas visų studentų sąrašas.
```shell
Vardas         Pavarde         Galutinis (Vid.)
--------------------------------------------------
Vardenis       Pavardenis      7.76
```
## Spartos analizė (benchmark)

Programos veikimo spartos analizė paleidžiama komandinėje eilutėje prie `./main` (Linux aplinkoje) pridedant vėliavą `-bench`, etapo skaičių tarp `1 ir 5` ir duomenų konteinerio tipo skaičių tarp `0 ir 2`.
> Pirmas skaicius (etapas): \
> 1 - 1000 įrašų, 2 - 10000 įrašų, 3 - 100000 įrašų, 4 - 1000000 įrašų, 5 - 10000000 įrašų \
> Antras skaicius (duomenų konteinerio tipas): \
> 0 - Vector, 1 - Deque, 2 - List \
> Trečias skaicius (duomenų konteinerio skirstymo strategija) \
> Strategijas žiūrėti [čia](#konteinerio-skirstymo-spartos-analizė).
```
./main -bench [1-5] [0-2] [1-4]
```

Testavimo sistema:
- CPU - AMD Ryzen 1700x 3.4 Ghz
- RAM - 16GB 2400 Mhz
- SSD - 1TB SATA

Testavimo atvejai. Laikas pateiktas sekundėmis.

|                              | 1000     | 10000   | 100000  | 1000000 | 10000000 |
| :---:                        | :---:    | :---:   | :---:   | :---:   | :---:    |
| **Vector <br/> nuskaitymas** | 0.00548  | 0.03766 | 0.34299 | 3.38359 | 35.2422  |
| **Vector <br/> rūšiavimas**  | 0.00012  | 0.00141 | 0.01709 | 0.2188  | 2.89106  |
| **Vector <br/> skirstymas**  | 0.000036 | 0.00037 | 0.00693 | 0.12256 | 1.69828  |
| **Vector <br/> iš viso**     | 0.005636 | 0.03944 | 0.36701 | 3.72495 | 39.83154 |
| | | | | | |
| **Deque <br/> nuskaitymas**  | 0.00566  | 0.03823 | 0.34723 | 3.47963 | 35.052   |
| **Deque <br/> rūšiavimas**   | 0.00016  | 0.00198 | 0.02271 | 0.30543 | 3.92397  |
| **Deque <br/> skirstymas**   | 0.000056 | 0.00057 | 0.01297 | 0.177   | 2.82585  |
| **Deque <br/> iš viso**      | 0.005876 | 0.04078 | 0.38291 | 3.96206 | 41.80182 |
| | | | | | |
| **List<br/> nuskaitymas**    | 0.00533  | 0.03677 | 0.33925 | 3.37886 | 34.5023  |
| **List <br/> rūšiavimas**    | 0.000081 | 0.00128 | 0.03005 | 0.64562 | 11.9655  |
| **List <br/> skirstymas**    | 0.00009  | 0.0008  | 0.02499 | 0.30177 | 4.2005   |
| **List <br/> iš viso**       | 0.005501 | 0.03885 | 0.39429 | 4.32625 | 50.6683  |

## Konteinerio skirstymo spartos analizė

### Konteinerio skirstymas yra vykdomas pasinaudojant 3 skirtingas strategijas (visose strategijose naudojamas `std::find_if()` metodas):

### 1 strategija:
Studentų įrašai skirstomi į du naujus to paties tipo konteinerius. Greičiausiai veikia naudojant `Vector` tipo konteinerį. Prie 10000000 įrašų atminties sunaudojimas 600 MB didesnis nei naudojant 3 strategiją.
|            | 1000     | 10000   | 100000  | 1000000 | 10000000 |
| :---:      | :---:    | :---:   | :---:   | :---:   | :---:    |
| **Vector** | 0.000056 | 0.00046 | 0.00904 | 0.15298 | 2.11046  |
| **Deque**  | 0.000085 | 0.00098 | 0.01829 | 0.20807 | 3.01634  |
| **List**   | 0.00011  | 0.0013  | 0.02878 | 0.3202  | 4.38611  |

### 2 strategija:
Studentų įrašai skirstomi panaudojant vieną naują to paties tipo konteinerį, o perkelti įrašai yra ištrinami **po vieną** iš pradinio konteinerio. Greičiausiai veikia naudojant `List` tipo konteinerį. Naudojant `Vector` ar `Deque` tipo konteinerius skirstymas nuo 1000000 įrašų užtrunka daugiau nei 10 min.
|            | 1000     | 10000   | 100000  | 1000000 | 10000000 |
| :---:      | :---:    | :---:   | :---:   | :---:   | :---:    |
| **Vector** | 0.001709 | 0.13318 | 13.0799 |    -    |    -     |
| **Deque**  | 0.00208  | 0.18571 | 18.2525 |    -    |    -     |
| **List**   | 0.000039 | 0.00039 | 0.01402 | 0.14046 | 1.99394  |

### 3 strategija:
Studentų įrašai skirstomi panaudojant vieną naują to paties tipo konteinerį, o perkelti įrašai yra ištrinami **vienu kartu** iš pradinio konteinerio. Greičiausiai veikia naudojant `Vector` tipo konteinerį.
|            | 1000     | 10000   | 100000  | 1000000 | 10000000 |
| :---:      | :---:    | :---:   | :---:   | :---:   | :---:    |
| **Vector** | 0.000036 | 0.00043 | 0.00937 | 0.13769 | 1.77564  |
| **Deque**  | 0.000058 | 0.00067 | 0.01576 | 0.16829 | 2.6044   |
| **List**   | 0.000082 | 0.00089 | 0.02602 | 0.31854 | 4.18603  |

Trečia strategija yra labiau optimizuota laiko ir atminties atžvilgiu nei pirma ar antra, todėl labiausiai tinka darbui su dideliais duomenų kiekiais.

### Vektoriaus optimizacija (4 strategija)
Buvo bandoma `Vector` klasę optimizuoti pasinaudojant `std::copy()` metodu nesėkmingai. Šios implementacijos vykdymo laikas yra ilgesnis nei prieš tai naudojamos. Optimizuoti labiau nepavyko, nes jau 3 strategijoje yra naudojamas `find_if()` metodas, kurio pagalba randamas atskirimo taškas. 3 strategijoje naudojamas būdas yra labiausiai optimizuotas iš kitų bandytų strategijų.

## Spartos analizė tarp struktūros ir klasės

Nuo [v1.1](https://github.com/metroff/VU_OP_uzd2_2/releases/tag/v1.1). Spartos analizė tarp struktūros ir klasės naudoja `Vector` tipo konteinerį ir [3 strategiją](#3-strategija).

| Optimizacija    | Struktūra |         | Klasė   |         | 
| :---            | :---:     | :---:   | :---:   | :---:   |
|                 | 100000    | 1000000 | 100000  | 1000000 |
| **O1**          |           |         |         |         |
| **Nuskaitymas** | 0.3585    | 3.47208 | 0.34901 | 3.39736 |
| **Skirstymas**  | 0.02498   | 0.34083 | 0.02763 | 0.36485 |
| **Išvedimas**   | 0.15058   | 1.5258  | 0.15434 | 1.56187 |
| **Iš viso**     | 0.53406   | 5.33871 | 0.53098 | 5.32408 |	
|                 |           |         |         |         |
| **O2**          |           |         |         |         |
| **Nuskaitymas** | 0.35197   | 3.40123 | 0.34419 | 3.39506 |
| **Skirstymas**  | 0.02561   | 0.35605 | 0.0284  | 0.36742 |
| **Išvedimas**   | 0.14424   | 1.45616 | 0.14522 | 1.47491 |
| **Iš viso**     | 0.52182   | 5.21344 | 0.51781 | 5.23739 |
|                 |           |         |         |         |
| **O3**          |           |         |         |         |
| **Nuskaitymas** | 0.35336   | 3.44756 | 0.34633 | 3.3711  |
| **Skirstymas**  | 0.02633   | 0.35089 | 0.02706 | 0.3656  |
| **Išvedimas**   | 0.14392   | 1.44935 | 0.14842 | 1.48009 |
| **Iš viso**     | 0.52361   | 5.2478  | 0.52181 | 5.21679 |

Programa greičiausiai veikia naudojant O3 optimizaciją ir Studento klasę. Su O2 optimizacija greičiausiai veikia naudojant Studento struktūrą. Failo dydis skiriasi tik naudojant O2 optimizaciją. Naudojant kitas optimizacijas failo dydis vienodas.

| Failo dydis | O1    | O2    | O3    | 
| :---        | :---: | :---: | :---: |
| Struktūra   | 232KB | 226KB | 248KB |
| Klasė       | 232KB | 232KB | 248KB |


## Įdiegimo instrukcija

1. Iš [Releases](https://github.com/metroff/VU_OP_uzd2/releases) aplanko parsisiųskite vieną iš programos versijų ir ją išsiarchyvuokite.
2. Susikompiliuoti `main.cpp` ir `include` aplanke esančius failus naudojant įrankius, kurie palaiko **C++11**.
    - Naudojant g++ įrankį (Linux aplinkoje):
    ```
    g++ -std=c++11 include/*.cpp main.cpp -o main && ./main
    ```
    - Naudojant makefile (Linux aplinkoje):
    ```
    make && ./main
    ```
3. Pasileisti sukompiliuotą failą.

## Changelog
- [v1.1](https://github.com/metroff/VU_OP_uzd2_2/releases/tag/v1.1) - Šioje versijoje `Student` klasėje implementuota `c++` trijų taisyklė, t.y. pridėtas kopijavimo konstruktorius ir operatorius, taip pat nurodytas destruktorius.
- [v1.1](https://github.com/metroff/VU_OP_uzd2_2/releases/tag/v1.1) - Šioje versijoje naudojama Studento klasė vietoj struktūros. Spartos analizę tarp struktūros ir klasės galima rasti [čia](#spartos-analizė-tarp-struktūros-ir-klasės).
- [v1.0](https://github.com/metroff/VU_OP_uzd2/releases/tag/v1.0) - Šioje versijoje pridėta [konteinerio skirstymo spartos analizė](#konteinerio-skirstymo-spartos-analizė). Pridėtas skirstymo strategijos pasirinkimas.
- [v0.5](https://github.com/metroff/VU_OP_uzd2/releases/tag/v0.5) - Šioje versijoje patobulinta [spartos analizė](#spartos-analizė-benchmark). Pridėtas duomenų konteinerio (`Vector`, `Deque`, `List`) pasirinkimas.
- [v0.4](https://github.com/metroff/VU_OP_uzd2/releases/tag/v0.4) - Šioje versijoje pridėta programos spartos analizė, kuri susideda iš:
    - Įrašų failo kūrimo;
    - Duomenų iš failo nuskaitymo;
    - Studentų rūšiavimo ir paskirstymo į dvi grupes pagal vidurkį;
    - Surūšiuotų studentų išvedimo į du skirtingus failus;
- [v0.3](https://github.com/metroff/VU_OP_uzd2/releases/tag/v0.3) - Šioje versijoje `main.cpp` buvęs kodas išskirstytas į failus, kurie yra `include` aplanke. Taip pat, realizuotas `Išimčių` (`Exception`) valdymas ir pagerintas atsitiktinių skaičių generavimas.
- [v0.2](https://github.com/metroff/VU_OP_uzd2/releases/tag/v0.2) - Šioje versijoje realizuotas studentų informacijos nuskaitymas iš failo `kursiokai.txt`. Failo `kursiokai.txt` struktūra turėtų būti:
    > Studento vardas (tarpas) Studento pavardė (tarpas) N pažymių atskirtų tarpais (tarpas) Egzamino pažymys
    ```
    Vardas                   Pavarde                    ND1       ND2       ND3       ND4       ND5       ND6       ND7       ND8       ND9      ND10      Egz.
    Vardas1                 Pavarde1                      8         5         8         3         3         7         3        10         2         3         3
    Vardas2                 Pavarde2                      6         6         5         5         1         8         4         3         3         8         7
    Vardas3                 Pavarde3                      8         3         2         7         7         9         5        10         9         9         5
    Vardas4                 Pavarde4                      7         9         8         9         6         8         8         8         3         9         1
    Vardas5                 Pavarde5                      7         4         6         5         8         2         1         2         8         9         9
    ```
- [v0.1](https://github.com/metroff/VU_OP_uzd2/releases/tag/v0.1) - Šioje versijoje realizuotas studentų ir jų pažymių įvedimas. Pažymiams suagoti buvo naudojami: C kalbos masyvas `main-array.cpp` ir vektorius `main-vector.cpp`. Pažymiai gali būti atsitiktinai generuojami, o galutinis įvertinimas gali būti paskaičiuotas naudojant **Vidurkį** arba **Medianą**.
    - [v0.1.1](https://github.com/metroff/VU_OP_uzd2/releases/tag/v0.1.1) - Studentai saugomi C kalbos masyve `main-array.cpp`.
