### `idt_set_gate(num, base, sel, flags)`
- **Описание**: Устанавливает дескриптор в IDT
- **Параметры**:
  - `num` (uint8_t): Номер прерывания
  - `base` (uint32_t): Адрес обработчика
  - `sel` (uint16_t): Селектор сегмента кода
  - `flags` (uint8_t): Флаги типа (0x8E для шлюза прерывания)

### `init_idt()`
- **Описание**: Инициализирует IDT и регистрирует обработчики
- **Особенности**: Настраивает прерывание клавиатуры (IRQ1)
