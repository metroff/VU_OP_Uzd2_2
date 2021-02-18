# Studentų pažymių apskaitos programa

Programa, kuri yra skirta apskaičiuoti studento galutinį pažymį.

## Naudojimosi instrukcija

Paleidus programą, komandinėje eilutėje reikės

* Įvesti vardą ir pavardę
* Įvesti namų darbų bei egzamino pažymius

> Programoje galima pasirinkti, kad pažymiai būtų generuojami automatiškai (RANDOM).

Programa paskaičiuoja visų pažymių vidurkį ar medianą ir išveda galutinį balą.

### Programos vykdymo eiga

1. Prašoma įvesti studento vardą ir pavardę
```shell
>> Iveskite studento varda: Vardenis
>> Iveskite studento pavarde: Pavardenis
```
2. Pateikiama galimybė įvesti pažymių kiekį iš anksto.
```shell
>> Ar zinote pazymiu kieki? (y/n): y
>> Iveskite ne neigiama pazymiu kieki: 5
```
3. Pateikiama galimybė atsitiktinai sugeneruoti pažymius.
```shell
>> Ar norite atsitiktinai sugeneruoti pazymius? (y/n): y
```
4. Pagal pasirenkimus išvedami įvesti ar sugeneruoti pažymiai.
```shell
>> Sugeneruoti 5 pazymiai: 5 1 4 10 2
>> Sugeneruotas galutinis pazymys: 10
```
5. Pateikiama užklausa kito studento pridėjimui.
```shell
>> Ivesti dar viena studenta? (y/n): n
```
6. Leidžiama pasirinkti vidurkį ar medianą galutinio balo skaičiavimui.
> Galutinis balas = 0.4 * pažymių (vidurkis / mediana) + 0.6 * egzamino pažymys.
```shell
>> Skaičiavimams naudoti mediana? (y-mediana, n-vidurkis) (y/n): n
```
7. Išvedamas visų studentų sąrašas.
```shell
Vardas         Pavarde         Galutinis (Vid.)
--------------------------------------------------
Vardenis       Pavardenis      7.76
```
## Įdiegimo instrukcija

1. Iš [Releases](https://github.com/metroff/VU_OP_uzd2/releases) aplanko parsisiųskite vieną iš programos versijų ir ją išsiarchyvuokite.
2. Susikompiliuoti `main-array.cpp` ar `main-vector.cpp` failą naudojant įrankius, kurie palaiko **C++11**.
3. Pasileisti sukompiliuotą failą.

## Changelog

- [v0.1](https://github.com/metroff/VU_OP_uzd2/releases/tag/v0.1) - Šioje versijoje realizuotas studentų ir jų pažymių įvedimas. Pažymiams suagoti buvo naudojami: C kalbos masyvas `main-array.cpp` ir vektorius `main-vector.cpp`. Pažymiai gali būti atsitiktinai generuojami, o galutinis įvertinimas gali būti paskaičiuotas naudojant **Vidurkį** arba **Medianą**.
