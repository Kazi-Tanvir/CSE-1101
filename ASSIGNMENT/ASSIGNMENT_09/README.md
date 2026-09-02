<div align="center">
  <h1>📝 Assignment 9</h1>
  <p><em>Student Continuous &amp; Final Assessment Marksheet System</em></p>
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
          Build a student marksheet system that reads continuous assessment marks (quiz, assignment, midterm, attendance) and final exam marks from text files, computes total marks per course, calculates CGPA, assigns letter grades, and writes a comprehensive result file.
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
        <td>File Marksheet System</td>
        <td>Reads student marks from 7 course files, computes weighted totals (60% continuous + 40% final), calculates CGPA, assigns grades, and exports results to <code>data/result.txt</code></td>
        <td align="center">📄 <a href="file_marksheet.c"><code>file_marksheet.c</code></a></td>
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
