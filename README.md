<<<<<<< HEAD
# PyScript AI Generator

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Qt](https://img.shields.io/badge/Qt-6.x-green.svg)
![License](https://img.shields.io/badge/license-MIT-blue.svg)

## 📝 Opis Projektu

**PyScript AI Generator** to zaawansowana aplikacja desktopowa napisana w C++ z wykorzystaniem frameworka Qt6. Aplikacja wykorzystuje lokalne modele językowe Ollama do automatycznego generowania i wykonywania kodu Python na podstawie opisu zadania w języku naturalnym.

### Główne Funkcje

- 🤖 **Generowanie kodu Python** przy użyciu AI (Ollama)
- ▶️ **Automatyczne wykonywanie** wygenerowanego kodu
- 🖥️ **Przyjazny interfejs GUI** stworzony w Qt Widgets
- 🧵 **Wielowątkowość** - operacje w tle nie blokują GUI
- ✅ **Testy jednostkowe** (Google Test)
- 📚 **Dokumentacja kodu** (Doxygen)
- 🛡️ **Pełna obsługa błędów** i wyjątków

---

## 🎯 Wymagania

### Oprogramowanie

- **System operacyjny:** Windows 10/11, Linux, macOS
- **Kompilator:** 
  - Windows: MSVC 2019+ lub MinGW
  - Linux/macOS: GCC 7+ lub Clang 5+
- **CMake:** 3.16 lub nowszy
- **Qt:** 6.2 lub nowszy (moduły: Core, Widgets, Network)
- **Python:** 3.7 lub nowszy
- **Ollama:** Zainstalowane i uruchomione lokalnie

### Dodatkowe narzędzia (opcjonalne)

- **Doxygen:** Do generowania dokumentacji HTML
- **Google Test:** Do uruchamiania testów jednostkowych
- **Qt Creator:** IDE do rozwijania projektu

---

## 🚀 Instalacja i Uruchomienie

### Krok 1: Instalacja Ollama

#### Windows
```bash
# Pobierz instalator z https://ollama.ai/download
# Uruchom instalator i postępuj zgodnie z instrukcjami
```

#### Linux
```bash
curl -fsSL https://ollama.ai/install.sh | sh
```

#### macOS
```bash
brew install ollama
```

### Krok 2: Pobranie modelu językowego

```bash
# Uruchom Ollama
ollama serve

# W nowym terminalu pobierz model (wybierz jeden)
ollama pull llama3          # Angielski model (zalecany)
ollama pull bielik          # Polski model (jeśli dostępny)
```

### Krok 3: Weryfikacja Ollama

Sprawdź czy Ollama działa:
```bash
curl http://localhost:11434/api/generate -d '{
  "model": "llama3",
  "prompt": "Hello",
  "stream": false
}'
```

### Krok 4: Instalacja Qt6

#### Windows
1. Pobierz **Qt Online Installer** z https://www.qt.io/download-qt-installer
2. Zainstaluj Qt 6.x z komponentami:
   - Qt 6.x for MSVC 2019 64-bit
   - Qt 6.x Sources
   - CMake

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential
```

#### Linux (Fedora)
```bash
sudo dnf install qt6-qtbase-devel qt6-qttools-devel cmake gcc-c++
```

### Krok 5: Instalacja Python

Upewnij się, że Python jest zainstalowany i dostępny w PATH:
```bash
python --version  # lub python3 --version
```

Jeśli nie masz Pythona:
- **Windows:** https://www.python.org/downloads/
- **Linux:** `sudo apt install python3 python3-pip`

### Krok 6: Klonowanie i kompilacja projektu

```bash
# Klonowanie repozytorium
git clone https://github.com/twoj-login/pyscript_ai_generator.git
cd pyscript_ai_generator

# Utworzenie katalogu build
mkdir build
cd build

# Konfiguracja CMake
cmake ..

# Kompilacja
cmake --build . --config Release

# Na Windows alternatywnie możesz użyć:
# cmake --build . --config Release --parallel
```

### Krok 7: Uruchomienie aplikacji

#### Windows
```bash
# Z katalogu build
.\Release\PyScriptAI.exe
```

#### Linux/macOS
```bash
# Z katalogu build
./PyScriptAI
```

---

## 🎮 Użytkowanie

### Podstawowe użycie

1. **Uruchom Ollama** (jeśli nie działa w tle):
   ```bash
   ollama serve
   ```

2. **Uruchom aplikację PyScript AI Generator**

3. **Wpisz opis zadania** w pole tekstowe, np.:
   - "oblicz sumę liczb od 1 do 100"
   - "wygeneruj 10 losowych liczb i posortuj je"
   - "wypisz tabliczkę mnożenia dla liczby 7"

4. **Kliknij przycisk "🚀 Generuj i Wykonaj"**

5. **Obserwuj wyniki:**
   - Wygenerowany kod Python pojawi się w środkowym polu
   - Wynik wykonania pojawi się w dolnym polu
   - Status operacji jest wyświetlany na pasku stanu

### Przykładowe Prompty

Zobacz plik `examples/example_prompts.txt` dla inspiracji.

---

## 🧪 Testy Jednostkowe

### Kompilacja testów

```bash
# Z katalogu build
cmake .. -DBUILD_TESTS=ON
cmake --build .
```

### Uruchomienie testów

```bash
# Test PythonExecutor
./tests/test_executor

# Test OllamaClient
./tests/test_ollama

# Lub użyj CTest do uruchomienia wszystkich testów
ctest --output-on-failure
```

---

## 📖 Dokumentacja Doxygen

### Generowanie dokumentacji

```bash
# Z katalogu głównego projektu
cd docs
doxygen Doxyfile
```

### Przeglądanie dokumentacji

Otwórz plik `docs/html/index.html` w przeglądarce:

```bash
# Windows
start docs/html/index.html

# Linux
xdg-open docs/html/index.html

# macOS
open docs/html/index.html
```

---

## 🏗️ Struktura Projektu

```
pyscript_ai_generator/
├── src/                      # Kod źródłowy
│   ├── main.cpp              # Punkt wejścia
│   ├── mainwindow.h/cpp/ui   # Główne okno GUI
│   ├── ollamaclient.h/cpp    # Klient Ollama API
│   ├── pythonexecutor.h/cpp  # Executor kodu Python
│   ├── workerthread.h/cpp    # Wątek roboczy
│   └── config.h              # Konfiguracja
├── tests/                    # Testy jednostkowe
│   ├── test_ollama.cpp
│   ├── test_executor.cpp
│   └── CMakeLists.txt
├── docs/                     # Dokumentacja
│   └── Doxyfile
├── examples/                 # Przykłady
│   └── example_prompts.txt
├── CMakeLists.txt            # Konfiguracja CMake
├── PyScriptAI.pro            # Projekt Qt Creator
├── .gitignore
├── README.md
└── requirements.txt          # Zależności Python (opcjonalne)
```

---

## ⚙️ Konfiguracja

### Zmiana modelu Ollama

Edytuj plik `src/config.h`:
```cpp
const QString DEFAULT_MODEL = "llama3";  // Zmień na "bielik" lub inny model
```

### Zmiana interpretera Python

W pliku `src/config.h`:
```cpp
const QString PYTHON_EXECUTABLE = "python";  // Zmień na "python3" jeśli potrzeba
```

### Timeout połączenia

W pliku `src/config.h`:
```cpp
const int NETWORK_TIMEOUT = 60000;  // w milisekundach
```

---

## 🛠️ Rozwój Projektu

### Otwieranie w Qt Creator

1. Uruchom **Qt Creator**
2. Kliknij **File → Open File or Project**
3. Wybierz plik `PyScriptAI.pro`
4. Skonfiguruj kit (kompilator + Qt)
5. Kliknij **Run** (Ctrl+R)

### Kompilacja z Qt Creator

- **Debug:** Ctrl+B
- **Release:** Zmień tryb na "Release" i Ctrl+B
- **Run:** Ctrl+R

---

## 🐛 Rozwiązywanie Problemów

### Problem: "Nie można połączyć się z Ollama API"

**Rozwiązanie:**
1. Sprawdź czy Ollama działa: `curl http://localhost:11434`
2. Uruchom: `ollama serve`
3. Sprawdź czy model jest pobrany: `ollama list`

### Problem: "Nie można uruchomić interpretera Python"

**Rozwiązanie:**
1. Sprawdź czy Python jest w PATH: `python --version`
2. W Windows dodaj Python do zmiennej środowiskowej PATH
3. Zmień `PYTHON_EXECUTABLE` w `config.h` na pełną ścieżkę

### Problem: "Qt libraries not found"

**Rozwiązanie:**
```bash
# Ustaw zmienną Qt6_DIR
export Qt6_DIR=/ścieżka/do/Qt/6.x/gcc_64/lib/cmake/Qt6

# Lub na Windows
set Qt6_DIR=C:\Qt\6.x\msvc2019_64\lib\cmake\Qt6
```

### Problem: Błędy kompilacji

**Rozwiązanie:**
1. Sprawdź wersję kompilatora (wymagany C++17)
2. Wyczyść katalog build: `rm -rf build && mkdir build`
3. Sprawdź czy wszystkie zależności Qt są zainstalowane

---

## 📄 Licencja

Ten projekt jest dostępny na licencji MIT. Zobacz plik `LICENSE` dla szczegółów.

---

## 👥 Autorzy

- **PyScript AI Generator Team**
- Projekt stworzony jako część przedmiotu "Języki Programowania Obiektowego"

---

## 🙏 Podziękowania

- [Qt Framework](https://www.qt.io/) - za doskonały framework GUI
- [Ollama](https://ollama.ai/) - za lokalne modele językowe
- [Google Test](https://github.com/google/googletest) - za framework testowy

---

## 📞 Kontakt

Jeśli masz pytania lub sugestie, utwórz **Issue** na GitHubie.

---

## 🎓 Cele Edukacyjne

Projekt spełnia wszystkie wymagania na ocenę 5.0:

- ✅ Wykorzystuje model językowy (Ollama)
- ✅ Automatycznie wykonuje wygenerowany kod
- ✅ Posiada GUI (Qt Widgets)
- ✅ Poprawnie obsługuje wyjątki
- ✅ Wykorzystuje wielowątkowość (QThread)
- ✅ Posiada dokumentację Doxygen
- ✅ Wyposażony w testy jednostkowe (Google Test)
- ✅ Gotowy do umieszczenia na GitHub
- ✅ Działa na Windows
- ✅ Komunikacja z użytkownikiem po polsku

---

**Powodzenia w rozwoju aplikacji! 🚀**
=======
# jpo2026
>>>>>>> e510e74e724d6aa50d30a0b5226045f4659160fd
