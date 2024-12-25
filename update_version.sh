#!/bin/bash

# Прочитать текущую версию из файла
CURRENT_VERSION=$(cat version.txt)

# Разделить версию на компоненты
IFS='.' read -r -a VERSION_PARTS <<< "$CURRENT_VERSION"
VERSION_MAJOR=${VERSION_PARTS[0]}
VERSION_MINOR=${VERSION_PARTS[1]}
VERSION_PATCH=${VERSION_PARTS[2]}

# Увеличить версию
VERSION_PATCH=$((VERSION_PATCH + 1))
NEW_VERSION="${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"

# Записать новую версию в файл
echo $NEW_VERSION > version.txt

# Добавить изменения в git
git add version.txt