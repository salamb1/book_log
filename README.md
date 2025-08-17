# Book Log (C++)

A console application to manage books: add, update, delete, search, and sort.  
Data is saved to files so each user has their own book list.

## Features
- Add, update, delete, and search books
- Sort by different criteria
- Save/load user-specific book records with file I/O
- Input validation for reliability

## Build & Run
```bash
g++ -std=c++17 -O2 book_log.cpp -o booklog
./booklog   # on macOS/Linux
booklog.exe # on Windows
