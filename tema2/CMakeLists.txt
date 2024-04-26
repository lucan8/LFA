cmake_minimum_required(VERSION 3.25)
project(DFA_MIN LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DFA_APPLICATION
               classes/State/State.cpp
               classes/Transition/Transition.cpp
               classes/Automaton/Automaton.cpp
               functions/functions.cpp
               NFA_TRANSFORMATION/NFA_TRANSFORMATION.cpp
               DFA_MINIMIZATION/DFA_MINIMIZATION.cpp
               DFA_APP/app.cpp
              )
