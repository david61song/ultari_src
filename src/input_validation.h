#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <stdbool.h>

#define MAX_STUDENT_ID_LENGTH 10
#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 64

bool validate_student_id(const char *student_id);

bool validate_password(const char *password);

#endif // INPUT_VALIDATION_H
