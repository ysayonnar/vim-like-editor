#include "../include/modes/insert_mode.h"
#include "../include/editor.h"
#include "../include/exceptions/unknown_command.h"
#include "../include/string.h"
#include <iostream>
#include <string>

void InsertMode::exit() const {
    editor.operating_mode = new NormalMode(editor);
}

void InsertMode::handle_input(String str) const {
    char last_symbol = str[str.get_length() - 1];
    editor.command_input = "";
    if (last_symbol == 27) {
        exit();
        return;
    }
    if (last_symbol == '\n') {
        // Разбиваем текущую строку в позиции курсора: всё, что справа — в новую строку
        int y = editor.buf.get_current_pos_y();
        int x = editor.buf.get_current_pos_x();
        Slice<UnicodeSymbol> &cur_line = editor.buf.data[y];
        Slice<UnicodeSymbol> new_line;

        // Сохраняем оригинал строки, чтобы можно было отменить операцию
        Slice<UnicodeSymbol> original = cur_line;

        int cur_len = cur_line.get_length();
        // Переносим символы, стоящие справа от курсора, в новую строку
        for (int i = x; i < cur_len; ++i) {
            new_line.push(cur_line[i]);
        }

        // Удаляем перенесённые символы из исходной строки
        while (cur_line.get_length() > x) {
            cur_line.pop_at(x);
        }

        // Вставляем новую строку после текущей
        int total_lines = editor.buf.data.get_length();
        if (y >= total_lines - 1) {
            editor.buf.data.push(new_line);
        } else {
            editor.buf.data.push_after(new_line, y);
        }

        // Перемещаем курсор в начало новой строки
        editor.buf.current_pos_x = 0;
        editor.buf.prev_pos_x = 0;
        editor.buf.next_line();

        // Добавляем действие в стек отмены: восстановить старую строку и удалить вставленную
        {
            Editor *ed = &editor;
            ed->push_undo([ed, y, original]() mutable {
                ed->buf.data[y] = original;
                // Удаляем строку y+1, если она существует
                if (y + 1 < ed->buf.data.get_length()) {
                    ed->buf.data.pop_at(y + 1);
                }
                ed->buf.current_pos_y = y;
                ed->buf.current_pos_x = original.get_length();
            });
        }
    } else if (last_symbol == 8 || last_symbol == 127) {
        if (editor.buf.get_current_pos_y() == 0 && editor.buf.get_current_pos_x() == 0) {
            return;
        }

        if (editor.buf.get_current_pos_x() == 0) {
            // Сливаем текущую строку с предыдущей (Backspace в начале строки)
            int cur_y = editor.buf.get_current_pos_y();
            int prev_y = cur_y - 1;
            // Сохраняем обе строки для отмены операции
            Slice<UnicodeSymbol> prev_orig = editor.buf.data[prev_y];
            Slice<UnicodeSymbol> cur_orig = editor.buf.data[cur_y];
            int old_length = prev_orig.get_length();
            int cur_line_length = cur_orig.get_length();
            for (int i = 0; i < cur_line_length; ++i) {
                editor.buf.data[prev_y].push(cur_orig[i]);
            }
            editor.buf.data.pop_at(cur_y);
            editor.buf.prev_line();
            editor.buf.current_pos_x = old_length;

            // Добавляем откат: вернуть предыдущую и текущую строки в исходное состояние
            {
                Editor *ed = &editor;
                ed->push_undo([ed, prev_y, prev_orig, cur_orig]() mutable {
                    ed->buf.data[prev_y] = prev_orig;
                    ed->buf.data.push_after(cur_orig, prev_y);
                });
            }
        } else {
            int y = editor.buf.get_current_pos_y();
            int pos = editor.buf.get_current_pos_x() - 1;
            UnicodeSymbol deleted = editor.buf.data[y][pos];
            editor.buf.data[y].pop_at(pos);
            editor.buf.prev_symbol();

            // Добавляем откат: снова вставить удалённый символ
            {
                Editor *ed = &editor;
                ed->push_undo([ed, y, pos, deleted]() mutable {
                    ed->buf.data[y].insert_at(pos, deleted);
                    ed->buf.current_pos_y = y;
                    ed->buf.current_pos_x = pos + 1;
                });
            }
        }
    } else {
        // Вставляем UnicodeSymbol в позицию курсора (допускается вставка в начало или в конец строки)
        UnicodeSymbol symbol(str.get_c_style());

        auto &line = editor.buf.data[editor.buf.get_current_pos_y()];
        int idx = editor.buf.get_current_pos_x();

        // Вставляем по индексу idx (0..length). При idx == length выполняется добавление в конец
        int y = editor.buf.get_current_pos_y();
        line.insert_at(idx, symbol);
        editor.buf.next_symbol();

        // Добавляем откат: удалить вставленный символ
        {
            Editor *ed = &editor;
            ed->push_undo([ed, y, idx]() mutable {
                ed->buf.data[y].pop_at(idx);
                ed->buf.current_pos_y = y;
                ed->buf.current_pos_x = idx;
            });
        }
    }

    throw UnknownCommand("ok");
}