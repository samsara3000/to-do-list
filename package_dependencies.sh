
#!/bin/bash

# Получить список зависимостей Qt
dependencies=$(ldd $1 | grep Qt | awk '{print $3}')

# Скопировать зависимости в целевой каталог
for dep in $dependencies; do
    cp $dep $2
done