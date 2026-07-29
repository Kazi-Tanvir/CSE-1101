<div align="center">
  <h1>🏨 Midterm Practice — Hotel Reservation System</h1>
  <p><em>Console-based hotel management system in C</em></p>
  <hr>
</div>

<details open>
  <summary><b>📋 PROJECT INFO</b></summary>
  <br>
  <table>
    <tbody>
      <tr>
        <td align="left" width="30%"><b>💻 Problem</b></td>
        <td align="left" width="70%"><code>Build a hotel reservation management system</code></td>
      </tr>
      <tr>
        <td align="left"><b>📅 Type</b></td>
        <td align="left"><code>Midterm Practice Project</code></td>
      </tr>
      <tr>
        <td align="left"><b>🗂️ Language</b></td>
        <td align="left"><code>C (stdio.h, string.h, math.h)</code></td>
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
        <td>🎯 <a href="hotelReservation.c"><code>hotelReservation.c</code></a></td>
        <td>Full hotel reservation system with menu-driven interface.</td>
        <td align="center"><code>✅ Done</code></td>
      </tr>
      <tr>
        <td>📄 <a href="input.txt"><code>input.txt</code></a></td>
        <td>Sample input data for testing the program.</td>
        <td align="center"><code>📎 Data</code></td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>⚙️ FEATURES</b></summary>
  <br>
  <ul>
    <li>Supports up to <strong>10 rooms</strong> with tiered pricing (₹2,000 – ₹200,000/night)</li>
    <li><strong>Add Reservation</strong> — Book a room with guest details, dates, and room type</li>
    <li><strong>Search Reservation</strong> — Look up bookings by reservation ID</li>
    <li><strong>Display by Date</strong> — View all reservations sorted by start date (bubble sort)</li>
    <li><strong>Display Vacancy</strong> — List all unoccupied rooms</li>
    <li><strong>Yearly Value</strong> — Calculate total revenue for a specific room based on stay duration</li>
    <li>Prevents double-booking of occupied rooms</li>
    <li>Menu-driven interface with 6 options</li>
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
        <td><code>addReservation()</code></td>
        <td>Collects guest info and books a room (with occupancy check)</td>
      </tr>
      <tr>
        <td><code>searchReservation()</code></td>
        <td>Finds and displays a reservation by ID</td>
      </tr>
      <tr>
        <td><code>displayDate()</code></td>
        <td>Lists all reservations sorted by start date using bubble sort</td>
      </tr>
      <tr>
        <td><code>displayVacancy()</code></td>
        <td>Shows all rooms that are currently unoccupied</td>
      </tr>
      <tr>
        <td><code>yearlyValue()</code></td>
        <td>Calculates total revenue for a room based on stay duration × rate</td>
      </tr>
      <tr>
        <td><code>dateToDays()</code></td>
        <td>Converts a date to an approximate day count for comparison</td>
      </tr>
    </tbody>
  </table>
</details>
