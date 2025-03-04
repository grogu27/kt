-- comment

class Main inherits IO {  -- class  inherits

    x: Int <- 42;  

    -- if
    factorial(n: Int): Int {  
        if n = 0 then 1 else n * factorial(n - 1) fi  
    };

    --  while
    loop_test(): Object {
        let y: Int <- 5 in
        while y > 0 loop
            y <- y - 1
        pool
    };

    -- 
    test(): Object {  
        let obj: Main <- new Main in obj.factorial(5)  
    };

    -- string
    string_test(): String {  
        "Hello, Cool!"  
    };

    -- logic
    logic_test(): Bool {
        not (x > 10) and true or false
    };

    (* comment   (*   dual comment      *)
              Hello world       *) 
       
    main(): Object {  
        out_string("Testing Cool lexer\n")  
    };
    (* abc (* *) -- dsf
  -- comm 
    *)

    (*
    * Example app.
    *
    *)

    -- This is a class

    "String (* hello *)"

    "Str"

    "Multiline string \
    Hello"

    "Hello\n"
};
