module Vivid.Test


class Other

    int age = 30;


    func Other()

        debug(255);

    end 
    
    func TestFunc(int b)

        debug(b+10);

    end 

end 

class TestClass


    Other ac;

    func TestClass()
    
        ac = new Other();

        ac.TestFunc(ac.age+255);


    end 

end 


