cmake_minimum_required(VERSION 3.10)
project(GameOfLife_Engineering)

# Standard C++17 (Moderne)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Détection de SFML
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Inclusion des fichiers d'en-tête (.hpp)
include_directories(include)

# Récupération automatique des sources (.cpp) dans le dossier src/
file(GLOB SOURCES "src/*.cpp")

# Création de l'exécutable
add_executable(JeuDeLaVie ${SOURCES})

# Liaison avec SFML
target_link_libraries(JeuDeLaVie sfml-graphics sfml-audio sfml-window sfml-system)

# (Optionnel pour Windows) Copie automatique des DLLs SFML à côté de l'exécutable après compilation
# Si tu as des problèmes de "dll manquante", on pourra activer ça.