♟️ Chess Game – C++ Console Application

📌 Overview

This project is a console-based chess game developed in C++. It simulates a standard game of chess with proper rule validation, turn management, and win-condition detection.

The project focuses on object-oriented design, game logic, and clean architecture, rather than advanced graphics.

🛠️ Built With

C++

Dev-C++

Console-based interface

✨ Main Features

Object-Oriented Design

Base Piece class

Derived classes: Pawn, Rook, Knight, Bishop, Queen, King

Move Validation

Each piece implements its own isValidMove() logic

Prevents illegal moves

Turn-Based System

Alternates turns between White and Black

Ensures players move only their own pieces

Capturing System

Supports capturing opponent pieces

Updates board state accordingly

Check and Checkmate Detection

Detects when a king is in check

Ends the game upon checkmate

Board Management

Chessboard represented internally using a 2D structure

Board updated after every valid move

Memory Management

Proper use of destructors

No memory leaks during gameplay

Scalable Architecture

Designed to allow future additions such as:

Castling

En passant

Pawn promotion

GUI integration

🚧 Limitations

The game currently runs in the console

Advanced chess rules (castling, en passant, promotion) are planned but optional

No graphical interface in the current version

📚 References

GitHub Repository (inspiration & structure): https://github.com/JuUnland/Chess

Tutorial Reference: https://youtu.be/WKs685H6uOQ?si=6HHlukzQTdiqSeUx

🎯 Learning Outcomes

Applied object-oriented programming principles

Implemented game logic and rule validation

Improved understanding of state management

Designed a scalable and maintainable architecture
