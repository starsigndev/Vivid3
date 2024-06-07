module Vivid.Test

class Tester

    func Tester()
    
        debug("Tester");

    end

    func Test(string aa)

        debug(aa);

    end 

end 

class TestClass

    func other(string a)

        debug(a);

    end 

    func TestClass()
    
        string name = "Antony Wells";

        Tester tc = new Tester();

        tc.Test(name);

    end 

end 


