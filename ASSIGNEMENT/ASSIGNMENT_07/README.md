<div align="center">
  <h1>📝 Assignment 7</h1>
  <p><em>Library Book Reservation System</em></p>
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
          Build a library book reservation system:<br>
          <code>• Manage up to 20 books and 50 members</code><br>
          <code>• Add books with ID, title, and availability status</code><br>
          <code>• Members can borrow 1 book at a time</code><br>
          <code>• Return borrowed books and update availability</code><br>
          <code>• Search member status to check borrowed book info</code>
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
        <td>Book Reservation System</td>
        <td align="center">📄 <a href="book_reservation.c"><code>book_reservation.c</code></a></td>
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
        <td><code>addBookAndPrint()</code></td>
        <td>Adds a new book (ID + title) and prints the current book list</td>
      </tr>
      <tr>
        <td><code>borrowBook()</code></td>
        <td>Lets a member borrow an available book (1 book limit per member)</td>
      </tr>
      <tr>
        <td><code>returnBook()</code></td>
        <td>Returns a member's borrowed book and marks it available again</td>
      </tr>
      <tr>
        <td><code>searchMember()</code></td>
        <td>Searches member by ID and shows their borrowed book info</td>
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
        <td><code>bookTitle[20][100]</code></td>
        <td><code>char</code></td>
        <td>Titles of up to 20 books</td>
      </tr>
      <tr>
        <td><code>bookID[20]</code></td>
        <td><code>int</code></td>
        <td>Unique ID for each book</td>
      </tr>
      <tr>
        <td><code>bookStatus[20]</code></td>
        <td><code>int</code></td>
        <td>1 = available, 0 = borrowed</td>
      </tr>
      <tr>
        <td><code>memberID[50]</code></td>
        <td><code>int</code></td>
        <td>Member identifiers (1–50)</td>
      </tr>
      <tr>
        <td><code>memberStatus[50]</code></td>
        <td><code>int</code></td>
        <td>0 = no book borrowed, otherwise = borrowed book ID</td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>📖 MENU OPTIONS</b></summary>
  <br>
  <table>
    <thead>
      <tr>
        <th align="center">Option</th>
        <th align="left">Action</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td align="center"><code>1</code></td>
        <td>Add Book &amp; Display List</td>
      </tr>
      <tr>
        <td align="center"><code>2</code></td>
        <td>Borrow Book</td>
      </tr>
      <tr>
        <td align="center"><code>3</code></td>
        <td>Return Book</td>
      </tr>
      <tr>
        <td align="center"><code>4</code></td>
        <td>Search Member Status</td>
      </tr>
      <tr>
        <td align="center"><code>5</code></td>
        <td>Exit</td>
      </tr>
    </tbody>
  </table>
</details>

<br>

<details open>
  <summary><b>📏 CONSTRAINTS</b></summary>
  <br>

  | Constraint | Value |
  |------------|-------|
  | Max Books | `20` (`MAX_BOOKS`) |
  | Max Members | `50` (`MAX_MEMBERS`) |
  | Books per Member | `1` |
</details>
