class A{
  val: Int;
  val: Int;
   
  getVal(): Int { val };
};

class B inherits A {
  bval: String;
  getBval(): String { bval };
};

class Main {
  main(): Object {
    let x: Int <- 1, y: String <- "Hello" in {
      out_string(y);
      out_int(x + 2);
    }
  };
};
