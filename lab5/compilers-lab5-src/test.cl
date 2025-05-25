class A {
  val: Int;
  val: Bool;              --  Ошибка: повторное объявление поля val
  getVal(): Int { val };
};

class A inherits IO {      --  Ошибка: класс A уже определён
  some(): Int { 0 };
};

class B inherits C {       --  Ошибка: класс C не существует
  x: Int;
};

class C inherits B {};     --  Цикл наследования: B → C → B

class Main2 {};            --  Ошибка: нет класса Main с методом main

class D {
  test(x: Int, x: String): Bool { true };  --  Ошибка: повторяющееся имя параметра x
};

class D {
  method(): Object {
    x + "Hello"            --  Ошибка типов: Int + String
  };
};

class F {
  method(): Object {
    y <- 5                 --  Ошибка: переменная y не объявлена
  };
};

class G {
  method(): Object {
    let z: Int <- 0, z: Bool <- true in z  --  Ошибка: переменная z объявлена повторно
  };
};
