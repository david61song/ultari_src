#include "input_validation.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

bool validate_student_id(const char *student_id) {
    if (student_id == NULL) return false;
    
    size_t len = strlen(student_id);
    if (len != MAX_STUDENT_ID_LENGTH) return false;
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit(student_id[i])) return false;
    }
    
    return true;
}

bool is_upper(char c) {
    return c >= 'A' && c <= 'Z';
}

bool is_lower(char c) {
    return c >= 'a' && c <= 'z';
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool is_special(char c) {
    const char *special_chars = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/";
    for (size_t i = 0; special_chars[i] != '\0'; i++) {
        if (c == special_chars[i]) {
            return true;
        }
    }
    return false;
}

bool validate_password(const char *password) {
    if (password == NULL) return false;
    
    size_t len = strlen(password);
    if (len < 9) return false;  // 최소 9자리
    
    bool has_upper = false, has_lower = false, has_digit = false, has_special = false;
    int type_count = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (is_upper(password[i])) has_upper = true;
        else if (is_lower(password[i])) has_lower = true;
        else if (is_digit(password[i])) has_digit = true;
        else if (is_special(password[i])) has_special = true;
    }
    
    if (has_upper) type_count++;
    if (has_lower) type_count++;
    if (has_digit) type_count++;
    if (has_special) type_count++;
    
    if (len == 9) {
        return type_count >= 3;  // 9자리인 경우 3종류 이상
    } else {
        return type_count >= 2;  // 10자리 이상인 경우 2종류 이상
    }
}
