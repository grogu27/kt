class Main {
  main(): Object {
    let x: Int <- 1, y: String <- "Hello" in {
      out_string(y);
      out_int(x + 2);
      -- Вложенный let должен быть обёрнут в отдельный блок
      let a: Int <- 1 + "Hello" in
        a;  -- нужно вернуть какое-то значение, даже если оно не используется
    }
  };
};


