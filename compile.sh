#!/bin/bash


echo Compilando...


g++ -std=c++11 -o osiris src/main.cpp src/codigo.cpp -I include/ -I/Users/adelinofernandes/Documents/systemc-2.3.1/include -L/Users/adelinofernandes/Documents/systemc-2.3.1/lib -lsystemc


