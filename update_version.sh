#!/bin/bash

# Прочитать текущую версию из файла
CURRENT_VERSION=$(cat version.txt)

# Увеличить версию
VERSION_MAJOR=${CURRENT_VERSION#}
NEW_VERSION=$VERSION_MAJOR + 1

# Записать новую версию в файл
echo $NEW_VERSION > version.txt

# Добавить изменения в git
git add version.txt