module Vivid.Test

class Other

    func Other()
    end

    func Test(int a)

        return a;

    end 

end 

class TestClass

    func TestClass()
    
        int ch = 20;

        Other tt = new Other();

        ch = ((tt.Test(25/2)*2)+100)*1000;



        debug(ch);


    end 

end 


