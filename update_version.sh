#!/bin/bash

# Прочитать текущую версию из файла
CURRENT_VERSION=$(cat version.txt)

# Увеличить версию
VERSION_MAJOR=${CURRENT_VERSION#v}
NEW_VERSION="v$VERSION_MAJOR"

# Записать новую версию в файл
echo $NEW_VERSION > version.txt

# Добавить изменения в git
git add version.txt