#! /usr/bin/env bash

echo "begin testing $1"

echo "LET'S GO!!!"

echo "Build with g++ and sanitizers"
rm -r build
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=san ../..
if [[ ! $? -eq 0 ]]
then
  echo "Building cmake with g++ and sanitizers failed"
  exit 1
fi
make
if [[ ! $? -eq 0 ]]
then
  echo "Make with g++ and sanitizers failed"
  exit 1
fi
cd ..
echo "Build with g++ and sanitizers achieved"

echo "Just build with g++"
rm -r build
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=g++ ../..
if [[ ! $? -eq 0 ]]
then
  echo "CMake with g++ failed"
  exit 1
fi
make
if [[ ! $? -eq 0 ]]
then
  echo "Make with g++ failed"
  exit 1
fi
echo "Build with g++ achieved"

cd ..

echo "Running tests"
./$1
if [[ ! $? -eq 0 ]]
then
  echo "Tests failed"
  exit 1
fi
echo "Google tests achieved"


echo "Let's try valgrind!"
valgrind --leak-check=yes --log-file=log.txt ./$1
echo "Valgrind log:"
cat log.txt
python3 ./valgrind_parser.py
if [[ ! $? -eq 0 ]]
then
  echo "Memory problems"
  exit 1
fi
echo "Valgrind achieved"


echo "You are amazing"
