module Vivid.Test


class TestClass

    func other(lambda t)
   
        debug("other!");
   
        invoke t;

    end


    func TestClass()

       lambda test

            debug("It works");

       end 

        other(test);

    end 

end 


