#include "../include/modes/visual_mode.h"
#include "../include/editor.h"
#include "../include/modes/normal_mode.h"
#include "../include/string.h"
#include <iostream>

VisualMode::VisualMode(Editor &editor, bool line_mode) : OperatingMode(editor, true), line_mode(line_mode) {
    editor.buf.selection_active = true;
    if (line_mode) {
        editor.buf.sel_anchor_y = editor.buf.get_current_pos_y();
        editor.buf.sel_anchor_x = 0; // начало строки
        editor.buf.current_pos_x = editor.buf.data[editor.buf.get_current_pos_y()].get_length();
    } else {
        editor.buf.sel_anchor_x = editor.buf.get_current_pos_x();
        editor.buf.sel_anchor_y = editor.buf.get_current_pos_y();
    }
}

void VisualMode::exit() const {
    editor.buf.selection_active = false;
    editor.operating_mode = new NormalMode(editor);
}

void VisualMode::handle_input(String str) const {
    char last_symbol = str[str.get_length() - 1];

    if (last_symbol == 27) { // ESC (Escape)
        editor.command_input = "";
        exit();
        return;
    }

    // Клавиши передвижения
    if (last_symbol == 'h') {
        editor.buf.prev_symbol();
    } else if (last_symbol == 'l') {
        editor.buf.next_symbol();
    } else if (last_symbol == 'j') {
        editor.buf.next_line();
    } else if (last_symbol == 'k') {
        editor.buf.prev_line();
    } else if (last_symbol == 'w') {
        editor.buf.next_word();
    } else if (last_symbol == 'b') {
        editor.buf.prev_word();
    } else if (last_symbol == 'y') {
        // Копируем (yank) выделение в буфер обмена
        int ay = editor.buf.sel_anchor_y;
        int ax = editor.buf.sel_anchor_x;
        int by = editor.buf.get_current_pos_y();
        int bx = editor.buf.get_current_pos_x();

        int sY = ay, sX = ax, eY = by, eX = bx;
        if (sY > eY || (sY == eY && sX > eX)) {
            sY = by;
            sX = bx;
            eY = ay;
            eX = ax;
        }

        if (sY == eY && sX == eX)
            return;

        editor.clipboard.clear();

        if (sY == eY) {
            Slice<UnicodeSymbol> fragment;
            int line_len = editor.buf.data[sY].get_length();
            int end_idx = std::min(eX, line_len);
            for (int i = sX; i < end_idx; ++i)
                fragment.push(editor.buf.data[sY][i]);
            editor.clipboard.data.push(fragment);
            editor.clipboard.set_linewise(false);
        } else {
            for (int line = sY; line <= eY; ++line)
                editor.clipboard.data.push(editor.buf.data[line]);
            editor.clipboard.set_linewise(true);
        }

        editor.buf.selection_active = false;
        editor.operating_mode = new NormalMode(editor);
        return;
    } else if (last_symbol == 'd') {
        // Удаляем выделение: копируем в буфер обмена и удаляем выбранный фрагмент
        int ay = editor.buf.sel_anchor_y;
        int ax = editor.buf.sel_anchor_x;
        int by = editor.buf.get_current_pos_y();
        int bx = editor.buf.get_current_pos_x();

        int sY = ay, sX = ax, eY = by, eX = bx;
        if (sY > eY || (sY == eY && sX > eX)) {
            sY = by;
            sX = bx;
            eY = ay;
            eX = ax;
        }

        if (sY == eY && sX == eX)
            return;

        // Сохраняем полные строки перед удалением, чтобы можно было откатить операцию
        std::vector<Slice<UnicodeSymbol>> saved_full_lines;
        for (int ln = sY; ln <= eY; ++ln)
            saved_full_lines.push_back(editor.buf.data[ln]);

        editor.clipboard.clear();

        if (sY == eY) {
            Slice<UnicodeSymbol> line_copy;
            int line_len = editor.buf.data[sY].get_length();
            int end_idx = std::min(eX, line_len);
            for (int i = sX; i < end_idx; ++i)
                line_copy.push(editor.buf.data[sY][i]);
            editor.clipboard.data.push(line_copy);
            editor.clipboard.set_linewise(false);

            for (int i = end_idx - 1; i >= sX; --i) {
                if (i >= 0 && i < editor.buf.data[sY].get_length())
                    editor.buf.data[sY].pop_at(i);
            }
        } else {
            // Первая частичная строка (в начале выделения)
            Slice<UnicodeSymbol> first_part;
            int first_len = editor.buf.data[sY].get_length();
            for (int i = sX; i < first_len; ++i)
                first_part.push(editor.buf.data[sY][i]);
            editor.clipboard.data.push(first_part);

            // Полные строки, полностью попавшие в выделение (средние)
            for (int line = sY + 1; line < eY; ++line)
                editor.clipboard.data.push(editor.buf.data[line]);

            // Последняя частичная строка (в конце выделения)
            Slice<UnicodeSymbol> last_part;
            int last_len = editor.buf.data[eY].get_length();
            int end_idx = std::min(eX, last_len);
            for (int i = 0; i < end_idx; ++i)
                last_part.push(editor.buf.data[eY][i]);
            editor.clipboard.data.push(last_part);
            editor.clipboard.set_linewise(true);

            // Формируем объединённую строку: префикс из sY + суффикс из eY
            Slice<UnicodeSymbol> merged;
            for (int i = 0; i < sX && i < editor.buf.data[sY].get_length(); ++i)
                merged.push(editor.buf.data[sY][i]);
            for (int i = eX; i < editor.buf.data[eY].get_length(); ++i)
                merged.push(editor.buf.data[eY][i]);

            editor.buf.data[sY] = merged;

            // Удаляем строки с sY+1 по eY
            int remove_count = eY - sY;
            for (int r = 0; r < remove_count; ++r)
                editor.buf.data.pop_at(sY + 1);
        }

        // Перемещаем курсор в начало области выделения
        editor.buf.current_pos_y = sY;
        editor.buf.current_pos_x = sX;
        int new_len = editor.buf.data[sY].get_length();
        if (editor.buf.current_pos_x > new_len)
            editor.buf.current_pos_x = new_len;

        editor.buf.selection_active = false;

        // Добавляем действие отката: восстановить сохранённые строки начиная с sY
        {
            Editor *ed = &editor;
            auto saved = saved_full_lines; // copy
            ed->push_undo([ed, sY, saved]() mutable {
                // Восстанавливаем первую строку
                ed->buf.data[sY] = saved[0];
                // Вставляем остальные строки после sY
                for (int i = 1; i < (int)saved.size(); ++i) {
                    ed->buf.data.push_after(saved[i], sY + i - 1);
                }
            });
        }

        editor.operating_mode = new NormalMode(editor);
        return;
    } else if (last_symbol == 'v') {
        exit();
        return;
    } else {
        // Игнорируем прочие клавиши
        return;
    }

    // Обеспечиваем, что выделение остаётся активным
    editor.buf.selection_active = true;
    return;
}