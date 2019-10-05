# Input library
Библиотека для работы с входным потоком

При инициализации объекта класса Input есть два пути:
- Указывается входной поток (потомок istream).
	- Если входной поток пуст, то конструктор выбросит исключение invalid_argument с сообщением "Stream is empty".
- Указывается <имя файла> входного файла.
	- Если входной файл с именем <имя файла> не существует, то конструктор выбросит исключение invalid_argument с сообщением "File \"<имя файла>\" doesn't exists".
	- Если входной файл с именем <имя файла> пуст, то конструктор выбросит исключение invalid_argument с сообщением "File \"<имя файла>\" is empty".

## Методы библиотеки

Когда объект класса Input создан, разработчику доступен ряд методов.

### Методы, описывающие состояние

#### GetFileName
**Сигнатура**:
```c++
string const & GetFileName() const
```

**Описание**: метод возвращает имя файла, над которым происходит работа объекта. Если объект работает не с файлом, а с потоком, то вернётся пустая строка.

**Входные параметры**: метод не принимает параметры.

**Возвращаемое значение**: имя файла или пустая строка.

**Пример: если в конструктор передан входной поток**:
```c++
stringstream stringStream("some string");
Input input(stringStream);
cout << input.GetFileName() << endl;
```
Вывод:
```

```
**Пример: если в конструктор передано имя файла (файл существует и не пуст)**:
```c++
Input input("fileName.txt");
cout << input.GetFileName() << endl;
```
Вывод:
```
fileName.txt
```

#### GetSize
**Сигнатура**:
```c++
size_t GetSize() const
```

**Описание**: метод возвращает размер потока.

**Входные параметры**: метод не принимает параметры.

**Возвращаемое значение**: размер потока.

**Пример**:
```c++
string const fileName = "not_empty_file";
ofstream of(fileName, ofstream::trunc);
of.write("0", 1);
of.close();
cout << Input(fileName).GetSize() << endl;
```
Вывод:
```
1
```

#### GetPosition
**Сигнатура**:
```c++
StreamPosition const & GetPosition() const
```

**Описание**: метод возвращает текущую позицию строки и столбца в потоке. Номер строки и столбца начинаются с единицы.

**Входные параметры**: метод не принимает параметры.

**Возвращаемое значение**: текущая позиция строки и столбца в потоке.

**Пример**:
```c++
stringstream stringStream("some string");
Input input(stringStream);
cout << input.GetPosition().GetLine() << " " << input.GetPosition().GetColumn() << endl;
```
Вывод:
```
1 1
```

#### GetCharPosition
**Сигнатура**:
```c++
size_t GetCharPosition() const
```

**Описание**: метод возвращает текущую позицию в потоке.

**Входные параметры**: метод не принимает параметры.

**Возвращаемое значение**: текущая позиция в потоке.

**Пример**:
```c++
string const fileName = "not_empty_file";
ofstream of(fileName, ofstream::trunc);
of.write("0", 1);
of.close();
Input input(fileName);
cout << input.GetCharPosition() << endl;
input.SkipArgument<char>();
cout << input.GetCharPosition() << endl;
input.SkipArgument<char>();
cout << input.GetCharPosition() << endl;
```
Вывод:
```
0
1
1
```

#### GetNextCharacter
**Сигнатура**:
```c++
bool GetNextCharacter(char & nextCharacter) const
```

**Описание**: возвращает следующий символ потока. Если впереди нет символа, то переданный параметр для помещения следующего символа не изменяется, а метод возвращает **false**.

**Входные параметры**:
- **nextCharacter**: ссылка на переменную типа char для помещения в него следующего символа потока.

**Возвращаемое значение**: **true**, если удалось получить следующий символ потока, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("!");
Input input(stringStream);

char firstCallNextCharacter = '#';
cout << "First call:" << endl;
cout << "\t" << "Method returned "
	<< (input.GetNextCharacter(firstCallNextCharacter) ? "true" : "false") << endl;
cout << "\t" << "Next character: " << firstCallNextCharacter << endl;

input.SkipArgument<char>(); // Skip one character in input stream

char secondCallNextCharacter = '#';
cout << "Second call:" << endl;
cout << "\t" << "Method returned "
	<< (input.GetNextCharacter(secondCallNextCharacter) ? "true" : "false") << endl;
cout << "\t" << "Next character: " << secondCallNextCharacter << endl;
```
Вывод:
```
First call:
	Method returned true
	Next character: !
Second call:
	Method returned false
	Next character: #
```

#### IsEndOfStream
**Сигнатура**:
```c++
bool IsEndOfStream() const
```

**Описание**: метод возвращает истину, если впереди в потоке не осталось символов.

**Входные параметры**: метод не принимает параметры.

**Возвращаемое значение**: **true**, если впереди в потоке не осталось символов, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("!");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\t" << "Method returned " << (input.IsEndOfStream() ? "true" : "false") << endl;

input.SkipArgument<char>(); // Skip one character in input stream

cout << "Second call:" << endl;
cout << "\t" << "Method returned " << (input.IsEndOfStream() ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned false
Second call:
	Method returned true
```

#### IsEndOfLine
**Сигнатура**:
```c++
bool IsEndOfLine() const
```

**Описание**: метод возвращает истину, если впереди в потоке следует символ конца строки. Символ конца строки - это любой из следующих символов: '\n', '\r'.

**Входные параметры**: метод не принимает параметры.

**Возвращаемое значение**: **true**, если впереди в потоке следует символ конца строки, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("!\n");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\t" << "Method returned " << (input.IsEndOfLine() ? "true" : "false") << endl;

input.SkipArgument<char>(); // Skip one character in input stream

cout << "Second call:" << endl;
cout << "\t" << "Method returned " << (input.IsEndOfLine() ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned false
Second call:
	Method returned true
```

### Методы для пропуска данных

#### SkipLine
**Сигнатура**:
```c++
bool SkipLine()
```

**Описание**: метод пропускает символы потока, пока не встретит символ конца строки. Если символа конца строки на пути не оказалось, то метод вернёт ложь. Встретив символ конца строки, метод его пропускает. Если на пути окажется символ конца строки '\r', а сразу за ним - '\n', то метод пропустит оба символа.

**Входные параметры**: метод не принимает параметры.

**Возвращаемое значение**: **true**, если в процессе пропуска символов был достигнут символ конца строки, в противном случае - **false**.

**Пример: символ конца строки не достигается**:
```c++
stringstream stringStream("!\n\r!");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipLine() ? "true" : "false") << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipLine() ? "true" : "false") << endl;

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.SkipLine() ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned true
Third call:
	Method returned false
```

**Пример: символ конца строки из двух символов**:
```c++
stringstream stringStream("!\r\n!");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipLine() ? "true" : "false") << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipLine() ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned false
```

#### SkipLines
**Сигнатура**:
```c++
bool SkipLines(size_t skipCount)
```

**Описание**: метод пропускает символы потока, пока не встретит символ конца строки указанное в параметре количество раз. Если ожидаемое количество символов конца строки на пути не оказалось, то метод вернёт ложь. Последовательность '\r\n' считается за один символ конца строки.

**Входные параметры**:
- **skipCount**: количество строк, которое нужно пропустить.

**Возвращаемое значение**: **true**, если в процессе пропуска символов было достигнуто указанное в параметре число символов конца строки, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("\n\n\n\n\n");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipLines(1) ? "true" : "false") << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipLines(2) ? "true" : "false") << endl;

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.SkipLines(3) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned true
Third call:
	Method returned false
```

**Пример**: с символом конца строки '\r\n':
```c++
stringstream stringStream("\r\n\n");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipLines(2) ? "true" : "false") << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipLines(1) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned false
```

#### SkipArgument
**Сигнатура**:
```c++
template<typename T>
bool SkipArgument(bool skipEndOfLine = true)
```

**Описание**: метод пропускает элемент указанного типа. Если значение указанного параметра - **true**, то метод ограничивается концом потока, иначе концом строки. Если не удалось прочитать пропускаемый элемент, то метод вернёт ложь.

**Входные параметры**:
- **skipEndOfLine**: если **true**, то метод не ограничится концом строки. По умолчанию - **true**.

**Возвращаемое значение**: **true**, если методу удалось пропустить элемент указанного типа, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("5 months ago");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipArgument<int>() ? "true" : "false") << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipArgument<string>() ? "true" : "false") << endl;

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.SkipArgument<int>() ? "true" : "false") << endl;

cout << "Fours call:" << endl;
cout << "\tMethod returned " << (input.SkipArgument<string>() ? "true" : "false") << endl;

cout << "Fifth call:" << endl;
cout << "\tMethod returned " << (input.SkipArgument<char>() ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned true
Third call:
	Method returned false
Fours call:
	Method returned true
Fifth call:
	Method returned false
```
**Пример**: ограничиваясь концом строки:
```c++
stringstream stringStream("5\n221");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipArgument<int>(false) ? "true" : "false") << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipArgument<int>(false) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned false
```

#### SkipArguments
**Сигнатура**:
```c++
template<typename T>
bool SkipArguments(size_t skipCount, bool skipEndOfLine = true)
```

**Описание**: метод пропускает элемент указанного типа указанное количество раз. Если значение параметра **skipEndOfLine** - **true**, то метод ограничивается концом потока, иначе концом строки. Если не удалось прочитать пропускаемый элемент, то метод вернёт ложь.

**Входные параметры**:
- **skipCount**: количество элементов указанного типа, которое нужно пропустить.
- **skipEndOfLine**: если **true**, то метод не ограничится концом строки. По умолчанию - **true**.

**Возвращаемое значение**: **true**, если методу удалось пропустить элемент указанного типа указанное количество раз, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("America, New Mexico, The 5 keys");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipArguments<string>(2) ? "true" : "false") << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipArguments<string>(2) ? "true" : "false") << endl;

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.SkipArguments<int>(1) ? "true" : "false") << endl;

cout << "Fours call:" << endl;
cout << "\tMethod returned " << (input.SkipArguments<string>(2) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned true
Third call:
	Method returned true
Fours call:
	Method returned false
```
**Пример**: не все элементы преобразуемы в указанный тип: 
```c++
stringstream stringStream("0 1 two 3");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipArguments<int>(4) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned false
```

#### SkipCharacters
**Сигнатура**:
```c++
bool SkipCharacters(unordered_set<char> const & characters)
```

**Описание**: метод пропускает символы входного потока, пока они принадлежат указанному множеству. Если в результате работы метода хотя бы один символ был пропущен, то метод вернёт истину.

**Входные параметры**:
- **characters**: множество символов, элементы которого нужно пропускать.

**Возвращаемое значение**: **true**, если метод пропустил хотя бы один символ входного потока, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("@#$%Hello, World!");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipCharacters({ '@', '#', '$', '%' }) ? "true" : "false") << endl;

string stringAfterSkippedCharacters;
input.ReadArguments(false, stringAfterSkippedCharacters);
cout << "\tString after skipped characters: " << stringAfterSkippedCharacters << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipCharacters({ '@', '#', '$', '%' }) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
	String after skipped characters: Hello,
Second call:
	Method returned false
```

#### SkipUntilCharacters
**Сигнатура**:
```c++
bool SkipUntilCharacters(unordered_set<char> const & characters)
```

**Описание**: метод пропускает символы входного потока, пока не встретится один из указанного множества. Если в результате работы метода был достигнут один из символов из указанного множества, то метод вернёт истину.

**Входные параметры**:
- **characters**: множество символов, при встрече с любым из них завершается процесс пропуска символов входного потока.

**Возвращаемое значение**: **true**, если метод достиг хотя бы один символ из указанного множества, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("Hello,@Hello,#World!");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipUntilCharacters({ '@', '#', '$', '%' }) ? "true" : "false") << endl;

input.SkipArgument<char>(); // Skip @

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipUntilCharacters({ '@', '#', '$', '%' }) ? "true" : "false") << endl;

input.SkipArgument<char>(); // Skip #

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.SkipUntilCharacters({ '@', '#', '$', '%' }) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned true
Third call:
	Method returned false
```

#### SkipUntilStrings
**Сигнатура**:
```c++
bool SkipUntilStrings(vector<string> const & strings)
```

**Описание**: метод пропускает символы входного потока, пока не встретится любая строка из указанного множества. Если в результате работы метода была достигнута одна из строк из указанного множества, то метод вернёт истину.

**Входные параметры**:
- **strings**: множество строк, при встрече с любой из них завершается процесс пропуска символов входного потока.

**Возвращаемое значение**: **true**, если метод достиг хотя бы одну строку из указанного множества, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("find m find me and me notme");
Input input(stringStream);

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.SkipUntilStrings({ "find me", "and me" }) ? "true" : "false") << endl;

input.SkipArguments<string>(2); // Skip find me

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.SkipUntilStrings({ "find me", "and me" }) ? "true" : "false") << endl;

input.SkipArgument<char>(); // Skip and me

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.SkipUntilStrings({ "find me", "and me" }) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned true
Third call:
	Method returned false
```

### Методы для считывания данных

#### ReadLine
**Сигнатура**:
```c++
bool ReadLine(string & line, bool doAppend = false)
```

**Описание**: метод считывает строку до символа конца строки из входного потока в указанный параметр **line**. Если значение параметра **doAppend** - **true**, то считанная строка будет дописана в конец **line**. Если после прочитанной строки удаётся пропустить символ конца строки, то метод вернёт истину. Если символом конца строки окажется '\r', а сразу за ним - '\n', то метод пропустит оба символа.

**Входные параметры**:
- **line**: строка, в которую запишется прочитанная с входного потока строка.
- **doAppend**: если **true**, то метод допишет прочитанную с входного потока строку в конец **line**, иначе параметр **line** будет перезаписан.

**Возвращаемое значение**: **true**, если метод достиг символ конца строки, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("first line\nsecond line\rthird line\r\nfours line");
Input input(stringStream);
string line;

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.ReadLine(line) ? "true" : "false") << endl;
cout << "\tRead line: " << line << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.ReadLine(line) ? "true" : "false") << endl;
cout << "\tRead line: " << line << endl;

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.ReadLine(line) ? "true" : "false") << endl;
cout << "\tRead line: " << line << endl;

cout << "Fours call:" << endl;
cout << "\tMethod returned " << (input.ReadLine(line) ? "true" : "false") << endl;
cout << "\tRead line: " << line << endl;
```
Вывод:
```
First call:
	Method returned true
	Read line: first line
Second call:
	Method returned true
	Read line: second line
Third call:
	Method returned true
	Read line: third line
Fours call:
	Method returned false
	Read line: fours line
```

#### ReadArguments
**Сигнатура**:
```c++
template<typename... Targs>
bool ReadArguments(bool readEndOfLine, Targs &... args)
```

**Описание**: метод считывает элементы из входного потока. Если значение параметра **readEndOfLine** - **true**, то метод ограничивается концом потока, иначе концом строки. Если не удалось прочитать какой-либо элемент, то метод вернёт ложь.

**Входные параметры**:
- **readEndOfLine**: если **true**, то метод не ограничится концом строки.
- **args**: элементы, куда будут помещены считанные данные.

**Возвращаемое значение**: **true**, если методу удалось считать все требуемые элементы из входного потока, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("1 2517\nstring 2");
Input input(stringStream);
bool element0;
int element1;
string element2;
bool element3;

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.ReadArguments(false, element0) ? "true" : "false") << endl;

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.ReadArguments(false, element1) ? "true" : "false") << endl;

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.ReadArguments(false, element2) ? "true" : "false") << endl;

cout << "Fours call:" << endl;
cout << "\tMethod returned " << (input.ReadArguments(true, element2) ? "true" : "false") << endl;

cout << "Fifth call:" << endl;
cout << "\tMethod returned " << (input.ReadArguments(false, element3) ? "true" : "false") << endl;
```
Вывод:
```
First call:
	Method returned true
Second call:
	Method returned true
Third call:
	Method returned false
Fours call:
	Method returned true
Fifth call:
	Method returned false
```

#### ReadUntilCharacters
**Сигнатура**:
```c++
bool ReadUntilCharacters(unordered_set<char> const & characters, string & readString, bool doAppend = false)
```

**Описание**: метод считывает последовательность символов из входного потока, пока не встретит любой символ из параметра **characters**. Если параметр **doAppend** - **true**, то считанная последовательность допишется в параметр **readString**, иначе **readString** будет перезаписан. Если метод не достигнет любой символ из параметра **characters**, то метод вернёт ложь.

**Входные параметры**:
- **characters**: множество символов, при встрече с любым из них завершается процесс считывания последовательности символов входного потока.
- **readString**: строка, в которую будет помещена считанная последовательность символов.
- **doAppend**: если **true**, то метод допишет считанную последовательность в конец **readString**. По умолчанию - **false**.

**Возвращаемое значение**: **true**, если метод достиг любой символ из множества **characters**, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("first#second@third");
Input input(stringStream);
string readString;

cout << "First call:" << endl;
cout << "\tMethod returned " << (input.ReadUntilCharacters({ '#', '@' }, readString) ? "true" : "false") << endl;
cout << "\tRead string: " << readString << endl;

input.SkipArgument<char>(); // Skip character '#'

cout << "Second call:" << endl;
cout << "\tMethod returned " << (input.ReadUntilCharacters({ '#', '@' }, readString, true) ? "true" : "false") << endl;
cout << "\tRead string: " << readString << endl;

input.SkipArgument<char>(); // Skip character '@'

cout << "Third call:" << endl;
cout << "\tMethod returned " << (input.ReadUntilCharacters({ '#', '@' }, readString, false) ? "true" : "false") << endl;
cout << "\tRead string: " << readString << endl
```
Вывод:
```
First call:
	Method returned true
	Read string: first
Second call:
	Method returned true
	Read string: firstsecond
Third call:
	Method returned false
	Read string: third
```

#### ReadUntilStrings
**Сигнатура**:
```c++
bool ReadUntilStrings(vector<string> const & strings, string & readString, bool doAppend = false)
```

**Описание**: метод считывает последовательность символов из входного потока, пока не встретит любую строку из параметра **strings**. Если параметр **doAppend** - **true**, то считанная последовательность допишется в параметр **readString**, иначе **readString** будет перезаписан. Если метод не достигнет любую строку из параметра **strings**, то метод вернёт ложь.

**Входные параметры**:
- **strings**: множество строк, при встрече с любой из них завершается процесс считывания последовательности символов входного потока.
- **readString**: строка, в которую будет помещена считанная последовательность символов.
- **doAppend**: если **true**, то метод допишет считанную последовательность в конец **readString**. По умолчанию - **false**.

**Возвращаемое значение**: **true**, если метод достиг любую строку из множества **strings**, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("first#!sec@ond@%third");
Input input(stringStream);
string readString;

cout << "First call: " << endl;
cout << "\tMethod returned " << (input.ReadUntilStrings({ "#!", "@%" }, readString) ? "true" : "false") << endl;
cout << "\tRead string: " << readString << endl;

input.SkipArgument<char>(); // Skip character '#'

cout << "Second call: " << endl;
cout << "\tMethod returned " << (input.ReadUntilStrings({ "#!", "@%" }, readString, true) ? "true" : "false") << endl;
cout << "\tRead string: " << readString << endl;

input.SkipArgument<char>(); // Skip character '@'

cout << "Third call: " << endl;
cout << "\tMethod returned " << (input.ReadUntilStrings({ "#!", "@%" }, readString, false) ? "true" : "false") << endl;
cout << "\tRead string: " << readString << endl;
```
Вывод:
```
First call: 
	Method returned true
	Read string: first
Second call: 
	Method returned true
	Read string: first!sec@ond
Third call: 
	Method returned false
	Read string: %third
```

#### ReadVector
**Сигнатура**:
```c++
template<
	typename TVectorElement,
	typename TReadElement = TVectorElement,
	typename Functor = std::function<bool(std::vector<TVectorElement> &, TReadElement &)>
>
bool ReadVector(
	std::vector<TVectorElement> & vector,
	bool readEndOfLine = false,
	Functor forEachReadElement = &EmplaceBackEachReadElement
)
```

**Описание**: метод считывает элементы из входного потока, преобразуя их в тип TVectorElement. Если параметр **readEndOfLine** - **true**, то метод ограничивается концом потока, иначе концом строки. Параметр **forEachReadElement** описывает поведение процесса считывания элементов. Если в результате работы метода хотя бы один элемент будет записан в **vector**, то метод вернёт **true**.

**Входные параметры**:
- **vector**: массив, в который будут помещены считанные элементы.
- **readEndOfLine**: если **true**, то метод не ограничится концом строки. По умолчанию - **false**.
- **forEachReadElement**: действие при каждом считанном элементе входного потока. Если функция возвращает **false**, то дальнейшее считывание прекращается. По умолчанию элемент вставляется в конец **vector**.

**Возвращаемое значение**: **true**, если метод успешно считал хотя бы один элемент из входного потока, в противном случае - **false**.

**Пример**: считывание массива строк:
```c++
stringstream stringStream("first second third");
Input input(stringStream);

vector<string> readStrings;

cout << "Method returned " << (input.ReadVector(readStrings) ? "true" : "false") << endl;
cout << "Read strings: ";
for (size_t i = 0; i < readStrings.size(); ++i)
{
	cout << readStrings[i];
	if (i != readStrings.size() - 1)
	{
		cout << ", ";
	}
}
cout << endl;
```
Вывод:
```
Method returned true
Read string: first, second, third
```

**Пример**: со вставкой элементов в начало массива:
```c++
stringstream stringStream("first second third");
Input input(stringStream);

vector<string> readStrings;
function<bool(vector<string> &, string &)> emplaceFrontReadElement = [](vector<string> & vect, string & element)
{
	vect.insert(vect.begin(), element);
	return true;
};

cout << "Method returned " << (input.ReadVector(readStrings, false, emplaceFrontReadElement) ? "true" : "false") << endl;
cout << "Read strings: ";
for (size_t i = 0; i < readStrings.size(); ++i)
{
	cout << readStrings[i];
	if (i != readStrings.size() - 1)
	{
		cout << ", ";
	}
}
cout << endl;
```
Вывод:
```
Method returned true
Read strings: third, second, first
```

**Пример**: с продолжением считывания при достижении символа конца строки:
```c++
stringstream stringStream("1 2 3\n4 5 6 seven");
Input input(stringStream);

vector<int> numbers;

bool readNumbersResult = input.ReadVector(numbers, true);

cout << "Method returned " << (readNumbersResult ? "true" : "false") << endl;
cout << "Read numbers: ";
for (size_t i = 0; i < numbers.size(); ++i)
{
	cout << numbers[i];
	if (i != numbers.size() - 1)
	{
		cout << ", ";
	}
}
cout << endl;
```
Вывод:
```
Method returned true
Read strings: 1, 2, 3, 4, 5, 6
```

#### ReadMatrix
**Сигнатура**:
```c++
template<
	typename TVectorElement,
	typename TReadElement = TVectorElement,
	typename ForEachElementFunctor = std::function<bool(std::vector<TVectorElement> &, TReadElement &)>,
	typename ForEachVectorFunctor = std::function<bool(std::vector<std::vector<TVectorElement>> &, std::vector<TReadElement> &)>
>
bool ReadMatrix(
	std::vector<std::vector<TVectorElement>> & matrix,
	bool readEndOfLine = false,
	ForEachElementFunctor forEachReadElement = &EmplaceBackEachReadElement<TVectorElement, TReadElement>,
	ForEachVectorFunctor forEachReadVector = &EmplaceBackEachReadElement<std::vector<TVectorElement>, std::vector<TReadElement>>
)
```

**Описание**: метод считывает элементы из входного потока, преобразуя их в тип TVectorElement и формируя некоторое количество **vector**, которые будут записаны в один **vector**, тем самым образуя матрицу. Если параметр **readEndOfLine** - **true**, то метод ограничивается концом потока, иначе концом строки. Параметр **forEachReadElement** описывает поведение процесса считывания элементов. Параметр **forEachReadVector** описывает поведение процесса считывания сформированного из элементов **vector** в матрицу. Если в результате работы метода хотя бы один **vector** будет записан в матрицу, то метод вернёт **true**.

**Входные параметры**:
- **matrix**: матрица, в которую будут помещены считанные элементы в составе некоторого количества **vector**.
- **readEndOfLine**: если **true**, то метод не ограничится концом строки. По умолчанию - **false**.
- **forEachReadElement**: действие при каждом считанном элементе входного потока. Если функция возвращает **false**, то дальнейшее формирование текущего **vector** прекращается. По умолчанию элемент вставляется в конец **vector**.
- **forEachReadVector**: действие при каждом сформированном **vector**. Если функция возвращает **false**, то дальнейшее считывание прекращается. По умолчанию **vector** вставляется в конец матрицы.

**Возвращаемое значение**: **true**, если метод успешно считал хотя бы один **vector** из входного потока, в противном случае - **false**.

**Пример**: считывание матрицы чисел:
```c++
stringstream stringStream("1 2 3\n4 5 6 seven");
Input input(stringStream);

vector<vector<int>> matrix;

bool readMatrixResult = input.ReadMatrix(matrix);

cout << "Method returned " << (readMatrixResult ? "true" : "false") << endl;
cout << "Read matrix: " << endl;
for (vector<int> const & row : matrix)
{
	copy(row.begin(), row.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}
```
Вывод:
```
Method returned true
Read matrix: 
1 2 3 
4 5 6 
```

**Пример**: со вставкой векторов в начало матрицы:
```c++
stringstream stringStream("1 2 3\n4 5 6 seven");
Input input(stringStream);

vector<vector<int>> matrix;

std::function<bool(std::vector<std::vector<int>> &, std::vector<int> &)> emplaceFrontReadElement = [](std::vector<std::vector<int>> & matrix, std::vector<int> & vector)
{
	if (vector.empty())
	{
		return false;
	}
	matrix.insert(matrix.begin(), vector);
	return true;
};

bool readMatrixResult = input.ReadMatrix(matrix, false, &Input::EmplaceBackElement<int>, emplaceFrontReadElement);

cout << "Method returned " << (readMatrixResult ? "true" : "false") << endl;
cout << "Read matrix: " << endl;
for (vector<int> const & row : matrix)
{
	copy(row.begin(), row.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}
```
Вывод:
```
Method returned true
Read matrix: 
4 5 6 
1 2 3 
```

#### Scan
**Сигнатура**:
```c++
bool Scan(
	std::vector<std::string> const & delimiters,
	StreamString & scannedStreamString,
	StreamString & delimiterStreamString
)
```

**Описание**: метод считывает последовательность символов до первого встречного элемента из **delimiters**. Считанная последовательность символов будет записана в параметр **scannedStreamString**, а разделитель, из-за которого считывание было прекращено, - в параметр **delimiterStreamString**. Если в результате работы метода будет найден один из переданных разделителей, то метод вернёт **true**.

**Входные параметры**:
- **delimiters**: разделители, которые стремится найти метод при считывании каждого очередного символа.
- **scannedStreamString**: считанная в результате работы метода последовательность символов. Если метод вернул **false**, то параметр останется неизменным.
- **delimiterStreamString**: разделитель, который был найден в результате работы метода. Если метод завершил свою работу по причине конца потока, то параметр примет значение инициализированного объекта класса **StreamString**. Если метод вернул **false**, то параметр останется неизменным.

**Возвращаемое значение**: **true**, если в результате работы метод нашёл один из переданных разделителей, в противном случае - **false**.

**Пример**:
```c++
stringstream stringStream("1 2;3 4,5##6\n7;8");
Input input(stringStream);

vector<string> delimiters {" ", ";", ",", "##"};

StreamString scannedStreamString;
StreamString delimiterStreamString;
while (input.Scan(delimiters, scannedStreamString, delimiterStreamString))
{
	cout << "Scanned string:" << endl;
	cout << "\t" << "String: " << "\"" << scannedStreamString.string << "\"" << endl;
	cout << "\t" << "Position:" << endl;
	cout << "\t\t" << "Line: " << scannedStreamString.position.GetLine() << endl;
	cout << "\t\t" << "Column: " << scannedStreamString.position.GetColumn() << endl;

	cout << "Delimiter:" << endl;
	cout << "\t" << "String: " << "\"" <<delimiterStreamString.string << "\"" << endl;
	cout << "\t" << "Position:" << endl;
	cout << "\t\t" << "Line: " << delimiterStreamString.position.GetLine() << endl;
	cout << "\t\t" << "Column: " << delimiterStreamString.position.GetColumn() << endl;
	cout << endl;
}
```
Вывод:
```
Scanned string:
	String: "1"
	Position:
		Line: 1
		Column: 1
Delimiter:
	String: " "
	Position:
		Line: 1
		Column: 2

Scanned string:
	String: "2"
	Position:
		Line: 1
		Column: 3
Delimiter:
	String: ";"
	Position:
		Line: 1
		Column: 4

Scanned string:
	String: "3"
	Position:
		Line: 1
		Column: 5
Delimiter:
	String: " "
	Position:
		Line: 1
		Column: 6

Scanned string:
	String: "4"
	Position:
		Line: 1
		Column: 7
Delimiter:
	String: ","
	Position:
		Line: 1
		Column: 8

Scanned string:
	String: "5"
	Position:
		Line: 1
		Column: 9
Delimiter:
	String: "##"
	Position:
		Line: 1
		Column: 10

Scanned string:
	String: "6
7"
	Position:
		Line: 1
		Column: 12
Delimiter:
	String: ";"
	Position:
		Line: 2
		Column: 2

Scanned string:
	String: "8"
	Position:
		Line: 2
		Column: 3
Delimiter:
	String: ""
	Position:
		Line: 1
		Column: 1
```
