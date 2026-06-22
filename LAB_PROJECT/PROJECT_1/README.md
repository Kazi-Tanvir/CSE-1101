<div align="center">
  <h1>🎮 Project 1 — Tic Tac Toe</h1>
  <p><em>Console-based Tic Tac Toe game in C</em></p>
  <hr>
</div>

<details open>
  <summary><b>📋 PROJECT INFO</b></summary>
  <br>
  <table>
    <tbody>
      <tr>
        <td align="left" width="30%"><b>💻 Problem</b></td>
        <td align="left" width="70%"><code>Build a Tic Tac Toe game (Player vs Computer)</code></td>
      </tr>
      <tr>
        <td align="left"><b>📅 Date</b></td>
        <td align="left"><code>09/06/2026</code></td>
      </tr>
      <tr>
        <td align="left"><b>🗂️ Language</b></td>
        <td align="left"><code>C (stdio.h, stdlib.h)</code></td>
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
        <td>🎯 <a href="1812.c"><code>1812.c</code></a></td>
        <td>Main implementation using individual global variables for each board cell.</td>
        <td align="center"><code>✅ Done</code></td>
      </tr>
      <tr>
        <td>🔧 <a href="temp.c"><code>temp.c</code></a></td>
        <td>Refactored version using arrays for board state and move tracking.</td>
        <td align="center"><code>🔄 WIP</code></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>⚙️ HOW IT WORKS</b></summary>
  <br>
  <ul>
    <li>Player chooses their character (<code>X</code> or <code>O</code>)</li>
    <li>Player and Computer take alternating turns</li>
    <li>Computer makes random moves using <code>rand()</code></li>
    <li>Board is displayed after each move</li>
    <li>Win detection checks all rows, columns, and diagonals</li>
    <li>Game ends on a win or a draw after 9 moves</li>
  </ul>
</details>

<br>

<details>
  <summary><b>📌 VERSIONS</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left" width="30%">Version</th>
        <th align="left" width="70%">Changes</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><code>1812.c</code></td>
        <td>Uses 9 separate global <code>char</code> variables (<code>b1</code>–<code>b9</code>) to represent the board.</td>
      </tr>
      <tr>
        <td><code>temp.c</code></td>
        <td>Refactored to use a <code>char board[9]</code> array and a <code>done[9]</code> tracker for cleaner logic.</td>
      </tr>
    </tbody>
  </table>
</details>
