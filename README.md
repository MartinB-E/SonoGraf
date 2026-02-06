# Sonograf

Projet de visualisation audio utilisant **SFML** (Linux uniquement).

## Prérequis

- Linux
- CMake ≥ 3.19
- Compilateur C++ compatible C++20
- SFML

### Debian / Ubuntu
```bash
sudo apt install cmake g++ libsfml-dev
```

### Arch Linux
```bash
sudo pacman -S cmake gcc sfml
```

## Compilation 
```bash 
git clone git@github.com:MartinB-E/SonoGraf.git
cd Sonograf

mkdir build
cd build

cmake ..
cmake --build .
```

L'executable est généré dans le dossier `build`.