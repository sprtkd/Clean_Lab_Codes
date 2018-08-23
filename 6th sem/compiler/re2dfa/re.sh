#!/bin/bash
cd re2dfa_pkg
gcc re2dfa.c -o re2dfa.out
./re2dfa.out
python 2.py
xdg-open e1.svg


