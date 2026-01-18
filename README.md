# 🐚 myshell — UNIX Shell Project

**Operating Systems Project — Developing a Simple UNIX Shell**

👤 **Author:** Ahmed Monir Almassri  
🎓 **Student ID:** 120220138  

---

## 📌 Overview
`myshell` is a simple UNIX command-line interpreter developed as part of an
Operating Systems course project.

The shell provides a basic user interface to the operating system, allowing
users to execute programs, manage directories, perform input/output
redirection, and run processes in the background.

This project is designed for **educational purposes** and implements a
subset of standard shell functionality.

---

## 🚀 Invocation

The shell can be started in two modes:

### 🔹 Interactive Mode
```bash
myshell
The shell prompts the user for commands and executes them interactively.
```
### 🔹 Batch Mode

```bash
myshell batchfile
```

Commands are read line-by-line from `batchfile`.
When end-of-file is reached, the shell exits automatically.

---

## 🧾 Command Line Format

A command consists of a command name followed by arguments, separated by
spaces or tabs.

Example:

```bash
ls -l /home
```

⚠️ Special symbols (`<`, `>`, `>>`, `&`) must be separated by whitespace.

---

## 🛠️ Internal Commands

| Command           | Description                                                             |
| ----------------- | ----------------------------------------------------------------------- |
| `cd <directory>`  | Change current directory (prints current if none given). Updates `PWD`. |
| `clr`             | Clear the terminal screen.                                              |
| `dir <directory>` | List contents of a directory.                                           |
| `environ`         | Display all environment variables.                                      |
| `echo <comment>`  | Display text (multiple spaces may be reduced).                          |
| `help`            | Display the user manual using a paging filter.                          |
| `pause`           | Pause execution until Enter is pressed.                                 |
| `quit`            | Exit the shell.                                                         |

---

## ▶️ Program Execution

Commands that are not internal are treated as **external programs**.

The shell:

* Creates a child process using `fork()`
* Executes the program using `exec()`

Each child process is executed with an environment variable:

```text
parent=<pathname>/myshell
```

---

## 🔁 I/O Redirection

### Input Redirection

```bash
command < inputfile
```

### Output Redirection

```bash
command > outputfile
```

* Creates file if it does not exist
* Truncates file if it exists

### Output Append

```bash
command >> outputfile
```

* Appends output if file exists

✅ Output redirection is also supported for:
`dir`, `environ`, `echo`, and `help`

---

## ⏱️ Background Execution

Commands can be executed in the background using `&`:

```bash
sleep 10 &
```

The shell immediately returns to the prompt without waiting for completion.

---

## 🌍 Environment Variables

The shell sets the following variables:

* **`shell`**
  Full path of the `myshell` executable.

* **`parent`**
  Set for child processes; contains full path of `myshell`.

---

## ❗ Error Handling

If a command fails to execute, an appropriate error message is displayed.
Common errors include:

* Invalid commands
* Missing files
* Invalid directories

---

## 📝 Notes

* All command-line tokens must be separated by whitespace.
* Pipes (`|`) and command chaining (`;`) are **not supported**.
* Quoted strings are **not supported**.

---

## 📚 License

This project is intended for educational use as part of an academic course.

