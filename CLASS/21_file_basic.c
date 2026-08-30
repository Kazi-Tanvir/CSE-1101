/**
 * ============================================================================
 * File:        file_io_docs.c
 * Description: Comprehensive reference & practical usage guide for standard
 *              C File I/O functions:
 *              - Formatted: fprintf, fscanf
 *              - Character: fputc, fgetc
 *              - String:    fputs, fgets
 *              - Binary:    fwrite, fread
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

/* Sample struct for binary read/write */
typedef struct {
    int id;
    char name[32];
    double score;
} StudentRecord;

/* ============================================================================
 * 1. FORMATTED I/O: fprintf & fscanf
 * ----------------------------------------------------------------------------
 * fprintf(FILE *stream, const char *format, ...);
 *   - Writes formatted text to a stream.
 *   - Return: Number of characters written, or a negative value on error.
 *
 * fscanf(FILE *stream, const char *format, ...);
 *   - Reads formatted data matching specifiers from a stream.
 *   - Return: Number of successfully matched and assigned input items, or EOF.
 * ============================================================================ */
void demo_formatted_io(void) {
    printf("\n=== 1. Formatted I/O (fprintf / fscanf) ===\n");

    /* --- Reading with fscanf --- */
    FILE *in = fopen("data/formatted_input.txt", "r");
    if (!in) {
        perror("Failed to open data/formatted_input.txt");
        return;
    }

    /* --- Writing with fprintf --- */
    FILE *out = fopen("data/formatted_output.txt", "w");
    if (!out) {
        perror("Failed to open data/formatted_output.txt");
        fclose(in);
        return;
    }

    char name[32];
    int age;
    float gpa;

    fprintf(out, "%-10s %-5s %-6s\n", "NAME", "AGE", "GPA");
    fprintf(out, "-------------------------\n");

    /* Loop until fscanf cannot match all 3 fields or reaches EOF */
    while (fscanf(in, "%31s %d %f", name, &age, &gpa) == 3) {
        printf("[fscanf Read]  Name: %-10s | Age: %d | GPA: %.2f\n", name, age, gpa);
        fprintf(out, "%-10s %-5d %-6.2f\n", name, age, gpa);
    }

    fclose(in);
    fclose(out);
    printf("-> Formatted data written to data/formatted_output.txt\n");
}

/* ============================================================================
 * 2. CHARACTER-BY-CHARACTER I/O: fgetc & fputc
 * ----------------------------------------------------------------------------
 * int fgetc(FILE *stream);
 *   - Reads the next character from stream as an unsigned char cast to int.
 *   - Return: The character read, or EOF on end-of-file / error.
 *   - NOTE: Return type MUST be 'int' to properly check against EOF (-1).
 *
 * int fputc(int c, FILE *stream);
 *   - Writes character c (converted to unsigned char) to the stream.
 *   - Return: Character written on success, or EOF on error.
 * ============================================================================ */
void demo_character_io(void) {
    printf("\n=== 2. Character I/O (fgetc / fputc) ===\n");

    FILE *in = fopen("data/char_input.txt", "r");
    if (!in) {
        perror("Failed to open data/char_input.txt");
        return;
    }

    FILE *out = fopen("data/char_output.txt", "w");
    if (!out) {
        perror("Failed to open data/char_output.txt");
        fclose(in);
        return;
    }

    int ch; /* Must be int, NOT char, to catch EOF correctly */
    int char_count = 0;

    while ((ch = fgetc(in)) != EOF) {
        fputc(ch, out);
        char_count++;
    }

    fclose(in);
    fclose(out);
    printf("-> Transferred %d characters to data/char_output.txt using fgetc/fputc.\n", char_count);
}

/* ============================================================================
 * 3. LINE-BY-LINE STRING I/O: fgets & fputs
 * ----------------------------------------------------------------------------
 * char *fgets(char *str, int n, FILE *stream);
 *   - Reads at most n-1 characters, stopping at newline (\n) or EOF.
 *   - Null-terminates the buffer. Keeps '\n' inside buffer if encountered.
 *   - Return: 'str' pointer on success, NULL on EOF or error.
 *
 * int fputs(const char *str, FILE *stream);
 *   - Writes null-terminated string to stream (does NOT append automatic newline).
 *   - Return: Non-negative value on success, EOF on error.
 * ============================================================================ */
void demo_string_io(void) {
    printf("\n=== 3. Line/String I/O (fgets / fputs) ===\n");

    FILE *in = fopen("data/line_input.txt", "r");
    if (!in) {
        perror("Failed to open data/line_input.txt");
        return;
    }

    FILE *out = fopen("data/line_output.txt", "w");
    if (!out) {
        perror("Failed to open data/line_output.txt");
        fclose(in);
        return;
    }

    char line_buffer[BUFFER_SIZE];
    int line_number = 1;

    while (fgets(line_buffer, sizeof(line_buffer), in) != NULL) {
        printf("[fgets Line %d] %s", line_number, line_buffer);

        /* Write custom prefix then write line using fputs */
        char prefix[32];
        snprintf(prefix, sizeof(prefix), "[LOG %d] ", line_number);
        fputs(prefix, out);
        fputs(line_buffer, out);

        line_number++;
    }

    fclose(in);
    fclose(out);
    printf("-> Processed lines written to data/line_output.txt\n");
}

/* ============================================================================
 * 4. BINARY BLOCK I/O: fwrite & fread
 * ----------------------------------------------------------------------------
 * size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
 *   - Writes 'count' elements, each of 'size' bytes, from memory buffer to file.
 *   - Return: Number of successfully written full items (compare with count).
 *
 * size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
 *   - Reads 'count' elements, each of 'size' bytes, from file into buffer.
 *   - Return: Number of items successfully read (may be less than count on EOF).
 * ============================================================================ */
void demo_binary_io(void) {
    printf("\n=== 4. Binary Block I/O (fwrite / fread) ===\n");

    const char *binary_file = "data/students.bin";

    /* Dataset to write */
    StudentRecord write_data[3] = {
        {101, "David Miller", 91.5},
        {102, "Eva Green",    88.0},
        {103, "Frank Wright",  95.2}
    };
    size_t total_records = sizeof(write_data) / sizeof(write_data[0]);

    /* --- Binary Write (mode: "wb") --- */
    FILE *out = fopen(binary_file, "wb");
    if (!out) {
        perror("Failed to open data/students.bin for writing");
        return;
    }

    size_t written = fwrite(write_data, sizeof(StudentRecord), total_records, out);
    fclose(out);
    printf("-> Wrote %zu binary records to %s using fwrite.\n", written, binary_file);

    /* --- Binary Read (mode: "rb") --- */
    FILE *in = fopen(binary_file, "rb");
    if (!in) {
        perror("Failed to open data/students.bin for reading");
        return;
    }

    StudentRecord read_data[3];
    size_t read_count = fread(read_data, sizeof(StudentRecord), total_records, in);
    fclose(in);

    printf("-> Read %zu records using fread:\n", read_count);
    for (size_t i = 0; i < read_count; i++) {
        printf("   Record [%zu] ID: %d | Name: %-15s | Score: %.2f\n",
               i, read_data[i].id, read_data[i].name, read_data[i].score);
    }
}

/* ============================================================================
 * MAIN ENTRY POINT
 * ============================================================================ */
int main(void) {
    printf("============================================================\n");
    printf("         C Standard File I/O Operations Demo               \n");
    printf("============================================================\n");

    demo_formatted_io();
    demo_character_io();
    demo_string_io();
    demo_binary_io();

    printf("\nAll file I/O operations completed successfully.\n");
    return EXIT_SUCCESS;
}