# Szybki Start - PyScript AI Generator

## Dla Windows (najprostszy sposób)

### 1. Wymagania wstępne
- Windows 10/11
- Qt Creator zainstalowane z https://www.qt.io/download
- Python zainstalowany (sprawdź: `python --version`)

### 2. Instalacja Ollama (5 minut)

1. Pobierz Ollama z: https://ollama.ai/download/windows
2. Uruchom instalator `OllamaSetup.exe`
3. Poczekaj na zakończenie instalacji
4. Otwórz Command Prompt i uruchom:
   ```cmd
   ollama pull llama3
   ```
5. Zweryfikuj instalację:
   ```cmd
   ollama list
   ```

### 3. Otwórz projekt w Qt Creator

1. Uruchom **Qt Creator**
2. Kliknij **File → Open File or Project**
3. Przejdź do folderu projektu
4. Wybierz plik **PyScriptAI.pro**
5. Kliknij **Open**
6. Wybierz **Kit** (np. "Desktop Qt 6.x MSVC2019 64bit")
7. Kliknij **Configure Project**

### 4. Uruchom projekt

1. W Qt Creator kliknij **zielony przycisk Run** (trójkąt) lub naciśnij **Ctrl+R**
2. Projekt skompiluje się i uruchomi automatycznie!

### 5. Pierwsze użycie

1. Upewnij się, że Ollama działa (powinno być uruchomione w tle po instalacji)
2. W aplikacji wpisz: **"oblicz sumę liczb od 1 do 100"**
3. Kliknij **Generuj i Wykonaj**
4. Obserwuj wynik!

---

## Dla Linux

### Ubuntu/Debian

```bash
# 1. Zainstaluj zależności
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential python3

# 2. Zainstaluj Ollama
curl -fsSL https://ollama.ai/install.sh | sh

# 3. Pobierz model
ollama pull llama3

# 4. Sklonuj i skompiluj projekt
cd /path/to/project
mkdir build && cd build
cmake ..
cmake --build .

# 5. Uruchom
./PyScriptAI
```

---

## Rozwiązywanie problemów

### Ollama nie działa?

**Windows:**
```cmd
# Sprawdź czy Ollama jest uruchomiona
ollama serve

# W nowym oknie terminala
ollama list
```

**Linux:**
```bash
# Uruchom jako serwis
systemctl start ollama

# Lub ręcznie
ollama serve
```

### Python nie znaleziony?

1. Zainstaluj Python z https://www.python.org/downloads/
2. Podczas instalacji zaznacz **"Add Python to PATH"**
3. Po instalacji zrestartuj komputer

### Qt Creator nie znajduje kompilatora?

1. Otwórz **Qt Creator**
2. Przejdź do **Tools → Options → Kits**
3. Sprawdź czy **Desktop Qt 6.x** jest skonfigurowany
4. Jeśli nie, zainstaluj Qt ponownie z komponentem **MSVC 2019** lub **MinGW**

---

## Testowanie

```bash
# Z katalogu build
cmake .. -DBUILD_TESTS=ON
cmake --build .
ctest --output-on-failure
```

---

## Generowanie dokumentacji

```bash
# Wymagane: Doxygen
cd docs
doxygen Doxyfile

# Otwórz
start html/index.html  # Windows
xdg-open html/index.html  # Linux
```

---

## Wskazówki

- 💡 Ollama musi być uruchomiona przed użyciem aplikacji
- 💡 Pierwsze uruchomienie może potrwać dłużej (ładowanie modelu)
- 💡 Używaj prostych i jasnych opisów zadań
- 💡 Przykładowe prompty znajdziesz w `examples/example_prompts.txt`

---
