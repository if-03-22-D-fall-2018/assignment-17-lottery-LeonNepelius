/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include "lottery.h"
#include "general.h"
#include <string.h> // for strtok to split the string to substring with separator
#include <stdlib.h> // for atoi to work (converts string to int)
#include <stdio.h>

#define 	UUID_LEN   40
#define 	MAX_TIP_LEN   17
#define 	MAX_LINE_LEN   (UUID_LEN + 1 + MAX_TIP_LEN + 1)

static FILE* stream;
static char separator;
static int drawing_of_numbers[TIP_SIZE];

bool init_lottery(const char *csv_file, char csv_separator)
{
  stream = fopen(csv_file, "r");
  separator = csv_separator;
  if (stream == 0) return false;
  return true;
}

bool get_tip(int tip_number, int tip[TIP_SIZE])
{
    if (tip_number < 0 || tip_number >= 44) return false;
    int count = 0;
    char line[MAX_LINE_LEN];
    while ( fgets(line, MAX_LINE_LEN, stream) != NULL) // read a line
    {
        if (count == tip_number)
        {
            if (line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0'; // need to remove \n (new line) to get the last number without \n
            count = 0;
            char str[2];
            str[0] = separator;
            str[1] = '\0';
            char* ptr = strtok(line, str); // gets the first string before separator
            while(ptr != NULL && count < TIP_SIZE)
            {
                ptr = strtok(NULL, str); // gets next string
                tip[count] = atoi(ptr); // converts the string to an int
                count++;
            }
            rewind(stream); // sets current to 0 to start at the beginning next time
            return true;
        }
        else
        {
            count++;
        }
    }
  return false;
}

bool set_drawing(int drawing_numbers[TIP_SIZE])
{
  for (int i = 0; i < TIP_SIZE; i++) {
    if (drawing_numbers[i] <= 0 || drawing_numbers[i] > 45) return false;
    else drawing_of_numbers[i] = drawing_numbers[i];
  }
  return true;
}

int get_tip_result(int tip_number)
{
  if (tip_number < 0 || tip_number >= 44) return -2;
  if (!drawing_of_numbers[0])return -1;
  int tip[TIP_SIZE];
  int count = 0;
  get_tip(tip_number,tip);
  for (int i = 0; i < TIP_SIZE; i++) {
    for (int j = 0; j < TIP_SIZE; j++) {
      if (drawing_of_numbers[i] == tip[j]) count++;
    }
  }
  return count;
}

int get_right_tips_count(int right_digits_count)
{
  fclose(stream);
  return 0;
}
