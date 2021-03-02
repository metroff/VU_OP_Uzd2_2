# Studentų pažymių apskaitos programa

Programa, kuri yra skirta apskaičiuoti studento galutinį pažymį.

## Naudojimosi instrukcija

Paleidus programą, komandinėje eilutėje reikės

* Pasirinkti, kad būtų duomenys nuskaitomi iš failo\
  ----------- Arba -----------
* Įvesti vardą ir pavardę
* Įvesti namų darbų bei egzamino pažymius

> Programoje galima pasirinkti, kad pažymiai būtų generuojami automatiškai (RANDOM).

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
7. Leidžiama pasirinkti vidurkį ar medianą galutinio balo skaičiavimui.
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
## Įdiegimo instrukcija

1. Iš [Releases](https://github.com/metroff/VU_OP_uzd2/releases) aplanko parsisiųskite vieną iš programos versijų ir ją išsiarchyvuokite.
2. Susikompiliuoti `main.cpp` failą naudojant įrankius, kurie palaiko **C++11**.
3. Pasileisti sukompiliuotą failą.

## Changelog

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
