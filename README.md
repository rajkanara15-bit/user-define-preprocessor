# User-Defined Preprocessor in C

## 📌 Overview

This project is a user-defined preprocessor implemented in the C programming language. It performs basic preprocessing operations on a C source file before compilation.

The program processes the source file through multiple stages and generates a preprocessed output file with the `.i` extension.

## ✨ Features

- **Macro Replacement** – Replaces user-defined macros declared using `#define`.
- **Comment Removal** – Removes single-line (`//`) and multiline (`/* ... */`) comments.
- **Header File Inclusion** – Processes `#include` directives and copies header file contents into the output.
- **Intermediate File Processing** – Uses intermediate files to perform preprocessing step by step.
- **Preprocessed Output Generation** – Generates a final `.i` file containing processed source code.

## ⚙️ Technologies Used

- C Programming Language
- GCC Compiler
- Standard C Library
- File Handling
- String Manipulation

## 🔄 Working Process

The preprocessor follows these stages:

1. Reads the input source file.
2. Identifies and stores user-defined macros.
3. Performs macro replacement.
4. Removes comments from the source code.
5. Processes header file inclusion.
6. Generates the final preprocessed output file.

## 📂 Project Files

| File | Description |
|---|---|
| `main.c` | Main program and preprocessing workflow |
| `myheader.h` | User-defined header file |
| `source.c` | Input source file used for testing |
| `source.macro` | Intermediate file after macro replacement |
| `source.clean` | Intermediate file after comment removal |

## ▶️ Compilation

Compile the program using GCC:

```bash
gcc main.c -o main.exe
```



Run the preprocessor by providing the source file as a command-line argument:

```bash
./main source.c
```


## 📄 Output

The program generates a preprocessed file with the `.i` extension.

The output contains the source code after performing:

- Macro replacement
- Comment removal
- Header file inclusion

## 🎯 Learning Outcomes

This project helped me understand:

- The basic working of a C preprocessor
- Macro definitions and replacements
- Comment handling in source code
- Header file inclusion
- File handling in C
- String manipulation using standard library functions
- Processing files through multiple stages

## 🚀 Future Improvements

- Improve macro replacement logic
- Handle more complex preprocessing cases
- Improve error handling
- Make header file handling portable across different systems
- Support more preprocessing directives

## 👨‍💻 Author

**Your Name**

---

⭐ If you find this project interesting, feel free to explore it!
