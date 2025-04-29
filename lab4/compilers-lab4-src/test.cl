class Main {
    y: Int <- 4;

    string_test(): String {  
        "Hello, Cool!"  
    };

    test() : Object {
    let x : Int <- 3 in
      if x < 5 then
        while not x = 0 loop x <- x - 1 pool
      else
        x
      fi
  };
};

class A {};
class B inherits A {
    string_test(): String {  
        "Hello, World!"  
    };
};
class C inherits B {};