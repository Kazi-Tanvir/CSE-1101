<div align="center">
  <h1>📝 Midterm Lab Exam</h1>
  <p><em>Timed lab exam — 3 programming questions in C</em></p>
  <hr>
</div>

<details open>
  <summary><b>📋 EXAM INFO</b></summary>
  <br>
  <table>
    <tbody>
      <tr>
        <td align="left" width="30%"><b>📅 Type</b></td>
        <td align="left" width="70%"><code>Midterm Lab Exam</code></td>
      </tr>
      <tr>
        <td align="left"><b>📅 Date</b></td>
        <td align="left"><code>29/07/2026</code></td>
      </tr>
      <tr>
        <td align="left"><b>🗂️ Language</b></td>
        <td align="left"><code>C (stdio.h)</code></td>
      </tr>
      <tr>
        <td align="left"><b>📊 Grading</b></td>
        <td align="left"><code>Automated via grader.sh (30 marks total)</code></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>🛠️ QUESTIONS</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left" width="15%">File</th>
        <th align="left" width="55%">Description</th>
        <th align="center" width="15%">Topic</th>
        <th align="center" width="15%">Status</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>📄 <a href="q1.c"><code>q1.c</code></a></td>
        <td>Given a month and year, output the number of days (handles leap years).</td>
        <td align="center"><code>Arrays</code></td>
        <td align="center"><code>✅ Done</code></td>
      </tr>
      <tr>
        <td>📄 <a href="q2.c"><code>q2.c</code></a></td>
        <td>Read N integers, sort them, and print a histogram using <code>*</code> characters.</td>
        <td align="center"><code>Sorting</code></td>
        <td align="center"><code>✅ Done</code></td>
      </tr>
      <tr>
        <td>📄 <a href="q3.c"><code>q3.c</code></a></td>
        <td>Compute the recursive digital root of a number (sum digits until single digit).</td>
        <td align="center"><code>Recursion</code></td>
        <td align="center"><code>✅ Done</code></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>⚙️ GRADER</b></summary>
  <br>

  The exam includes an automated grading script:

  | File | Description |
  |------|-------------|
  | [`grader.sh`](grader.sh) | Bash script that compiles each `q*.c`, runs test cases, and reports marks |
  | [`tests/`](tests/) | Directory containing input/output test files for each question |

  **Usage:**
  ```bash
  ./grader.sh .
  ```

  **Test file structure:**
  ```
  tests/
  ├── q1/
  │   ├── in001.txt
  │   ├── out001.txt
  │   └── ...
  ├── q2/
  │   ├── in001.txt
  │   ├── out001.txt
  │   └── ...
  └── q3/
      ├── in001.txt
      ├── out001.txt
      └── ...
  ```

  Each question is graded out of **10 marks** (proportional to passed test cases).

</details>
