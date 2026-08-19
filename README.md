<div align="center">
  <img height=300" alt="images" src="https://github.com/user-attachments/assets/e0f0de23-0e96-414a-972c-9775f839bc40" />
</div>

# 📇 Address Book - Library Edition
Address book manager written in C  packaged as a shared library.

## 📝 Overview
This project builds on a linked-list address book by splitting it into two parts: `lib/`, which holds the linked list and CSV persistence code and compiles into a shared library (`libaddrbook`), and `src/`, which holds the interactive CLI (`main.c`) that links against that library. The build is driven by three separate Makefiles - one for `lib/`, one for `src/`, and one at the project root tying them together.

## 🏗️ Architecture
- **`lib/`** - `address_book.c/h` (linked list operations) and `csv_reader.c/h` (CSV load/save), compiled into `libaddrbook.so.1.0`
- **`src/`** - `main.c`, the interactive menu-driven CLI, linked against `libaddrbook`

## 🛠️ Building
The shared library must be built and installed to `/opt/lib` before the CLI can be linked against it:
```sh
cd lib
make
sudo make install
```
This compiles `libaddrbook.so.1.0` and creates the `libaddrbook.so.1` / `libaddrbook.so` symlinks in `/opt/lib`.

Then build the CLI:
```sh
cd src
make
```
The resulting binary is `src/addrbook`.

## ▶️ Usage
Run the app through `run.sh`, which sets `LD_LIBRARY_PATH` to `/opt/lib` for the duration of the run so the dynamic linker can find `libaddrbook`:
```sh
./run.sh
```
You'll be shown the same interactive menu:

Options:

Display all records in address book
Add new address to the book
Add new addess at specific location
Delete address at specific index
Delete entire address book
Find address by index
Find address by name, surname, email or phone number
Quit

## 💾 Persistence
On startup, the CLI looks for `addresses.csv` in the current user's home directory (`$HOME/addresses.csv`) and loads any contacts found there, starting empty if the file doesn't exist. Additions, deletions, and bulk changes are written back to the same file.

## 📌 Notes
- CSV records are stored in the order: `Name,Surname,Email,PhoneNumber`.
- Field length limits: name/surname/phone number up to 19 characters, email up to 49 characters.
- The program exits cleanly on `Ctrl+C`, `SIGTERM`, `SIGHUP`, or `SIGQUIT`, freeing the linked list before quitting.

---
## 📋 Original Task

### Task 1
Automate address book building

For this task, you need to create a Makefile for your address book. This Makefile will be used to automate the build for your project.

Your Makefile should have these targets:
- all
- clean
- target called by your program name
- target for building .o files

Use as much as possible implicit variables in your Makefile.

Update your git repository when you finish making the Makefile.

### Task 2
Transforming your program into library

In this task, you need to transform your linked list source code into a shared object (library) from the previous address book task.

All the source code of the program must be in src directory. Linked list code must be in lib directory. Whole project must have 3 Makefiles. One makefile to compile src directory contents, one makefile to compile lib directory contents and the last one is the main makefile for the project.

Don't forget to update your git repository. Put this task in a separate branch.
