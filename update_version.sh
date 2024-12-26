#!/bin/bash

# Прочитать текущую версию из файла
CURRENT_VERSION=$(cat version.txt)

# Увеличить версию
NEW_VERSION=$((CURRENT_VERSION + 1))

# Записать новую версию в файл
echo $NEW_VERSION > version.txt

# Добавить изменения в git
git add version.txt