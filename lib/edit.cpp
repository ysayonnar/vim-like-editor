#include "../include/commands/edit.h"
#include "../include/commands/basic_movement.h"
#include "../include/editor.h"
#include "../include/exceptions/exit_command.h"

void CutSymbol::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }

    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.cut_current_symbol();
    }
}

void CutLine::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }

    int start_line = editor.buf.get_current_pos_y();
    int end_line = start_line + times_to_repeat - 1;
    if (end_line >= editor.buf.data.get_length()) {
        end_line = editor.buf.data.get_length() - 1;
    }

    // Копируем строки в буфер обмена и сохраняем их для возможности отката
    editor.clipboard.clear();
    editor.clipboard.set_linewise(true);
    std::vector<Slice<UnicodeSymbol>> saved_lines;
    for (int i = start_line; i <= end_line; ++i) {
        editor.clipboard.data.push(editor.buf.data[i]);
        saved_lines.push_back(editor.buf.data[i]);
    }

    // Добавляем откат: вставить сохранённые строки обратно, начиная с start_line
    {
        Editor *ed = &editor;
        auto saved = saved_lines;
        ed->push_undo([ed, start_line, saved]() mutable {
            for (int i = 0; i < (int)saved.size(); ++i) {
                ed->buf.data.push_after(saved[i], start_line + i - 1);
            }
        });
    }

    // Удаляем строки из буфера
    for (int i = 0; i < times_to_repeat; i++) {
        editor.buf.cut_current_line();
    }
}

void NewLineAfterAndInsert::execute(String combination) const {
    editor.buf.new_line_after();
    editor.buf.next_line();

    editor.operating_mode = new InsertMode(editor);
}

void NewLineBeforeAndInsert::execute(String combination) const {
    editor.buf.new_line_before();
    editor.buf.prev_line();

    editor.operating_mode = new InsertMode(editor);
}

void SaveQuit::execute(String combination) const {
    if (combination == ":w\n" || combination == ":wq\n") {
        editor.buf.save(editor.filename);
    }

    if (combination == ":q\n" || combination == ":wq\n") {
        throw ExitCommand("exit");
    }
}

void Paste::execute(String combination) const {
    // Вставка содержимого буфера обмена в текущую позицию курсора
    int line = editor.buf.get_current_pos_y();
    int col = editor.buf.get_current_pos_x();
    // Выполняем вставку
    if (editor.clipboard.is_linewise()) {
        int inserted = editor.clipboard.data.get_length();
        editor.clipboard.paste_into(editor.buf, line, col);
        // Добавляем откат: удалить вставленные строки
        {
            Editor *ed = &editor;
            ed->push_undo([ed, line, inserted]() mutable {
                for (int i = 0; i < inserted; ++i) {
                    ed->buf.data.pop_at(line + 1);
                }
            });
        }
    } else {
        // По символам (не построчно)
        int chars = editor.clipboard.data.get_length() > 0 ? editor.clipboard.data[0].get_length() : 0;
        editor.clipboard.paste_into(editor.buf, line, col);
        {
            Editor *ed = &editor;
            ed->push_undo([ed, line, col, chars]() mutable {
                // Удаляем вставленные символы при откате
                for (int i = 0; i < chars; ++i) {
                    ed->buf.data[line].pop_at(col);
                }
            });
        }
    }
}

void YankLine::execute(String combination) const {
    int times_to_repeat = extract_num(combination);
    if (times_to_repeat == 0) {
        times_to_repeat = 1;
    }

    int start_line = editor.buf.get_current_pos_y();
    int end_line = start_line + times_to_repeat - 1;
    if (end_line >= editor.buf.data.get_length()) {
        end_line = editor.buf.data.get_length() - 1;
    }

    editor.clipboard.clear();
    editor.clipboard.set_linewise(true);
    for (int i = start_line; i <= end_line; ++i) {
        editor.clipboard.data.push(editor.buf.data[i]);
    }
}

void UndoCmd::execute(String combination) const {
    editor.undo_last();
}