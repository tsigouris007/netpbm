#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define P1 1
#define P2 2
#define P3 3
#define P4 4
#define P5 5
#define P6 6

// https://www.geeksforgeeks.org/c-program-to-write-an-image-in-pgm-format/
// od -tx1c NIbin.ppm | head -n 100

char remove_comment(char *buffer) {
  char *pos = strstr(buffer, "#"); // Returns a pointer where the needle # was found
  if (pos)
    return buffer[strcspn(buffer, pos)] = '\0';
  return 'x'; // Defaults to a character to break loops
}

// Cleanup string from newlines and null terminators
char cleanup(char *buffer) {
  return buffer[strcspn(buffer, "\r\n")] = '\0';
}

int get_magic_num(char *buffer) {
  if (strcmp(buffer, "P1") == 0)
    return 1;
  if (strcmp(buffer, "P2") == 0)
    return 2;
  if (strcmp(buffer, "P3") == 0)
    return 3;
  if (strcmp(buffer, "P4") == 0)
    return 4;
  if (strcmp(buffer, "P5") == 0)
    return 5;
  if (strcmp(buffer, "P6") == 0)
    return 6;

  return 0;
}

int main(void) {
  char buffer[BUFSIZ]; // defined in stdio

  // Read magic number
  fgets(buffer, BUFSIZ, stdin);
  cleanup(buffer);
  int magic_num = get_magic_num(buffer);
  // printf("Magic Number: %d\n", magic_num);

  // Try to read the size
  fgets(buffer, BUFSIZ, stdin);
  cleanup(buffer);

  // Remove any potential comments
  while (remove_comment(buffer) != 'x')
    fgets(buffer, BUFSIZ, stdin);
  
  // Finally read the size
  char *token = strtok(buffer, " ");
  int width = atoi(token);
  token = strtok(NULL, " ");
  int height = atoi(token);
  // printf("Dimensions: %dx%d\n", width, height);

  // Try to read the max integer color value
  fgets(buffer, BUFSIZ, stdin);
  cleanup(buffer);

  // Portable Gray + Pix Map
  int max_color_value = 0;
  if (magic_num == P2 || magic_num == P3 || magic_num == P5 || magic_num == P6)
    max_color_value = atoi(buffer);

  // if (max_color_value != 0)
  //   printf("Max Color Value: %d\n", max_color_value);

  printf("P%d\n", magic_num);
  printf("%d %d\n", width, height);
  printf("%d\n", max_color_value);

  while(fgets(buffer, BUFSIZ, stdin) != NULL) {
    for (int i = 0; i < BUFSIZ; i++) {
      unsigned char c = buffer[i];
      printf("%c", c);
    }
    putchar('\n');
    // printf("%s", buffer);
  }
  return 0;
}