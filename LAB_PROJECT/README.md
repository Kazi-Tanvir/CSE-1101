<div align="center">
  <h1>🚀 CSE 1101 - Lab Projects</h1>
  <p><em>Course Lab Project Submissions</em></p>
  <hr>
</div>

<details open>
  <summary><b>📂 PROJECTS</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left" width="25%">Project</th>
        <th align="left" width="40%">Description</th>
        <th align="center" width="15%">Status</th>
        <th align="center" width="20%">Date</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>🎮 <a href="ASSIGNMENT_1/"><b>Assignment 1</b></a></td>
        <td>Tic Tac Toe — Console-based Player vs Computer game</td>
        <td align="center"><code>✅ Done</code></td>
        <td align="center"><code>09/06/2026</code></td>
      </tr>
      <tr>
        <td>🔤 <a href="ASSIGNMENT_2/"><b>Assignment 2</b></a></td>
        <td>Hangman — Word guessing game with ASCII art</td>
        <td align="center"><code>✅ Done</code></td>
        <td align="center"><code>July 2026</code></td>
      </tr>
      <tr>
        <td>📝 <a href="MIDTERM_EXAM/"><b>Midterm Exam</b></a></td>
        <td>Timed lab exam — 3 questions (arrays, sorting, recursion)</td>
        <td align="center"><code>✅ Done</code></td>
        <td align="center"><code>July 2026</code></td>
      </tr>
      <tr>
        <td>🏨 <a href="MIDTERM_PRACTICE/"><b>Midterm Practice</b></a></td>
        <td>Hotel Reservation System — Menu-driven management app</td>
        <td align="center"><code>✅ Done</code></td>
        <td align="center"><code>July 2026</code></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>🛠️ PROJECT DETAILS</b></summary>
  <br>

  ### 🎮 Assignment 1 — Tic Tac Toe

  A console-based Tic Tac Toe game written in C where the player competes against the computer.

  | File | Description |
  |------|-------------|
  | [`tictactoe_no_array.c`](ASSIGNMENT_1/tictactoe_no_array.c) | Main version using global variables |
  | [`tictactoe.c`](ASSIGNMENT_1/tictactoe.c) | Refactored version using arrays |

  **Features:**
  - Player vs Computer gameplay
  - Character selection (X / O)
  - Random computer moves via `rand()`
  - Win detection (rows, columns, diagonals)
  - Draw detection after 9 moves

  ---

  ### 🔤 Assignment 2 — Hangman

  A console-based Hangman game with ASCII art and a built-in word bank of 20 programming-related words.

  | File | Description |
  |------|-------------|
  | [`hangman.c`](ASSIGNMENT_2/hangman.c) | Full game with ASCII hangman, word bank, and replay menu |

  **Features:**
  - Random word selection from 20-word bank
  - ASCII hangman art that builds on wrong guesses
  - 6 attempts per round
  - Case-insensitive input with validation
  - Duplicate guess detection
  - Menu-driven with replay support

  ---

  ### 📝 Midterm Exam

  Timed lab exam with 3 programming questions and an automated grading system.

  | File | Description |
  |------|-------------|
  | [`q1.c`](MIDTERM_EXAM/q1.c) | Days in a month (with leap year handling) |
  | [`q2.c`](MIDTERM_EXAM/q2.c) | Sorted histogram using `*` characters |
  | [`q3.c`](MIDTERM_EXAM/q3.c) | Recursive digital root of a number |
  | [`grader.sh`](MIDTERM_EXAM/grader.sh) | Automated test grader (30 marks total) |

  ---

  ### 🏨 Midterm Practice — Hotel Reservation System

  A menu-driven hotel reservation management system supporting up to 10 rooms.

  | File | Description |
  |------|-------------|
  | [`hotelReservation.c`](MIDTERM_PRACTICE/hotelReservation.c) | Full reservation system with booking, search, and revenue calculation |
  | [`input.txt`](MIDTERM_PRACTICE/input.txt) | Sample test input |

  **Features:**
  - Add / Search / Display reservations
  - Vacancy tracking and double-booking prevention
  - Date-sorted display (bubble sort)
  - Revenue calculation per room

</details>
