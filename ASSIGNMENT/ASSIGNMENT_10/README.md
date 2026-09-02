<div align="center">
  <h1>📝 Assignment 10</h1>
  <p><em>Self-Referential Struct Student Grading System</em></p>
  <hr>
</div>

<details open>
  <summary><b>📋 ASSIGNMENT DETAILS</b></summary>
  <br>
  <table>
    <tbody>
      <tr>
        <td align="left" width="30%" valign="top"><b>💻 Problem</b></td>
        <td align="left" width="70%">
          Extend Assignment 9 by using a self-referential struct (linked list) to manage student records. Read marks from course files, compute weighted totals, calculate CGPA, assign grades, and export results — all using <code>struct Student *next</code> for chaining.
        </td>
      </tr>
      <tr>
        <td align="left"><b>📅 Date</b></td>
        <td align="left"><code>31/08/2026</code></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>📂 SOURCE FILES</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left">Program</th>
        <th align="left">Description</th>
        <th align="center">Source File</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>Self-Referential Struct System</td>
        <td>Uses <code>struct Student</code> with a <code>*next</code> pointer to build a linked list of 50 students across 7 courses. Reads data from files, computes 60/40 weighted marks, calculates CGPA &amp; letter grades, and writes results to <code>data/result.txt</code></td>
        <td align="center">📄 <a href="self_ref_struct.c"><code>self_ref_struct.c</code></a></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>📁 DATA FILES</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left">File</th>
        <th align="left">Description</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><code>data/name_cg.txt</code></td>
        <td>Student names and credit grades input</td>
      </tr>
      <tr>
        <td><code>data/1101_CSE.txt</code></td>
        <td>CSE 1101 course marks</td>
      </tr>
      <tr>
        <td><code>data/1101L_CSE.txt</code></td>
        <td>CSE 1101L lab marks</td>
      </tr>
      <tr>
        <td><code>data/1102_CSE.txt</code></td>
        <td>CSE 1102 course marks</td>
      </tr>
      <tr>
        <td><code>data/1103_STAT.txt</code></td>
        <td>STAT 1103 course marks</td>
      </tr>
      <tr>
        <td><code>data/1105_GE.txt</code></td>
        <td>GE 1105 course marks</td>
      </tr>
      <tr>
        <td><code>data/1106_SE.txt</code></td>
        <td>SE 1106 course marks</td>
      </tr>
      <tr>
        <td><code>data/1107_MATH.txt</code></td>
        <td>MATH 1107 course marks</td>
      </tr>
      <tr>
        <td><code>data/result.txt</code></td>
        <td>Generated output — full student marksheet with grades and CGPA</td>
      </tr>
    </tbody>
  </table>
</details>
