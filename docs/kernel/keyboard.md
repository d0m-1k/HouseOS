### `init_keyboard()`
- **Описание**: Настраивает контроллер прерываний (PIC) для клавиатуры
- **Особенности**: Отправляет команды ICW1-ICW4 в порты 0x20-0x21

### `kernel_keyboard_handler()`
- **Описание**: Обрабатывает скан-код клавиатуры
- **Особенности**: Преобразует скан-код в символ, выводит на экран и в COM-порт
