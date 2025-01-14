#include "../header.h"



int add_char_to_enter(WINDOW *win, int ch, int max_buf, char *buffer_ip, int *buffer_pos) {
    if (*buffer_pos < max_buf) {                                                                   // Убедитесь, что позиция буфера не превышает максимальную длину
        if (isprint(ch)) {                                                                         // Проверяем, что символ является печатаемым
            buffer_ip[*buffer_pos] = ch;                                                           // Добавляем символ к буферу
            if (max_buf == 64) {                                                                   // если пароль заменять на *
                ch = '*';
            }
            mvwprintw(win, 0, 0 + *buffer_pos, "%c", ch);                                          // Выводим символ на экран в соответствии с позицией в строке
            (*buffer_pos)++;                                                                       // Увеличиваем позицию буфера для следующего символа
        }
    }
}

int delete_char_from_enter(WINDOW *win, char *buffer_ip, int *buffer_pos) {
    if (*buffer_pos > 0) {                                                                         // Убеждаемся, что есть символы для удаления
        (*buffer_pos)--;                                                                           // Уменьшаем позицию буфера для удаления последнего символа
        buffer_ip[*buffer_pos] = '\0';                                                             // Устанавливаем последний символ в буфере как нулевой символ, чтобы удалить его
        mvwprintw(win, 0, 0 + *buffer_pos, " ");                                                   // Печатаем пробел на месте удаленного символа на экране
    }
}