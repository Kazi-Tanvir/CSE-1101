<div align="center">
  <h1>📝 Assignment 6</h1>
  <p><em>Student Grading System</em></p>
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
          Build a student grading system for 50 students across 7 subjects:<br>
          <code>• 2 types of marks per subject — Continuous (60%) &amp; Final (40%)</code><br>
          <code>• Calculate weighted total marks per subject</code><br>
          <code>• Convert marks to GPA using grading scale</code><br>
          <code>• Compute overall CGPA (6 subjects × 3 credits + 1 subject × 1.5 credits)</code><br>
          <code>• Assign letter grades (A+ to F)</code><br>
          <code>• Search student by ID and display all records</code>
        </td>
      </tr>
      <tr>
        <td align="left"><b>📅 Start Date</b></td>
        <td align="left"><code>01/08/2026</code></td>
      </tr>
      <tr>
        <td align="left"><b>🏁 Completion Date</b></td>
        <td align="left"><code>01/08/2026</code></td>
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
        <th align="center">Source File</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>Student Grading App</td>
        <td align="center">📄 <a href="grading_app.c"><code>grading_app.c</code></a></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>⚙️ FUNCTIONS</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left">Function</th>
        <th align="left">Description</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><code>checkCGPA(marks)</code></td>
        <td>Converts total marks (0–100) to GPA (0.0–4.0)</td>
      </tr>
      <tr>
        <td><code>checkGrade(cgpa, grade[])</code></td>
        <td>Converts GPA to letter grade string (A+ to F)</td>
      </tr>
      <tr>
        <td><code>countCGPA(idx)</code></td>
        <td>Computes weighted CGPA for a student using 60/40 marks &amp; credit hours</td>
      </tr>
      <tr>
        <td><code>searchID()</code></td>
        <td>Searches and displays a student's full result by index</td>
      </tr>
      <tr>
        <td><code>displayAll()</code></td>
        <td>Displays all students with CGPA and grade</td>
      </tr>
      <tr>
        <td><code>inputStudents()</code></td>
        <td>Takes input for N students (name + 7×2 marks)</td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>🗃️ GLOBAL ARRAYS</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left">Array</th>
        <th align="left">Type &amp; Size</th>
        <th align="left">Purpose</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td><code>studentName[50][100]</code></td>
        <td><code>char</code></td>
        <td>Names of up to 50 students</td>
      </tr>
      <tr>
        <td><code>subjectId[7]</code></td>
        <td><code>int</code></td>
        <td>Subject identifiers</td>
      </tr>
      <tr>
        <td><code>studentMarks[50][7][2]</code></td>
        <td><code>int</code></td>
        <td>Marks — [student][subject][0=continuous, 1=final]</td>
      </tr>
      <tr>
        <td><code>subjectGrade[50][7][10]</code></td>
        <td><code>char</code></td>
        <td>Per-subject letter grade for each student</td>
      </tr>
      <tr>
        <td><code>studentCGPA[50]</code></td>
        <td><code>float</code></td>
        <td>Overall CGPA per student</td>
      </tr>
      <tr>
        <td><code>studentGrade[50][10]</code></td>
        <td><code>char</code></td>
        <td>Overall letter grade per student</td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>📚 Grading Scale</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="left">Marks Range</th>
        <th align="center">GPA</th>
        <th align="center">Grade</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td>80 - 100</td>
        <td align="center">4.0</td>
        <td align="center">A+</td>
      </tr>
      <tr>
        <td>75 - 79</td>
        <td align="center">3.75</td>
        <td align="center">A</td>
      </tr>
      <tr>
        <td>70 - 74</td>
        <td align="center">3.5</td>
        <td align="center">A-</td>
      </tr>
      <tr>
        <td>65 - 69</td>
        <td align="center">3.25</td>
        <td align="center">B+</td>
      </tr>
      <tr>
        <td>60 - 64</td>
        <td align="center">3.0</td>
        <td align="center">B</td>
      </tr>
      <tr>
        <td>55 - 59</td>
        <td align="center">2.75</td>
        <td align="center">B-</td>
      </tr>
      <tr>
        <td>50 - 54</td>
        <td align="center">2.5</td>
        <td align="center">C+</td>
      </tr>
      <tr>
        <td>45 - 49</td>
        <td align="center">2.25</td>
        <td align="center">C</td>
      </tr>
      <tr>
        <td>40 - 44</td>
        <td align="center">2.0</td>
        <td align="center">D</td>
      </tr>
      <tr>
        <td>&lt; 40</td>
        <td align="center">0.0</td>
        <td align="center">F</td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>📐 CGPA Formula</b></summary>
  <br>

  **Weighted Marks:**
  ```
  Total = (Continuous × 0.6) + (Final × 0.4)
  ```

  **Credit Distribution:**
  | Subjects | Credits |
  |----------|---------|
  | Subject 1–6 | 3.0 each |
  | Subject 7 | 1.5 |
  | **Total** | **19.5** |

  **CGPA Calculation:**
  ```
  CGPA = Σ(GPA × Credits) / 19.5
  ```
</details>
