<div align="center">
  <h1>🔤 Assignment 2 — Hangman</h1>
  <p><em>Console-based word guessing game in C</em></p>
  <hr>
</div>

<details open>
  <summary><b>📋 PROJECT INFO</b></summary>
  <br>
  <table>
    <tbody>
      <tr>
        <td align="left" width="30%"><b>💻 Problem</b></td>
        <td align="left" width="70%"><code>Build a Hangman word guessing game</code></td>
      </tr>
      <tr>
        <td align="left"><b>📅 Date</b></td>
        <td align="left"><code>July 2026</code></td>
      </tr>
      <tr>
        <td align="left"><b>🗂️ Language</b></td>
        <td align="left"><code>C (stdio.h, string.h, stdlib.h)</code></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>🛠️ SOURCE FILES</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left" width="30%">File</th>
        <th align="left" width="50%">Description</th>
        <th align="center" width="20%">Status</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>🎯 <a href="hangman.c"><code>hangman.c</code></a></td>
        <td>Full Hangman game with ASCII art, word bank, and menu system.</td>
        <td align="center"><code>✅ Done</code></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>⚙️ HOW IT WORKS</b></summary>
  <br>
  <ul>
    <li>A random word is selected from a built-in bank of 20 programming-related words</li>
    <li>Player guesses one letter at a time (case-insensitive)</li>
    <li>ASCII hangman figure is progressively drawn on wrong guesses</li>
    <li>Player has <strong>6 attempts</strong> before the game ends</li>
    <li>Tracks and displays all previously guessed letters</li>
    <li>Input validation — rejects non-alphabetic and duplicate guesses</li>
    <li>Menu-driven with replay support</li>
  </ul>
</details>

<br>

<details>
  <summary><b>📌 KEY FUNCTIONS</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left" width="35%">Function</th>
        <th align="left" width="65%">Purpose</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><code>drawHangman()</code></td>
        <td>Renders ASCII art hangman based on wrong guess count</td>
      </tr>
      <tr>
        <td><code>displayWord()</code></td>
        <td>Shows the current state of the word with blanks</td>
      </tr>
      <tr>
        <td><code>processGuess()</code></td>
        <td>Checks if the guessed letter exists in the word</td>
      </tr>
      <tr>
        <td><code>isAlreadyGuessed()</code></td>
        <td>Prevents duplicate letter guesses</td>
      </tr>
      <tr>
        <td><code>isWordComplete()</code></td>
        <td>Checks if all letters have been revealed</td>
      </tr>
      <tr>
        <td><code>selectWord()</code></td>
        <td>Randomly picks a word from the word bank</td>
      </tr>
      <tr>
        <td><code>resetGame()</code></td>
        <td>Resets all game state for a new round</td>
      </tr>
      <tr>
        <td><code>playGame()</code></td>
        <td>Main game loop handling turns and win/loss</td>
      </tr>
    </tbody>
  </table>
</details>
