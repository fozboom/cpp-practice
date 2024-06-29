#! /usr/bin/env bash

echo "begin testing $1"


echo "Check for banned words"
python3 banned_words_checker.py --solution=../include/geometry/$1.hpp --bannded-words=banned_words.json
if [[ ! $? -eq 0 ]]
then
  echo "В вашем коде есть забаненые слова!"
  exit 1
fi

python3 banned_words_checker.py --solution=../src/$1.cpp --bannded-words=banned_words.json
if [[ ! $? -eq 0 ]]
then
  echo "В вашем коде есть забаненые слова!"
  exit 1
fi
echo "Banned words check achieved"


#echo "clang-tidy check"
#clang-tidy -extra-arg=-std=c++20 -quiet ../include/geometry/$1.hpp
#if [[ ! $? -eq 0 ]]
#then
 # echo "Проверка clang-tidy не пройдена"
  #exit 1
#fi

#clang-tidy -extra-arg=-std=c++20 -quiet ../src/$1.cpp
#if [[ ! $? -eq 0 ]]
#then
 # echo "Проверка clang-tidy не пройдена"
  #exit 1
#fi
#echo "clang-tidy achieved"


#echo "clang-format check"
#clang-format -i -style='{BasedOnStyle: Google, DerivePointerAlignment: false, PointerAlignment: Left, AlignOperands: true}' ../include/geometry/$1.hpp &&
#clang-format -i -style='{BasedOnStyle: Google, DerivePointerAlignment: false, PointerAlignment: Left, AlignOperands: true}' ../src/$1.cpp &&
#git diff --ignore-submodules --color > diff &&
#cat diff
#if [[ -s diff ]]
#then
 # echo "Проверка clang-format не пройдена"
  #exit 1
#fi
#echo "clang-format achieved"


echo "Начинаем билдить"

echo "Build with clang and sanitizers"
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=san ..
if [[ ! $? -eq 0 ]]
then
  echo "Сборка cmake с clang++ and sanitizers не сработала"
  exit 1
fi
make
if [[ ! $? -eq 0 ]]
then
  echo "Make с clang++ and sanitizers не сработал"
  exit 1
fi
cd ..
echo "Build with clang++ and sanitizers achieved"


echo "Build with g++ and sanitizers"
rm -r build
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=san ..
if [[ ! $? -eq 0 ]]
then
  echo "Сборка cmake с g++ and sanitizers не сработала"
  exit 1
fi
make
if [[ ! $? -eq 0 ]]
then
  echo "Make с g++ and sanitizers не сработал"
  exit 1
fi
cd .. 
echo "Build with g++ and sanitizers achieved"

echo "Just build with g++"
rm -r build
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=g++ ..
if [[ ! $? -eq 0 ]]
then
  echo "Сборка cmake с g++ не сработала"
  exit 1
fi
make
if [[ ! $? -eq 0 ]]
then
  echo "Make с g++ не сработал"
  exit 1
fi
echo "Build with g++ achieved"


echo "Running tests"
./$1
if [[ ! $? -eq 0 ]]
then
  echo "Тесты не пройдены"
  exit 1
fi
echo "Google tests achieved"


echo "Попробуем valgrind!"
valgrind --leak-check=yes --log-file=log.txt ./$1
echo "Valgrind log:"
cat log.txt
python3 ../valgrind_parser.py
if [[ ! $? -eq 0 ]]
then
  echo "А кто украл free?"
  exit 1
fi
echo "Valgrind achieved"


echo "Вы потрясающие!"
